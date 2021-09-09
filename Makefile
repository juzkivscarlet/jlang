exec = run.jx
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *~
	-rm *.jx
	-rm *.o
	-rm src/*.o
	-rm *.out
	-rm *.swp
	
	clear

