#include "main.h"

static gint configure_event(GtkWidget *widget, GdkEventConfigure *event) {
    if (pixmap)
        gdk_pixmap_unref(pixmap);

    pixmap = gdk_pixmap_new(widget->window, widget->allocation.width,
            widget->allocation.height, -1);
    gdk_draw_rectangle(pixmap, widget->style->white_gc, TRUE, 0, 0,
            widget->allocation.width, widget->allocation.height);

    return TRUE;
}

static gint expose_event(GtkWidget *widget, GdkEventExpose *event) {
    gdk_draw_pixmap(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(
            widget)], pixmap, event->area.x, event->area.y, event->area.x,
            event->area.y, event->area.width, event->area.height);

    return FALSE;
}

static gint key_press_event(GtkWidget *widget, GdkEventKey *event) {
    switch (event->keyval) {
        case GDK_Left:
            movePaddle(-1);
            break;
        case GDK_Right:
            movePaddle(1);
            break;
    }
    return 1;
}

gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    //gtk_main_quit();
    return FALSE; //Propagate event
}

void on_window_destroy(GtkObject *object, gpointer data) {
    gtk_main_quit();
    exit(0);
}

gboolean InitCallback() {
    g_signal_connect(G_OBJECT(draw), "expose_event", G_CALLBACK(expose_event),
            NULL);
    g_signal_connect(G_OBJECT(draw), "configure_event", G_CALLBACK(
            configure_event), NULL);
    g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(
            key_press_event), NULL);
    g_signal_connect(G_OBJECT(window), "delete-event", GTK_SIGNAL_FUNC(
            on_window_delete_event), NULL);
    g_signal_connect(G_OBJECT(window), "destroy",
            GTK_SIGNAL_FUNC(on_window_destroy), NULL);
    return TRUE;
}
