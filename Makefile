make: converter.o c_price_getter.o
	gcc -g -m32 c_price_getter.o converter.o -o main
	
c_price_getter.o: c_price_getter.c
	gcc -g -c -m32 c_price_getter.c 

converter.o: converter.asm
	nasm -f elf converter.asm -o converter.o

clean:
	rm main
	rm *.o

.PHONY: remove

remove :
	cd /tmp; \
	pwd; \
	rm fifo_crypto

