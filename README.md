# Vampyr: The Talisman of Invocation Utilities

vampyr-utils is a repo for utilities for decoding files from _Vampyr:
Talisman of Invocation_, the 1989 DOS game made by Victor Shao and Brian Weston.
For more information on the game, visit the unofficial wiki:
https://vampyr-talisman-of-invocation.fandom.com/wiki/Vampyr:_Talisman_of_Invocation_Wikia

The game can be downloaded here:
https://archive.org/details/msdos_VAMPYR20_shareware

It can be played using DOSBox:
http://www.dosbox.com/

## Requirements

For `cppsrc`:

* C++14 compiler
* CMake 3.10+

For `pascal`:

* Free Pascal

## Building

Using CMake:

	mkdir build
	cd build
	cmake ..
	make

## Utility Index

All images are .BMP with 24bit color (no alpha).

C++:

* `bmp2con` - Convert an image to .CON
* `con2bmp` - Convert .CON to an image with EGA palette
* `map2bmp` - Generate a map image from a .MAP file
* `map_layer_enconter` - Take a map image and layer NPCs on top
* `splitss` - Split a horizontally laid out sprite sheet into component images
* `stichss` - Turn a bunch of images into a single sprite sheet

Pascal:

* `ENCONTER` - Translate the provided `ENCONTER.SET` into CSV
* `sign` - Translate the provided `SIGN.DAT` into CSV
* `mondat` - Translate the provided `*MON.DAT` into CSV
* `VCHEAT` - Modify `PLAYER.SAV` to max out stats

## License

Uses `stb_image.h` and `stb_image_write.h`:  
Public Domain  
https://github.com/nothings/stb

Everything else: see [LICENSE](LICENSE)
