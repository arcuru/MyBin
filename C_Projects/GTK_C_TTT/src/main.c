#include <gtk-2.0/gtk/gtk.h>

#define GUI_XML_FILE	"ui/ttt.glade"
#define SELECT_XML_FILE	"ui/game_select.glade"
#define RESULTS_XML_FILE	"ui/game_results.glade"
#define X_IMG_FILE
#define O_IMG_FILE
#define DEFAULT_WINDOW_WIDTH	400
#define DEFAULT_WINDOW_HEIGHT	400
#define TTT_INDEX(r,c)	(((r)*3)+c)

gint first_turn = 1;
gint gArray[10];

typedef struct {
	GtkWindow *window;
	GtkWindow *extrawindow;
	GtkButton **button_list;
	gint* list; //1 is player 1, 2 is player 2, 0 is unused
	GtkWidget *x_img;
	GtkWidget *o_img;
	gint turn; //1 is player 1, 2 is player 2
	gint winner;
	GtkStatusbar *statusbar;
	gboolean AI;
	gboolean gridlocked;
} TTTData;

void new_game(TTTData *data);
void new_game_click(GtkButton *button, TTTData *data);
void on_close_clicked(GtkButton *button, TTTData *data);
gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event,
		TTTData *data);
void on_window_destroy(GtkObject *object, TTTData *data);
void on_grid_clicked(GtkButton *button, TTTData *data);
void AI_move(TTTData *data);
gint* winning_moves(gint player, gint* gridlist);
gint end_of_game(gint* gridlist);
void game_complete(TTTData *data);

int main(int argc, char** argv) {

	GtkBuilder *builder;
	TTTData *data;

	data = g_slice_new(TTTData);
	data->button_list = (GtkButton**) g_malloc(sizeof(GtkButton*) * 9);
	data->list = (gint*) g_malloc(sizeof(gint) * 9);

	gtk_init(&argc, &argv);

	//data->x_img = gtk_image_new_from_file(X_IMG_FILE);
	//data->o_img = gtk_image_new_from_file(O_IMG_FILE);
	builder = gtk_builder_new();

	gtk_builder_add_from_file(builder, GUI_XML_FILE, NULL);
	data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
	char str1[] = "grid0";
	int i;
	for (i=0;i<=8;i++) {
		data->button_list[i] = GTK_BUTTON(gtk_builder_get_object(builder, str1));
		str1[4]++;
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
	data->gridlocked = TRUE;
	gtk_widget_show(GTK_WIDGET(data->window));
	g_object_unref(G_OBJECT(builder));
	new_game(data);
	gtk_main();
	return 0;
}

void new_game(TTTData *data) {
	GtkBuilder *builder;
	data->gridlocked = TRUE;
	data->AI = FALSE;
	first_turn=1;
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, SELECT_XML_FILE, NULL);
	data->extrawindow = GTK_WINDOW(gtk_builder_get_object(builder,
			"select_game"));
	gtk_builder_connect_signals(builder, data);
	gtk_widget_show(GTK_WIDGET(data->extrawindow));
	g_object_unref(G_OBJECT(builder));
	return;
}
void next_match(TTTData *data) {
	//Set tictactoe playing field to blank
	int n;
	for (n = 0; n < 9; n++) {
		data->list[n] = 0;
		//gtk_button_set_image(data->button_list[n], NULL);
		gtk_button_set_label(data->button_list[n], (const gchar*) "");
		gtk_button_set_relief(data->button_list[n], GTK_RELIEF_NORMAL);
	}
	data->turn = first_turn;//set first turn player
	if (data->turn == 1)
		gtk_statusbar_push(data->statusbar, 1, "Player 1");
	else {
		if (data->AI == TRUE) {
			gtk_statusbar_push(data->statusbar, 1, "Computer AI");
			AI_move(data);
		} else {
			gtk_statusbar_push(data->statusbar, 1, "Player 2");
		}
	}

}

void new_game_click(GtkButton *button, TTTData *data) {
	gtk_widget_destroy(GTK_WIDGET(data->extrawindow));
	next_match(data);
	return;
}

void on_close_clicked(GtkButton *button, TTTData *data) {
	gtk_widget_destroy(GTK_WIDGET(data->extrawindow));
	return;
}
void on_start_clicked(GtkButton *button, TTTData *data) {
	gtk_widget_destroy(GTK_WIDGET(data->extrawindow));
	data->gridlocked = FALSE;
	next_match(data);
	return;
}

gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event,
		TTTData *data) {
	//gtk_main_quit();
	return FALSE; //Propagate event
}

void on_window_destroy(GtkObject *object, TTTData *data) {
	gtk_main_quit();
	return;
}

void on_one_player_toggled(GtkItem *item, TTTData *data) {
	data->AI = !(data->AI);
	return;
}

