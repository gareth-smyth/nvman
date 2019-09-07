#include <stdio.h>
#include <string.h>
#include <exec/types.h>
#include <proto/nonvolatile.h>

int get_protection(const char *appName, const char *titleName) {
    struct MinList *items;
    struct NVEntry *entry;
    int protection = -1;
    BOOL foundApp = FALSE;

    items = GetNVList(NULL, FALSE);

    if (IsListEmpty((struct List *) items)) {
        printf("Non volatile storage is empty\n");
        FreeNVData(items);
        return (-1);
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