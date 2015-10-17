#ifndef BEEP_H
#define BEEP_H

/*  beep - just what it sounds like, makes the console beep - but with
 * precision control.  See the man page for details.
 *
 * Try beep -h for command line args
 *
 * This code is copyright (C) Johnathan Nightingale, 2000.
 *
 * This code may distributed only under the terms of the GNU Public License
 * which can be found at http://www.gnu.org/copyleft or in the file COPYING
 * supplied with this code.
 *
 * This code is not distributed with warranties of any kind, including implied
 * warranties of merchantability or fitness for a particular use or ability to
 * breed pandas in captivity, it just can't be done.
 *
 * Bug me, I like it:  http://johnath.com/  or johnath@johnath.com
 */

#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>

/* I don't know where this number comes from, I admit that freely.  A
   wonderful human named Raine M. Ekman used it in a program that played
   a tune at the console, and apparently, it's how the kernel likes its
   sound requests to be phrased.  If you see Raine, thank him for me.

   June 28, email from Peter Tirsek (peter at tirsek dot com):

   This number represents the fixed frequency of the original PC XT's
   timer chip (the 8254 AFAIR), which is approximately 1.193 MHz. This
   number is divided with the desired frequency to obtain a counter value,
   that is subsequently fed into the timer chip, tied to the PC speaker.
   The chip decreases this counter at every tick (1.193 MHz) and when it
   reaches zero, it toggles the state of the speaker (on/off, or in/out),
   resets the counter to the original value, and starts over. The end
   result of this is a tone at approximately the desired frequency. :)
*/
#ifndef CLOCK_TICK_RATE
#define CLOCK_TICK_RATE 1193180
#endif

#define VERSION_STRING "beep-1.2.2"
char *copyright =
"Copyright (C) Johnathan Nightingale, 2002.  "
"Use and Distribution subject to GPL.  "
"For information: http://www.gnu.org/copyleft/.";

/* Meaningful Defaults */
#define DEFAULT_FREQ       880/* Middle A */
#define DEFAULT_LENGTH     200   /* milliseconds */
#define DEFAULT_REPS       1
#define DEFAULT_DELAY      100   /* milliseconds */
#define DEFAULT_END_DELAY  NO_END_DELAY
#define DEFAULT_STDIN_BEEP NO_STDIN_BEEP

/* Other Constants */
#define NO_END_DELAY    0
#define YES_END_DELAY   1

#define NO_STDIN_BEEP   0
#define LINE_STDIN_BEEP 1
#define CHAR_STDIN_BEEP 2

typedef struct beep_parms_t {
  float freq;     /* tone frequency (Hz)      */
  int length;     /* tone length    (ms)      */
  int reps;       /* # of repetitions         */
  int delay;      /* delay between reps  (ms) */
  int end_delay;  /* do we delay after last rep? */
  int stdin_beep; /* are we using stdin triggers?  We have three options:
                     - just beep and terminate (default)
                     - beep after a line of input
                     - beep after a character of input
                     In the latter two cases, pass the text back out again,
                     so that beep can be tucked appropriately into a text-
                     processing pipe.
                  */
  struct beep_parms_t *next;  /* in case -n/--new is used. */
} beep_parms_t;

/* Momma taught me never to use globals, but we need something the signal
   handlers can get at.*/
int console_fd = -1;

/* If we get interrupted, it would be nice to not leave the speaker beeping in
   perpetuity. */
void handle_signal(int signum) {
  switch(signum) {
  case SIGINT:
    if(console_fd >= 0) {
      /* Kill the sound, quit gracefully */
      ioctl(console_fd, KIOCSOUND, 0);
      close(console_fd);
      exit(signum);
    } else {
      /* Just quit gracefully */
      exit(signum);
    }
  }
}

/* print usage and exit */
void usage_bail(const char *executable_name) {
  printf("Usage:\n%s [-f freq] [-l length] [-r reps] [-d delay] "
         "[-D delay] [-s] [-c]\n",
         executable_name);
  printf("%s [Options...] [-n] [--new] [Options...] ... \n", executable_name);
  printf("%s [-h] [--help]\n", executable_name);
  printf("%s [-v] [-V] [--version]\n", executable_name);
  exit(1);
}



void play_beep(beep_parms_t parms) {
  int i; /* loop counter */

  /* try to snag the console */
  if((console_fd = open("/dev/console", O_WRONLY)) == -1) {
    fprintf(stderr, "Could not open /dev/console for writing.\n");
    printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
    perror("open");
    exit(1);
  }

  /* Beep */
  for (i = 0; i < parms.reps; i++) {                    /* start beep */
    if(ioctl(console_fd, KIOCSOUND, (int)(CLOCK_TICK_RATE/parms.freq)) < 0) {
      printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
      perror("ioctl");
    }
    /* Look ma, I'm not ansi C compatible! */
    usleep(1000*parms.length);                          /* wait...    */
    ioctl(console_fd, KIOCSOUND, 0);                    /* stop beep  */
    if(parms.end_delay || (i+1 < parms.reps))
       usleep(1000*parms.delay);                        /* wait...    */
  }                                                     /* repeat.    */

  close(console_fd);
}

int currentFreq = 0;
void startBeep(float freq) {
    if(freq == currentFreq) return;
    currentFreq = freq;

    /* try to snag the console */
    if((console_fd = open("/dev/console", O_WRONLY)) == -1) {
      fprintf(stderr, "Could not open /dev/console for writing.\n");
      printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
      perror("open");
      exit(1);
    }

    /* Beep */
      if(ioctl(console_fd, KIOCSOUND, (int)(CLOCK_TICK_RATE/freq)) < 0) {
        printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
        perror("ioctl");
      }
}


void stopBeep() {
    ioctl(console_fd, KIOCSOUND, 0);                    /* stop beep  */
    currentFreq = 0;
}


#endif // BEEP_H

