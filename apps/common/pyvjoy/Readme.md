## What is this?

A Python wrapper for the C++ API defined in `vjoyinterface.h`. C++ feeder applications
typically include that header file, linking with the corresponding `.lib` file, and
dynamically load the correspoding `.dll` file at run time. Python developers can wrap
the `.dll` file using the Python `ctypes`, but instead it is recommended to build and use
this Python library:

1.  It is easier to use
2.  and more maintainable
3.  with more error-checking at compile time
4.  with a nicer API via the `vjoymodern.cpp` wrapper that is not possible with DLLs
5.  possibly better performance because of data conversions happening in C++ (not benchmarked).

## How to build it?

Building the Python extension requires having Python installed with dev headers
at `C:\Program Files\Python313\include`. If your install path is different,
change the path in the project "C/C++ > General > Additional Includes" and
"Linker > General > Additional Library Directories".

This extension needs to be built for the Python version that you plan to use
in your (feeder) application. [See details here](https://docs.python.org/3/c-api/stable.html)

## vJoy developer notes

Future developers: consider [moving to nanobind](https://nanobind.readthedocs.io/en/latest/why.html).
