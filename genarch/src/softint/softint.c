/*
 * Copyright (C) 2006 Josef Cejka
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

#include <softint/softint.h>

#define ABSVAL(x) ( (x) > 0 ? (x) : -(x))
#define SGN(x) ( (x) >= 0 ? 1 : 0 )
				      
static unsigned int divandmod32(unsigned int a, unsigned int b, unsigned int *remainder)
{
	unsigned int result;
	int steps = sizeof(unsigned int); 
	
	*remainder = 0;
	result = 0;
	
	if (b == 0) {
		/* FIXME: division by zero */
		return 0;
	}
	
	if ( a < b) {
		*remainder = a;
		return 0;
	}

	for ( ; steps > 0; steps--) {
		/* shift one bit to remainder */
		*remainder = ( (*remainder) << 1) | (( divident >> 31) & 0x1);
		result <<= 1;
		
		if (*remainder >= b) {
				*remainder -= b;
				result |= 0x1;
		}
		divident <<= 1;
	}

	return result;
}


static unsigned long divandmod64(unsigned long a, unsigned long b, unsigned long *remainder)
{
	unsigned long result;
	int steps = sizeof(unsigned long); 
	
	*remainder = 0;
	result = 0;
	
	if (b == 0) {
		/* FIXME: division by zero */
		return 0;
	}
	
	if ( a < b) {
		*remainder = a;
		return 0;
	}

	for ( ; steps > 0; steps--) {
		/* shift one bit to remainder */
		*remainder = ( (*remainder) << 1) | (( divident >> 63) & 0x1);
		result <<= 1;
		
		if (*remainder >= b) {
				*remainder -= b;
				result |= 0x1;
		}
		divident <<= 1;
	}

	return result;
}

/* 32bit integer division */
int __divsi3(int a, int b) 
{
	unsigned int rem;
	int result;
	
	result = (int)divandmod32(ABSVAL(a), ABSVAL(b), &rem);

	if ( SGN(a) == SGN(b)) return result;
	return -result;
}

/* 64bit integer division */
long __divdi3(long a, long b) 
{
	unsigned long rem;
	long result;
	
	result = (long)divandmod64(ABSVAL(a), ABSVAL(b), &rem);

	if ( SGN(a) == SGN(b)) return result;
	return -result;
}

/* 32bit unsigned integer division */
unsigned int __udivsi3(unsigned int a, unsigned int b)
{
	unsigned int rem;
	return divandmod32(a, b, &rem);
}

/* 64bit unsigned integer division */
unsigned long __udivdi3(unsigned long a, unsigned long b)
{
	unsigned long rem;
	return divandmod64(a, b, &rem);
}

/* 32bit remainder of the signed division */
int __modsi3(int a, int b)
{
	unsigned int rem;
	divandmod32(a, b, &rem);
	
	/* if divident is negative, remainder must be too*/
	if (!(SGN(a))) {
		return -((int)rem);
	}
	
	return (int)rem;
}

/* 64bit remainder of the signed division */
long __moddi3(long a, long b)
{
	unsigned long rem;
	divandmod64(a, b, &rem);
	
	/* if divident is negative, remainder must be too*/
	if (!(SGN(a))) {
		return -((long)rem);
	}
	
	return (long)rem;
}

/* 32bit remainder of the unsigned division */
unsigned int __umodsi3(unsigned int a, unsigned int b)
{
	unsigned int rem;
	divandmod32(a, b, &rem);
	return rem;
}

/* 64bit remainder of the unsigned division */
unsigned long __umoddi3(unsigned long a, unsigned long b)
{
	unsigned long rem;
	divandmod64(a, b, &rem);
	return rem;
}

unsigned long __udivmoddi3(unsigned long a, unsigned long b, unsigned long *c)
{
	return divandmod64(a, b, c);
}


