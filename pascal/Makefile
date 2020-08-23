.PHONY: all
all: ENCONTER sign mondat VCHEAT

ENCONTER: ENCONTER.PAS
	fpc ENCONTER.PAS

sign: sign.pas
	fpc sign.pas

mondat: mondat.pas
	fpc mondat.pas

VCHEAT: VCHEAT.pas
	fpc VCHEAT.pas

.PHONY: clean
clean:
	$(RM) ENCONTER sign mondat VCHEAT *.o
