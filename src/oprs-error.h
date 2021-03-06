/*                               -*- Mode: C -*- 
 * oprs-error.h -- 
 * 
 * Copyright (c) 1991-2013 Francois Felix Ingrand.
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


#ifndef INCLUDE_oprs_error
#define INCLUDE_oprs_error

#include <setjmp.h>

#include "oprs-error-pub.h"

typedef enum {
     PE_UNEXPECTED_DUMP_TYPE,

     PE_UNEXPECTED_GEXPR_TYPE,
     PE_UNEXPECTED_GMEXPR_TYPE,
     PE_UNEXPECTED_GTEXPR_TYPE,
     PE_UNEXPECTED_MEXPR_TYPE,

     PE_UNEXPECTED_TEMPORAL_OPER,
     PE_UNEXPECTED_LOGICAL_OPER,

     PE_UNIFYING_GTEXPR,

     PE_UNEXPECTED_TERM_TYPE, 

     PE_UNEXPECTED_INSTRUCTION_TYPE,

     PE_UNEXPECTED_CONDITION_TYPE,

     PE_EXPECTED_INTEGER_TERM_TYPE, 
     PE_EXPECTED_LONG_LONG_TERM_TYPE, 
     PE_EXPECTED_INT_ARRAY_TERM_TYPE, 
     PE_EXPECTED_FLOAT_TERM_TYPE, 
     PE_EXPECTED_FLOAT_ARRAY_TERM_TYPE, 
     PE_EXPECTED_ATOM_TERM_TYPE, 
     PE_EXPECTED_LISP_LIST_TERM_TYPE, 
     PE_EXPECTED_VARIABLE_TERM_TYPE,
     PE_EXPECTED_LENV_TERM_TYPE,
     PE_EXPECTED_GTEXPRESSION_TERM_TYPE,
     PE_EXPECTED_GEXPRESSION_TERM_TYPE,
     PE_EXPECTED_INTENTION_TERM_TYPE,
     PE_EXPECTED_OP_INSTANCE_TERM_TYPE,
     PE_EXPECTED_FACT_TERM_TYPE,
     PE_EXPECTED_GOAL_TERM_TYPE,
     PE_EXPECTED_U_POINTER_TERM_TYPE,
     PE_EXPECTED_C_LIST_TERM_TYPE,
     PE_EXPECTED_EXPRESSION_TERM_TYPE,
     PE_EXPECTED_STRING_TERM_TYPE,

     PE_OUT_OF_BOUND_ARRAY_ACCES,

     PE_DEAD_INTENTION,
     PE_CAR_FROM_EMPTY_LISP_LIST,

     PE_UNREGISTERED_ERROR
} Oprs_Error;

#endif /* INCLUDE_oprs_error */
