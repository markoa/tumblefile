
#include <iostream>
#include <gtkmm.h>
#include "main-window.hh"

MainWindow::MainWindow()
:
    hide_button_("Hide"),
    quit_button_(Gtk::Stock::QUIT),
    tray_icon_(*this)
{
    set_border_width(10);
    set_size_request(200, 150);

    label_.set_markup("<span size='large'>Tumblefile is running.</span>"),
  
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
