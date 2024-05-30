#include "clean_room.h"

static void draw_motor(cairo_t *cr, int flag)
{
    cairo_set_line_width(cr, 5);
    if (flag == 0)
        cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    else
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++)
    {
        cairo_move_to(cr, 0, 0);
        cairo_line_to(cr, 100, 0);
        cairo_rotate(cr, 2 * M_PI / 3);
    }
    cairo_stroke(cr);
}

static void draw_text(cairo_t *cr, double x, double y, const char* text)
{
    cairo_move_to(cr, x - 25, y - 120);
    cairo_set_font_size(cr, 20);
    cairo_show_text(cr, text);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    guint width, height;
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    width = allocation.width;
    height = allocation.height;
    cairo_save(cr);
    cairo_translate(cr, width / 4, height / 2);
    cairo_rotate(cr, angle1);
    draw_motor(cr, 0);
    cairo_restore(cr);
    draw_text(cr, width / 4, height / 2, "clean");
    cairo_save(cr);
    cairo_translate(cr, 3 * width / 4, height / 2);
    cairo_rotate(cr, angle2);
    draw_motor(cr, 1);
    cairo_restore(cr);
    draw_text(cr, 3 * width / 4, height / 2, "exhaust");
    return FALSE;
}

static gboolean time_handler(Data* data)
{
    if (data->motor1)
    {
        data->angle1 += 0.1;
        if (data->angle1 > 2 * M_PI)
            data->angle1 = 0;
    }
    if (data->motor2)
    {
        data->angle2 += 0.1;
        if (data->angle2 > 2 * M_PI)
            data->angle2 = 0;
    }
    if (data->motor1 || data->motor2)
        gtk_widget_queue_draw(data->widget);
    if (!data->status)
        gtk_main_quit();
    usleep(100);
    return TRUE;
}

void	thread_function(void *temp)
{
    Data        *data;

    data = (Data*)temp;
    // gtk_init(NULL, NULL);
    // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // darea = gtk_drawing_area_new();
    // gtk_container_add(GTK_CONTAINER(window), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    // g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    g_timeout_add(50, (GSourceFunc)time_handler, data);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 300);
    gtk_window_set_title(GTK_WINDOW(window), "Motor Rotation Simulation");
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
