all: puredata

tinyosc.o: puredata/lib/tinyosc.h
	gcc -Werror -O0 -g -c puredata/lib/tinyosc.c -o puredata/build/tinyosc.o 

puredata: puredata_setup tinyosc.o puredata/lib/tinyosc.h
	gcc -Wall -Wextra -Werror puredata/main.c puredata/build/tinyosc.o -o puredata/build/main

puredata_setup:
	# Check if puredata/lib exists
	if [ ! -d "puredata/lib" ]; then \
		git clone git@github.com:mhroth/tinyosc.git puredata/lib; \
	fi; \
	mkdir -p puredata/build
