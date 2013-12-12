Vampyr: The Talisman of Invocation Utilities
============================================

vampyr-utils are utilities made in Java for decoding files from _Vampyr:
Talisman of Invocation_, the 1989 DOS game made by Victor Shao and Brian Weston.

Courtesy of the Internet Archive, the game can be downloaded here:

```
https://archive.org/details/VampyrTheTalismanOfInvocation
```

Unless you have an MS-DOS computer, I'd suggest playing _Vampyr_ using DOSBox.
That can be downloaded from the DOSBox website:

```
http://www.dosbox.com/
```

Requirements
------------

  * Java Development Kit
  * Apache Ant

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

License
-------

vampyr-utils is licensed under the _Do What the Fuck You Want To_ public
license. A copy can be found in the `LICENSE` file in the base of the project
directory. You can also find a copy at the license website:

```
http://www.wtfpl.net
```

This license, suprisingly, allows you to just do what the fuck you want to with
the files in the project directory. I really don't care; have fun!

Future Plans
------------

  * Split the CLI from the libraries
  * GUI?
  * Split shared functionality into `Shared.java`
  * More error checking
  * Saving to something other than PNG

I Digress: Version Differences
------------------------------

There are two versions of _Vampyr_: 1.1 and 2.0. In 1.1 there is a bug which
prevents the player from finishing a story-line critical quest, thereby
preventing the completion of the game. Version 2.0 fixed that bug -- along with
several others listed in the README -- and changed some of the graphics.

So play version 2.0 if you want to beat the game.
