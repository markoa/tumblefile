
#include <iostream>
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

const int FIVE_MINUTES = 300;

MainWindow::MainWindow()
:
    hide_button_("Hide"),
    quit_button_(Gtk::Stock::QUIT),
    tray_icon_(*this)
{
    set_border_width(10);
    set_size_request(300, 200);

    label_.set_line_wrap();
    label_.set_markup("<span size='large'>Tumblefile is running.</span>\n\n<span>It will timestamp and move files from\nDesktop to Documents every 5 minutes.</span>"),
  
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

    Glib::signal_timeout().connect_seconds(sigc::ptr_fun(&timeout_handler), FIVE_MINUTES);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::toggle_hide()
{
    if (is_visible()) {
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

} // namespace tf
