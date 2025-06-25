#include <gtk/gtk.h>
#include <adwaita.h>

struct log_click_event_data_t
{
  GtkWidget
    *window,
    *label
  ;
};

static void
log_click_event (GtkWidget * /*widget*/,
                 gpointer data )
{
  static int i = 0;
  
  struct log_click_event_data_t
    *log_click_event_data = data;
  
  GtkWidget
    *window = log_click_event_data->window,
    *label = log_click_event_data->label;

  g_autofree gchar* label_text = g_strdup_printf( "Press count : %d", ++i+1);

  gtk_label_set_text ( GTK_LABEL (label), label_text );

  if (i > 14)
    gtk_window_destroy( GTK_WINDOW (window) );

}

static void
activate (GtkApplication *app,
          gpointer        /*user_data*/)
{
  GtkWidget *window,
            *box,
            *label,
            *button;

  g_autofree GString* press_count_label_text;

  press_count_label_text = g_string_new ("Press count : 1");

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window),
                        "Window");
                        
  gtk_window_set_default_size (GTK_WINDOW (window),
                               1600,
                               900);

  gtk_window_present (GTK_WINDOW (window));

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL,
                     0);

  gtk_widget_set_halign (box,
                         GTK_ALIGN_CENTER);

  gtk_widget_set_valign (box,
                         GTK_ALIGN_CENTER);

  button = gtk_button_new_with_label ( "Press me!" );
  gtk_box_append (GTK_BOX (box),
                  button);

  label = gtk_label_new (press_count_label_text->str);
  gtk_widget_set_halign (box,
                         GTK_ALIGN_CENTER);

  gtk_widget_set_valign (box,
                         GTK_ALIGN_CENTER);

  gtk_box_append (GTK_BOX (box),
                  label);
  
  gtk_window_set_child (GTK_WINDOW (window),
                        box);

  static struct log_click_event_data_t
  log_click_event_data[1];

  log_click_event_data->label  = label;
  log_click_event_data->window = window;

  g_signal_connect (button,
                     "clicked",
                     G_CALLBACK (log_click_event),
                     log_click_event_data);

  gtk_window_present (GTK_WINDOW (window));

}

int
main (int   argc,
      char *argv[])
{
  g_autoptr (AdwApplication) app = NULL;
  int status;

  app = adw_application_new ("uk.ginix.pheasant",
                             G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect (app,
                    "activate",
                    G_CALLBACK (activate),
                    NULL);

  status = g_application_run (G_APPLICATION (app),
                              argc,
                              argv);

  g_object_unref (app);

  return status;
}
