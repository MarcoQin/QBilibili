CFLAGS = -g

debug/decryptor:debug/decryptor.o debug/xxtea.o
	g++ -o $@ $^

debug/decryptor.o:src/decryptor.cpp
	g++ $(CFLAGS) -o $@ -c $<

debug/xxtea.o:src/xxtea.cpp src/xxtea.h
	g++ $(CFLAGS) -o $@ -c $<

clean :
	rm debug/decryptor debug/*.o
