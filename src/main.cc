
#include <iostream>
#include <string>
#include <gtkmm/main.h>
#include "engine.hh"
#include "main-window.hh"

int
main(int argc, char** argv)
{
    Gio::init();

    bool run_minimized = false;

    if (argc >= 2) {
        std::string first_arg(argv[1]);
        if (first_arg == "--minimized" || first_arg == "-M")
            run_minimized = true;
    }

    if (argc >= 2 && !run_minimized) {
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

        if (!run_minimized)
            main_window.show();

        Gtk::Main::run();
    }

    return 0;
}
