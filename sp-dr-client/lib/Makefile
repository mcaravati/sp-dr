CC=g++

all: webassembly java python

clean:
	rm -f *.o *.so *.js *.wasm

webassembly: spdr_client_websocket.cpp spdr_client_websocket.hpp spdr_client.h
	em++ spdr_client_websocket.cpp --bind -DUSE_EMSCRIPTEN -lwebsocket.js -o spdr.js
	mv spdr.{js,wasm} ../js

java: spdr_client.cpp spdr_client.h
	# Build library without support
	$(CC) -c -fPIC spdr_client.cpp -o spdr.o
	$(CC) -shared -o libspdr.so spdr.o

	# Copy libraries for Maven to use
	mkdir -p ../java/target/classes/spdr/client/linux-x86_64
	cp libspdr.so ../java/target/classes/spdr/client/linux-x86_64

python: spdr_client.cpp spdr_client.h
	# Build library with boost support
	$(CC) -c -fPIC spdr_client.cpp -o spdr.o -Iboost/ -I/usr/include/python3.11 -DUSE_PYTHON
	$(CC) -shared -Wl,-soname,libspdr.so -o libspdr.so spdr.o -lpython3.11 -lboost_python311 -Iboost -Lboost/stage/lib