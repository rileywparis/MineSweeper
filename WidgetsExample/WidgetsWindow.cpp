#include "WidgetsWindow.h"

wxBEGIN_EVENT_TABLE(WidgetsWindow, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

WidgetsWindow::WidgetsWindow() : wxFrame(nullptr, wxID_ANY, "Mine Sweeper", wxPoint(400, 200), wxSize(1280, 720))
{
	btn = new wxButton * [mHeight * mWidth];
	wxGridSizer* grid = new wxGridSizer(mHeight, mWidth, 0, 0);
	mField = new int[mHeight * mWidth];

	for (int x = 0; x < mHeight; x++)
		for (int y = 0; y < mWidth; y++)
		{
			btn[y * mHeight + x] = new wxButton(this, 10000 + (y * mHeight + x));
			grid->Add(btn[y * mHeight + x], 1, wxEXPAND | wxALL);

			btn[y * mHeight + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &WidgetsWindow::OnButtonClicked, this);
			mField[y * mHeight + x] = 0;
		}

	this->SetSizer(grid);
	grid->Layout();
}

WidgetsWindow::~WidgetsWindow()
{
	delete[] btn;
	delete mField;
}

void WidgetsWindow::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % mHeight;
	int y = (evt.GetId() - 10000) / mHeight;

	if (mFirstClick)
	{
		int mines = 99;
		while (mines)
		{
			int rx = rand() % mHeight;
			int ry = rand() % mWidth;

			if (mField[ry * mHeight + rx] == 0 && rx != x && ry != y)
			{
				mField[ry * mHeight + rx] = -1;
				mines--;
			}
		}
		mFirstClick = false;
	}

	btn[y * mHeight + x]->Enable(false);

	if (mField[y * mHeight + x] == -1)
	{
		wxMessageBox("BOOM");

		mFirstClick = true;
		for (int x = 0; x < mHeight; x++)
			for (int y = 0; y < mWidth; y++)
			{
				mField[y * mHeight + x] = 0;
				btn[y * mHeight + x]->SetLabel("");
				btn[y * mHeight + x]->SetBackgroundColour(wxNullColour);
				btn[y * mHeight + x]->Enable(true);
			}
	}
	else
	{
		int mineCount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
				if (x + i >= 0 && x + 1 < mHeight && y + j >= 0 && y + j < mWidth)
					if (mField[(y + j) * mHeight + (x + i)] == -1)
						mineCount++;

			if (mineCount > 0)
				btn[y * mHeight + x]->SetLabel(std::to_string(mineCount));
			switch (mineCount)
			{
			case 0:
				break;
			case 1:
				btn[y * mHeight + x]->SetBackgroundColour(wxColor(100, 200, 0));
				break;
			case 2:
				btn[y * mHeight + x]->SetBackgroundColour(wxColor(150, 150, 0));
				break;
			case 3:
				btn[y * mHeight + x]->SetBackgroundColour(wxColor(150, 75, 0));
				break;
			case 4:
				btn[y * mHeight + x]->SetBackgroundColour(wxColor(200, 50, 0));
				break;
			default:
				btn[y * mHeight + x]->SetBackgroundColour(*wxRED);
				break;
			}
		}
	}
	evt.Skip();
}
