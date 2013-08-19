#ifndef WTKDEFS_H
/*
 * wtkdefs.h
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This header file provides a set of utility macro definitions, which
 * may be required by other more user visible header files.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2013, MinGW.org Project.
 *
 * ---------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ---------------------------------------------------------------------------
 *
 */
#define WTKDEFS_H  1

/* Some functions expose an extern "C" interface, (some may even be written
 * in C), but within C++ clients we subsume them into the WTK namespace; we
 * provide a set of macros to facilitate this...
 */
#ifdef __cplusplus
/*
 * ...for the (normal) C++ case...
 */
# define EXTERN_C               extern "C"
# define BEGIN_NAMESPACE(NAME)  namespace NAME {
# define END_NAMESPACE(NAME)    }

#else
/* ...while also providing an interface which exposes them globally,
 * so that they may also be called from C code.
 */
# define EXTERN_C		extern
# define BEGIN_NAMESPACE(NAME)
# define END_NAMESPACE(NAME)
#endif

#endif /* WTKDEFS_H: $RCSfile$: end of file */
