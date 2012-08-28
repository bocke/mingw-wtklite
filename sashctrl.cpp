/*
 * sashctrl.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation for each of the three C++ classes
 * which are required to implement sash window controls.  It must be compiled
 * to generate three separate object modules:--
 *
 *   c++ -c sashctrl.cpp -o sashctrl.o
 *   c++ -D HSASH_IMPLEMENTATION -c sashctrl.cpp -o hsashctl.o
 *   c++ -D VSASH_IMPLEMENTATION -c sashctrl.cpp -o vsashctl.o
 *
 * to obtain the implementations of the SashWindowMaker abstract base class,
 * together with its HorizontalSashWindowMaker and VerticalSashWindowMaker
 * derived classes, respectively.
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
#define  WIN32_LEAN_AND_MEAN

#include "wtkplus.h"

/* Identify the class implementation to be compiled; each of
 * the HSASH_IMPLEMENTATION and VSASH_IMPLEMENTATION must be
 * explicitly requested.  Initially, we assume that either of
 * these may have been specified, so we deselect the fallback
 * case...
 */
#undef CORE_IMPLEMENTATION

/* ...then...
 */
#ifdef HSASH_IMPLEMENTATION
 /* ...when the horizontal sash case IS selected, we ensure that
  * the vertical sash case ISN'T...
  */
# undef  VSASH_IMPLEMENTATION

/* ...otherwise, when the horizontal sash case ISN'T selected...
 */
#elif !defined VSASH_IMPLEMENTATION
 /* ...and the vertical sash case ISN'T either, then we reselect
  * the fallback case.
  */
# define CORE_IMPLEMENTATION
#endif

namespace WTK
{
# ifdef CORE_IMPLEMENTATION
  /* Neither the HSASH_IMPLEMENTATION nor the VSASH_IMPLEMENTATION
   * was selected; implement the SashWindowMaker class.
   */
  SashWindowMaker::SashWindowMaker
  ( HINSTANCE app, double minval, double initval, double maxval ):
    ChildWindowMaker( app ), MinRangeFactor( minval ), MaxRangeFactor( maxval ),
    DisplacementFactor( initval ){ ValidateDisplacementFactor(); }

  void SashWindowMaker::RegisterWindowClassName( const char *ClassName )
  {
    /* Helper routine, to ensure that an appropriate window class name
     * is registered, as required for instantiation of any object of the
     * derived HorizontalSashWindowMaker or VerticalSashWindowMaker class.
     */
    WindowClassMaker WindowClassRegistry( AppInstance );
    WindowClassRegistry.SetCursor( LoadCursor( NULL, CursorStyle() ));
    WindowClassRegistry.Register( ClassName );
  }

  long SashWindowMaker::OnLeftButtonDown( void )
  {
    /* Capture the mouse over a sash bar, and initiate the drag
     * operation to resize the adjacent sash panes.
     */
    HWND owner;
    SetCapture( AppWindow );

    /* Establish the viewport region of the owner window, within
     * which the sash panes are defined.
     */
    GetClientRect( (owner = GetParent( AppWindow )), &frame );
    long width = GetFrameWidth(), height = GetFrameHeight();

    /* Adjust the frame bounds to accommodate the entire extent
     * of the owner window, then relative to those, establish the
     * clipping region within which mouse movement is to be confined
     * while dragging the sash bar.
     */
    GetWindowRect( owner, &frame );
    long border = (GetFrameWidth() - width) / 2;
    SetClippingRegion( width, height, border );
    ClipCursor( &frame );

    /* Readjust the frame bounds to the entire extent of the owner
     * window, (they will have been modified while setting up the
     * clipping region), then further adjust the top edge and left
     * side entries, to reflect the offset of the viewport within
     * the overall window bounds.
     */
    GetWindowRect( owner, &frame );
    frame.top = frame.bottom - border - height;
    frame.left += border;
    return EXIT_SUCCESS;
  }

  long SashWindowMaker::OnMouseMove( WPARAM flags )
  {
    /* When the mouse has been captured over a sash bar...
     */
    if( flags & MK_LBUTTON )
    {
      /* ...compute the position to which it has been dragged,
       * ensuring that it remains within the permitted bounds...
       */
      SetDisplacementFactor( GetMessagePos() );
      ValidateDisplacementFactor();

      /* ...then dynamically update the owner window display,
       * to reflect the sash movement.
       */
      WindowObjectReference( GetParent( AppWindow ))->AdjustLayout();
    }
  }

