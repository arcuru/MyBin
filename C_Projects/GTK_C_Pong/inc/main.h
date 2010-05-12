#ifndef MAIN_H_
#define MAIN_H_

#include <gtk-2.0/gtk/gtk.h>
#include <gtk-2.0/gdk/gdkkeysyms.h>
#include <stdlib.h>

extern GtkWidget *window;
extern GdkPixmap *pixmap;
extern GtkWidget *draw;

void movePaddle(gint);

#endif /* MAIN_H_ */
