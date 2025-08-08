#include <gtk/gtk.h>

static GtkWidget *input;
static GtkWidget *output;
static GtkApplication *app_global;


static void process_img(GtkWidget *widget, gpointer user_data) {
	char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(input));

	if (filename) {
		char cmd[512];
		snprintf(cmd, sizeof(cmd), "cp \"%s\" /tmp/img", filename);
		system(cmd);
		system("tesseract /tmp/img - | wl-copy");
		
		GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
		gchar *text = gtk_clipboard_wait_for_text(cb);

		if (text != NULL) {
			gtk_label_set_text(GTK_LABEL(output),text);
		} else {
			gtk_label_set_text(GTK_LABEL(output),"Text not found in image");
		};

		g_free(text);
		g_free(filename);
	};
};

static void killapp(GtkWidget *widget, gpointer user_data) {
    g_application_quit(G_APPLICATION(app_global));
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkBuilder *builder;
	GtkWidget *window, *close;

	builder = gtk_builder_new_from_file("/usr/share/ocr-tool/ui.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));


	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "/usr/share/ocr-tool/style.css", NULL);
	gtk_style_context_add_provider_for_screen(
	    gdk_screen_get_default(),
	    GTK_STYLE_PROVIDER(provider),
	    GTK_STYLE_PROVIDER_PRIORITY_USER
	);
	g_object_unref(provider);

	gtk_window_set_application(GTK_WINDOW(window), app);
	gtk_widget_show_all(window);
	
	
	input = GTK_WIDGET(gtk_builder_get_object(builder, "input"));
	output = GTK_WIDGET(gtk_builder_get_object(builder, "output"));	
	close = GTK_WIDGET(gtk_builder_get_object(builder, "close"));

	
	g_signal_connect(input, "file-set", G_CALLBACK(process_img), input);	
	g_signal_connect(close, "clicked", G_CALLBACK(killapp), NULL);

};

int main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.ocr.com", G_APPLICATION_DEFAULT_FLAGS);
	app_global = app;
	g_signal_connect(app,"activate",G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
};
