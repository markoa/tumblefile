
#include <gtkmm/stock.h>
#include "tray-icon.hh"
#include "main-window.hh"

TrayIcon::TrayIcon(MainWindow& w) :
    main_window_(w)
{
    status_icon_ = Gtk::StatusIcon::create(Gtk::Stock::YES);

    status_icon_->signal_activate().connect(
            sigc::mem_fun(*this, &TrayIcon::active_main_window));

    status_icon_->set_tooltip("tumblefile");
}

TrayIcon::~TrayIcon()
{
}

void
TrayIcon::active_main_window()
{
    main_window_.toggle_hide();
}
