.PHONY: all
all: ENCONTER sign mondat

ENCONTER: ENCONTER.PAS
	fpc ENCONTER.PAS

sign: sign.pas
	fpc sign.pas

mondat: mondat.pas
	fpc mondat.pas

.PHONY: clean
clean:
	$(RM) ENCONTER sign mondat