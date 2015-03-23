/*
 * wtkraise.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for RaiseAppWindow(), a helper
 * function which checks for any already running instance of the calling
 * application, and promotes any such existing instance to foreground.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2013, 2014, MinGW.org Project.
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
#include "wtklite.h"

namespace WTK
{
  EXTERN_C int RaiseAppWindow( HINSTANCE Instance, unsigned int ClassID )
  {
    /* Helper to search for any running instance of a specified window
     * class; when one is found, activate it, and bring to foreground.
     */
    HWND AppWindow = FindWindow(
	StringResource( Instance, ClassID ), NULL
      );
    if( (AppWindow != NULL) && IsWindow( AppWindow ) )
    {
      /* ...and when one is, we identify its active window...
       */
      HWND AppPopup = GetLastActivePopup( AppWindow );
      if( IsWindow( AppPopup ) )
	AppWindow = AppPopup;

      /* ...bring it to the foreground...
       */
      SetForegroundWindow( AppWindow );
      /*
       * ...restore it from minimised state, if necessary...
       */
      if( IsIconic( AppWindow ) )
	ShowWindow( AppWindow, SW_RESTORE );

      /* ...and tell caller it may defer execution to this
       * newly promoted foreground application.
       */
      return (int)(true);
    }
    return (int)(false);
  }
}

/* $RCSfile$: end of file */
