all: hw0301.o func0301.c hw0302.o func0302.c 
	gcc func0301.c hw0301.o -o hw0301
	gcc func0302.c hw0302.o -o hw0302

hw0301: hw0301.c
	gcc -c hw0301.c -o hw0301.o 
	gcc -shared hw0301.o -o libhw0301.so

hw0302: hw0302.c
	gcc -c hw0302.c -o hw0302.o 
	gcc -shared hw0302.o -o libhw0302.so
