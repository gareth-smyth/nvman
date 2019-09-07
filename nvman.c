
#include <stdio.h>
#include <exec/types.h>
#include <exec/lists.h>
#include <proto/exec.h>
#include <proto/nonvolatile.h>

struct Library *NVBase;
struct NVInfo *info;
struct MinList *items;
struct MinNode *entry;

int main()
{
  /* UWORD err;
  char data[] = "0123456789"; */
  printf("NVRam Manager\n");

  NVBase = OpenLibrary("nonvolatile.library", 40L);
  if(!NVBase) {
    printf("Could not open nonvolatile.library\n");
  }

  info = GetNVInfo(FALSE);
  printf("Max: %lu\n", info->nvi_MaxStorage);
  printf("Free:%lu\n", info->nvi_FreeStorage);

  /* err = StoreNV("MyApp", "MyItem2", &data, 1, TRUE);
  printf("Store result:%u\n", err); */

  items = GetNVList(NULL, FALSE);

  for(entry = items->mlh_Head; entry->mln_Succ != NULL; entry = entry->mln_Succ) {
    printf("%s\n", ((struct NVEntry*)entry)->nve_Name);
    printf("%lu\n", ((struct NVEntry*)entry)->nve_Size);
    printf("%lu\n", ((struct NVEntry*)entry)->nve_Protection);
  }

  FreeNVData(items);

  CloseLibrary(NVBase);
}

