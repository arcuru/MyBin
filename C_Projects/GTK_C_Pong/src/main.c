#include "main.h"
#include <stdio.h>
#include <sys/time.h>
#include "callback.h"

#define DISPLAY_HEIGHT	500
#define DISPLAY_WIDTH	500
//#define DEBUG

typedef struct paddle_struct {
    gint x;
    gint y;
    gint width;
    gint height;
    gint speed;
} paddles;

typedef struct ball_struct {
    gint x; //position in pixmap of src ball
    gint y;
    gint width; //size of src image (just the ball)
    gint height;
    gint dx; //movement speed
    gint dy;
    gint xsrc; //corner of actual ball in src
    gint ysrc;
} balls;

paddles *paddle;
balls *ball;

GtkWidget *window = NULL;
GdkPixmap *pixmap = NULL;
GtkWidget *draw = NULL;
static GdkGC *black = NULL;
static GdkGC *white = NULL;
static GdkPixbuf *ballimage = NULL;

gboolean checkPos();
void DrawBall(gboolean);
void DrawPaddle(gboolean);
void Fill(GdkGC*, gint x, gint y, gint width, gint height);

//Original written by Professor George Riley for his class
//CS 1372 at GT Fall 2008
//Generates pseudorandom value between minimum & maximum

gint UniformRandom(gint minimum, gint maximum) {
    // Choose a uniform random value
    static gboolean seeded = FALSE;
    static unsigned long heuristic_sequence = 0;
    if (!seeded) { // Seed the random number generator with time of day
        struct timeval tv;
        gettimeofday(&tv, 0);
        heuristic_sequence++; // Always make sure different than last time.
        gint seed = (tv.tv_sec ^ tv.tv_usec ^ (heuristic_sequence << 8))
                & 0x7fffffff;
        srand48(seed);
        seeded = TRUE;
    }
    gdouble r = drand48();
    return (minimum + r * (maximum - minimum));
}

//#define IMAGE_INDEX(initial,x,y,rowstride,n_channels)	((initial)+(y)*(rowstride)+(x)*(n_channels))

void BallInfo() {
    gint width, height, rowstride, n_channels;
    guchar *pixels, *p;
    n_channels = gdk_pixbuf_get_n_channels(ballimage);
    g_assert(gdk_pixbuf_get_colorspace(ballimage) == GDK_COLORSPACE_RGB);
    g_assert(gdk_pixbuf_get_bits_per_sample(ballimage) == 8);
    width = gdk_pixbuf_get_width(ballimage);
    height = gdk_pixbuf_get_height(ballimage);
    rowstride = gdk_pixbuf_get_rowstride(ballimage);
    pixels = gdk_pixbuf_get_pixels(ballimage);
    gint x, y;
    ball->xsrc = width;
    ball->ysrc = height;
    ball->width = 0;
    ball->height = 0;
    for (x = 0; x < width; ++x) {
        for (y = 0; y < height; ++y) {
            p = pixels + y * rowstride + x * n_channels;
            if ((p[0] != 255) && (p[1] != 255) & (p[2] != 255)) {
                if (x < ball->xsrc)
                    ball->xsrc = x;
                if (y < ball->ysrc)
                    ball->ysrc = y;
                if (x - ball->xsrc > ball->width)
                    ball->width = x - ball->xsrc;
                if (y - ball->ysrc > ball->height)
                    ball->height = y - ball->ysrc;
            }
        }
    }
    //Correct for width & height need for inclusiveness
    ++ball->width;
    ++ball->height;
    return;
}

gint main(gint argc, char** argv) {
    gtk_init(&argc, &argv);
    ball = g_slice_new(balls);
    paddle = g_slice_new(paddles);
    white = g_slice_new(GdkGC);
    black = g_slice_new(GdkGC);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Pong");

    draw = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), draw);
    InitCallback();
    gtk_widget_show_all(window);

    pixmap = gdk_pixmap_new(draw->window, draw->allocation.width,
            draw->allocation.height, -1);

    black = draw->style->black_gc;
    white = draw->style->white_gc;

    GtkWidget *ballimagetmp = gtk_image_new_from_file("data/chromium.png");
    ballimage = gtk_image_get_pixbuf(GTK_IMAGE(ballimagetmp));
    BallInfo();

    paddle->width = 100;
    paddle->height = 10;
    paddle->y = DISPLAY_HEIGHT - paddle->height;
    paddle->x = (DISPLAY_WIDTH / 2) - (paddle->width / 2);
    paddle->speed = paddle->width / 2;

    if (DISPLAY_WIDTH < paddle->width) {
        printf("Paddle too big");
        return 2;
    }
    if (DISPLAY_WIDTH < ball->width) {
        printf("Ball too big");
        return 2;
    }
    if (DISPLAY_HEIGHT < paddle->height + ball->height) {
        printf("Height of paddle and ball too big");
        return 2;
    }

    ball->x = UniformRandom(0, DISPLAY_WIDTH - ball->width); //Initial position
    ball->y = UniformRandom(0, (DISPLAY_HEIGHT - ball->height - paddle->height)
            / 2);
    ball->dx = UniformRandom(3, 7); //Initial speed/direction of travel
    ball->dy = UniformRandom(3, 7);
    if (UniformRandom(1, 2) == 1)//Allow negative values initially
        ball->dx *= -1;
    if (UniformRandom(1, 2) == 1)
        ball->dy *= -1;

    Fill(white, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    DrawPaddle(TRUE);
    DrawBall(TRUE);

#ifdef DEBUG
    ball->dx = 0;
    ball->dy = 0;
#else
    for (g_usleep(2 * G_USEC_PER_SEC); g_main_context_iteration(NULL, 0);)
        ;
#endif
    while (TRUE) {
        DrawBall(FALSE);
        gint i;
        for (i = 0; i < ABS(ball->dx) || i < ABS(ball->dy); ++i) {//Move ball
            if (i < ABS(ball->dx)) {
                ball->x += ABS(ball->dx) / ball->dx;
                if (!checkPos()) {
                    ball->dx *= -1;
                    ball->x += 2 * ABS(ball->dx) / ball->dx;
                }
            }
            if (i < ABS(ball->dy)) {
                ball->y += ABS(ball->dy) / ball->dy;
                if (!checkPos()) {
                    ball->dy *= -1;
                    ball->y += 2 * ABS(ball->dy) / ball->dy;
                }
            }
        }
        DrawBall(TRUE);
        for (g_usleep(20000); g_main_context_iteration(NULL, 0);)
            ;
    }
    return 0;
}

