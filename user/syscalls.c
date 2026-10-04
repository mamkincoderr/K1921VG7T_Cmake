/* Минимальный слой системных вызовов newlib: stdout/stderr -> UART0, куча из символов
 * компоновщика.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include "console.h"

int _write(int fd, const char *buf, int len)
{
    (void)fd;
    for (int i = 0; i < len; i++) {
        if (buf[i] == '\n') {
            console_putc('\r');
        }
        console_putc(buf[i]);
    }
    return len;
}

int _read(int fd, char *buf, int len)
{
    (void)fd;
    int n = 0;
    while (n < len) {
        int c = console_getc_nonblock();
        if (c < 0) {
            break;
        }
        buf[n++] = (char)c;
    }
    return n;
}

void *_sbrk(ptrdiff_t incr)
{
    extern char _heap_start[], _heap_end[];
    static char *brk = 0;
    if (brk == 0) {
        brk = _heap_start;
    }
    if (brk + incr > _heap_end) {
        errno = ENOMEM;
        return (void *)-1;
    }
    char *prev = brk;
    brk += incr;
    return prev;
}

int _close(int fd)                    { (void)fd; return -1; }
int _fstat(int fd, struct stat *st)   { (void)fd; st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd)                   { (void)fd; return 1; }
off_t _lseek(int fd, off_t o, int w)  { (void)fd; (void)o; (void)w; return 0; }
int _getpid(void)                     { return 1; }
int _kill(int pid, int sig)           { (void)pid; (void)sig; errno = EINVAL; return -1; }
void _exit(int status)                { (void)status; for (;;) { } }
