#include "beeper.h"

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

#ifndef CLOCK_TICK_RATE
#define CLOCK_TICK_RATE 1193180
#endif


Beeper::Beeper() {
    _isBeeping = false;
    _currentFrequency = 0;

    /* try to snag the console */
    if((_consoleFd = open("/dev/console", O_WRONLY)) == -1) {
      fprintf(stderr, "Could not open /dev/console for writing.\n");
      printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
      perror("open");
      exit(1);
    }
}

void Beeper::startBeep(float frequency) {
    if(!_isBeeping || _currentFrequency != frequency) {

        if(_currentFrequency != frequency)
            stopBeep();

        _isBeeping = true;
        _currentFrequency = frequency;



        /* Beep */
        if(ioctl(_consoleFd, KIOCSOUND, (int)(CLOCK_TICK_RATE/frequency)) < 0) {
          printf("\a");  /* Output the only beep we can, in an effort to fall back on usefulness */
          perror("ioctl");
        }
    }
}


void Beeper::stopBeep() {
    ioctl(_consoleFd, KIOCSOUND, 0);                    /* stop beep  */
    _currentFrequency = 0;
    _isBeeping = false;
}
