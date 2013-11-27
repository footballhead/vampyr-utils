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

Con2PNG
-------

Con2PNG is a utility which turns a _Vampyr_ image file, generally ending in 
`.CON`, into an ordinary `.PNG` file.

See `Con2PNG.md` for more info.

Map2PNG
-------

Map2PNG is a utility which turns a _Vampyr_ `.MAP` file into a `.PNG` file using
the provided tilesets.

See `Map2PNG.md` for more info.

The Future
----------

  * Add a map reader which accepts .CON files
  * Split the CLI from the back-end libraries
  * GUI?
  * More error checking
  * Saving to something other than PNG

Side Note: Version Differences
------------------------------

There are two versions of _Vampyr_: 1.1 and 2.0. In 1.1 there is a bug which
prevents the player from finishing a story-line critical quest, thereby
preventing the completion of the game. Version 2.0 fixed that bug -- along with
several others listed in the README -- and changed some of the graphics.

So play version 2.0 if you want to beat the game.
