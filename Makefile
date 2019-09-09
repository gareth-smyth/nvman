
ifeq ($(OS),Windows_NT)
	DELCOM = del -f
else

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux) 
DELCOM = rm -f
else ifeq ($(UNAME_S),Darwin)
DELCOM = rm -f
else
	DELCOM = DELETE FORCE
endif
endif

VBCC?=/opt/vbcc/
NDK=$(VBCC)/NDK_3.9
NDK_INC=$(NDK)/Include/include_h
CFLAGS?= -I$(NDK_INC)/libraries/ -I$(NDK_INC) -I.

nvman: src/nvman.c src/commands.c src/commands.h src/utils.c src/utils.h
	vc +aos68k $(CFLAGS) src/nvman.c src/commands.c src/utils.c -o nvman -lauto -lamiga 

clean:
	$(DELCOM) nvman
