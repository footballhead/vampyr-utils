.PHONY: all
all: ENCONTER sign

ENCONTER: ENCONTER.PAS
	fpc ENCONTER.PAS

sign: sign.pas
	fpc sign.pas

.PHONY: clean
clean:
	$(RM) ENCONTER 