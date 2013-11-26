Vampyr: The Talisman of Invocation Utilities
============================================

These are utilities, made in Java, for decoding files from _Vampyr: Talisman of
Invocation_, the 1989 DOS game by Victor Shao and Brian Weston.

Courtesy of the Internet Archive, the game can be downloaded here:

```
https://archive.org/details/VampyrTheTalismanOfInvocation
```

For the best experience, play using DOSBox, which is available at the DOSBox
website:

```
http://www.dosbox.com/
```

Requirements
------------

A functioning version of Java is required. I'm not sure which version is the
minimum.

Usage
-----

First, compile (see below). Then run:

```
java blackforestprogramming.vampyrutils.Con2PNG input.con width height palette.txt output.png
```

where:

  * `input.con` is the raw image data
  * `width` is the width of the image
  * `height` is the height of the image
  * `palette.txt` is the palette file (see appropriate section)
  * `output.png` is the output PNG file; it only does PNG so far

Compilation
-----------

In the project root run:

```
javac blackforestprogramming/vampyrutils/Con2PNG.java
```

Palette File
-----------

Images in _Vampyr_ only use 16 colors, stored as binary in the image file from
`0x00` to `0x0F`. Therefore, the palette file contains 16 colors, one on each
line; the first line is the color for `0x00`, the second line is the color for
`0x01`, and so forth.

Each line is formated like the following:

```
X,Y,Z
```

where `X` is red, `Y` is green, and `Z` is blue. Each of `X`, `Y`, and `Z` must
be a number between 0 and 255, as color channels usually are.

A sample palette file, `menu-palette.txt`, has been provided. It can be used to
decode images used on the main menu, such as `ITEM.00[1-7]` or `SCROLL.PIC`.

The Future
----------

  * Add a map reader which accepts .CON files
  * Split the CLI from the back-end libraries
  * GUI?
  * More error checking

Side Note: Version Differences
------------------------------

There are two versions of Vampyr: 1.1 and 2.0. In 1.1 there is a bug which
prevents the player from finishing a story-line critical quest, thereby
preventing the completion of the game. Version 2.0 fixed that bug -- along with
several others listed in the README -- and changed some of the graphics.

So play version 2.0 if you want to beat the game.
