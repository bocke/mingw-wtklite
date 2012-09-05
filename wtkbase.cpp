/*
 * wtkbase.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the constructor for WindowClassMaker C++ class objects,
 * and the implementation for the Create() method of the WindowMaker class.
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
#define WIN32_LEAN_AND_MEAN

#include "wtkplus.h"

namespace WTK
{
  WindowClassMaker::WindowClassMaker( HINSTANCE instance, unsigned id ):
  GenericWindow( instance )
  {
    /* Construct a window class registration helper, and assign
     * default attributes to suit top-level windows.
     */
    hInstance = instance;
    style = CS_HREDRAW | CS_VREDRAW;
    hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    lpszMenuName = MAKEINTRESOURCE( id );
    hCursor = LoadCursor( (HINSTANCE)(NULL), IDC_ARROW );
    hIcon = LoadIcon( instance, lpszMenuName );
    lpfnWndProc = WindowProcedure;
    cbClsExtra = cbWndExtra = 0;
  }

  HWND WindowMaker::Create( const char *ClassName, const char *Caption )
  {
    /* Create a generic top-level application window, with attributes
     * appropriate to a registered (named) window class.
     */
    AppWindow = CreateWindow( ClassName,
	Caption, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS,
	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
	(HWND)(NULL), (HMENU)(NULL), AppInstance, this
      );
    if( ! AppWindow ) throw( runtime_error( "CreateWindow FAILED" ) );
    return AppWindow;
  }
}

/* $RCSfile$: end of file */
