#include <gtk/gtk.h>
#include "Sudoku.h"

#define GUI_XML_FILE	"ui/main.glade"
#define DEFAULT_WINDOW_WIDTH	400
#define DEFAULT_WINDOW_HEIGHT	400

typedef struct {
	GtkWindow *window;
	GtkEntry **entry_list;
	GtkStatusbar *statusbar;
} SuData;
/*
 typedef struct {
 GtkRadioButton *one_player;
 GtkRadioButton *two_player;
 } SelectStruct;
 */

int main(int argc, char** argv) {

	GtkBuilder *builder;
	SuData *data;

	data = g_slice_new(SuData);
	data->entry_list = (GtkEntry**) g_malloc(sizeof(GtkEntry*) * 81);

	gtk_init(&argc, &argv);

	//data->x_img = gtk_image_new_from_file(X_IMG_FILE);
	//data->o_img = gtk_image_new_from_file(O_IMG_FILE);
	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder, GUI_XML_FILE, NULL);
	data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window1"));
	char str1[] = "entry0";
	int i;
	for (i = 0; i <= 80; i++) {
		data->entry_list[i] = GTK_WIDGET(gtk_builder_get_object(builder, str1));//This is incorrect, do string stuff with itoa() [ strcat("entry",itoa(i)) ]
		str1[5]++;
	}/*
	 data->button_list[0] = GTK_BUTTON(gtk_builder_get_object(builder, "grid0"));
	 data->button_list[1] = GTK_BUTTON(gtk_builder_get_object(builder, "grid1"));
	 data->button_list[2] = GTK_BUTTON(gtk_builder_get_object(builder, "grid2"));
	 data->button_list[3] = GTK_BUTTON(gtk_builder_get_object(builder, "grid3"));
	 data->button_list[4] = GTK_BUTTON(gtk_builder_get_object(builder, "grid4"));
	 data->button_list[5] = GTK_BUTTON(gtk_builder_get_object(builder, "grid5"));
	 data->button_list[6] = GTK_BUTTON(gtk_builder_get_object(builder, "grid6"));
	 data->button_list[7] = GTK_BUTTON(gtk_builder_get_object(builder, "grid7"));
	 data->button_list[8] = GTK_BUTTON(gtk_builder_get_object(builder, "grid8"));*/
	data->statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder,
			"statusbar1"));

	gtk_builder_connect_signals(builder, data);
	gtk_window_set_default_size(data->window, DEFAULT_WINDOW_WIDTH,
			DEFAULT_WINDOW_HEIGHT);
	gtk_widget_show(GTK_WIDGET(data->window));
	g_object_unref(G_OBJECT(builder));
	gtk_main();
	return 0;
}

void solve(SuData *data) {
	int* sudokuPuzzle = (gint*) g_malloc(sizeof(gint) * 81);
	gint i;
	for (i = 0; i < 81; i++) {
		const gchar* tmp = gtk_entry_get_text(data->entry_list[i]);
		sudokuPuzzle[i] = (int) tmp - '0';
		if (sudokuPuzzle[i] > 9) {
			gtk_entry_set_text(data->entry_list[0], "F");
		}
	}
	sudokuPuzzle = SudokuSolver(sudokuPuzzle);
	if (sudokuPuzzle != NULL) {
		gint i;
		for (i = 0; i < 81; i++) {
			gtk_entry_set_text(data->entry_list[i], (gchar*) '0'
					+ sudokuPuzzle[i]);
		}
	}
}
