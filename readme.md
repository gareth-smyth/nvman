## NVMAN

A cli based non-volatile memory manager for the Amiga built on top of nonvolatile.library.

### Requirements
* vbcc (should be fine with other compilers)
* AmigaOS NDK 3.9 (setup correctly for VBCC)

### Build 
Just run `make` (tested on win32) or directly `vc -c99 src/nvman.c src/commands.c src/utils.c -o nvman` (tested on winuae)

### Execution
> \<param> is a required parameter.  
> \[param] is an optional paramter.  
> Parameter order is significant.  
* `nvman list` - Show non nonvolatile storage info and list all the apps and titles 
* `nvman delete <app_name> <title_name> [-f]` - Delete the title, if unlocked.  \[-f] will unlock a locked title before deletion.
* `nvman unlock <app_name> <title_name>` - Unlock the title
* `nvman lock <app_name> <title_name>` - Lock the title
* `nvman create <app_name> <title_name> [-f]` - Create a new save with 10 bytes of dummy data. This will overwrite any unlocked title with the same app name and title. \[-f] will force overwrite of existing locked title.
* `nvman deleteall [-f]` - Delete all unlocked titles in nvram. \[-f] will force deletion of all titles by unlocking them if locked. 
* TODO `nvman dump <output file>` - Dump the entire non volatile storage contents
* TODO `nvman restore <input file>` - Restore a previously dumped non volatile storage over the top of existing

### TODO
* All the above commands
* Clean up code possibly adding tests
* Dump/restore individual app/title
* Interactive mode
