
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <iostream>
#include <list>
#include <string>
#include <glib.h>
#include <glib/gprintf.h>
#include <giomm.h>

using namespace std;

namespace tf {

namespace engine {

void
enumerate_files(const std::string& dir_path, list<string>& paths)
{
    Glib::Dir dir(dir_path);
    list<string> entries(dir.begin(), dir.end());

    list<string>::const_iterator it(entries.begin());
    list<string>::const_iterator end(entries.end());

    for ( ; it != end; ++it) {
        string path = Glib::build_filename(dir_path, *it);

        if (Glib::file_test(path, Glib::FILE_TEST_IS_REGULAR)) {
            cout << path << endl;
            paths.push_back(path);
        }
    }
}

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

Glib::ustring
get_desktop_path()
{
    const gchar* desktop_path;
    desktop_path = g_get_user_special_dir(G_USER_DIRECTORY_DESKTOP);
    return Glib::ustring(desktop_path);
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

void
visit_desktop()
{
    list<string> file_paths;
    Glib::ustring desktop_path = get_desktop_path();
    Glib::ustring todays_path = init_todays_dir();

    enumerate_files(desktop_path, file_paths);

    list<string>::iterator it(file_paths.begin());
    list<string>::iterator end(file_paths.end());

    for ( ; it != end; ++it) {
        //Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(*it);
        //move_file(todays_path, file);
        cout << *it << endl;
    }
}

} // namespace engine

} // namespace tf
