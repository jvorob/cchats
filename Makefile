all: 
	gcc *.c *.h

run: all
	./a.out

clean:
	rm *.gch a.out
