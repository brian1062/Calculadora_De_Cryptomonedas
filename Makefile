make:
	gcc -g c_price_getter.c -o c_price
	python3 crypto.py
clear:
	rm c_price

