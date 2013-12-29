#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct termios orig_stdin_termios;

void set_non_canonical_mode(int fd) {
    struct termios termios;

    tcgetattr(fd, &termios);

    /* turn off canonical mode */
    termios.c_lflag &= ~(ICANON);
    /* turn off echoing of typed characters */
    termios.c_lflag &= ~(ECHO);
    /* timeout is in tenths of a second; make read() timeout after
       ten seconds */
    termios.c_cc[VTIME] = 100;
    /* set the minimum number of bytes returned by read() to zero,
       this enables us to easily detect a timeout condition */
    termios.c_cc[VMIN] = 0;

    /* set the new attributes immediately */
    tcsetattr(fd, TCSANOW, &termios);
}

void restore_stdin_termios(void) {
    fprintf(stdout, "Restoring stdin termios settings.\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_stdin_termios);
}

int main() {
    uint8_t byte;

    /* we need to be able to restore the original termios settings when
       we exit(). Otherwise, the users terminal will have the settings
       that we set, the kernel does not clean this up for us */
    tcgetattr(STDIN_FILENO, &orig_stdin_termios);
    atexit(restore_stdin_termios);

    set_non_canonical_mode(STDIN_FILENO);

    while( read(STDIN_FILENO, &byte, sizeof(byte)) > 0 ) {
        fprintf(stdout, "rx: 0x%02x\n", byte);
    }

    fprintf(stdout, "Timeout reached. Exiting.\n");

    exit(0);
}
