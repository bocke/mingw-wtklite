/*
 * wtkalign.c
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation of AlignWindow(), a helper
 * function for controlling the placement of child windows relative
 * to their parent, or to the screen bounds.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2013, MinGW.org Project.
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
#define  WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "wtkalign.h"

void AlignWindow( HWND child, unsigned int alignment )
{
  /* Helper to be invoked while handling a WM_CREATE or WM_INITDIALOG
   * message; it adjusts the position at which the window or dialogue
   * box is created, such that it is displayed either neatly centred,
   * or flush with specified boundaries, on the screen, or within its
   * parent window.
   */
  HWND parent = ((alignment & WTK_ALIGN_ONSCREEN) == 0)
    /*
     * Unless alignment relative to the screen is specified, we must
     * identify the parent window from which the alignment bounds are
     * to be deduced.
     */
    ? GetParent( child )
    : NULL;

  if( parent == NULL )
    /* When no parent has yet been identified, we are either explicitly
     * attempting to align within the desktop bounds, or the window we
     * are attempting to align has no valid parent; in either case, we
     * use the desktop window as the effective parent.
     */
    parent = GetDesktopWindow();

  if( parent != NULL )
  {
    /* We now have a valid effective parent, so we may continue...
     */
    RECT screen, window;
    unsigned int mode;

    /* First, we obtain the physical co-ordinates of the four corners
     * for both the dialogue box in its default position, and for the
     * parent window, all mapped as screen co-ordinates.
     */
    GetWindowRect( child, &window );
    GetWindowRect( parent, &screen );

    /* Adjust the left-right position, setting the left ordinate for the
     * "screen" co-ordinate group to the physical left ordinate for final
     * placement of the dialogue on-screen...
     */
    switch( mode = alignment & WTK_ALIGN_HCENTRE )
    {
      case WTK_ALIGN_RIGHT:
      case WTK_ALIGN_HCENTRE:
	/* In the case of right or centred alignment, we initially push
	 * the left ordinate of the "window" co-ordinate group as far to
	 * the right as possible, while still keeping the window within
	 * the designated screen bounds...
	 */
	window.left += screen.right - screen.left - window.right;
	if( mode == WTK_ALIGN_HCENTRE )
	  /* ...then, in the centred case, we move it back to the left,
	   * by half of the distance between the leftmost "screen" bound
	   * and the right-adjusted "window" ordinate.
	   */
	  screen.left += (window.left > 0) ? window.left >> 1 : 0;

      case WTK_ALIGN_LEFT:
	/* In the case of left alignment we have nothing to do -- the
	 * left bound of the "screen" co-ordinate group is already set
	 * to the position where we want to place the left side of the
	 * aligned window.
	 */
	break;

      default:
	/* In the case where no left-right alignment is specified, we
	 * can simply make the left "screen" ordinate coincide with the
	 * default position of the window.
	 */
	screen.left = window.left;
    }

    /* Adjust the top-bottom position, setting the top ordinate for the
     * "screen" co-ordinate group to the physical top ordinate for final
     * placement of the dialogue on-screen...
     */
    switch( mode = alignment & WTK_ALIGN_VCENTRE )
    {
      case WTK_ALIGN_BOTTOM:
      case WTK_ALIGN_VCENTRE:
	/* In the case of bottom or centred alignment, we initially push
	 * the top ordinate of the "window" co-ordinate group downwards as
	 * far as is possible, while still keeping the window within the
	 * designated screen bounds...
	 */
	window.top += screen.bottom - screen.top - window.bottom;
	if( mode == WTK_ALIGN_VCENTRE )
	  /* ...then, in the centred case, we adjust it upwards again,
	   * by half of the distance between the topmost "screen" bound
	   * and the downwards adjusted top "window" ordinate.
	   */
	  screen.top += (window.top > 0) ? window.top >> 1 : 0;

      case WTK_ALIGN_TOP:
	/* In the case of top alignment we have nothing to do -- the
	 * top bound of the "screen" co-ordinate group is already set
	 * to the position where we want to place the top edge of the
	 * aligned window.
	 */
	break;

      default:
	/* In the case where no top-bottom alignment is specified, we
	 * can simply make the top "screen" ordinate coincide with the
	 * default position of the window.
	 */
	screen.top = window.top;
    }

    /* Finally, we reposition the dialogue box to the top left screen
     * co-ordinate we've just computed, preserving its original size.
     */
    SetWindowPos( child, HWND_TOP, screen.left, screen.top, 0, 0, SWP_NOSIZE );
  }
}

/* $RCSfile$: end of file */
