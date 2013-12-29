#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

struct termios orig_stdin_termios;

#define check_print_flag(out, flags, flag) \
    if( (flags) & (flag) ) { \
        fprintf(out, "%s ", #flag); \
    }

void fprint_termios_iflag(FILE *out, tcflag_t flags) {
    fprintf(out, "iflag: ");

    check_print_flag(out, flags, IGNBRK);
    check_print_flag(out, flags, BRKINT);
    check_print_flag(out, flags, IGNPAR);
    check_print_flag(out, flags, PARMRK);
    check_print_flag(out, flags, INPCK);
    check_print_flag(out, flags, ISTRIP);
    check_print_flag(out, flags, INLCR);
    check_print_flag(out, flags, IGNCR);
    check_print_flag(out, flags, ICRNL);
    check_print_flag(out, flags, IUCLC);
    check_print_flag(out, flags, IXON);
    check_print_flag(out, flags, IXANY);
    check_print_flag(out, flags, IXOFF);
    check_print_flag(out, flags, IMAXBEL);
    check_print_flag(out, flags, IUTF8);

    fprintf(out, "\n");
}

void fprint_termios_oflag(FILE *out, tcflag_t flags) {
    fprintf(out, "oflag: ");

    check_print_flag(out, flags, OPOST);
    check_print_flag(out, flags, OLCUC);
    check_print_flag(out, flags, ONLCR);
    check_print_flag(out, flags, OCRNL);
    check_print_flag(out, flags, ONOCR);
    check_print_flag(out, flags, ONLRET);
    check_print_flag(out, flags, OFILL);
    check_print_flag(out, flags, OFDEL);

    /* taken from bits/termios.h */
#if defined __USE_MISC || defined __USE_XOPEN
    check_print_flag(out, flags, NLDLY);
    check_print_flag(out, flags, CRDLY);
    check_print_flag(out, flags, TABDLY);
    check_print_flag(out, flags, BSDLY);
    check_print_flag(out, flags, FFDLY);
#endif

    check_print_flag(out, flags, VTDLY);

#ifdef __USE_MISC
    check_print_flag(out, flags, XTABS);
#endif

    fprintf(out, "\n");
}

void fprint_termios_cflag(FILE *out, tcflag_t flags) {
    fprintf(out, "cflag: ");

#ifdef __USE_MISC
    check_print_flag(out, flags, CBAUD);
#endif

    check_print_flag(out, flags, B0);
    check_print_flag(out, flags, B50);
    check_print_flag(out, flags, B75);
    check_print_flag(out, flags, B110);
    check_print_flag(out, flags, B134);
    check_print_flag(out, flags, B150);
    check_print_flag(out, flags, B200);
    check_print_flag(out, flags, B300);
    check_print_flag(out, flags, B600);
    check_print_flag(out, flags, B1200);
    check_print_flag(out, flags, B1800);
    check_print_flag(out, flags, B2400);
    check_print_flag(out, flags, B4800);
    check_print_flag(out, flags, B9600);
    check_print_flag(out, flags, B19200);
    check_print_flag(out, flags, B38400);

#ifdef __USE_MISC
    check_print_flag(out, flags, EXTA);
    check_print_flag(out, flags, EXTB);
#endif

    check_print_flag(out, flags, CSIZE);
    check_print_flag(out, flags, CSTOPB);
    check_print_flag(out, flags, CREAD);
    check_print_flag(out, flags, PARENB);
    check_print_flag(out, flags, PARODD);
    check_print_flag(out, flags, HUPCL);
    check_print_flag(out, flags, CLOCAL);

#ifdef __USE_MISC
    check_print_flag(out, flags, CBAUDEX);
#endif

    check_print_flag(out, flags, B57600);
    check_print_flag(out, flags, B115200);
    check_print_flag(out, flags, B230400);
    check_print_flag(out, flags, B460800);
    check_print_flag(out, flags, B500000);
    check_print_flag(out, flags, B576000);
    check_print_flag(out, flags, B921600);
    check_print_flag(out, flags, B1000000);
    check_print_flag(out, flags, B1152000);
    check_print_flag(out, flags, B1500000);
    check_print_flag(out, flags, B2000000);
    check_print_flag(out, flags, B2500000);
    check_print_flag(out, flags, B3000000);
    check_print_flag(out, flags, B3500000);
    check_print_flag(out, flags, B4000000);

#ifdef __USE_MISC
    check_print_flag(out, flags, CIBAUD);
    check_print_flag(out, flags, CMSPAR);
    check_print_flag(out, flags, CRTSCTS);
#endif

    fprintf(out, "\n");
}

void fprint_termios_lflag(FILE *out, tcflag_t flags) {
    fprintf(out, "lfag: ");

    check_print_flag(out, flags, ISIG);
    check_print_flag(out, flags, ICANON);
#if defined __USE_MISC || __USE_XOPEN
    check_print_flag(out, flags, XCASE);
#endif
    check_print_flag(out, flags, ECHO);
    check_print_flag(out, flags, ECHOE);
    check_print_flag(out, flags, ECHOK);
    check_print_flag(out, flags, ECHONL);
    check_print_flag(out, flags, NOFLSH);
    check_print_flag(out, flags, TOSTOP);
#ifdef __USE_MISC
    check_print_flag(out, flags, ECHOCTL);
    check_print_flag(out, flags, ECHOPRT);
    check_print_flag(out, flags, ECHOKE);
    check_print_flag(out, flags, FLUSHO);
    check_print_flag(out, flags, PENDIN);
#endif
    check_print_flag(out, flags, IEXTEN);
    check_print_flag(out, flags, EXTPROC);

    fprintf(out, "\n");
}

#define print_cc(out, cc, idx) \
    fprintf((out), "%s: 0x%02x\n", #idx, (cc)[idx])

void fprint_termios_cc(FILE *out, cc_t *cc) {
    fprintf(out, "cc: \n");

    print_cc(out, cc, VINTR);
    print_cc(out, cc, VQUIT);
    print_cc(out, cc, VERASE);
    print_cc(out, cc, VKILL);
    print_cc(out, cc, VEOF);
    print_cc(out, cc, VTIME);
    print_cc(out, cc, VMIN);
    print_cc(out, cc, VSWTC);
    print_cc(out, cc, VSTART);
    print_cc(out, cc, VSTOP);
    print_cc(out, cc, VSUSP);
    print_cc(out, cc, VEOL);
    print_cc(out, cc, VREPRINT);
    print_cc(out, cc, VDISCARD);
    print_cc(out, cc, VWERASE);
    print_cc(out, cc, VLNEXT);
    print_cc(out, cc, VEOL2);
}

void fprint_termios(FILE *out, struct termios *termios) {
    fprint_termios_iflag(out, termios->c_iflag);
    fprint_termios_oflag(out, termios->c_oflag);
    fprint_termios_cflag(out, termios->c_cflag);
    fprint_termios_lflag(out, termios->c_lflag);
    fprint_termios_cc(out, termios->c_cc);
}

void print_termios(struct termios *termios) {
    fprint_termios(stdout, termios);
}

void set_non_canonical_mode(int fd) {
    struct termios termios;

    tcgetattr(fd, &termios);

    termios.c_lflag &= ~(ICANON);
    termios.c_lflag &= ~(ECHO);
    termios.c_cc[VTIME] = 100;
    termios.c_cc[VMIN] = 0;

    tcsetattr(fd, TCSANOW, &termios);
}

void restore_stdin_termios(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_stdin_termios);
}

int main() {
    struct termios termios;
    uint8_t byte;

    tcgetattr(STDIN_FILENO, &orig_stdin_termios);
    atexit(restore_stdin_termios);

    set_non_canonical_mode(STDIN_FILENO);

    while( read(STDIN_FILENO, &byte, sizeof(byte)) > 0 ) {
        fprintf(stdout, "rx: 0x%02x\n", byte);
    }

    fprintf(stdout, "Timeout reached. Exiting.\n");

    exit(0);
}
