#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

struct redirect {
    const char *filename_from;
    int len;
    const char *filename_to;
};

struct redirect redirects[] = {
    { "/proc/board_id", 14, "/fake/proc/board_id" },
    { "/proc/usid", 10, "/fake/proc/usid" },
    { "/proc/mac_addr", 14, "/fake/proc/mac_addr" },
    { "/proc/mac_sec", 13, "/fake/proc/mac_sec" },
    { "/proc/bootmode", 14, "/fake/proc/bootmode" },
    { "/proc/postmode", 14, "/fake/proc/postmode" },
};

const char *do_redirect(const char *fn) {
    int i;
    for (i = 0; i < sizeof(redirects) / sizeof(struct redirect); i++) {
        if (strncmp(fn, redirects[i].filename_from, redirects[i].len) == 0) {
            fprintf(stderr, "fakeproc: redirect %s -> %s\n", fn, redirects[i].filename_to);
            return redirects[i].filename_to;
        }
    }
    return fn;
}

int open(const char *fn, int flags) {
    static int (*real_open)(const char *fn, int flags);
    const char *redir_fn = do_redirect(fn);

    if (!real_open) {
         real_open = dlsym(RTLD_NEXT, "open");
    }

    return real_open(redir_fn, flags);
}

FILE *fopen(const char *fn, const char *mode) {
    static FILE *(*real_fopen)(const char *fn, const char *mode);
    const char *redir_fn = do_redirect(fn);

    if (!real_fopen) {
        real_fopen = dlsym(RTLD_NEXT, "fopen");
    }

    return real_fopen(redir_fn, mode);
}
