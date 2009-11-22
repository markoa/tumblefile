
#include <gtkmm/stock.h>
#include <glib/gi18n.h>
#include "tray-icon.hh"
#include "main-window.hh"

namespace tf {

TrayIcon::TrayIcon(MainWindow& w) :
    main_window_(w)
{
    status_icon_ = Gtk::StatusIcon::create(Gtk::Stock::YES);

    status_icon_->signal_activate().connect(
            sigc::mem_fun(*this, &TrayIcon::active_main_window));

    set_tooltip();
}

TrayIcon::~TrayIcon()
{
}

void
TrayIcon::active_main_window()
{
    main_window_.toggle_hide();
    set_tooltip();
}

void
TrayIcon::set_tooltip()
{
    if (main_window_.get_visible()) {
        status_icon_->set_tooltip_text(
                _("Tumblefile – click to hide the window")
                );
    } else {
        status_icon_->set_tooltip_text(
                _("Tumblefile – click to show the window")
                );
    }
}

} // namespace tf
