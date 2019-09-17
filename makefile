all: binstatus xwake xbell xmousepos

binstatus: binstatus.c
	    cc -o binstatus binstatus.c -lX11
xwake: xwake.c
	    cc -o xwake xwake.c -lX11 -lXss
xbell: xbell.c
	    cc -g -Wall -std=c89 -pedantic -o xbell xbell.c -lX11
xmousepos: xmousepos.c
	    cc -g -Wall -std=c89 -pedantic -o xmousepos xmousepos.c -lX11
clean:
	@rm -f binstatus xwake xbell xmousepos
	@rm -f *.o
