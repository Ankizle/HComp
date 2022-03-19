#include <gtk/gtk.h>
#include <gdk/x11/gdkx.h>
#include <iostream>

#include <X11/Xlib.h>

#include "hcompx.h"

GtkWidget* window;
GtkWidget* layout;
GtkWidget* search;
GtkWidget* gobtn;

void search_enter(GtkWidget* wid, gpointer data) {
    GtkEntryBuffer* bufe = gtk_entry_get_buffer(GTK_ENTRY(search));
    char* uri = (char*) malloc(sizeof(char) * gtk_entry_buffer_get_length(bufe));
    strcpy(uri, gtk_entry_buffer_get_text(bufe));

    Window xID = gdk_x11_surface_get_xid(gtk_native_get_surface(GTK_NATIVE(window)));

    std::cout << xID << std::endl;

    //uri now stores the uri (hcomp uri) we're trying to visit
    // Window w = gdk_x11_surface_get_xid(GDK_SURFACE(window));
    openDisp(uri, xID);
    // openDisp(uri, XDefaultRootWindow(XOpenDisplay(0)));
}

static void activate(GtkApplication* app, gpointer user_data) {

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "HComp");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    
    layout = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_window_set_child(GTK_WINDOW(window), layout);
    
    search = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search), "Search...");
    gtk_box_append(GTK_BOX(layout),search);
    
    gobtn = gtk_button_new_with_label("Go");
    gtk_box_append(GTK_BOX(layout),gobtn);
    g_signal_connect(gobtn, "clicked", G_CALLBACK(search_enter), search);
    
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char** argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("hc.om.p", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}