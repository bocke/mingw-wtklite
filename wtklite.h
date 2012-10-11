#ifndef WTKLITE_H
/*
 * wtklite.h
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This header file is to be included by all users of this MS-Windows
 * C++ class framework.
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
#define WTKLITE_H  1

#include <stdlib.h>
#include <windows.h>
#include "wtkexcept.h"

/* This header file is primarily intended to be used only for C++.  However,
 * configure scripts may try to compile it as C, when checking availability;
 * thus, we ignore C++ specific content when compiling as C, to ensure that
 * configure doesn't choke in such cases.
 */
#ifdef __cplusplus

namespace WTK
{
  class StringResource
  {
    /* A utility class to facilitate retrieval of string data
     * from a program module's resource database; instantiated
     * by passing the program module's instance handle and the
     * numeric resource ID, its effective "value" is a const
     * character pointer to a copy of the resource string.
     */
    public:
      StringResource( HINSTANCE, unsigned int );
      operator const char *() const { return value; }
      ~StringResource(){ free( (void *)(value) ); }

    private:
      const char *value;
  };

  class GenericDialogue
  {
    /* A simple class to facilitate display of a dialogue box,
     * from a resource template.  The default dialogue procedure
     * will accept only a simple dismissal request, (similar to the
     * behaviour of a MessageBox() dialogue); users may derive from
     * this class, overriding the Dismiss() method, to implement
     * more sophisticated dialogues.
     */
    public:
      GenericDialogue( HINSTANCE app, HWND parent, int ID )
      { DialogBox( app, MAKEINTRESOURCE( ID ), parent, Dismiss ); }
      static BOOL CALLBACK Dismiss( HWND, unsigned, WPARAM, LPARAM );
  };

  class GenericWindow
  {
    /* An abstract base class, from which all regular window object
     * classes are derived; it implements the "window procedure", which
     * directs windows messages to the appropriate handlers, which are
     * themselves implemented in the derived classes.
     */
    protected:
      HWND AppWindow;
      HINSTANCE AppInstance;
      GenericWindow( HINSTANCE appid ): AppInstance( appid ){}
      static long CALLBACK WindowProcedure( HWND, unsigned, WPARAM, LPARAM );
      virtual long Controller( unsigned, WPARAM, LPARAM );

    public:
      /* This hook is provided to facilitate the implementation of
       * sash window controls, (not standard in MS-Windows-API).
       */
      virtual long AdjustLayout(){ return 1L; }

    private:
      /* The following (incomplete) list identifies the windows
       * messages which this framework can currently handle, and
       * implements a default "do nothing" handler for each.
       *
       * In most cases, the mapping of these handler names to their
       * equivalent windows message IDs should be self evident.  In
       * case of doubt, see wndproc.cpp for the definitive list.
       *
       * FIXME: Only a small subset of possible window messages is
       * currently supported; this list should be extended to cover
       * all possible message types.
       *
       */
      virtual long OnCreate(){ return 1L; }
      virtual long OnCommand( WPARAM ){ return 1L; }
      virtual long OnDestroy(){ return 0L; }
      virtual long OnSize( WPARAM, int, int ){ return 1L; }
      virtual long OnHorizontalScroll( int, int, HWND ){ return 1L; }
      virtual long OnVerticalScroll( int, int, HWND ){ return 1L; }
      virtual long OnNotify( WPARAM, LPARAM ){ return 1L; }
      virtual long OnPaint(){ return 1L; }
      virtual long OnLeftButtonDown(){ return 1L; }
      virtual long OnLeftButtonUp(){ return 1L; }
      virtual long OnMouseMove( WPARAM ){ return 1L; }
  };

  class WindowClassMaker: protected WNDCLASS, protected GenericWindow
  {
    /* A utility class to facilitate the registration of window
     * "class" names, (in the MS-Windows-API sense); it provides
     * an interface to the RegisterClass() function, together with
     * a complement of inline methods for initialisation of the
     * attributes of the registered WNDCLASS structure.
     */
    public:
      WindowClassMaker( HINSTANCE, unsigned = 0 );
      inline void SetHandler( WNDPROC MessageHandler )
      {
	/* Bind a specified "window procedure" to the registered
	 * class; nominally it is the standard implementation from
	 * the GenericWindow base class.
	 */
	lpfnWndProc = MessageHandler;
      }
      inline void SetIcon( HICON icon )
      {
	/* Associate an icon with the registered class.
	 */
	hIcon = icon;
      }
      inline void SetCursor( HCURSOR Cursor )
      {
	/* Specify the default cursor to use in windows of
	 * the registered class.
	 */
	hCursor = Cursor;
      }
      inline void SetMenuName( const char *MenuName )
      {
	/* Associate a named menu with windows of the registered
	 * class.
	 */
	lpszMenuName = MenuName;
      }
      inline void SetBackground( HBRUSH colour )
      {
	/* Set the background colour for windows of the
	 * registered class.
	 */
	hbrBackground = colour;
      }
      inline int Register( const char *ClassName )
      {
	/* Register the named window class...
	 */
	lpszClassName = ClassName;
	if( int retval = RegisterClass( this ) ) return retval;

	/* ...bailing out, in the event of any error.
	 */
	throw( runtime_error( "Window Class Registration FAILED" ) );
      }
  };

