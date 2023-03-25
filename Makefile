compiler = gcc

main: ustring.o
	$(compiler) -o ustr ustring.o
	./ustr
	rm ustr *.o
