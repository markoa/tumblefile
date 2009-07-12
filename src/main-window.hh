
#ifndef __TUMBLEFILE_MAIN_WINDOW__
#define __TUMBLEFILE_MAIN_WINDOW__

#include <gtkmm.h>
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

    Gtk::VBox vbox_;
    Gtk::Label label_;
    Gtk::HBox button_box_;
    Gtk::Button hide_button_;
    Gtk::Button quit_button_;
    TrayIcon tray_icon_;
    std::pair<int, int> window_position_;
};

#endif // __TUMBLEFILE_MAIN_WINDOW__
