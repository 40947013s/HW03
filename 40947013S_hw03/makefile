all: hw0301.o func0301.c hw0302.o func0302.c hw0303.o hw0304.o 
	gcc func0301.c hw0301.o -o hw0301
	gcc func0302.c hw0302.o -o hw0302
	gcc hw0303.o -o hw0303
	gcc hw0304.o -o hw0304

hw0301: hw0301.c
	gcc -c hw0301.c -o hw0301.o 
	gcc -shared hw0301.o -o libhw0301.so

hw0302: hw0302.c
	gcc -c hw0302.c -o hw0302.o 
	gcc -shared hw0302.o -o libhw0302.so

hw0303: hw0303.c
	gcc -c hw0303.c -o hw0303.o 
	gcc -shared hw0303.o -o libhw0303.so

hw0304: hw0304.c
	gcc -c hw0304.c -o hw0304.o 
	gcc -shared hw0304.o -o libhw0304.so