#include <gtkmm.h>

int main(int argc, char** argv) {
	Gtk::Main kit(argc, argv);
	Gtk::Window window; 
	window.set_default_size(600, 400);
	window.set_title("Primeira interface grafica com GTK+");
	Gtk::Main::run(window); 
}

// Compile g++ simple.cpp -o simplex $(pkg-config gtk-3.0 --cflags --libs)
