Map2PNG Help
============

Map2PNG is a utility which turns a _Vampyr_ `.MAP` file into a `.PNG` file using
the provided tilesets.

Compilation
-----------

```
make
```

Built targets can be found under the `build` directory.

CLI Usage
---------

```
java -jar Map2PNG.jar input.map width height univ.png tileset.png output.png
```

where:

  * `input.map` is the _Vampyr_ map file
  * `width` is the width of the map
  * `height` is the height of the map
  * `univ.png` is the universal tileset; see the **Universal Tileset VS Map Tileset** section below
  * `tileset.png` is the map-specific tileset; see the **Universal Tileset VS Map Tileset** section below
  * `output.png` is the output PNG file

Library Usage
-------------

Section under construction.
  
Universal Tileset VS Map Tileset
--------------------------------

_Vampyr_ uses two tilesets to render its maps: `UNIV.CON`, which contains tiles
used in all maps such as grass, and `<MAPNAME>.CON`, which contains tiles
specific to the map.

The universal tileset must be, at minimum, 144x18 px, enough to hold eight 18x18
px tiles. You can generate the one used in the game with Con2PNG; see the
**Example** section.

The map-specific tileset must be, at minimum, 360x18px, enough to hold twenty
18x18 px tiles.

Example
-------

```
java -jar Con2PNG.jar UNIV.CON 270 18 game-palette.txt UNIV.CON.png
java -jar Con2PNG.jar AFTER.CON 380 18 game-palette.txt AFTER.CON.png
java -jar Map2PNG.jar AFTER.MAP 50 50 UNIV.CON.png AFTER.CON.png AFTER.MAP.png
```

First, in the above example, the universal tileset, `UNIV.CON.png`, is generated
from `UNIV.CON` with Con2PNG. Next, the map-specific tileset, `AFTER.CON.png`,
is generated from `AFTER.CON`, again using Con2PNG. Finally, these tilesets are
used to create a render of `AFTER.MAP`, a 50x50 tile map, which is saved to
`AFTER.MAP.png`.

`UNIV.CON`, `AFTER.CON`, and `AFTER.MAP` can be found in the _Vampyr_ game
directory and are included in the `example` directory. `game-palette.txt` is a
sample palette which can be found in the `palettes` directory.

This example can also be built with the following:

```
make example
```
