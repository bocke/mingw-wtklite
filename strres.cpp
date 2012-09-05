/*
 * strres.cpp
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This file provides the implementation of the constructor for the
 * StringResource class.
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
#include <string.h>
#include <stdio.h>

/* MSDN says that the maximum length of any one string resource
 * is 4097 characters; it isn't clear if this limit includes the
 * terminating NUL, so we'll assume we may need one more.
 */
#define WTK_STRING_RESOURCE_MAX  4098

WTK::StringResource::StringResource( HINSTANCE inst, unsigned int id )
{
  /* First, allocate a temporary buffer, of sufficient size to
   * accommodate a copy of the longest possible string resource.
   */
  char *tmp; value = NULL;
  if( (tmp = (char *)(malloc( WTK_STRING_RESOURCE_MAX ))) == NULL )
    throw( runtime_error( "Insufficient memory" ) );

  /* Attempt to load the specified resource into this buffer...
   */
  if( ! LoadString( inst, id, tmp, WTK_STRING_RESOURCE_MAX ) )
  {
    /* ...but if that fails, release the temporary buffer
     * to avoid leaking memory...
     */
    free( (void *)(tmp) );

    /* ...and bail out, with a suitable diagnostic message.
     */
    throw( runtime_error( error_text( "String resource #%u not found", id )) );
  }

  /* Having successfully loaded the resource, adjust the memory
   * allocation to fit, without wastage...
   */
  if( (value = (char *)(realloc( tmp, 1 + strlen( tmp ) ))) == NULL )
    /*
     * ...making the temporary buffer reference permanent, in
     * the event that the reallocation should fail.
     */
    value = tmp;
}

/* $RCSfile$: end of file */
