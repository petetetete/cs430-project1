all: ppmrw.c ppmrw.h
	gcc ppmrw.c -o ppmrw

clean:
	rm -rf ppmrw *~ *.o
