/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca*/
/*
Fermath Project: Graphic Functions
Version:1.0
*/

//Functions using gtk+ 2.0
#define icon "logo.ico"
#define logobw "logobw.jpg"



GtkWidget *label;//etiqueta para mostrar el texto. Tiene que se global, para que las funciones accedan a ella.

//funcion para cambiar el formato del texto de label
void select_font(GtkWidget *widget, gpointer label) {
    gint result;
    GtkWidget *dialog = gtk_font_selection_dialog_new("Select Font");
    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if(result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY) {
        PangoFontDescription *font_desc;
        gchar *fontname = gtk_font_selection_dialog_get_font_name(
                              GTK_FONT_SELECTION_DIALOG(dialog));
        font_desc = pango_font_description_from_string(fontname);
        gtk_widget_modify_font(GTK_WIDGET(label), font_desc);
        g_free(fontname);
    }
    gtk_widget_destroy(dialog);
}

//crea GdkPixbuf a partir de una foto para crear un icono.
GdkPixbuf *create_pixbuf(const gchar *filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    //crea una nueva pixbuf a partir del nombre de la imagen.
    if(!pixbuf) {// si el nombre de la imagen no existe genera un fallo
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

//genera una nueva ventana donde apaecera la información de la aplicación
void show_about(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(logobw, NULL);
    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"Fermath");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"1.0");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) Programmed by:\nAntonio Jimenez Martínez\nAndrés Ortiz Corrales\nMariano Palomo Villafranca  ");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Calculadora multifunción.");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),"https://github.com/fermathproject/fermath");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

