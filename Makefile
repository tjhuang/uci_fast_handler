all:
	gcc -o show show.c -Wall -luci

clean:
	rm -f show
