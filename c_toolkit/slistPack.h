/*                               -*- Mode: C -*- 
 * slistPack.h -- Simple list header.
 * 
 * Copyright (c) 1991-2014 Francois Felix Ingrand.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef INCLUDE_slistPack
#define INCLUDE_slistPack

#include "slistPack-pub.h"

typedef struct simple_node Snode;

typedef enum {SLT_DYNAMIC, SLT_SINGLE, SLT_DOUBLE, SLT_STATIC, SLT_EMPTY} Slist_Type;

struct simple_node {
     Snode *next;
     const void *node;
};

struct simple_list  {
#ifdef CHECK_LOOP_REENTRANCE
     void *loop_used;
#endif
     union {
	  Snode *dy;
	  const void **st;
	  const void *sd;
     } first;
     union {
	  Snode *dy;
	  const void **st;
	  const void *sd;
     } last;
     union {
	  Snode *dy;
	  const void **st;
	  const void *sd;
     } current;
     unsigned int length;
     Slist_Type type;
     unsigned int dynamic;
};
#endif
