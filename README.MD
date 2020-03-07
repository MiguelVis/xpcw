XPCW
====

(c) Miguel García / FloppySoftware

www.floppysoftware.es

XPCW is a graphics and keyboard library for the Amstrad PCW, under the CP/M operating system.

![XPCW image](http://www.floppysoftware.es/images/pcw-xpcw.png "XPCW image")

It consists of a CP/M Plus RSX file, with some library files (`.h`) for MESCC, my own version of the Small-C compiler.

The RSX is written in Z80 assembler source code.

It can be accessed by any CP/M program or language, provided it follows its conventions (read the RSX source code for more information).

The `XPCW.RSX` file, has to be attached to any program that uses this library.

Only one MESCC library is needed (`xpcw.h`), the other are optional.

The libraries are:
- `xpcw.h` - Main library.
- `xdraw.h` - Functions to draw pixels, lines, etc.
- `xtext.h` - Functions to write text, set the font, change attributes, etc.
- `xchrdef.h` - Functions to get / set character definitions.
- `xbitmap.h` - Functions to draw bitmaps.
- `xkeyb.h` - Functions to access the keyboard.

See the libraries source code, for more information about the available functions.

As an example, you can see the `XDEMO` program.

One of my games for the Amstrad PCW, ***Squarex***, uses XPCW,
and ***Samaruc***, my GUI project for the Amstrad PCW, has been ported to XPCW with success.

You will find two additional tools:
- `BMPTOPCW` - To convert BMP images to XPCW format.
- `PCWFONT` - To manage PCW characters fonts.

License
-------

This program is freeware, and it's licensed under the GNU GPL license.
