all: hw0302.o func0302.c 
	gcc func0302.c hw0302.o -o hw0302

hw0302: hw0302.c
	gcc -c hw0302.c -o hw0302.o 
	gcc -shared hw0302.o -o libhw0302.so
