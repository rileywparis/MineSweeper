#pragma once
#include "wx/wx.h"

class WidgetsWindow : public wxFrame
{
public:
	WidgetsWindow();
	~WidgetsWindow();
	wxButton** btn;
	int mHeight = 16;
	int mWidth = 30;
	int* mField = nullptr;
	bool mFirstClick = true;
private:
	void OnButtonClicked(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};
