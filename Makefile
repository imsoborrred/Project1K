all:
	gcc main.c assembler.c decoder.c loader.c alu.c mux.c d0d1.c -o k2processor

assemble:
	k2processor $(FILENAME)

simulate:
	k2processor $(FILENAME)

clean:
	del k2processor.exe *.o *.bin

help:
	@echo Available targets:
	@echo   make all
	@echo   make assemble FILENAME=fibonacci.asm
	@echo   make simulate FILENAME=fibonacci.bin
	@echo   make clean
	@echo   make help 