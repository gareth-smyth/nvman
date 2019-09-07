ifeq ($(OS),Linux)
	DELCOM = rm -f
else ifeq ($(OS),Windows_NT)
	DELCOM = del -f
else ifeq ($(OS),Darwin)
	DELCOM = rm -f
else
	DELCOM = DELETE FORCE
endif

nvman: nvman.c
	vc +aos68k nvman.c -o nvman

clean:
	$(DELCOM) nvman
