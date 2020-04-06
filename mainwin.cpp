#include "mainwin.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "entrydialog.h"

Mainwin::Mainwin() : store{nullptr} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
    set_title("Store");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // /////// ////////////////////////////////////////////////////////////////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    // vbox->add(*menubar);

   //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

    //Creating a view menu to add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    //Append view customer to the view menu
    Gtk::MenuItem *menuitem_viewcustomer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_viewcustomer->signal_activate().connect([this] {this->on_view_customer_click();});
    viewmenu->append(*menuitem_viewcustomer);

    //Append view desktop to the view menu
    Gtk::MenuItem *menuitem_viewdesktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_viewdesktop->signal_activate().connect([this] {this->on_view_desktop_click();});
    viewmenu->append(*menuitem_viewdesktop);

    //Append view peripheral to the view menu
    Gtk::MenuItem *menuitem_viewperi = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_viewperi->signal_activate().connect([this] {this->on_view_peripheral_click();});
    viewmenu->append(*menuitem_viewperi);
    //Append view order to the view menu
    Gtk::MenuItem *menuitem_vieworder = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_vieworder->signal_activate().connect([this] {this->on_view_order_click();});
    viewmenu->append(*menuitem_vieworder);


    //Creating Insert menu
    Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);


    //Append insert customer to the insert menu
    Gtk::MenuItem *menuitem_insertcustomer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_insertcustomer->signal_activate().connect([this] {this->on_insert_customer_click();});
    insertmenu->append(*menuitem_insertcustomer);

    //Append insert desktop to the insert menu
    Gtk::MenuItem *menuitem_insertdesktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_insertdesktop->signal_activate().connect([this] {this->on_insert_desktop_click();});
    insertmenu->append(*menuitem_insertdesktop);

    //Append insert peripherals to the insert menu
    Gtk::MenuItem *menuitem_insertperi = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_insertperi->signal_activate().connect([this] {this->on_insert_peripheral_click();});
    insertmenu->append(*menuitem_insertperi);

    //Append insert order to the insert menu
    Gtk::MenuItem *menuitem_insertorder = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_insertorder->signal_activate().connect([this] {this->on_insert_order_click();});
    insertmenu->append(*menuitem_insertorder);


    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);


    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);

    // ///////////// //////////////////////////////////////////////////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);
    // vbox->add(*toolbar);

    


    //     Q U I T
    // Push the quit botton all the way to the right by setting set_expand true
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);
    toolbar->append(*sep);

    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit");
    quit_button->signal_clicked().connect([this] {this->on_quit_click();});
    toolbar->append(*quit_button);
    
    // S T A T U S   B A R   D I S P L A Y ////////////////////////////////////
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);
    // vbox->add(*msg);

    // Make the box and everything in it visible
    vbox->show_all();

   

}

Mainwin::~Mainwin() { }

void Mainwin::on_quit_click(){
    close();
}

// /////////////////
// C A L L B A C K S
// /////////////////

// COMBINED observer / callback
void Mainwin::on_button_click(int button) {
    try {
        // Catch the "impossible" out of data exception
        store->take_data(button);
        set_data();
    } catch(std::exception& e) {
        data->set_markup("<b>FAIL:</b> " + std::string{e.what()} + ", start new order");
    }
}

void Mainwin::() {
    set_data();
    set_msg();
}




void Mainwin::on_about_click() {
 Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("Store");
    dialog.set_version("Version 1.2.1");
    dialog.set_copyright("Copyright 2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {""};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {""};
    dialog.set_artists(artists);
    dialog.run();
}

// /////////////////
// U T I L I T I E S
// /////////////////


void Mainwin:: on_view_peripheral_click(){
   std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Peripherals</b></big><tt>\n\n";
    for(int i=0; i<store->num_options(); ++i) 
        oss << i << ") " << store->option(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}
void Mainwin::on_view_desktop_click(){
 std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "<big><b>Products</b></big><tt>\n\n";
    for(int i=0; i<store->num_desktops(); ++i) 
        oss << i << ") " << store->desktop(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");

}
void Mainwin::on_view_order_click(){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "<big><b>Orders</b></big><tt>\n\n";
    for(int i=0; i<store->num_orders(); ++i) 
        oss << i << ") " << store->order(i) << "\n\n";
    oss<<"</tt>";
    set_data(oss.str());
    set_msg("");
}
void Mainwin::on_view_customer_click(){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "<big><b>Customers</b></big><tt>\n\n";
    for(int i=0; i<store->num_customers(); ++i) 
        oss << i << ") " << store->customer(i) << "\n";
    oss<<"</tt>";
    set_data(oss.str()); 
    set_msg("");
}
void Mainwin::on_insert_peripheral_click(){
    std::string peripheral = get_string("Name of new peripheral?");
    double cost = get_double("Cost?");

    Options option{peripheral, cost};
    store->add_option(option);

    on_view_peripheral_click();
    set_msg("Added peripheral " + peripheral);  

}
void Mainwin::on_insert_desktop_click(){
        on_view_peripheral_click();
       
    int desktop = store->new_desktop();
            while(true) {
                std::ostringstream oss;
                oss<<store->desktop(desktop)<<"\nAdd which peripheral (-1 when done)?"

                int option = get_int(oss.str());
                if(option == -1) break;
                try {
                    store->add_option(option, desktop);
                } catch(std::exception& e) {
                    std::cerr << "#### INVALID OPTION ####\n\n";
                }
            }

}
void Mainwin::on_insert_order_click() {
    on_view_customer_click();

    int customer = get_int("Customer?");
    if(customer == -1) return;

    int order = store->new_order(customer);

    on_view_desktop_click();
    while(true) {
        int desktop = get_int("Desktop (-1 when done)?");

        if(desktop == -1) break;
        store->add_desktop(desktop, order);
    }
    on_view_order_click();
    set_msg("Added an order"+std::to_string(order)+" for $"+std::to_string(store->order(order).price()));
}
void Mainwin::on_insert_customer_click() {
    std::string name = get_string("Customer name?");
    if(name.size()) {
        std::string phone = get_string("Customer phone (xxx-xxx-xxxx)?");
        std::string email = get_string("Customer email (xxx@domain.com)?");

        Customer customer{name, phone, email};
        store->add_customer(customer);
    }
    on_view_customer_click();
    set_msg("Added customer " + name);

}
Mainwin:: std::string get_string(std::string prompt){
    EntryDialog the_string{*this, prompt};
    the_string.run();
    return the_string.get_text();


}
Mainwin:: double get_double(std::string prompt){
    try{
        return std::stod(get_string(prompt));
    }catch(std::exception& e){
        return -1.0;
    }

}
Mainwin:: int get_int(std::string prompt){
    try{
        return std::stoi(get_string(prompt));
    }catch(std::exception& e){
        return -1;
    }


}
void Mainwin::set_data(std::string s){
       data->set_markup(s);
        }


void Mainwin:: set_msg(std::string s){
    msg->set_markup(s);


}


    // Display the collected status on the status bar
    msg->set_markup(s);

    // Update the visual display of data
    s = "<span size='24000' weight='bold'>";
    for(int i=0; i<store->data_left(); ++i) s.append("| ");
    s.append("</span>  (" + std::to_string(store->data_left()) + " data)");
    data->set_markup(s);

   
}