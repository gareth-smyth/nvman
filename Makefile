ifeq ($(OS),Linux)
	DELCOM = rm -f
else ifeq ($(OS),Windows_NT)
	DELCOM = del -f
else ifeq ($(OS),Darwin)
	DELCOM = rm -f
else
	DELCOM = DELETE FORCE
endif

nvman: src/nvman.c src/commands.c src/commands.h src/utils.c src/utils.h
	vc +aos68k src/nvman.c src/commands.c src/utils.c -o nvman

clean:
	$(DELCOM) nvman
