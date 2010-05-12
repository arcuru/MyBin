#include <gtk/gtk.h>

static GdkPixmap *pixmap = NULL;

static gint configure_event(GtkWidget *widget, GdkEventConfigure *event) {
	if (pixmap)
		gdk_pixmap_unref(pixmap);

	pixmap = gdk_pixmap_new(widget->window, widget->allocation.width,
			widget->allocation.height, -1);
	gdk_draw_rectangle(pixmap, widget->style->white_gc, TRUE, 0, 0,
			widget->allocation.width, widget->allocation.height);

	return TRUE;
}
#include <stdio.h>
static gint expose_event(GtkWidget *widget, GdkEventExpose *event) {
	gdk_draw_pixmap(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(
			widget)], pixmap, event->area.x, event->area.y, event->area.x,
			event->area.y, event->area.width, event->area.height);

	return FALSE;
}

int main(int argc, char** argv) {

	GtkWidget *window, *draw;
	gtk_init(&argc,&argv);
	gint width = 512, height = 512;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window, width, height);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	draw = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), draw);
	g_signal_connect(G_OBJECT(draw), "expose_event", G_CALLBACK(expose_event),
			NULL);
	g_signal_connect(G_OBJECT(draw), "configure_event", G_CALLBACK(
			configure_event), NULL);
	gtk_widget_show_all(window); /* before creating pixmap, gc etc */

	//gtk_main();

	pixmap = gdk_pixmap_new(draw->window, draw->allocation.width,
			draw->allocation.height, -1);
	gdk_draw_rectangle(pixmap, draw->style->black_gc, TRUE, 0, 0, //draw all white
			draw->allocation.width, draw->allocation.height);
	//gdk_draw_drawable(draw->window, draw->style->fg_gc[GTK_WIDGET_STATE(draw)],
	//		pixmap, 0, 0, 0, 0, -1, -1);

	gtk_widget_queue_draw_area(draw, 0, 0, draw->allocation.width,
			draw->allocation.height);

	gtk_main();
	return 0;
}
