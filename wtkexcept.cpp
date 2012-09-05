/*
 * wtkexcept.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the WTK::runtime_error class,
 * a derivative of std::exception similar to std::runtime_error, but using
 * a "const char *" argument in preference to a std::string, to classify
 * the exception.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, MinGW.org Project.
 *
 * Based on the implementation of mingw-get's dmh_exception class
 * Originally written by Charles Wilson <cwilso11@users.sourceforge.net>
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
#include "wtkexcept.h"

namespace WTK
{
  static const char *unspecified = "Unspecified exception";

  runtime_error::runtime_error() throw(): message( unspecified ){}

  runtime_error::runtime_error( const char *msg ) throw(): message( unspecified )
  { if( msg && *msg ) message = msg; }

  const char *runtime_error::what() const throw(){ return message; }
}

/* $RCSfile$: end of file */
