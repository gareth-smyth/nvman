
#include <stdio.h>
#include <string.h>
#include <exec/types.h>
#include <exec/lists.h>
#include <proto/exec.h>
#include <proto/nonvolatile.h>

struct Library *NVBase;
struct NVInfo *info;
struct MinList *items;
struct NVEntry *entry;

int show_info();

void show_usage();

int delete(const char *appName, const char *titleName);

int get_protection(const char *appName, const char *titleName);

int lock(const char *appName, const char *titleName);

int unlock(const char *appName, const char *titleName);

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
    } else {
        printf("Unknown command or wrong options\n");
        show_usage();
    }

    CloseLibrary(NVBase);

    return err;
}

int delete(const char *appName, const char *titleName) {
    int err;
    int protection = get_protection(appName, titleName);

    printf("Deleting %s %s\n", appName, titleName);

    if (protection == -1) {
        printf("Could not find app '%s' title '%s'\n", appName, titleName);
        return (4);
    } else if (protection & NVEF_DELETE) {
        printf("App '%s' title '%s' is locked\n", appName, titleName);
        return (5);
    }

    err = DeleteNV(appName, titleName, TRUE);

    if (!err) {
        printf("Could not delete app %s title %s with error %d\n", appName, titleName, err);
    } else {
        printf("Success\n");
    }

    return err;
}

void show_usage() {
    printf("Usage\n");
    printf("nvman list - Show non nonvolatile storage info and list all the apps and titles\n");
    printf("nvman delete <app_name> <title_name> - Delete the title\n");
    printf("nvman lock <app_name> <title_name> - Lock the title\n");
    printf("nvman unlock <app_name> <title_name> - Unlock the title\n");
}

int show_info() {
    STRPTR appName;
    info = GetNVInfo(TRUE);
    if (!info) {
        printf("Could not get info for non volatile storage\n");
        return (2);
    }

    printf("Max storage:%lu bytes\n", info->nvi_MaxStorage * 10);
    printf(" Free space:%lu bytes\n\n", info->nvi_FreeStorage * 10);

    items = GetNVList(NULL, FALSE);

    if (IsListEmpty((struct List *) items)) {
        printf("Non volatile storage is empty\n");
        return (3);
    }

    printf("Stored titles\n");
    printf("App name             Title                Size Locked\n");
    for (entry = (struct NVEntry *) items->mlh_Head;
         entry->nve_Node.mln_Succ != NULL;
         entry = (struct NVEntry *) entry->nve_Node.mln_Succ) {
        if (((entry->nve_Protection) & ((ULONG) NVEF_APPNAME))) {
            appName = entry->nve_Name;
        } else {
            printf("%-21s%-21s%-5lu", appName, entry->nve_Name, entry->nve_Size);
            printf("%-5s\n", ((entry->nve_Protection) & ((ULONG) NVEF_DELETE)) ? "Yes" : "No");
        }
    }

    FreeNVData(items);
}

int lock(const char *appName, const char *titleName) {
    int err;
    int protection = get_protection(appName, titleName);

    printf("Locking %s %s\n", appName, titleName);

    if (protection == -1) {
        printf("Could not find app '%s' title '%s'\n", appName, titleName);
        return (6);
    } else if (protection & NVEF_DELETE) {
        printf("App '%s' title '%s' is already locked\n", appName, titleName);
        return (0);
    }

    err = SetNVProtection(appName, titleName, NVEF_DELETE, TRUE);

    if (!err) {
        printf("Could not lock app %s title %s with error %d\n", appName, titleName, err);
    } else {
        printf("Success\n");
    }

    return err;
}

int unlock(const char *appName, const char *titleName) {
    int err;
    int protection = get_protection(appName, titleName);

    printf("Unlocking %s %s\n", appName, titleName);

    if (protection == -1) {
        printf("Could not find app '%s' title '%s'\n", appName, titleName);
        return (7);
    } else if (!(protection & NVEF_DELETE)) {
        printf("App '%s' title '%s' is already unlocked\n", appName, titleName);
        return (0);
    }

    err = SetNVProtection(appName, titleName, 0, TRUE);

    if (!err) {
        printf("Could not unlock app %s title %s with error %d\n", appName, titleName, err);
    } else {
        printf("Success\n");
    }

    return err;
}

int get_protection(const char *appName, const char *titleName) {
    int protection = -1;
    BOOL foundApp = FALSE;

    items = GetNVList(NULL, FALSE);

    if (IsListEmpty((struct List *) items)) {
        printf("Non volatile storage is empty\n");
        return (3);
    }

    for (entry = (struct NVEntry *) items->mlh_Head;
         entry->nve_Node.mln_Succ != NULL;
         entry = (struct NVEntry *) entry->nve_Node.mln_Succ) {
        if (((entry->nve_Protection) & ((ULONG) NVEF_APPNAME))) {
            if (strcmp(appName, entry->nve_Name) == 0) {
                foundApp = TRUE;
            } else {
                foundApp = FALSE;
            }
        } else {
            if (foundApp && (strcmp(titleName, entry->nve_Name) == 0)) {
                protection = entry->nve_Protection;
            }
        }
    }

    FreeNVData(items);

    return protection;
}