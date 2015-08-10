all:
	gcc -o show show.c -Wall -luci
	gcc -o load_config load_config.c -Wall -luci

clean:
	rm -f show
