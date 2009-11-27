
#include <config.h>
#include <iostream>
#include <string>
#include <glib.h>
#include <glib/gi18n.h>
#include <gtkmm/main.h>
#include "engine.hh"
#include "main-window.hh"

int
main(int argc, char** argv)
{
    static gboolean show_version = FALSE;
    static gboolean run_minimized = FALSE;
    GError *error = 0;
    GOptionContext *context;

    static const GOptionEntry entries[] =
    {
        { "version", 'v', 0, G_OPTION_ARG_NONE, &show_version, _("Show version information and exit"), NULL },
        { "minimized", 'm', 0, G_OPTION_ARG_NONE, &run_minimized, _("Run with window minimized to tray"), NULL },

        { NULL }
    };

    Gio::init();

    context = g_option_context_new("tumblefile options");
    g_option_context_add_main_entries(context, entries, GETTEXT_PACKAGE);
    g_option_context_add_group(context, gtk_get_option_group (TRUE));

    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        std::cout << "Option parsing failed: " << error->message << std::endl;
        exit(1);
    }

    g_option_context_free(context);

    if (show_version) {
        std::cout << g_get_prgname() << " " << PACKAGE_VERSION << std::endl;
        exit(0);
    }

    if (argc >= 2 && !run_minimized) {
        // Command line mode: process all given options as file paths.
        Glib::ustring todays_path = tf::engine::init_todays_dir();
        std::cout << "cd " << todays_path << std::endl;
        for (int i = 0; i < argc-1; ++i)
            tf::engine::process_commandline_path(todays_path, argv[i+1]);
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
