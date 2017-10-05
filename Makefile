all:
	gcc -c csvdblt.c
	ar rc libcsvdblt.a csvdblt.o
	rm *.o
test:
	gcc  test.c libcsvdblt.a -o test
debug:
	gcc -g test.c libcsvdblt.a -o test_debug
clean:
	rm test test_debug
