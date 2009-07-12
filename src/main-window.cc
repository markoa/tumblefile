
#include <iostream>
#include <gtkmm.h>
#include "main-window.hh"

MainWindow::MainWindow()
    : quit_button_(Gtk::Stock::QUIT),
    tray_icon_(*this)
{
    set_border_width(10);
    set_size_request(200, 150);
  
    quit_button_.signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::on_quit_button_clicked));

    add(quit_button_);

    show_all_children();
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

void MainWindow::on_quit_button_clicked()
{
    Gtk::Main::quit();
}
