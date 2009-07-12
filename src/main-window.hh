
#ifndef __AUTOFOOMM_MAIN_WINDOW__
#define __AUTOFOOMM_MAIN_WINDOW__

#include <gtkmm/button.h>
#include <gtkmm/statusicon.h>
#include <gtkmm/window.h>
#include <utility>
#include "tray-icon.hh"

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

    void toggle_hide();

protected:
    virtual bool on_delete_event(GdkEventAny* event);

    void on_quit_button_clicked();

    Gtk::Button quit_button_;
    TrayIcon tray_icon_;
    std::pair<int, int> window_position_;
};

#endif // __AUTOFOOMM_MAIN_WINDOW__