  void SashWindowMaker::ValidateDisplacementFactor()
  {
    /* Helper routine to ensure that sash bar movement
     * remains within permitted bounds.
     */
    if( DisplacementFactor < MinRangeFactor )
      DisplacementFactor = MinRangeFactor;
    else if( DisplacementFactor > MaxRangeFactor )
      DisplacementFactor = MaxRangeFactor;
  }

  long SashWindowMaker::OnLeftButtonUp( void )
  {
    /* Complete a drag operation on a sash bar; first we
     * release the mouse from the clipping region...
     */
    ReleaseCapture();
    ClipCursor( NULL );

    /* ...then perform a final update of the owner window,
     * to clean up any display artefacts which may have been
     * left behind by dragging the sash bar...
     */
    HWND owner = GetParent( AppWindow );
    InvalidateRect( owner, NULL, TRUE );
    UpdateWindow( owner );

    /* ...and we are done.
     */
    return EXIT_SUCCESS;
  }

#else
  /* When compiling each of the HSASH_IMPLEMENTATION module, and
   * the VSASH_IMPLEMENTATION module...
   */
  class MousePositionMapper
  {
    /* This locally declared, all-inline class is used to facilitate 
     * identification of the co-ordinates of the mouse position.
     */
    private:
      union { unsigned long v; struct { unsigned short x, y; }; } pos;

    public:
      MousePositionMapper( unsigned long v ){ pos.v = v; }
      long X(){ return pos.x; }
      long Y(){ return pos.y; }
  };

#endif
#ifdef HSASH_IMPLEMENTATION
  /* This is the case where we are compiling the implementation for
   * the HorizontalSashWindowMaker class.
   */
  const char *HorizontalSashWindowMaker::ClassName = NULL;
  const char *HorizontalSashWindowMaker::RegisteredClassName( void )
  {
    /* Helper routine to ensure that the appropriate window class
     * name is registered on first instantiation of any class object.
     */
    if( ClassName == NULL )
      RegisterWindowClassName( ClassName = "HSashCtrl" );
    return ClassName;
  }

  void HorizontalSashWindowMaker::
  SetClippingRegion( long width, long height, long border )
  {
    /* Helper routine, called by the OnLeftButtonDown() method which is
     * inherited from the SashWindowMaker base class, to establish left
     * and right movement bounds for the sash bar, within the frame of
     * the owner window.
     */
    ScaleFactor = (double)(width);
    frame.right -= border + (long)( (1.0 - MaxRangeFactor) * ScaleFactor );
    frame.left += border + (long)( MinRangeFactor * ScaleFactor );
  }

  void HorizontalSashWindowMaker::SetDisplacementFactor( unsigned long pos )
  {
    /* Helper routine, called by the OnMouseMove() method which is
     * inherited from the SashWindowMaker base class, to establish the
     * offset of the sash bar from the left hand side of the owner
     * window, as it is dragged by the mouse.
     */
    MousePositionMapper locate( pos );
    DisplacementFactor = (double)(locate.X() - frame.left) / ScaleFactor;
  }

# elif defined VSASH_IMPLEMENTATION
  /* This is the case where we are compiling the implementation for
   * the VerticalSashWindowMaker class.
   */
  const char *VerticalSashWindowMaker::ClassName = NULL;
  const char *VerticalSashWindowMaker::RegisteredClassName( void )
  {
    /* Helper routine to ensure that the appropriate window class
     * name is registered on first instantiation of any class object.
     */
    if( ClassName == NULL )
      RegisterWindowClassName( ClassName = "VSashCtrl" );
    return ClassName;
  }

  void VerticalSashWindowMaker::
  SetClippingRegion( long width, long height, long border )
  {
    /* Helper routine, called by the OnLeftButtonDown() method which is
     * inherited from the SashWindowMaker base class, to establish upper
     * and lower movement bounds for the sash bar, within the frame of
     * the owner window.
     */
    ScaleFactor = (double)(height); frame.bottom -= border;
    frame.top = frame.bottom - (long)( (1.0 - MinRangeFactor) * ScaleFactor );
    frame.bottom -= (long)( (1.0 - MaxRangeFactor) * ScaleFactor );
  }

  void VerticalSashWindowMaker::SetDisplacementFactor( unsigned long pos )
  {
    /* Helper routine, called by the OnMouseMove() method which is
     * inherited from the SashWindowMaker base class, to establish the
     * offset of the sash bar from the top edge of the owner window,
     * as it is dragged by the mouse.
     */
    MousePositionMapper locate( pos );
    DisplacementFactor = (double)(locate.Y() - frame.top) / ScaleFactor;
  }

# endif
}

/* $RCSfile$: end of file */