//Fill in a rectangle with given dimensions and color

void Fill(GdkGC *color, gint x, gint y, gint width, gint height) {
    gdk_draw_rectangle(pixmap, color, TRUE, x, y, width, height);
    gtk_widget_queue_draw_area(draw, x, y, width, height);
}

//Draw ball
//true to draw, false to erase

void DrawBall(gboolean set) {
    if (set == TRUE)
        gdk_draw_pixbuf(pixmap, NULL, ballimage, ball->xsrc, ball->ysrc,
            ball->x, ball->y, ball->width, ball->height,
            GDK_RGB_DITHER_NORMAL, 0, 0);
    else
        Fill(white, ball->x, ball->y, ball->width, ball->height);
    gtk_widget_queue_draw_area(draw, ball->x, ball->y, ball->width,
            ball->height);
}

void PaddleCollision(gboolean set) {
    static gint score = 0;
    if (set) {
        score += ABS(ball->dx) + ABS(ball->dy); //Adds to score based on speed of ball
        ball->dx += ABS(ball->dx) / ball->dx; //Speed up
        ball->dy += ABS(ball->dy) / ball->dy; //Changes direction of ball slightly
        printf("Score: %d\n", score);
    } else {
        printf("Final Score: %d\n", score);
        exit(0);
    }
    return;
}

//Did the ball hit anything?

gboolean checkPos() {
    if ((ball->x + ball->width >= DISPLAY_WIDTH) || (ball->x <= 0) || (ball->y
            <= 0)) {
        return FALSE;
    } else if (ball->y + ball->height >= paddle->y) {
        if (DISPLAY_WIDTH - paddle->x < paddle->width) {//paddle is wrapped around
            if (ball->x <= paddle->x + paddle->width - DISPLAY_WIDTH) {
                PaddleCollision(TRUE);
                return FALSE;
            }
        }
        if (((ball->x >= paddle->x) && (ball->x <= paddle->x + paddle->width))
                || ((ball->x + ball->width >= paddle->x) && (ball->x
                + ball->width <= paddle->x + paddle->width))) {//Ball hit the paddle
            PaddleCollision(TRUE);
            return FALSE;
        }
        PaddleCollision(FALSE);
    }
    return TRUE;
}

//Draws or removes entire paddle from show
//Set=true to draw, false to remove

void DrawPaddle(gboolean set) {
    if (set == TRUE) {
        if (DISPLAY_WIDTH - paddle->x < paddle->width) {
            Fill(black, paddle->x, paddle->y, DISPLAY_WIDTH - paddle->x,
                    paddle->height);
            Fill(black, 0, paddle->y, paddle->width - (DISPLAY_WIDTH
                    - paddle->x), paddle->height);
        } else
            Fill(black, paddle->x, paddle->y, paddle->width, paddle->height);
    } else {
        if (DISPLAY_WIDTH - paddle->x < paddle->width) {
            Fill(white, paddle->x, paddle->y, DISPLAY_WIDTH - paddle->x,
                    paddle->height);
            Fill(white, 0, paddle->y, paddle->width - (DISPLAY_WIDTH
                    - paddle->x), paddle->height);
        } else
            Fill(white, paddle->x, paddle->y, paddle->width, paddle->height);
    }
    return;
}

//Move paddle based on keystroke

void movePaddle(gint direction) {
    DrawPaddle(FALSE);
    paddle->x += paddle->speed * direction;
    while (paddle->x < 0) //Keep 0 < paddle->x < DISPLAY_WIDTH
        paddle->x += DISPLAY_WIDTH;
    while (paddle->x > DISPLAY_WIDTH)
        paddle->x -= DISPLAY_WIDTH;
    DrawPaddle(TRUE);
}
