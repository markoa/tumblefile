
#include <iostream>
#include <glib/gi18n.h>
#include <gtkmm.h>
#include "engine.hh"
#include "main-window.hh"

namespace tf {

bool
timeout_handler()
{
    engine::visit_desktop();
    return true; // always continue execution
}

bool
startup_timeout_handler()
{
    engine::setup_autostart();
    return false; // run only once
}

const int FOUR_SECONDS = 4;
const int FIVE_MINUTES = 300;

MainWindow::MainWindow()
:
    hide_button_(_("Hide")),
    quit_button_(Gtk::Stock::QUIT),
    tray_icon_(*this)
{
    set_size_request(350, 200);

    label_.set_line_wrap();
    label_.set_markup(get_app_description());
  
    hide_button_.signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::toggle_hide));

    quit_button_.signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::on_quit_button_clicked));

    vbox_.pack_start(label_);
    vbox_.pack_start(button_box_, false, false);
    button_box_.pack_start(hide_button_);
    button_box_.pack_start(quit_button_);
    add(vbox_);

    show_all_children();

    set_default_icon_name("tumblefile");

    Glib::signal_timeout().connect_seconds(
            sigc::ptr_fun(&timeout_handler), FIVE_MINUTES);

    Glib::signal_timeout().connect_seconds(
            sigc::ptr_fun(&startup_timeout_handler), FOUR_SECONDS);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::toggle_hide()
{
    if (get_visible()) {
        get_position(window_position_.first, window_position_.second);
        hide();
    }
    else {
        show();
        move(window_position_.first, window_position_.second);
    }
}

bool
MainWindow::on_delete_event(GdkEventAny* /*event*/)
{
    toggle_hide();
    return true;
}

void
MainWindow::on_quit_button_clicked()
{
    Gtk::Main::quit();
}

Glib::ustring
MainWindow::get_app_description()
{
    Glib::ustring desc("<span size='large'>");

    desc += _("Tumblefile is running.");
    desc += "</span>\n\n<span>";
    desc += _("It will timestamp and move files from Desktop to Documents every 5 minutes.");
    desc += "</span>";

    return desc;
}

} // namespace tf
