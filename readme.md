## NVMAN

A cli based non-volatile memory manager for the Amiga built on top of nonvolatile.library.

### Requirements
* vbcc (should be fine with other compilers)
* AmigaOS NDK 3.9 (setup correctly for VBCC)

### Build 
Just run make

### Execution
* `nvman` - Show non nonvolatile storage info and list all the apps and titles 
* TODO `nvman delete <app_name> <title_name>` - Delete the title
* TODO `nvman create <app_name> <title_name> <size in bytes>` - Create a new save with dummy data
* TODO `nvman dump <output file>` - Dump the entire non volatile storage contents
* TODO `nvman restore <input file>` - Restore a previously dumped non volatile storage over the top of existing
