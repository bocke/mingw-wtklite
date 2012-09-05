/*
 * errtext.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the WTK::error_text class,
 * a utility class to facilitate formatting of diagnostic messages for
 * use with the WTK::runtime_error exception class.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, MinGW.org Project.
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
#include <stdio.h>
#include <stdarg.h>

#include "wtkexcept.h"

namespace WTK
{
  char error_text::message[256];

  error_text::error_text( const char *fmt, ... ) throw()
  {
    /* Constructor: uses printf semantics to format an error message,
     * storing the resultant text int the class's static buffer.
     */
    va_list argv;
    va_start( argv, fmt );
    vsnprintf( message, sizeof( message ), fmt, argv );
    va_end( argv );
  }
}

/* $RCSfile$: end of file */
