//compilar g++ -o interfaz interfaz.cpp `pkg-config --libs --cflags gtk+-2.0`
/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca  
*/
/*
Fermath Project: interfaz.cpp
Version:0.4
*/
#include <gtk/gtk.h>
#include <iostream>
#include <stdio.h>
#include <string>



using namespace std;

GtkWidget *label;//etiqueta para mostrar el texto. Tiene que se global, para que las funciones accedan a ella.

//muestra cadena en el label
void mostrar_formula(GtkWidget *widget, GtkEntry* entry)
{
    const char * cadena;
    cadena=gtk_entry_get_text(entry);
    gtk_label_set_text(GTK_LABEL(label), cadena);//escribe en label el valor de buf
    cout<<cadena<<endl;
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
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("logo.png", NULL);
    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog),"Fermath");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) Programmed by:\nAntonio Jimenez Martínez\nAndrés Ortiz Corrales\nMariano Palomo Villafranca  ");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Calculadora multifunción.");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),"https://github.com/fermathproject/fermath");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy(dialog);
}


int main(int argc, char** argv) {

    GtkWidget *label1;//etiqueta para mostrar el texto
    GtkWidget *window;//ventana principal
    GtkWidget *frame;//cremaos un planel con los diferentes botones
    GtkWidget *calcular;//creamos un boton para calcular
	GtkWidget *entry1;//entrada de texto

	GtkWidget *menubar;
  	GtkWidget *filemenu;
  	GtkWidget *file;
  	GtkWidget *quit;
	GtkWidget *font;
	GtkWidget *binfo;

    gtk_init(&argc, &argv);//aqui se inicializa GTK+ lbrary

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//creamos una GtkWindow widge
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);//centramos la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);//determinamos el tamaño
    gtk_window_set_title(GTK_WINDOW(window), "fermath");//le ponemos un titulo a la ventana

    frame = gtk_fixed_new();//creamos un panel
    gtk_container_add(GTK_CONTAINER(window), frame);//añadimos el panel a la ventana




	//creamos el menu
	menubar = gtk_menu_bar_new();//creamos el menus
  	filemenu = gtk_menu_new();//creamos el 1º apartado menu

  	file = gtk_menu_item_new_with_label("menu");
  	quit = gtk_menu_item_new_with_label("salir");
	font = gtk_menu_item_new_with_label("formato");
	binfo = gtk_menu_item_new_with_label("informacion");


  	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), font);
  	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), binfo);
  	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  	gtk_fixed_put(GTK_FIXED(frame),menubar,0,0);
	//creamos el menu
    calcular = gtk_button_new_with_label("calcular");//creamos el boton escribe
    gtk_widget_set_size_request(calcular, 80, 35);//determinamso el tamaño del boton escribe
    gtk_fixed_put(GTK_FIXED(frame), calcular, 50, 100);//situamos el boton en la ventana
	

	label1 = gtk_label_new("Escriba expresion: ");//creamos una etiqueta con el numero 0
    gtk_fixed_put(GTK_FIXED(frame), label1, 50, 50);//situamos la etiqueta en la ventana	


    label = gtk_label_new("0");//creamos una etiqueta con el numero 0
    gtk_fixed_put(GTK_FIXED(frame), label, 250, 100);//situamos la etiqueta en la ventana

	entry1 = gtk_entry_new();//creamos una entiqueta para introducir texto
	gtk_fixed_put(GTK_FIXED(frame), entry1, 250,50);//situamos la etiqueta en la ventana

    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("logo.ico"));//pone de icono de la ventana la foto "logo.ico"
    gtk_widget_show_all(window);//mostrmaos la ventana



    g_signal_connect(G_OBJECT(font), "activate", G_CALLBACK(select_font), label);
	//cuando le damos al boton font, accedemos a una ventna para cmabiar el formato

	g_signal_connect(G_OBJECT(binfo),  "activate",G_CALLBACK(show_about), (gpointer) window);
	//cuando le damos al boton binfo, accedemos a una ventna que nos muestra información sobre el sistema.

    g_signal_connect(entry1, "activate",G_CALLBACK(mostrar_formula),entry1);
	//utilizamos dos señales para que se muestre en la etiqueta:
	//hacer enter en la escritura
	//hacer click en el boton
    g_signal_connect(calcular, "clicked",G_CALLBACK(mostrar_formula), entry1);
    //conectamos la funcion mostrar_formula con el boton MOSTRAR.


 	g_signal_connect(window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	//cuando le damos a x se cierra el programa.
	
	g_signal_connect(G_OBJECT(quit), "activate",G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();//la aplicación entra en un main loop


    return 0;
}
