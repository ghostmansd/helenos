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

#ifndef POSIX_MATH_H_
#define POSIX_MATH_H_

#ifndef __POSIX_DEF__
#define __POSIX_DEF__(x) x
#endif

#ifdef __GNUC__
	#define HUGE_VAL (__builtin_huge_val())
#endif

/* Normalization Functions */
extern double __POSIX_DEF__(ldexp)(double x, int exp);
extern double __POSIX_DEF__(frexp)(double num, int *exp);

double __POSIX_DEF__(fabs)(double x);
double __POSIX_DEF__(floor)(double x);
double __POSIX_DEF__(modf)(double x, double *iptr);
double __POSIX_DEF__(fmod)(double x, double y);
double __POSIX_DEF__(pow)(double x, double y);
double __POSIX_DEF__(exp)(double x);
double __POSIX_DEF__(sqrt)(double x);
double __POSIX_DEF__(log)(double x);
double __POSIX_DEF__(sin)(double x);
double __POSIX_DEF__(cos)(double x);
double __POSIX_DEF__(atan2)(double y, double x);

#endif /* POSIX_MATH_H_ */

/** @}
 */