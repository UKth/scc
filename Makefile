all: scc

scc: main.c
	g++ -o scc main.c

clean:
	rm -f SCC *.o
