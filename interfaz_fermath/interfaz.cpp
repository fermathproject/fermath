//compilar g++ -o interfaz interfaz.cpp `pkg-config --libs --cflags gtk+-2.0`
/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  
*/
/*
Fermath Project: interfaz.cpp
Version:0.1
*/
#include <gtk/gtk.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "entrada.h"


using namespace std;



//muestra cadena en el label
void mostrar_formula(GtkWidget *widget, gpointer label)//se le pasa plus y label
{
    const char * cadena;
    cadena=mostrar_cambiar();
    gtk_label_set_text(GTK_LABEL(label), cadena);//escribe en label el valor de buf
}

//funcion para cambiar el formato del texto de label
void select_font(GtkWidget *widget, gpointer label)
{
    gint result;
    GtkWidget *dialog = gtk_font_selection_dialog_new("Select Font");
    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY)
    {
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
GdkPixbuf *create_pixbuf(const gchar * filename)
{
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
void show_about(GtkWidget *widget, gpointer data)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("logo.jpg", NULL);
    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"Fermath");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(c) Antonio Jimenez");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Calculadora multifunción.");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),"https://github.com/fermathproject/fermath");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}


int main(int argc, char** argv) {

    GtkWidget *label;//etiqueta para mostrar el texto
    GtkWidget *window;//ventana principal
    GtkWidget *frame;//cremaos un planel con los diferentes botones
    GtkWidget *mostrar;//creamos un boton para mostrar la formula escrita
    GtkWidget *font;//cremaos un boton para modificar el formato
	GtkWidget *binfo;//creamos un boton para acceder a la información del sistema.


    gtk_init(&argc, &argv);//aqui se inicializa GTK+ lbrary

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creamos una GtkWindow widge
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//centramos la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);//determinamos el tamaño
    gtk_window_set_title(GTK_WINDOW(window), "fermath");//le ponemos un titulo a la ventana

    frame = gtk_fixed_new();//creamos un panel
    gtk_container_add(GTK_CONTAINER(window), frame);//añadimos el panel a la ventana

    mostrar = gtk_button_new_with_label("escribe");//creamos el boton escribe
    gtk_widget_set_size_request(mostrar, 80, 35);//determinamso el tamaño del boton escribe
    gtk_fixed_put(GTK_FIXED(frame), mostrar, 50, 50);//situamos el boton en la ventana



    font = gtk_button_new_with_label("formato");//creamos el boton del formato
    gtk_widget_set_size_request(font, 80, 35);//determinamso el tamaño del boton formato
    gtk_fixed_put(GTK_FIXED(frame), font, 50, 400);//situamos el boton en la ventana

	
	binfo = gtk_button_new_with_label("info");//creamos el boton info
    gtk_widget_set_size_request(binfo, 80, 35);//determinamso el tamaño del boton info
    gtk_fixed_put(GTK_FIXED(frame), binfo, 400, 400);//situamos el boton en la ventana

    label = gtk_label_new("0");//creamos una etiqueta con el numero 0
    gtk_fixed_put(GTK_FIXED(frame), label, 190, 58);//situamos la etiqueta en la ventana

    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("logo.jpg"));//pone de icono de la ventana la foto "logo.jpg"
    gtk_widget_show_all(window);//mostrmaos la ventana



    g_signal_connect(font, "clicked", G_CALLBACK(select_font), label);
	//cuando le damos al boton font, accedemos a una ventna para cmabiar el formato

	g_signal_connect(binfo, "clicked",G_CALLBACK(show_about), (gpointer) window);
	//cuando le damos al boton binfo, accedemos a una ventna que nos muestra información sobre el sistema.

    g_signal_connect(mostrar, "clicked",G_CALLBACK(mostrar_formula), label);
	//conectamos la funcion mostrar_formula con el boton MOSTRAR.

 	g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	//cuando le damos a x se cierra el programa.

    gtk_main();//la aplicación entra en un main loop


    return 0;
}
