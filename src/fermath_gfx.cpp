/* (C) Programmed by:
   Antonio Jimenez Martínez
   Andrés Ortiz Corrales
   Mariano Palomo Villafranca
*/
/*
Fermath Project: graphic interface fermath
Version:1.1
*/
#include <gtk/gtk.h>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <stack>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <sstream>
using namespace std;
#include "include/expression.h"
#include "include/conversion.h"
#include "include/gfx.h"

const data_src *src;
//muestra cadena en el label
void fermath_calculate(GtkWidget *widget, GtkEntry *entry) {
    string strin2(gtk_entry_get_text(entry));
    string strin;
    string strout;
    for(unsigned int i=0; i<strin2.size(); i++) {
        if(strin2[i]!=32)	strin.push_back(strin2[i]);
    }
    if(strin.empty()==false) {
        strout=calculate_expression(strin,*src);
        gtk_label_set_text(GTK_LABEL(label), strout.c_str());//escribe en label el valor de buf
        //cout<<cadena<<endl;
    }
}



int main(int argc, char **argv) {
    data_src database;
    ifstream input("database.fermath");
    database.read(input);
    input.close();
    src=&database;
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
    gtk_window_set_title(GTK_WINDOW(window), "Fermath");//le ponemos un titulo a la ventana
    frame = gtk_fixed_new();//creamos un panel
    gtk_container_add(GTK_CONTAINER(window), frame);//añadimos el panel a la ventana
    //creamos el menu
    menubar = gtk_menu_bar_new();//creamos el menus
    filemenu = gtk_menu_new();//creamos el 1º apartado menu
    file = gtk_menu_item_new_with_label("Menu");
    quit = gtk_menu_item_new_with_label("Salir");
    font = gtk_menu_item_new_with_label("Formato");
    binfo = gtk_menu_item_new_with_label("Informacion");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), font);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), binfo);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_fixed_put(GTK_FIXED(frame),menubar,0,0);
    //creamos el menu
    calcular = gtk_button_new_with_label("Calcular");//creamos el boton escribe
    gtk_widget_set_size_request(calcular, 80, 35);//determinamso el tamaño del boton escribe
    gtk_fixed_put(GTK_FIXED(frame), calcular, 50, 100);//situamos el boton en la ventana
    label1 = gtk_label_new("Escriba expresion: ");//creamos una etiqueta con el numero 0
    gtk_fixed_put(GTK_FIXED(frame), label1, 50, 50);//situamos la etiqueta en la ventana
    label = gtk_label_new("0");//creamos una etiqueta con el numero 0
    gtk_fixed_put(GTK_FIXED(frame), label, 250, 100);//situamos la etiqueta en la ventana
    entry1 = gtk_entry_new();//creamos una entiqueta para introducir texto
    gtk_fixed_put(GTK_FIXED(frame), entry1, 250,50);//situamos la etiqueta en la ventana
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf(icon));//pone de icono de la ventana la foto "logo.ico"
    gtk_widget_show_all(window);//mostrmaos la ventana
    g_signal_connect(G_OBJECT(font), "activate", G_CALLBACK(select_font), label);
    //cuando le damos al boton font, accedemos a una ventna para cmabiar el formato
    g_signal_connect(G_OBJECT(binfo),  "activate",G_CALLBACK(show_about), (gpointer) window);
    //cuando le damos al boton binfo, accedemos a una ventna que nos muestra información sobre el sistema.
    g_signal_connect(entry1, "activate",G_CALLBACK(fermath_calculate),entry1);
    //utilizamos dos señales para que se muestre en la etiqueta:
    //hacer enter en la escritura
    //hacer click en el boton
    g_signal_connect(calcular, "clicked",G_CALLBACK(fermath_calculate), entry1);
    //conectamos la funcion mostrar_formula con el boton MOSTRAR.
    g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
    //cuando le damos a x se cierra el programa.
    g_signal_connect(G_OBJECT(quit), "activate",G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();//la aplicación entra en un main loop
    return 0;
}

