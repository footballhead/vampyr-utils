# A very basic and inflexibe Makefile
# Since Map2PNG.java imports Con2PNG.java both should be built
# Note to self: makefiles NEED tabs

main:
	mkdir -p build
	cd src ; javac -d ../build blackforestprogramming/vampyrutils/Map2PNG.java
	cd build ; jar cfe Con2PNG.jar blackforestprogramming.vampyrutils.Con2PNG blackforestprogramming/vampyrutils/Con2PNG.class
	cd build ; jar cfe Map2PNG.jar blackforestprogramming.vampyrutils.Map2PNG blackforestprogramming/vampyrutils/Map2PNG.class blackforestprogramming/vampyrutils/Con2PNG.class

example: main
	mkdir -p example/output
	java -jar build/Con2PNG.jar example/UNIV.CON 270 18 palettes/game-palette.txt example/output/UNIV.CON.png
	java -jar build/Con2PNG.jar example/AFTER.CON 360 18 palettes/game-palette.txt example/output/AFTER.CON.png
	java -jar build/Map2PNG.jar example/AFTER.MAP 50 50 example/output/UNIV.CON.png example/output/AFTER.CON.png example/output/AFTER.MAP.png
	@echo The files have been saved to ./example/output/

clean:
	rm -f -r build
	rm -f -r example/output

.PHONY: clean main example
