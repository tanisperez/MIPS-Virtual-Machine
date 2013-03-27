all:
	$(MAKE) --directory=src/mas/
	$(MAKE) --directory=src/mips/
	@echo BUILD SUCCESSFULL!

debug:
	$(MAKE) debug --directory=src/mas/
	$(MAKE) debug --directory=src/mips/
	@echo BUILD SUCCESSFULL! [DEBUG MODE]

clean:
	rm -f bin/mips
	rm -f bin/mas
	rm -f bin/*.bin
	rm -f bin/*.elf
	$(MAKE) clean --directory=src/mas/
	$(MAKE) clean --directory=src/mips/