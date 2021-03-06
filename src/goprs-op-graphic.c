
/*                               -*- Mode: C -*- 
 * xoprs-op-graphic.c -- 
 * 
 * Copyright (c) 1991-2011 Francois Felix Ingrand, LAAS/CNRS.
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


#include "config.h"

#include <stdio.h>
#include <math.h>

#include <string.h>

#include <gtk/gtk.h>
#include "xm2gtk.h"

#include "macro.h"

#include "oprs-type.h"
#include "op-structure.h"

#include "gope-graphic.h"
#include "ope-global.h"
#include "ope-edit_f.h"
#include "ope-graphic_f.h"
#include "ope-external_f.h"
#include "op-structure_f.h"

#include "xm2gtk_f.h"

void goprs_canvas_mouse_press(Widget w, Draw_Data *dd, CairoGCs *cgcsp, GdkEventButton *event)
{
  int button = event->button;
  
#ifdef GTK_IGNORE
     if (button == 3) {
	  OG *og;
	  int x = event->xbutton.x + dd->left;
	  int y = event->xbutton.y + dd->top;

	  sl_loop_through_slist(dd->op->list_og_edge_text, og, OG *)
	       if (XPointInRegion(og->region, x, y)) {
		    dd->og_selected_on_press = og;
		    draw_clip_box(w, dd, og);
		    dd->mode = DM_RELEVANT_OP;
		    return;
	       }
	  sl_loop_through_slist(dd->op->list_og_inst, og, OG *)
	       if (XPointInRegion(og->region, x, y)) {
		    dd->og_selected_on_press = og;
		    draw_clip_box(w, dd, og);
		    dd->mode = DM_RELEVANT_OP;
		    return;
	       }
	  if (XPointInRegion(dd->op->ginvocation->region, x, y)) {
	       dd->og_selected_on_press = dd->op->ginvocation;
	       draw_clip_box(w, dd, dd->op->ginvocation);
	       dd->mode = DM_RELEVANT_OP;
	       return;
	  }
	  if (XPointInRegion(dd->op->geffects->region, x, y)) {
	       dd->og_selected_on_press = dd->op->geffects;
	       draw_clip_box(w, dd, dd->op->geffects);
	       dd->mode = DM_RELEVANT_OP;
	       return;
	  }
     } else {
#endif
	  dd->start_x = event->x;
	  dd->start_y = event->y;
	  dd->mode = MOVING_CANVAS;
	  //     }
}

void goprs_canvas_mouse_motion(Widget w, Draw_Data *dd, CairoGCs *cgcsp, GdkEventMotion *event)
{
     if (dd->mode == MOVING_CANVAS) {
	  int dx, dy;
	  int x = event->x + dd->left;
	  int y = event->y + dd->top;

	  dx = x - dd->start_x;
	  dy = y - dd->start_y;
	  dd->start_x = x;
	  dd->start_y = y;
	  set_canvas_view_rel(dd, dx, dy);
     }
}

void goprs_canvas_mouse_release(Widget w, Draw_Data *dd, CairoGCs *cgcsp,  GdkEventButton *event)
{
     int button = event->button;
     
     // gtk     if (button != Button3) {
	  if (dd->mode == MOVING_CANVAS) {
	       int x = event->x;
	       int y = event->y;
	       int dx = x - dd->start_x;
	       int dy = y - dd->start_y;

	       set_canvas_view_rel(dd, dx, dy);
	  }
#ifdef IGNORE_GTK
     } else 
	  if (dd->mode == DM_RELEVANT_OP) {
	       int x = event->xbutton.x + dd->left;
	       int y = event->xbutton.y + dd->top;

	       if (dd->og_selected_on_press) {
		    draw_clip_box(w, dd, dd->og_selected_on_press);
		    if (XPointInRegion(dd->og_selected_on_press->region, x, y)) {
			 if(dd->og_selected_on_press->type == DT_EDGE_TEXT)
			      xp_find_rel_ops(dd->og_selected_on_press->u.gedge_text->edge->u.gedge->edge);
			 else if (dd->og_selected_on_press->type == DT_INST)
			      xp_find_rel_ops(dd->og_selected_on_press->u.ginst->edge);
			 else if(dd->og_selected_on_press->type == DT_TEXT)
			      if (dd->og_selected_on_press->u.gtext->text_type == TT_INVOCATION)
				   xp_find_rel_ops_expr_except_me(current_op->invocation, current_op);
/* 			      else if (dd->og_selected_on_press->u.gtext->text_type == TT_EFFECTS) */
/* 				   xp_find_rel_ops_list_expr(current_op->effects); */
			 else 
			      fprintf(stderr, LG_STR("This graphic type has no gtexpr.\n",
						     "This graphic type has no gtexpr.\n"));
		    }
		    dd->og_selected_on_press = NULL;
	       }
	  }
#endif
}

