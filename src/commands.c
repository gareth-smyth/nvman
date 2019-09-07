#include <stdio.h>
#include <proto/nonvolatile.h>

#include "utils.h"

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
    struct NVInfo *info;
    STRPTR appName;
    struct MinList *items;
    struct NVEntry *entry;

    info = GetNVInfo(TRUE);

    if (!info) {
        printf("Could not get info for non volatile storage\n");
        return (2);
    }

    printf("Max storage:%lu bytes\n", info->nvi_MaxStorage * 10);
    printf(" Free space:%lu bytes\n\n", info->nvi_FreeStorage * 10);
    FreeNVData(info);

    items = GetNVList(NULL, FALSE);

    if (IsListEmpty((struct List *) items)) {
        printf("Non volatile storage is empty\n");
        FreeNVData(items);
        return (3);
    }

    printf("Stored titles\n");
    printf("App name             Title                Size Locked\n");
    for (entry = (struct NVEntry *) items->mlh_Head;
         entry->nve_Node.mln_Succ != NULL;
         entry = (struct NVEntry *) entry->nve_Node.mln_Succ) {
        if (entry->nve_Protection & NVEF_APPNAME) {
            appName = entry->nve_Name;
        } else {
            printf("%-21s%-21s%-5lu", appName, entry->nve_Name, entry->nve_Size);
            printf("%-5s\n", entry->nve_Protection & NVEF_DELETE ? "Yes" : "No");
        }
    }

    FreeNVData(items);
    return(0);
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
