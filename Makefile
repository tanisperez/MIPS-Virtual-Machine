all:
	$(MAKE) --directory=src/mas/
	$(MAKE) --directory=src/mips/
	@echo BUILD SUCCESSFULL!

clean:
	$(MAKE) clean --directory=src/mas/
	$(MAKE) clean --directory=src/mips/
	rm -f bin/mips
	rm -f bin/mas
	rm -f bin/*.bin