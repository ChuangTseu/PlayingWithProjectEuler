# PlayingWithProjectEuler
Solving problems from [Project Euler](https://projecteuler.net/), playing with modern C++ and other languages (Racket, Python, etc.).

# Building
*Brace yourself !*

No decent build system is used right now, that's why the Visual Studio 2015 project files are included as is.

It is then needed to manually setup the various include and library paths in the project build options. (Or just use *vcpkg*!)

# Dependencies

#### FMT : *for a type generic print with a cool Python like syntax*

[FMT Website](http://fmtlib.net/latest/index.html) 
[FMT Github](https://github.com/fmtlib/fmt) 

#### MPIR : *for big numbers operations. Note that this library wraps [GMP](https://gmplib.org) and makes it usable with Visual Studio*

[MPIR Website](http://mpir.org) 
[MPIR Github](https://github.com/wbhart/mpir) 
