#include "pch.h"
#include "SetZoom.h"

//---------------------------------------------------------------------

CSetZoomApp theApp;

// デバッグ用コールバック関数。デバッグメッセージを出力する。
void ___outputLog(LPCTSTR text, LPCTSTR output)
{
	::OutputDebugString(output);
}

CSetZoomApp::CSetZoomApp()
{
	m_instance = 0;
	m_SetZoom = 0;
}

CSetZoomApp::~CSetZoomApp()
{
}

BOOL CSetZoomApp::DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			MY_TRACE(_T("DLL_PROCESS_ATTACH\n"));

			// DLL インスタンスハンドルを m_instance に格納する。
			m_instance = instance;
			MY_TRACE_HEX(m_instance);

			break;
		}
	case DLL_PROCESS_DETACH:
		{
			MY_TRACE(_T("DLL_PROCESS_DETACH\n"));

			break;
		}
	}

	return TRUE;
}

void CSetZoomApp::load(int* track_def)
{
	// ini ファイルから設定を読み込む。
	TCHAR path[MAX_PATH] = {};
	::GetModuleFileName(m_instance, path, MAX_PATH);
	::PathRenameExtension(path, _T(".ini"));
	MY_TRACE_TSTR(path);

	track_def[0] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom1"), track_def[0], path);
	track_def[1] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom2"), track_def[1], path);
	track_def[2] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom3"), track_def[2], path);
	track_def[3] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom4"), track_def[3], path);
	track_def[4] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom5"), track_def[4], path);
	track_def[5] = ::GetPrivateProfileInt(_T("Settings"), _T("Zoom6"), track_def[5], path);
}

BOOL CSetZoomApp::func_init(FILTER *fp)
{
	MY_TRACE(_T("CSetZoomApp::func_init()\n"));

	HMODULE exedit_auf = ::GetModuleHandle(_T("exedit.auf"));
	m_SetZoom = (Type_SetZoom)((DWORD)exedit_auf + 0x000395E0);

	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom1を適用", fp->hwnd, 0, 0, 0);
	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom2を適用", fp->hwnd, 1, 0, 0);
	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom3を適用", fp->hwnd, 2, 0, 0);
	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom4を適用", fp->hwnd, 3, 0, 0);
	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom5を適用", fp->hwnd, 4, 0, 0);
	fp->exfunc->add_menu_item(fp, (LPSTR)"Zoom6を適用", fp->hwnd, 5, 0, 0);

	return TRUE;
}

BOOL CSetZoomApp::func_exit(FILTER *fp)
{
	MY_TRACE(_T("CSetZoomApp::func_exit()\n"));

	return TRUE;
}

BOOL CSetZoomApp::func_proc(FILTER *fp, FILTER_PROC_INFO *fpip)
{
	MY_TRACE(_T("CSetZoomApp::func_proc()\n"));

	return FALSE;
}

BOOL CSetZoomApp::func_update(FILTER *fp, int status)
{
	for (int i = 0; i < 6; i++)
	{
		::SetDlgItemTextA(fp->hwnd, 0x2EE4 + i,
			yulib::format("%d - Zoom%dを適用", fp->track[i], i + 1));
	}

	setZoom(fp, status - FILTER_UPDATE_STATUS_TRACK);

	return TRUE;
}

BOOL CSetZoomApp::func_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, void *editp, FILTER *fp)
{
	switch (message)
	{
	case WM_FILTER_CHANGE_WINDOW:
		{
			MY_TRACE(_T("CSetZoomApp::func_WndProc(WM_FILTER_CHANGE_WINDOW)\n"));

			break;
		}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
			::SendMessage(::GetWindow(hwnd, GW_OWNER), message, wParam, lParam);
			break;
		}
	case WM_FILTER_COMMAND:
		{
			int index = LOWORD(wParam);
			MY_TRACE_INT(index);

			setZoom(fp, index);

			break;
		}
	case WM_COMMAND:
		{
			int index = LOWORD(wParam) - MID_FILTER_BUTTON;
			MY_TRACE_INT(index);

			setZoom(fp, index);

			break;
		}
	}

	return FALSE;
}

void CSetZoomApp::setZoom(FILTER *fp, int index)
{
	if (index < 0 || index > 5)
		return;

	MY_TRACE(_T("CSetZoomApp::setZoom(%d) => %d\n"), index, fp->track[index]);

	(*m_SetZoom)(fp->track[index]);
}

//---------------------------------------------------------------------
