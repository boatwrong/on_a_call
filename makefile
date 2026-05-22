.PHONY: all build clean

all:
	make -C ./api $@
	make -C ./client $@

clean:
	make -C ./api $@
	make -C ./client $@
