
#ifndef __TUMBLEFILE_ENGINE__
#define __TUMBLEFILE_ENGINE__

#include <string>
#include <glibmm/ustring.h>

namespace tf {

namespace engine {

Glib::ustring init_todays_dir();

void process_commandline_path(const Glib::ustring& dir_path, const std::string& arg);

void visit_desktop();

void setup_autostart();

} // namespace engine

} // namespace tf

#endif // __TUMBLEFILE_ENGINE__
