
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <glib.h>
#include <glib/gprintf.h>
#include <giomm.h>
#include <gtkmm/main.h>
#include "main-window.hh"

using namespace std;

GDate*
get_current_date()
{
    GDate* today;

    today = g_date_new();
    g_date_set_time_t(today, time(NULL));

    return today;
}

Glib::ustring
get_timestamp(const char* format)
{
  struct timeval tv;
  struct tm* ptm;
  char time_string[15];

  // Obtain the time of day, and convert it to a tm struct.
  gettimeofday(&tv, NULL);
  ptm = localtime(&tv.tv_sec);

  strftime(time_string, sizeof (time_string), format, ptm);
  Glib::ustring str(time_string);

  return str;
}

Glib::ustring
init_todays_dir()
{
    const gchar* documents_dir_path;
    GDate* date_today;
    gchar month_and_day[65];
    gchar todays_path[129];
    Glib::ustring res;

    documents_dir_path = g_get_user_special_dir(G_USER_DIRECTORY_DOCUMENTS);

    date_today = get_current_date();

    if (!g_date_strftime(month_and_day, 65, "%Y-%m-%B/%d-%A", date_today)) {
        g_error("Failed to generate month_and_day");
    }

    g_sprintf(todays_path, "%s%c%s%c",
              documents_dir_path, G_DIR_SEPARATOR,
              month_and_day, G_DIR_SEPARATOR);
    g_mkdir_with_parents(todays_path, S_IRWXU);

    res = todays_path;
    g_date_free(date_today);

    return res;
}

void
move_file(const Glib::ustring& dir_path, const Glib::RefPtr<Gio::File>& file)
{
    Glib::ustring timestamp, target_path;
    Glib::RefPtr<Gio::File> destination;

    if (! file->query_exists()) {
        cout << "Skipping " << file->get_path() << " (file does not exist)" << endl;
        return;
    }

    timestamp = get_timestamp("%Y%m%d.%H%M.");
    target_path = dir_path + timestamp + file->get_basename();
    destination = Gio::File::create_for_path(target_path);

    cout << file->get_path() << " → " << target_path << endl;

    try {
        file->move(destination);
    } catch (const Gio::Error& ex) {
        cerr << "Failed to move file " << file->get_path();
        cerr << ": " << ex.what() << endl;
    }
}

void
process_commandline_path(const Glib::ustring& dir_path, const std::string& arg)
{
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_commandline_arg(arg);
    move_file(dir_path, file);
}

int
main(int argc, char** argv)
{
    Gio::init();

    if (argc >= 2) {
        Glib::ustring todays_path = init_todays_dir();
        cout << "cd " << todays_path << endl;
        for (int i = 0; i < argc-1; ++i) {
            process_commandline_path(todays_path, argv[i+1]);
        }
    } else {
        Gtk::Main kit(argc, argv);
        MainWindow main_window;
        main_window.show();
        Gtk::Main::run();
    }
    
    return 0;
}
