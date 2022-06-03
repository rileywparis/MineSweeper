#include "WidgetsApp.h"

wxIMPLEMENT_APP(WidgetsApp);
//wxBEGIN_EVENT_TABLE(cMain, wxFrame);

bool WidgetsApp::OnInit()
{
	window = new WidgetsWindow();
	window->Show();

	/*int width = 1280;
	int height = 720;

	wxButton btn;
	btn = new wxButton * [width * height];
	wxGridSizer* grid = new wxGridSizer(width, height, 0, 0);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			btn[y * width + x] = new wxButton(this, 10000 + (y * width + x));
			grid->Add(btn[y * width + x], 1, wxEXPAND | wxALL);
		}
	}

	this->SetSizer*/


	return true;
}
