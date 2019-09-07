
#include <stdio.h>
#include <exec/types.h>
#include <exec/lists.h>
#include <proto/exec.h>
#include <proto/nonvolatile.h>

struct Library *NVBase;
struct NVInfo *info;
struct MinList *items;
struct NVEntry *entry;

int show_info();

int main() {
    int err;

    printf("NVRam Manager\n\n");

    NVBase = OpenLibrary("nonvolatile.library", 40L);
    if (!NVBase) {
        printf("Could not open nonvolatile.library\n");
        return(1);
    }

    err = show_info();

    CloseLibrary(NVBase);

    return err;
}

int show_info() {
    STRPTR appName;
    info = GetNVInfo(FALSE);
    if (!info) {
        printf("Could not get info for non volatile storage\n");
        return(2);
    }

    printf("Max Storage:  %lu bytes\n", info->nvi_MaxStorage * 10);
    printf("Free       :%lu bytes\n\n", info->nvi_FreeStorage * 10);

    items = GetNVList(NULL, FALSE);

    if(IsListEmpty((struct List*)items)) {
        printf("Non volatile storage is empty\n");
        return(3);
    }

    printf("Stored titles\n");
    printf("App name             Title                Size Locked\n");
    for (entry = (struct NVEntry *)items->mlh_Head;
         entry->nve_Node.mln_Succ != NULL;
         entry = (struct NVEntry *)entry->nve_Node.mln_Succ) {
        if(((entry->nve_Protection) & ((ULONG)NVEF_APPNAME))) {
            appName = entry->nve_Name;
        } else {
            printf("%-21s%-21s%-5lu", appName, entry->nve_Name, entry->nve_Size);
            printf("%-5s\n", ((entry->nve_Protection) & ((ULONG) NVEF_DELETE)) ? "Yes" : "No");
        }
    }

    FreeNVData(items);
}