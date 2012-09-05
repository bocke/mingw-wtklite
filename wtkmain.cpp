/*
 * wtkmain.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the standard methods of
 * the MainWindowMaker class.
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
  int MainWindowMaker::Invoked()
  {
    /* Initiate the message processing loop for the main window.
     */
    MSG message; int status;
    while( (status = GetMessage( &message, NULL, 0, 0 )) != 0 )
    {
      if( status == -1 )
	throw( runtime_error( "Unexpected message handler exception" ) );

      else
      {
	TranslateMessage( &message );
	DispatchMessage( &message );
      }
    }
  }

  long MainWindowMaker::OnDestroy()
  {
    /* When the top level window is being destroyed, we notify the
     * message loop that the application is terminating.
     */
    PostQuitMessage( EXIT_SUCCESS );
    return EXIT_SUCCESS;
  }
}

/* $RCSfile$: end of file */
