#include "QLuaLoader.h"
#include <string>
#include <algorithm>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "xxtea.h"
#define KEY "123456"
#define FILE_LEN 1024*1024*10


extern "C"
{
    int q_lua_loader(lua_State *L)
    {
        static const std::string BYTECODE_FILE_EXT    = ".luac";
        static const std::string NOT_BYTECODE_FILE_EXT = ".lua";

        int status = -1;

        std::string filename(luaL_checkstring(L, 1));
        std::cout << "load file: " << filename << std::endl;
        size_t pos = filename.rfind(BYTECODE_FILE_EXT);
        if (pos != std::string::npos)
        {
            filename = filename.substr(0, pos);
        }
        else
        {
            pos = filename.rfind(NOT_BYTECODE_FILE_EXT);
            if (pos == filename.length() - NOT_BYTECODE_FILE_EXT.length())
            {
                filename = filename.substr(0, pos);
            }
        }

        pos = filename.find_first_of(".");
        while (pos != std::string::npos)
        {
            filename.replace(pos, 1, "/");
            pos = filename.find_first_of(".");
        }

        // search file in package.path
        // Data chunk;
        unsigned char* fileData;
        unsigned long readsize = 0;
        std::string chunkName;
        // FileUtils* utils = FileUtils::getInstance();

        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path");
        std::string searchpath(lua_tostring(L, -1));
        lua_pop(L, 1);
        size_t begin = 0;
        size_t next = searchpath.find_first_of(";", 0);
        fileData = (unsigned char*)malloc(FILE_LEN);

        do
        {
            if (next == std::string::npos)
                next = searchpath.length();
            std::string prefix = searchpath.substr(begin, next);
            if (prefix[0] == '.' && prefix[1] == '/')
            {
                prefix = prefix.substr(2);
            }

            pos = prefix.find("?.lua");
            chunkName = prefix.substr(0, pos) + filename + BYTECODE_FILE_EXT;
            std::cout << chunkName << std::endl;

            FILE *fp;

            fp = fopen(chunkName.c_str(), "rb");

            if (!fp) {
                fclose(fp);
                chunkName = prefix.substr(0, pos) + filename + NOT_BYTECODE_FILE_EXT;
                fp = fopen(chunkName.c_str(), "rb");
            }

            if (!fp) {
                fclose(fp);
                begin = next + 1;
                next = searchpath.find_first_of(";", begin);
                continue;
            }
#if defined(_MSC_VER)
            auto descriptor = _fileno(fp);
#else
            auto descriptor = fileno(fp);
#endif
            struct stat statBuf;
            if (fstat(descriptor, &statBuf) == -1) {
                fclose(fp);
                begin = next + 1;
                next = searchpath.find_first_of(";", begin);
                continue;
            }

            size_t size = statBuf.st_size;
            std::cout << "filename: " << chunkName << std::endl;
            std::cout << "statBuf.st_size: " << size << std::endl;

            // if (fileData) {
                // free(fileData); // ???
            // }

            if (readsize > 0) {
                readsize = 0;
            }

            // fileData = (unsigned char*)malloc(size + 1);
            // fileData = (unsigned char*)malloc(FILE_LEN);


            // readsize = fread(fileData, 1, size + 100, fp);
            readsize = fread(fileData, 1, FILE_LEN, fp);
            fclose(fp);


            // if (utils->isFileExist(chunkName))
            // {
                // chunk = utils->getDataFromFile(chunkName);
                // break;
            // }
            // else
            // {
                // chunkName = prefix.substr(0, pos) + filename + NOT_BYTECODE_FILE_EXT;
                // if (utils->isFileExist(chunkName))
                // {
                    // chunk = utils->getDataFromFile(chunkName);
                    // break;
                // }
            // }

            begin = next + 1;
            next = searchpath.find_first_of(";", begin);
        } while ((int)begin < (int)searchpath.length());

        // if (readsize > 0 && fileData)
        if (readsize)
        {
            // LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            // stack->luaLoadBuffer(L, reinterpret_cast<const char*>(chunk.getBytes()),
                                 // static_cast<int>(chunk.getSize()), chunkName.c_str());
            unsigned int len = 0;
            // std::cout << "readsize: "<< readsize<< std::endl;
            // std::cout << "fileData 11: " << fileData[11] << std::endl;
            // printf("fileData 11: %uc\n", fileData[61]);
            // std::cout << fileData << std::endl;
            //
            //
            //
            std::cout << "<<<<<<<<<" << std::endl;
            std::cout << chunkName << std::endl;
            pos = chunkName.find_last_of(".");
            std::string fname = chunkName.replace(pos, pos + 4, ".el");
            // unsigned char* result = xxtea_decrypt(fileData, readsize, (unsigned char*)KEY, 32, &len);

            // std::cout << "decriypt size: "<< len << std::endl;
            // std::cout << result << std::endl;
            // std::cout << (char*)result << std::endl;
            //
            //
            // FILE *f1;
            // unsigned char* fileData = (unsigned char*)malloc(FILE_LEN);
            // f1 = fopen("/Users/marcoqin/marco/QBilibili/build/QBilibili.app/Contents/MacOS/../Resources/bi.lua", "rb");
            // unsigned long num = fread(fileData, 1, FILE_LEN, f1);
            // fclose(f1);
            unsigned int dataLen = 0;
            unsigned char* data = xxtea_encrypt(fileData, readsize, (unsigned char*)KEY, 32, &dataLen);

            // unsigned char* data = xxtea_decrypt(fileData, readsize, (unsigned char*)KEY, 32, &dataLen);

            // FILE *f = fopen("/Users/marcoqin/marco/QBilibili/src/lua/cocos2dx-lua-crypto/bi.lua", "web+");
            std::cout << fname << std::endl;
            FILE *f = fopen(fname.c_str(), "web+");
            fwrite(data, 1, dataLen, f);
            fclose(f);

            // status = luaL_loadbuffer(L, (char*)data, dataLen, chunkName.c_str());
            status = luaL_loadbuffer(L, (char*)fileData, readsize, chunkName.c_str());
            // std::cout << "luaL_loadbuffer status: " << status << std::endl;
            // free(result);
        }
        else
        {
            // CCLOG("can not get file data of %s", chunkName.c_str());
            std::cout << "can not get file data of" <<  chunkName.c_str() << std::endl;
            return status;
        }

        std::cout << status << std::endl;
        // return status;
        return 1;

    }
}