  class WindowMaker: protected GenericWindow
  {
    /* An intermediate class, implementing some common methods for
     * use by derived window classes.
     */
    public:
      WindowMaker( HINSTANCE inst ): GenericWindow( inst ){}
      HWND Create( const char *, const char * );
      int Show( int mode ){ return ShowWindow( AppWindow, mode ); }
      int Update(){ return UpdateWindow( AppWindow ); }
  };

  class MainWindowMaker: public WindowMaker
  {
    /* A stock window class, suitable for providing the implementation
     * of an application's main window.
     */
    public:
      MainWindowMaker( HINSTANCE instance ): WindowMaker( instance ){}
      virtual int Invoked();

    private:
      virtual long OnDestroy();
  };

  class ChildWindowMaker: public WindowMaker
  {
    /* A stock window class, suitable for providing the implementation
     * of a general purpose child window.
     */
    public:
      ChildWindowMaker( HINSTANCE inst ): WindowMaker( inst ){}
      HWND Create( int, HWND, const char *, unsigned long = 0 );
  };

  inline GenericWindow *WindowObjectReference( HWND window )
  {
    /* A helper function; it returns a pointer to the C++ class
     * object which is associated with a specified window handle.
     */
    return (GenericWindow *)(GetWindowLongPtr( window, GWLP_USERDATA ));
  }

  class SashWindowMaker: public ChildWindowMaker
  {
    /* An abstract base class, providing the basis for implementation
     * of both horizontal and vertical sash window controls.
     */
    protected:
      long OnLeftButtonDown();
      long OnMouseMove( WPARAM );
      long OnLeftButtonUp();

      RECT frame;
      double ScaleFactor, DisplacementFactor, MinRangeFactor, MaxRangeFactor;
      SashWindowMaker( HINSTANCE, double, double, double );

      inline long GetFrameHeight(){ return (frame.bottom - frame.top); }
      inline long GetFrameWidth(){ return (frame.right - frame.left); }

      virtual const char *CursorStyle( void ) = 0;
      virtual void SetClippingRegion( long, long, long ) = 0;
      virtual void SetDisplacementFactor( unsigned long ) = 0;
      void RegisterWindowClassName( const char * );
      void ValidateDisplacementFactor( void );

    public:
      int Displacement( int span = 1 ){ return (int)(DisplacementFactor * span); }
  };

  class HorizontalSashWindowMaker: public SashWindowMaker
  {
    /* The concrete class implementing a sash bar control, which
     * divides its owner window into two horizontally adjacent panes
     * of complementary adjustable width.
     */
    public:
      HorizontalSashWindowMaker
      ( int id, HWND owner, HINSTANCE app,
	double minval, double initval, double maxval
      ): SashWindowMaker( app, minval, initval, maxval )
      { Create( id, owner, RegisteredClassName(), WS_BORDER ); }

    private:
      static const char *ClassName;
      const char *RegisteredClassName( void );
      inline const char *CursorStyle( void ){ return IDC_SIZEWE; }
      void SetDisplacementFactor( unsigned long );
      void SetClippingRegion( long, long, long );
  };

  class VerticalSashWindowMaker: public SashWindowMaker
  {
    /* The concrete class implementing a sash bar control, which
     * divides its owner window into two vertically adjacent panes
     * of complementary adjustable height.
     */
    public:
      VerticalSashWindowMaker
      ( int id, HWND owner, HINSTANCE app,
	double minval, double initval, double maxval
      ): SashWindowMaker( app, minval, initval, maxval )
      { Create( id, owner, RegisteredClassName(), WS_BORDER ); }

    private:
      static const char *ClassName;
      const char *RegisteredClassName( void );
      inline const char *CursorStyle( void ){ return IDC_SIZENS; }
      void SetClippingRegion( long, long, long );
      void SetDisplacementFactor( unsigned long );
  };
}

#endif /* __cplusplus */
#endif /* ! WTKLITE_H: $RCSfile$: end of file */
