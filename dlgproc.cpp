/*
 * dlgproc.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the default dialogue procedure
 * which is available to all window classes derived from GenericDialogue.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, 2013, MinGW.org Project.
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

#include "wtklite.h"
#include "wtkalign.h"

namespace WTK
{
  BOOL CALLBACK GenericDialogue::Dismiss
  ( HWND window, unsigned msg, WPARAM wParam, LPARAM lParam )
  {
    /* This is a minimal dialogue box procedure; it provides
     * no more than a mechanism to dismiss the dialogue.
     */
    switch( msg )
    {
      /* We need to handle only two message types:
       */
      case WM_INITDIALOG:
	/* Other than positioning this dialogue box centrally,
	 * relative to its parent window, we make this a no-op,
	 * while marking it as handled.
	 */
	AlignWindow( window, WTK_ALIGN_CENTRED );
	return TRUE;

      case WM_COMMAND:
	switch( LOWORD( wParam ) )
	{
	  /* Here, we respond to only the IDOK and IDCANCEL
	   * messages, by closing the dialogue...
	   */
	  case IDOK:
	  case IDCANCEL:
	    EndDialog( window, 0 );
	    return TRUE;
	}
    }
    /* ...while in every other case, we simply ignore the message,
     * leaving it for any other handler which may wish to process it.
     */
    return FALSE;
  }
}

/* $RCSfile$: end of file */
