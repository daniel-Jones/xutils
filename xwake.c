/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>

/*
 * start - the time to start preventing the screen from sleeping
 * end - the time to stop preventing the screen from sleeping
 * must be in "xx:xx" format
 */
char *start 	= "08:00";
char *end 	= "00:00";

void
gettime(int *store)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	store[0] = tm->tm_hour;
	store[1] = tm->tm_min;
}

void
gettriggertimes(int *startarr, int *endarr)
{
	char smodify[6];
	char emodify[6];
	strncpy(smodify, start, 6);
	strncpy(emodify, end, 6);
	startarr[0] = atoi(strtok(smodify, ":"));
	startarr[1] = atoi(strtok(NULL, ":"));

	endarr[0] = atoi(strtok(emodify, ":"));
	endarr[1] = atoi(strtok(NULL, ":"));

}

int
main(int argc, char *argv[])
{
	int time[2];
	int startarr[2];
	int endarr[2];
	int setwontsleep = 0;
	gettriggertimes(startarr, endarr);
	Display *dsp = XOpenDisplay(NULL);
	if(!dsp)
	{
		fprintf(stderr, "cannot open X display\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		if (strcmp(argv[1], "reset") == 0)
		{
			puts("enabling screensaver and exiting");
			XScreenSaverSuspend(dsp, False);
			XFlush(dsp);
			XCloseDisplay(dsp);
			return 0;
		}
		else
		{
			printf("usage: %s [reset]\nreset: re-enable screensaver\n", argv[0]);
			return 0;
		}
	}
	while (1)
	{
		gettime(time);
		if (setwontsleep == 0 && (startarr[0] == time[0]) && (startarr[1] == time[1]))
		{
			XScreenSaverSuspend(dsp, True);
			XFlush(dsp);
			setwontsleep = 1;
		}
		else if (setwontsleep == 1 && endarr[0] == time[0] && endarr[1] == time[1])
		{
			XScreenSaverSuspend(dsp, False);
			XFlush(dsp);
			setwontsleep = 0;
		}
		sleep(5);
	}
	XCloseDisplay(dsp);
	return 0;
}
