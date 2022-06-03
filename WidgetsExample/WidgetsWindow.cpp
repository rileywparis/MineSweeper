#include "WidgetsWindow.h"

wxBEGIN_EVENT_TABLE(WidgetsWindow, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

WidgetsWindow::WidgetsWindow() : wxFrame(nullptr, wxID_ANY, "Mine Sweeper", wxPoint(400, 200), wxSize(1280, 720))
{
	//button1 = new wxButton(this, wxID_ANY, "Hello", wxPoint(10, 10), wxSize(100, 100));
	//button2 = new wxButton(this, wxID_ANY, "Goodbye", wxPoint(110, 10), wxSize(100, 100));
	/*int height = 16;
	int width = 30;
	wxButton **btn;*/

	btn = new wxButton * [nWidth * nHeight];
	wxGridSizer* grid = new wxGridSizer(nWidth, nHeight, 0, 0);

	nField = new int[nWidth * nHeight];

	for (int x = 0; x < nWidth; x++)
	{
		for (int y = 0; y < nHeight; y++)
		{
			btn[y * nWidth + x] = new wxButton(this, 10000 + (y * nWidth + x));
			grid->Add(btn[y * nWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &WidgetsWindow::OnButtonClicked, this);
			nField[y * nWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

WidgetsWindow::~WidgetsWindow()
{
	delete[] btn;
}

void WidgetsWindow::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nWidth;
	int y = (evt.GetId() - 10000) / nWidth;

	if (firstClick)
	{
		int mines = 99;

		while (mines)
		{
			int rx = rand() % nWidth;
			int ry = rand() % nHeight;

			if (nField[ry * nWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nWidth + rx] = -1;
				mines--;
			}
		}

		firstClick = false;
	}

	btn[y * nWidth + x]->Enable(false);

	if (nField[y * nWidth + x] == -1)
	{
		wxMessageBox("BOOM");

		firstClick = true;
		for (int x = 0; x < nWidth; x++)
		{
			for (int y = 0; y < nHeight; y++)
			{
				nField[y * nWidth + x] = 0;
				btn[y * nWidth + x]->SetLabel("");
				btn[y * nWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + 1 < nWidth && y + j >= 0 && y + j < nHeight)
				{
					if (nField[(y + j) * nWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}

			if (mine_count > 0)
			{
				btn[y * nWidth + x]->SetLabel(std::to_string(mine_count));
			}
		}
	}
	evt.Skip();
}
