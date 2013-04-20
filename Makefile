all:
	$(MAKE) --directory=src/mas/
	$(MAKE) --directory=src/mips/
	@echo BUILD SUCCESSFULL!

debug:
	$(MAKE) debug --directory=src/mas/
	$(MAKE) debug --directory=src/mips/
	@echo BUILD SUCCESSFULL! [DEBUG MODE]

programs:
	$(MAKE) --directory=examples/

clean:
	rm -f bin/mips
	rm -f bin/mas
	rm -f bin/*.bin
	rm -f bin/*.elf
	rm -f bin/a.out
	rm -f bin/*.exe
	$(MAKE) clean --directory=src/mas/
	$(MAKE) clean --directory=src/mips/
	$(MAKE) clean --directory=examples/

install:
	cp bin/mas /usr/bin/mas
	cp bin/mips /usr/bin/mips

uninstall:
	rm -f /usr/bin/mas
	rm -f /usr/bin/mips
