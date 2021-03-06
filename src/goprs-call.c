/*                               -*- Mode: C -*- 
 * goprs-call.c -- 
 * 
 * Copyright (c) 1991-2012 Francois Felix Ingrand.
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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>

#include <gtk/gtk.h>
#include "xm2gtk.h"

#include "constant.h"

#include "macro.h"
#include "oprs-type.h"
#include "goprs-call_f.h"

#include "xm2gtk_f.h"

static gint	oprsInputId;		/* oprs input id */

extern char	*oprsprompt;

PBoolean debug_xoprs;

static PBoolean log_to_file = FALSE;
static int log_fd;

void bell(int volume)
{
/*    XBell(XtDisplay(toplevel), volume); */
}

/* append string s2 to end of string s1 and return the result */

char *concat(char *s1, char *s2)
{
    if (s2) {
        if (s1 == NULL) {
            s1 = XtMalloc((strlen(s2)+1)*sizeof(char));
            strcpy(s1, s2);
        }
        else {
            s1 = XtRealloc(s1, strlen(s1)+strlen(s2)+2);
            strcat(s1, s2);
        }
    }
    return (s1);
}
#include <sys/time.h>
#include <errno.h>
void read_oprs(gpointer master, gint source, GdkInputCondition ignore)
{
     char s[BUFSIZ];
     Widget textview = (Widget)master;

     size_t chars_read = BUFSIZ;
     
     while (chars_read == BUFSIZ){
       PROTECT_SYSCALL_FROM_EINTR(chars_read, read(source, s, BUFSIZ));
       if (chars_read == -1) {
	 perror("read-oprs: read");
	 return;
       }
     
       if (log_to_file) {
	 if (write(log_fd,s,chars_read) == -1)
	   perror("oprs-cat: log_file: write");
       }
       if (chars_read > 0) {
	 AppendTextWindow(textview, s, chars_read, FALSE);
       }
     }
}

void call_oprs_cat(char *log_file, Widget textview)
{				/* This version is much simpler... no need for an external program */
  int fds[2];
  
  if (pipe(fds) < 0)
    perror("call_oprs_cat:pipe");

  // Redirect fds[1] to be writed with the standard output.
  if( dup2(fds[1], STDOUT_FILENO) < 0)
    perror("call_oprs_cat:dup2");	/* Get stdout plug on sp[1] */
  
  if (log_file) {
    if ((log_fd = open(log_file,O_WRONLY | O_CREAT | O_TRUNC,0664)) == -1) {
      perror("call_oprs: open");
    } else {
      fprintf(stderr,"call_oprs: loging output in \"%s\".\n", log_file);
      log_to_file = TRUE;
    }
  }
  oprsInputId = gdk_input_add(fds[0], GDK_INPUT_READ, read_oprs, textview);
}

#ifdef IGNORE
void call_oprs_cat(char *log_file, Widget textview)
{
     int pid, sp[2];

     if (socketpair(AF_UNIX, SOCK_STREAM, 0, sp) < 0) {
	  perror("call_oprs: socketpair");
	  exit(1);
     }
     fcntl(sp[1], F_SETFD, 1);      /* this is to avoid that the ns will be dup when we fork */
     
     if ((pid = fork()) < 0) {
	  perror("fork");
	  exit(1);
     }

     if (pid) {			/* The father */
	  close(sp[0]);		/* Close one side */
	  fcntl(sp[1], F_SETFL, FNDELAY); /* I am not sure this is required... */
	  if (dup2(sp[1],1) < 0)
	       perror("call_oprs_cat:dup2");	/* Get stdout plug on sp[1] */

	  oprsInputId = gdk_input_add(sp[1],GDK_INPUT_READ, read_oprs, textview);
     } else {			/* The child */
	  char *argv[3];

	  close(sp[1]);
	  /* dup2(sp[1],2); */
	  fcntl(sp[0], F_SETFL, FNDELAY);
	  dup2(sp[0],1);
	  dup2(sp[0],0);

	  argv[0] = "oprs-cat";
	  if (log_file) {
	       argv[1] = log_file;
	       argv[2] = NULL;
	  } else 
	       argv[1] = NULL;

	  execvp(argv[0], argv);
	  perror("xoprs: cannot exec oprs-cat");
	  exit(2);
     }
}
#endif
