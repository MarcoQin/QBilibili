#include "QLuaLoader.h"
#include <string>
#include <algorithm>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "xxtea.h"
#define KEY "123456"


extern "C"
{
    int q_lua_loader(lua_State *L)
    {
        static const std::string BYTECODE_FILE_EXT    = ".luac";
        static const std::string NOT_BYTECODE_FILE_EXT = ".lua";

        std::string filename(luaL_checkstring(L, 1));

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

        unsigned char* fileData;
        size_t readsize = 0;
        std::string chunkName;

        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path");
        std::string searchpath(lua_tostring(L, -1));
        lua_pop(L, 1);
        size_t begin = 0;
        size_t next = searchpath.find_first_of(";", 0);

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

            if (readsize > 0) {
                readsize = 0;
            }

            fileData = (unsigned char*)malloc(size + 1);
            readsize = fread(fileData, 1, size, fp);
            fclose(fp);

            begin = next + 1;
            next = searchpath.find_first_of(";", begin);
        } while ((int)begin < (int)searchpath.length());

        if (readsize > 0)
        {
            size_t dataLen = 0;
            unsigned char* data = (unsigned char*)xxtea_decrypt(fileData, readsize, KEY, &dataLen);
            luaL_loadbuffer(L, (char*)data, dataLen, chunkName.c_str());
            free(data);
        }
        else
        {
            std::cout << "can not get file data of" <<  chunkName.c_str() << std::endl;
            return 0;
        }

        return 1;
    }
}
