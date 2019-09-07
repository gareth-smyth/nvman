#include <stdio.h>
#include <string.h>
#include <exec/types.h>
#include <exec/lists.h>
#include <proto/exec.h>

#include "commands.h"

struct Library *NVBase;

int main(int argc, char **argv) {
    int err = 0;

    printf("NVRam Manager\n\n");

    NVBase = OpenLibrary("nonvolatile.library", 40L);
    if (!NVBase) {
        printf("Could not open nonvolatile.library\n");
        return (1);
    }

    if (argc < 2 || strcmp(argv[1], "?") == 0) {
        show_usage();
    } else if (strcmp(argv[1], "list") == 0 && argc == 2) {
        err = show_info();
    } else if (strcmp(argv[1], "delete") == 0 && argc == 4) {
        err = delete(argv[2], argv[3]);
    } else if (strcmp(argv[1], "lock") == 0 && argc == 4) {
        err = lock(argv[2], argv[3]);
    } else if (strcmp(argv[1], "unlock") == 0 && argc == 4) {
        err = unlock(argv[2], argv[3]);
    } else if (strcmp(argv[1], "create") == 0 && argc == 4) {
        err = create(argv[2], argv[3]);
    } else {
        printf("Unknown command or wrong options\n");
        show_usage();
    }

    CloseLibrary(NVBase);

    return err;
}
