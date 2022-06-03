#pragma once
#include "wx/wx.h"
#include "Main.h"

class WidgetsWindow : public wxFrame
{
public:
	WidgetsWindow();
	~WidgetsWindow();
	int nWidth = 16;
	int nHeight = 30;
	wxButton** btn;
	int* nField = nullptr;
	bool firstClick = true;
private:
	wxButton* button1;
	wxButton* button2;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
