#pragma once

//---------------------------------------------------------------------

typedef void (*Type_SetZoom)(int newZoomValue);

class CSetZoomApp
{
public:

	HINSTANCE m_instance;
	Type_SetZoom m_SetZoom;

public:

	CSetZoomApp();
	~CSetZoomApp();

	BOOL DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved);
	void load(int* track_def);
	BOOL func_init(FILTER *fp);
	BOOL func_exit(FILTER *fp);
	BOOL func_proc(FILTER *fp, FILTER_PROC_INFO *fpip);
	BOOL func_update(FILTER *fp, int status);
	BOOL func_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, void *editp, FILTER *fp);

	void setZoom(FILTER *fp, int index);
};

extern CSetZoomApp theApp;

//---------------------------------------------------------------------
