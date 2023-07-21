CC=g++

all: webassembly

clean:
	rm -f *.o *.so *.js *.wasm

libspdr.so: spdr.o
	$(CC) -shared -o libspdr.so spdr.o

spdr.o: spdr_client.cpp spdr_client.h
	$(CC) -c -fPIC spdr_client.cpp -o spdr.o

webassembly: spdr_client.cpp spdr_client.h
	em++ spdr_client.cpp --bind -DUSE_EMSCRIPTEN -o spdr.js

java: libspdr.so
	mkdir -p ../java/target/classes/spdr/client/linux-x86_64
	cp libspdr.so ../java/target/classes/spdr/client/linux-x86_64