void AI_move(TTTData *data) {
	data->gridlocked = TRUE;
	if (winning_moves(2, data->list)[0] != 10) {
		data->gridlocked = FALSE;
		on_grid_clicked(data->button_list[winning_moves(2, data->list)[0]],
				data);
	} else if (winning_moves(1, data->list)[0] != 10) {
		data->gridlocked = FALSE;
		on_grid_clicked(data->button_list[winning_moves(1, data->list)[0]],
				data);
	} else {
		gint a;
		for (a = 0; a < 9; a++) {
			if (data->list[a] == 0) {
				data->gridlocked = FALSE;
				on_grid_clicked(data->button_list[a], data);
				return;
			}
		}
	}
	return;
}

void on_grid_clicked(GtkButton *button, TTTData *data) {
	//GtkWidget *image = gtk_button_get_image(button);
	//if (data->gridlocked == TRUE)
	//return;
	if (end_of_game(data->list) > 0) {
		game_complete(data);
		return;
	}
	gint n;
	for (n = 0; n < 9; n++) { //determine which position was clicked
		if (data->button_list[n] == button) {
			break;
		}
	}
	if (data->list[n] == 0) {
		data->list[n] = data->turn; //Mark list with current player
		if (data->turn == 1) { //display correct image
			//gtk_button_set_image(button, gtk_image_new_from_file(X_IMG_FILE));
			gtk_button_set_label(button, (const gchar*) "X");
		} else {
			//gtk_button_set_image(button, gtk_image_new_from_file(O_IMG_FILE));
			gtk_button_set_label(button, (const gchar*) "O");
		}
		gtk_button_set_relief(button, GTK_RELIEF_NONE);
		data->winner = end_of_game(data->list);
		if (data->winner > 0) {
			game_complete(data);
			return;
		}
		if (data->turn == 1) {
			data->turn = 2;
			gtk_statusbar_pop(data->statusbar, 1);
			if (data->AI == FALSE) {
				gtk_statusbar_push(data->statusbar, 1, "Player 2");
			} else {
				gtk_statusbar_push(data->statusbar, 1, "Computer AI");
				AI_move(data);
			}

		} else {
			data->turn = 1;
			gtk_statusbar_pop(data->statusbar, 1);
			gtk_statusbar_push(data->statusbar, 1, "Player 1");
		}
	}
	return;
}

//Where can player inputted win?
gint* winning_moves(gint player, gint* gridlist) {
	if (end_of_game(gridlist) != 0)
		return NULL;
	gint a, b, index = 0;
	gArray[0] = 10;
	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			if (gridlist[TTT_INDEX(a,b)] == 0) {
				gridlist[TTT_INDEX(a,b)] = player;
				if (end_of_game(gridlist) == player) {
					gArray[index++] = TTT_INDEX(a,b);
				}
				gridlist[TTT_INDEX(a,b)] = 0;
			}
		}
	}
	gArray[index] = 10;
	return gArray;
}
//0 is not done, 3 is cat game
gint end_of_game(gint* gridlist) {
	gint a, val1, val2, val3;
	for (a = 0; a < 3; a++) {
		val1 = gridlist[TTT_INDEX(a,0)];
		val2 = gridlist[TTT_INDEX(a,1)];
		val3 = gridlist[TTT_INDEX(a,2)];
		if ((val1 != 0) && (val1 == val2) && (val1 == val3)) {
			return val1;
		}
		val1 = gridlist[TTT_INDEX(0,a)];
		val2 = gridlist[TTT_INDEX(1,a)];
		val3 = gridlist[TTT_INDEX(2,a)];
		if ((val1 != 0) && (val1 == val2) && (val1 == val3)) {
			return val1;
		}
	}
	val1 = gridlist[TTT_INDEX(0,0)];
	val2 = gridlist[TTT_INDEX(1,1)];
	val3 = gridlist[TTT_INDEX(2,2)];
	if ((val1 != 0) && (val1 == val2) && (val1 == val3)) {
		return val1;
	}
	val1 = gridlist[TTT_INDEX(0,2)];
	val2 = gridlist[TTT_INDEX(1,1)];
	val3 = gridlist[TTT_INDEX(2,0)];
	if ((val1 != 0) && (val1 == val2) && (val1 == val3)) {
		return val1;
	}
	for (a = 0; a < 9; a++)
		if (gridlist[a] == 0)
			return 0;
	return 3;
}

void game_complete(TTTData *data) {
	data->gridlocked = TRUE;
	if (first_turn == 1)
		first_turn = 2;
	else
		first_turn = 1;

	GtkBuilder *builder;
	gchar *tmpstr = (gchar*) g_malloc(sizeof(char) * 20);
	gulong q = 20;

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, RESULTS_XML_FILE, NULL);
	data->extrawindow = GTK_WINDOW(gtk_builder_get_object(builder,
			"dialog_window"));
	if (data->winner == 3)
		g_snprintf(tmpstr, q, "Nobody Wins");
	else
		g_snprintf(tmpstr, q, "Player %d Wins!", data->turn);
	gtk_label_set_label(GTK_LABEL(
			gtk_builder_get_object(builder, "result_view")), tmpstr);
	gtk_builder_connect_signals(builder, data);
	gtk_widget_show(GTK_WIDGET(data->extrawindow));
	g_object_unref(G_OBJECT(builder));
	return;
}
