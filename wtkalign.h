#ifndef WTKALIGN_H
/*
 * wtkalign.h
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of an AlignWindow() function, to complement the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This header file is to be included by all users of AlignWindow().
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
#define WTKALIGN_H  1

/* AlignWindow() is written in C, but for C++ clients we subsume
 * it into the WTK namespace.
 */
#include "wtkdefs.h"

BEGIN_NAMESPACE( WTK )

/* Specify reference bounds for child window alignment.
 * By default, child windows are aligned within the frame of their parent.
 * Adding this bit-flag, (by bit-wise OR), to the alignment parameter which
 * is passed to the WTK::AlignWindow function, will override this default,
 * so alignment becomes relative to the screen bounds.
 */
#define WTK_ALIGN_ONSCREEN	  0x0100

/* Define the individual component flags, for specification of window
 * placement relative to each of the four alignment boundaries.
 */
#define WTK_ALIGN_LEFT    	  0x0001
#define WTK_ALIGN_RIGHT   	  0x0002
#define WTK_ALIGN_HCENTRE 	  0x0003
#define WTK_ALIGN_TOP     	  0x0010
#define WTK_ALIGN_BOTTOM  	  0x0020
#define WTK_ALIGN_VCENTRE 	  0x0030

/* Combine these, to define the nine logical placement classes.
 */
#define WTK_ALIGN_TOPLEFT	( WTK_ALIGN_TOP      |  WTK_ALIGN_LEFT    )
#define WTK_ALIGN_TOPRIGHT	( WTK_ALIGN_TOP      |  WTK_ALIGN_RIGHT   )
#define WTK_ALIGN_CENTRETOP	( WTK_ALIGN_TOP      |  WTK_ALIGN_HCENTRE )
#define WTK_ALIGN_CENTRELEFT	( WTK_ALIGN_LEFT     |  WTK_ALIGN_VCENTRE )
#define WTK_ALIGN_CENTRERIGHT	( WTK_ALIGN_RIGHT    |  WTK_ALIGN_VCENTRE )
#define WTK_ALIGN_CENTRED    	( WTK_ALIGN_HCENTRE  |  WTK_ALIGN_VCENTRE )
#define WTK_ALIGN_CENTREBOTTOM	( WTK_ALIGN_BOTTOM   |  WTK_ALIGN_HCENTRE )
#define WTK_ALIGN_BOTTOMRIGHT	( WTK_ALIGN_BOTTOM   |  WTK_ALIGN_RIGHT   )
#define WTK_ALIGN_BOTTOMLEFT	( WTK_ALIGN_BOTTOM   |  WTK_ALIGN_LEFT    )

/* Provide a set of aliases to suit American users, (and any others
 * who can't spell "centre").
 */
#define WTK_ALIGN_CENTERED	  WTK_ALIGN_CENTRED
#define WTK_ALIGN_CENTERTOP	  WTK_ALIGN_CENTRETOP
#define WTK_ALIGN_CENTERLEFT	  WTK_ALIGN_CENTRELEFT
#define WTK_ALIGN_CENTERBOTTOM	  WTK_ALIGN_CENTREBOTTOM
#define WTK_ALIGN_CENTERRIGHT	  WTK_ALIGN_CENTRERIGHT

/* Declare the prototype for the alignmemnt function.
 */
EXTERN_C void AlignWindow( HWND child, unsigned int alignment );

END_NAMESPACE( WTK )

#endif /* WTKALIGN_H: $RCSfile$: end of file */
