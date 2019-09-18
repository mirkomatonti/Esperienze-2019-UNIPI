CC = gcc
CFLAGS = -std=c99 -g -pedantic -Wall  -Wmissing-field-initializers -D_POSIX_C_SOURCE=200809L  -fsanitize=address -fno-omit-frame-pointer 
OPTFLAGS = -lm
.PHONY: clean 

all:	libinterpolazione main 


vandermonde:	src/vandermonde.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS) 

newton:		src/newton.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS) 

lagrange:		src/lagrange.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS) 				

chebyshev:	src/chebyshev.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS) 	

spline:		src/spline.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS)

points:		src/points.c 
				$(CC) $(CFLAGS) $^ -c -o $@.o $(OPTFLAGS) 
				


libinterpolazione:	vandermonde newton chebyshev lagrange spline points
		@echo "Compilo Libreria"
		ar rvs $@.a vandermonde.o newton.o chebyshev.o lagrange.o spline.o points.o
		
main:	src/main.c
		@echo "Compilo eseugibile"
		$(CC) $(CFLAGS) $< -o $@.out -L . -linterpolazione $(OPTFLAGS) 
		
clean:	
		@echo "Cleaning"
		-rm -f *.a
		-rm -f *.o
		-rm -f *.out
		-rm -f plot/*.png
		