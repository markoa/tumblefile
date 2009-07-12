#ifndef _TRAY_ICON_HH_
#define _TRAY_ICON_HH_

#include <gtkmm/statusicon.h>

class MainWindow;

class TrayIcon {
public:
    TrayIcon(MainWindow& wnd);
    ~TrayIcon();
private:
    void active_main_window();

    MainWindow& main_window_;
    Glib::RefPtr<Gtk::StatusIcon> status_icon_;
};

#endif // _TRAY_ICON_HH_
