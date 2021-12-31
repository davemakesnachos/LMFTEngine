LMFT Engine
===========

This is a simple 2d game engine built with SDL2.

Design goals are as follows:

* Easy to use.
* Prioritize use of C++11 features where possible.
* Allow as much of implementation as possible to be data driven.

Dependencies
------------

* SDL2 - https://www.libsdl.org/

* SDL_image - https://www.libsdl.org/projects/SDL_image/

* nholmann/json - https://github.com/nlohmann/json.git

* box2d - https://github.com/erincatto/box2d

Building
--------

### Prequisites

SDL2 and related dependencies can be installed using package manager without issue:

    $ sudo apt install libsdl2-dev libsdl2-image-dev

The ``box2d`` and ``nholmann/json`` packages should be built and installed based
on instructions on the project page.

### Building LMFT and Examples

Building is now based on CMake.

```
$ mkdir build/
$ cd build/
$ cmake ..
$ make
```
