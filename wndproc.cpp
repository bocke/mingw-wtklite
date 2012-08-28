/*
 * wndproc.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for the default window procedure,
 * which is used by all window classes derived from GenericWindow.
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

#include "wtkplus.h"

namespace WTK
{
# define OnEventCase(MSG,ACTION)  case MSG: if( ACTION == 0L ) return 0L; break
# define SplitWord(PARAM_NAME)	  LOWORD(PARAM_NAME), HIWORD(PARAM_NAME)

  long CALLBACK GenericWindow::WindowProcedure
  ( HWND window, unsigned message, WPARAM w_param, LPARAM l_param )
  {
    /* Generic dispatcher for all window procedures.  This is a static
     * member function of the generic window class; as such, it must do
     * no more than establish a pointer to the class instance, before
     * delegating processing to a regular member function.
     */
    GenericWindow *me;
    if( message == WM_NCCREATE )
    {
      /* This message is dispatched during processing of CreateWindow(),
       * which has been called by the class constructor; we have arranged
       * that the requisite class instance pointer will have been passed
       * within the CREATESTRUCT at *l_param, and we must now save it.
       */
      me = (GenericWindow *)(((CREATESTRUCT *)(l_param))->lpCreateParams);
      SetWindowLong( window, GWL_USERDATA, (long)(me) );

      /* We must also store the passed window handle within the class
       * instance data space...
       */
      me->AppWindow = window;
    }
    else
      /* ...otherwise we retrieve the class instance pointer we saved,
       * during the CreateWindow() call...
       */
      me = (GenericWindow *)(GetWindowLong( window, GWL_USERDATA ));

    /* ...before delegating the handling of the current message to the
     * controller associated with the class instance...
     */
    return me ? me->Controller( message, w_param, l_param )
      /*
       * ...or to the default window procedure, if no controller can
       * be identified.
       */
      : DefWindowProc( window, message, w_param, l_param );
  }

  long GenericWindow::Controller
  ( unsigned message, WPARAM w_param, LPARAM l_param )
  {
    /* Centralised marshalling function for all window messages.  It is
     * to this function that the preceding static function delegates all
     * message handling requests; these are then forwarded...
     */
    switch( message )
    {
      /* ...to the appropriate handler from those enumerated below.  In
       * its default implementation, each of these virtual functions does
       * no more than simply return; an actual window class must derive
       * from the GenericWindow class, and override any such of these
       * message handlers as may be required.
       *
       * FIXME: Only a small subset of possible window messages is
       * currently supported; this list should be extended to cover
       * all possible message types.
       *
       */
      OnEventCase( WM_CREATE,         OnCreate() );
      OnEventCase( WM_COMMAND,        OnCommand( w_param ) );
      OnEventCase( WM_MOUSEMOVE,      OnMouseMove( w_param ) );
      OnEventCase( WM_LBUTTONDOWN,    OnLeftButtonDown() );
      OnEventCase( WM_LBUTTONUP,      OnLeftButtonUp() );
      OnEventCase( WM_NOTIFY,         OnNotify( w_param, l_param ) );
      OnEventCase( WM_SIZE,           OnSize( w_param, SplitWord(l_param) ) );
      OnEventCase( WM_HSCROLL,        OnHorizontalScroll( SplitWord(w_param), (HWND)(l_param)) );
      OnEventCase( WM_VSCROLL,        OnVerticalScroll( SplitWord(w_param), (HWND)(l_param)) );
      OnEventCase( WM_PAINT,          OnPaint() );
      OnEventCase( WM_DESTROY,        OnDestroy() );
    }
    /* In the event that no handler is provided for any particular message,
     * fall back to MS-Windows own default handler.
     */
    return DefWindowProc( AppWindow, message, w_param, l_param );
  }
}

/* $RCSfile$: end of file */
