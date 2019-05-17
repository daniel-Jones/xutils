all: binstatus xwake xbell

binstatus: binstatus.c
	    cc -o binstatus binstatus.c -lX11
xwake: xwake.c
	    cc -o xwake xwake.c -lX11 -lXss
xbell: xbell.c
	    cc -o xbell xbell.c -lX11
clean:
	@rm -f binstatus xwake xbell
	@rm -f *.o
