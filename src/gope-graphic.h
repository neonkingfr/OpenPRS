/*                               -*- Mode: C -*-
 * ope-graphic.h -- Defines some constants and structure for the op-editor.
 *
 * Copyright (c) 1991-2013 Francois Felix Ingrand, LAAS/CNRS.
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

#ifndef INCLUDE_ope_graphic
#define INCLUDE_ope_graphic

/* #include "constant.h" */
/* #include "opaque.h" */
/* #include "op-structure.h" */

/* Some values and fraction of Pi. */
#ifndef M_PI
#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#define M_PI_4	0.78539816339744830962
#endif

#define MAX_NUMBER_LIGNES 64 /* I do not know... */

#define OP_TITLE_X 2;
#define OP_TITLE_Y 2;

/* Default size of the work area */
#define WORK_HEIGHT 1000
#define WORK_WIDTH 1500

/* Default Work font */
#define WORK_FONT "fixed"

/* Length in pixel of the arrow */
#define ARR_LENGTH 20

/* Angle of the arrow */
#define ARR_ANGLE (M_PI/12)

/* Maximum number of knots on one edge... */
#define MAX_KNOT 32

/* Size in pixel of the bounding box around a knot */
#define KNOT_SIZE 16

/* Number of pixels around text */
#define PIX_AROUND_TEXT 3
#define PIX_REGION_AROUND_OG 2

#define MAX3(a,b,c)     (((a) > (b)) ? (MAX(a,c)) : (MAX(b,c)))

#define EMPTY_STRING(s) ((s)[0]=='\0')

#define NOT_EMPTY_STRING(s) (!(EMPTY_STRING(s)))

typedef enum {XWD} DumpFormat;

/* Enumeration of the Drawing mode */
typedef enum {
     NOTHING = FALSE, DRAW_NODE, DRAW_EDGE, DRAW_KNOT, EDGE_SELECTED, NODE_SELECTED, EDIT_OG, DESTROY_OG, MOVE_OG,
     MOVING_OG, MOVING_CANVAS, CONVERT_END,  CONVERT_START, ALIGN_OG, ALIGNING_OG, DRAW_IFNODE,
     ALIGN_OG_V, ALIGNING_OG_V, ALIGN_OG_H, ALIGNING_OG_H, DUPLICATE_OBJECTS, DUPLICATING_NODE,
     DUPLICATING_EDGE, DUPLICATING_EDGE2, MERGE_NODE, MERGING_NODE, FLIP_SPLIT, FLIP_JOIN,
     OPEN_NODE, DM_RELEVANT_OP,
     MAX_DRAW_MODE
}    Draw_Mode;

extern PString mode_help[MAX_DRAW_MODE];

/* Enumeration of the Text Field type */
typedef enum {
  TT_INVOCATION, TT_CONTEXT, TT_CALL, TT_SETTING, TT_PROPERTIES, TT_DOCUMENTATION, TT_EFFECTS, TT_ACTION, TT_BODY, TT_TITLE, TT_TEXT_NONE
}    Text_Type;

typedef struct gnode {
     Node *node;
     gchar *xmstring;
     guint swidth, sheight;
} Gnode; /* Graphic Node structure */

typedef struct gknot {
     gint x, y;
     OG *edge;
} Gknot; /* Graphic Knot structure */

typedef Slist *List_Knot;

typedef struct gtext_string {
     gint off_x, off_y;
     gchar *xmstring;
} Gtext_String;
     
typedef Slist *List_Gtext_String;

typedef struct gedge_text {
     gint dx, dy;
     PString log_string;
     List_Gtext_String lgt_log_string;
     guint text_width;
     PBoolean fill_lines;
     OG *edge;
} Gedge_text; /* Graphic Edge Text structure */

typedef struct gtext {
     PString string;
     List_Gtext_String lgt_string;
     guint text_width;
     PBoolean fill_lines;
     PBoolean visible;
     Text_Type text_type;
     List_OG      	list_og_inst;
} Gtext; /* Graphic Text structure */

typedef struct gedge {
     Edge *edge;
     OG *text;
     gint x1, y1, x2, y2;
     gint fx1, fx2, fy1, fy2;
     List_Knot list_knot;
} Gedge; /*Graphic Edge structure */

typedef struct ginst {
     Instruction *inst;
     Edge *edge;        /* For X-Oprs */
     int num_line, nb_lines, indent, width; /* Temporay informations saved 
					       while pretty-printing the text body */
} Ginst; /* Graphic Instruction structure */

struct og {
  Draw_Type type;
  gint x, y;
  guint width, height;
  GdkRegion *region;
  PBoolean selected;
  union {
    Gnode *gnode;
    Gedge *gedge;
    Gedge_text *gedge_text;
    Gtext *gtext;
    Gknot *gknot;
    Ginst *ginst;
  }     u;
}; /* Object Graphic structure */

typedef struct copy_area_index {
     int top, left;
} Copy_Area_Index;

typedef struct cairo_gc {
  cairo_t *cr_basic;	
  cairo_t *cr_title;
  cairo_t *cr_edge;
  cairo_t *cr_node;
  cairo_t *cr_text;
} CairoGCs; 

struct draw_data {
  GtkWidget *topLevelWindow;
  GtkWidget *canvas;
  GdkDrawable *window;
  CairoGCs *cgcsp; 
  guint canvas_height;		  /* canvas dimensions     */
  guint canvas_width;
  guint work_height;
  guint work_width;
  int top;				  /* top */
  int left;				  /* left */
  
  guint start_x, start_y, last_x, last_y;
  int dx, dy;
  cairo_t *sgc;				  /* selected GC       */
  cairo_t *xorgc;				  /* xor GC       */
  PBoolean just_compiling;
  GtkWidget *vscrollbar;
  GtkWidget *hscrollbar;
  //void *font;			  /* The font struct       */
  //void *fontlist;
  Draw_Mode mode, old_mode;
  OG *edited_og;
  OG *node_selected;
  OG *second_node_selected;
  OG *edge_selected;
  OG *og_moving;
  OG *og_align;
  OG *og_aligning;
  OG *og_selected_on_press;
  OG *sensitive_og;
  GdkRegion *expose_region;
  Op_Structure *op;
  List_Knot list_knot;
  unsigned int pressed_button;
  Squeue *copy_area_index_queue;
};

typedef Slist *ListOPFile;

typedef Slist *ListOP;

typedef Slist *ListSymbol;

typedef enum {
     GRASPER_GRAPH, SUN_GRAPH, ACS_GRAPH
}    Opf_Type;

typedef struct {
     PString name;
     PString fname;
     PString dname;
     ListOP list_op;
     PBoolean modified;
     PBoolean filed;
     PBoolean backed_up;
     Opf_Type type;
     ListSymbol list_sym;
} OPFile;

typedef Slist *ListLastSelectedOP;

extern int node_x, node_y, visible , text_dx, text_dy, string_width, fill_lines;
extern Slist *edge_location;
extern Draw_Data *global_draw_data;
extern CairoGCs *opCGCsp;		/* this will be the one for the main */

#endif
