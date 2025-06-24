#include <gtk/gtk.h>

static void
log_click_event (GtkWidget *widget,
                 gpointer window )
{
  static int i = 0;

  g_print("Button was clicked! (%d)\n\r", i++);

  if (i > 14) {
    g_print("I has exceeded 14, closing!\n\r");

    gtk_window_destroy( GTK_WINDOW (window) );
  }

}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget
    *window,
    *box,
    *button
  ;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 1600, 900);
  gtk_window_present (GTK_WINDOW (window));

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_window_set_child ( GTK_WINDOW (window), box );

  button = gtk_button_new_with_label ( "Press me!" );

  g_signal_connect ( button, "clicked", G_CALLBACK (log_click_event), window );

  gtk_box_append( GTK_BOX (box), button);

  gtk_window_present ( GTK_WINDOW (window) );
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("uk.ginix.pheasant", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
