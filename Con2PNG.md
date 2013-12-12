Con2PNG Help
============

Con2PNG is a utility which turns _Vampyr_ image data, generally `.con` files,
into ordinary PNGs.

Compilation
-----------

```
ant
```

Built targets can be found under the `build` directory.

CLI Usage
---------

```
java -jar Con2PNG.jar input.con width height palette.txt output.png
```

where:

  * `input.con` is the _Vampyr_ image data
  * `width` is the width of the image
  * `height` is the height of the image
  * `palette.txt` is the palette file (see the Palette Definition File section)
  * `output.png` is the output PNG file

Library Usage
-------------

Section under construction.
  
Palette Definition File
-----------------------

_Vampyr_ images use only 16 colors, each one stored as `0x00` through `0x0F`.
Palette definition files present a way to translate these arbitrary numbers into
color onscreen.

Palette definition files are plain-text files which contain 16 colors, one on
each line. The color on line 1 will be used to color `0x00`, line 2 will be
used with `0x01`, and so on. A color is stored as follows:

```
R,G,B
```

where:

  * `R` is the red channel
  * `G` is the green channel
  * `B` is the blue channel
  
Each of `R`, `G`, and `B` is a number between 0 and 255.

Sample palette definition files can be found in the `palette` directory, in the
root of the project.

Example
-------

```
java -jar Con2PNG.jar ITEM.001 25 25 menu-palette.txt ITEM.001.png
```

The above example uses the palette definition from `menu-palette.txt` to turn
`ITEM.001`, a 25x25 px image used on one of the credits screens, into
`ITEM.001.png`.

`ITEM.001` can be found in the _Vampyr_ game directory.
