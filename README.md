SpinningCube3D
=============

Small OpenGL demo made in Qt. It renders 3D cube the rotation of
which user can control with arrow keys. Made using QOpenGLWindow class.

I made this project when trying to understand how OpenGL pipeline works.
If you're interested in seeing tutorial based on this, write me an e-mail
at qiubit.bugzilla@gmail.com

![screen](http://i.imgur.com/KJICZfj.png)

Requirements
------------

SpinningCube3D requires OpenGL 3.30+ with VSync support and Qt 5.4+

Installation
------------

The easiest way to compile SpinningCube3D would be to import SpinningCube3D.pro
into QtCreator. You can also build it using GNU Make using the following commands:

```bash
qmake -o SpinningCube3D.pro
make debug
```

This should create the executable in `debug` folder.

Controls
--------

`Arrow keys` - rotate cube

`Escape` - exit application
