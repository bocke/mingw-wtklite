#ifndef WTKEXCEPT_H
/*
 * wtkexcept.h
 *
 * ---------------------------------------------------------------------------
 *
 * Implementation of a minimal C++ class framework for use with the
 * Microsoft Windows Application Programming Interface.
 *
 * $Id$
 *
 * This header file declares the exception class WTK::runtime_error.
 * It is implicitly included when including wtkplus.h, but may also be
 * explicitly included by any application which wishes to use the WTK
 * exception class, without the rest of the WTK C++ class framework.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, MinGW.org Project.
 *
 * Based on the implementation of mingw-get's dmh_exception class
 * Originally written by Charles Wilson <cwilso11@users.sourceforge.net>
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
#define WTKEXCEPT_H  1

#include <exception>

namespace WTK
{
  class runtime_error: public std::exception
  {
    /* An exception class, similar to std::runtime_error, but using
     * a "const char *" rather than a "std::string" to categorise and
     * describe the exception.
     */
    public:
      runtime_error() throw();
      runtime_error( const char * ) throw();
      virtual const char *what() const throw();
      virtual ~runtime_error() throw(){}

    protected:
      const char *message;
  };

  class error_text
  {
    /* A helper class to dynamically place message text, up to a
     * maximum of 256 characters, into a static buffer whence it
     * may be retrieved on catching a runtime_error exception.
     */
    public:
      error_text( const char *, ... ) throw();
      operator const char *() const throw(){ return message; }

    private:
      static char message[256];
  };
}

#endif /* ! WTKEXCEPT_H: $RCSfile$: end of file */
