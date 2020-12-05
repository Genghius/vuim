all: vuim.c
	cc -lncurses -o vuim vuim.c
install:
	cc -lncurses -o vuim vuim.c
	cp vuim ~/.local/bin/
clean:
	rm -f vuim
