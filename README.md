README for MinGW Windows ToolKit
================================

Written by Keith Marshall <keithmarshall@users.sourceforge.net>
Copyright (C) 2012, MinGW.org Project


Synopsis
--------

This package implements a minimal C++ class framework, encapsulating
the MS-Windows API.  It has been developed to facilitate implementation
of the GUI components of mingw-get; as such, it does not aim to provide
a fully featured API class framework, but rather, it is restricted to
providing only those features which are necessary for mingw-get.

It may be extended in the future, as the need arises.


Licence
-------

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice, this permission notice, and the following
disclaimer shall be included in all copies or substantial portions of
the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.


Building from a Source TarBall
------------------------------

This package is delivered in source format, suitable for building in
accordance with the standard GNU paradigm; building out-of-source, (or
in a subdirectory of the source tree), is recommended:--

  1) tar xf wtk-<version>-mingw32-src.tar.gz
  2) mkdir wtk-<version>/build
  3) cd wtk-<version>/build
  4) ../configure
  5) make
  6) make install


Building from SCM Repository
----------------------------

If the source code has been obtained from MinGW.org's git repository, it
will be necessary to also source the build-aux module from this repository,
and link, (or copy), the install-sh file into the top source directory of
the WTK tree.  Then, cd to the top of the WTK tree, and proceed:--

  1) autoconf
  2) mkdir build
  3) cd build
  4) ../configure
  5) make
  6) make install

$RCSfile$: end of file
