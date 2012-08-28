/*
 * wtkchild.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the Create() method of
 * the ChildWindowMaker class.
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
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
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
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include "wtkplus.h"

namespace WTK
{
  HWND ChildWindowMaker::Create
  ( int id, HWND Parent, const char *ClassName, unsigned long style )
  {
    /* Create a generic child window, with specified ID, and
     * owned by specified parent.
     */
    HWND child_window = CreateWindow( ClassName,
	NULL, style | WS_CHILD | WS_CLIPSIBLINGS, 0, 0, 0, 0,
	Parent, (HMENU)(id), AppInstance, this
      );
    if( ! child_window )
    {
      /* On failure, compose diagnostic message, and bail out.
       */
      const char *fmt = "%s: CreateWindow FAILED";
      char description[1 + snprintf( NULL, 0, fmt, ClassName )];
      snprintf( description, sizeof( description ), fmt, ClassName );
      throw( runtime_error( description ) );
    }
    /* On success, return the window handle.
     */
    return child_window;
  }
}

/* $RCSfile$: end of file */
