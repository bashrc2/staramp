
all:
	gcc -Wall -std=c99 -pedantic -O3 -o staramp -Isrc src/*.c -lm -fopenmp

debug:
	gcc -Wall -std=c99 -pedantic -g -o staramp -Isrc src/*.c -lm -fopenmp

clean:
	rm -f src/*.plist staramp *.png
