make:
	gcc -g -m32 -c c_price_getter.c -o c_price_getter.o
	gcc -g -m32 c_price_getter.o converter.o -o main
clean:
	rm main
	rm *.o

