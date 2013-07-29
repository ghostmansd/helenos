/*
 * Copyright (c) 2011 Petr Koupy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup libposix
 * @{
 */
/** @file Mathematical operations.
 */

#define LIBPOSIX_INTERNAL
#define __POSIX_DEF__(x) posix_##x

#include "internal/common.h"
#include "posix/math.h"

/**
 * 
 * @param x
 * @param exp
 * @return
 */
double posix_ldexp(double x, int exp)
{
	// TODO: low priority, just a compile-time dependency of binutils
	not_implemented();
}

/**
 * 
 * @param num
 * @param exp
 * @return
 */
double posix_frexp(double num, int *exp)
{
	// TODO: low priority, just a compile-time dependency of binutils
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_cos(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @param y
 * @return
 */
double posix_pow(double x, double y)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_floor(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_fabs(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @param iptr
 * @return
 */
double posix_modf(double x, double *iptr)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @param y
 * @return
 */
double posix_fmod(double x, double y)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_log(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @param y
 * @return
 */
double posix_atan2(double y, double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_sin(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_exp(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/**
 * 
 * @param x
 * @return
 */
double posix_sqrt(double x)
{
	// TODO: Python dependency
	not_implemented();
}

/** @}
 */