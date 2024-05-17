#include "clean_room.h"

void draw_motor(cairo_t *cr, int flag) {
    cairo_set_line_width(cr, 5);
    // Draw the motor blades
    if (flag == 0)
        cairo_set_source_rgb(cr, 0.0, 0.0, 1.0); // Set the color to blue
    else
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Set the color to blue
    for (int i = 0; i < 3; i++) {
        cairo_move_to(cr, 0, 0);
        cairo_line_to(cr, 100, 0);
        cairo_rotate(cr, 2 * M_PI / 3); // Rotate 120 degrees
    }
    cairo_stroke(cr);
}

void draw_text(cairo_t *cr, double x, double y, const char* text) {
    // Position the text above the motor without rotation effect
    cairo_move_to(cr, x - 25, y - 120); // Adjust the text position
    cairo_set_font_size(cr, 20);
    cairo_show_text(cr, text); // Draw the text
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    guint width, height;
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    width = allocation.width;
    height = allocation.height; // Use the full height for drawing.
    // Draw the first motor on the left
    cairo_save(cr);
    cairo_translate(cr, width / 4, height / 2);
    cairo_rotate(cr, angle1);
    draw_motor(cr, 0);
    cairo_restore(cr);
    // Draw the "클린" text separately to avoid rotation
    draw_text(cr, width / 4, height / 2, "clean");
    // Draw the second motor on the right
    cairo_save(cr);
    cairo_translate(cr, 3 * width / 4, height / 2);
    cairo_rotate(cr, angle2);
    draw_motor(cr, 1);
    cairo_restore(cr);
    // Draw the "배기" text separately to avoid rotation
    draw_text(cr, 3 * width / 4, height / 2, "exhaust");
    return FALSE;
}

gboolean time_handler(GtkWidget *widget)
{
    if (data.motor1)
    {
        angle1 += 0.1;
        if (angle1 > 2 * M_PI) angle1 = 0;
    }
    if (data.motor2)
    {
        angle2 += 0.1;
        if (angle2 > 2 * M_PI) angle2 = 0;
    }
    if (data.motor1 || data.motor2)
        gtk_widget_queue_draw(widget);
    usleep(100);
    return TRUE;
}

void on_window_destroy(GtkWidget *widget, gpointer data)
{
    if (!data.status)
        gtk_main_quit();
}

void	thread_function(void *temp)
{
	GtkWidget   *window;
    GtkWidget   *darea;

    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    // g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    g_timeout_add(50, (GSourceFunc)time_handler, (gpointer)window);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 300); // Adjusted for wider layout
    gtk_window_set_title(GTK_WINDOW(window), "Motor Rotation Simulation");
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
