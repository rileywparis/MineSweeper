#include "WidgetsWindow.h"

WidgetsWindow::WidgetsWindow() : wxFrame(nullptr, wxID_ANY, "Widgets!", wxPoint(400, 200), wxSize(800, 800))
{
	button1 = new wxButton(this, wxID_ANY, "Hello", wxPoint(10, 10), wxSize(100, 100));
	button2 = new wxButton(this, wxID_ANY, "Goodbye", wxPoint(110, 10), wxSize(100, 100));
};
