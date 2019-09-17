#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <X11/Xlib.h>

#define BUFFSIZE 256
#define XPOSITIONFILE "/.xmousepos"

char *
gethomepath(char *dest, size_t size)
{
	/*
	 * copy home path into dest with maximum length size
	 * get home path from $HOME first, if that is fails
	 * use the user database
	 */
	char *home;
	home = getenv("HOME");
	if (home)
		strncpy(dest, home, size);
	if (home == NULL || dest == NULL) /* last ditch attempt */
	{
		uid_t uid;
		struct passwd *pw;
		uid = getuid();
		pw = getpwuid(uid);
		if (pw == NULL)
			return NULL;
		strncpy(dest, pw->pw_dir, size);
	}
	return dest;
}

int
main(int argc, char *argv[])
{
	char *path;
	Display *display;
	/* attempt to get path before anything */
	path = malloc(BUFFSIZE);
	gethomepath(path, BUFFSIZE);
	if (path == NULL)
	{
		goto freeandexit;
	}
	strncat(path, XPOSITIONFILE, BUFFSIZE);
	puts(path);

	/* open display */
	display = XOpenDisplay(NULL);
	if (display == NULL)
		fprintf(stderr, "cannot open x display\n");

	

freeandexit:
	XCloseDisplay(display);
	free(path);
	return 0;
}
