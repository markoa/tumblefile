
#include <iostream>
#include <gtkmm/main.h>
#include "engine.hh"
#include "main-window.hh"

int
main(int argc, char** argv)
{
    Gio::init();

    if (argc >= 2) {
        Glib::ustring todays_path = tf::engine::init_todays_dir();
        std::cout << "cd " << todays_path << std::endl;
        for (int i = 0; i < argc-1; ++i) {
            tf::engine::process_commandline_path(todays_path, argv[i+1]);
        }
    } else {
        Gtk::Main kit(argc, argv);
        tf::MainWindow main_window;
        // By not attaching window to run(), hiding the window will not
        // invoke Gtk::main::quit() automatically.
        main_window.show();
        Gtk::Main::run();
    }

    return 0;
}
