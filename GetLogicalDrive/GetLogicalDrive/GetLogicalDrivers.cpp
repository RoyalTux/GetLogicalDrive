//#include "GetLogicalDrivers.h"
//#include <random>
//
//GetLogicalDrivers* GetLogicalDrivers::ptr = NULL;
//
//GetLogicalDrivers::GetLogicalDrivers(void)
//{
//	ptr = this;
//}
//
//void GetLogicalDrivers::Cls_OnClose(HWND hwnd)
//{
//	EndDialog(hwnd, 0);
//}
//
//BOOL GetLogicalDrivers::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
//{
//	hComboBox = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
//		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_SORT, 25, 50, 300, 400, hwnd, 0, HINSTANCE(ptr), 0);
//
//	const DWORD number_of_drives = 32;
//	TCHAR buffer[512];
//	TCHAR* b_ptr;
//	b_ptr = buffer;
//	GetLogicalDriveStrings(number_of_drives, buffer);
//
//	TCHAR letter = char(65);
//	int i = 1;
//	int mask = GetLogicalDrives();
//	//TCHAR textt[10];
//	//wsprintf(textt, TEXT("%d"), mask);
//	//MessageBox(hDialog, textt, TEXT("INFO"), MB_OK);
//	while (*b_ptr)
//	{
//		while (b_ptr[0] != letter)
//		{
//			letter = char(65 + i);
//			++i;
//		}
//		int n = ((mask >> i) & 0x00000001);
//		if (!n)
//		{
//			b_ptr = b_ptr + wcslen(b_ptr) + 1;
//			continue;
//		}
//
//		int type = GetDriveType(b_ptr);
//		TCHAR type_name[16];
//		switch (type)
//		{
//		case DRIVE_FIXED:
//			lstrcpy(type_name, TEXT(" (fixed)"));
//			break;
//		case DRIVE_REMOVABLE:
//			lstrcpy(type_name, TEXT(" (removable)"));
//			break;
//		case DRIVE_REMOTE:
//			lstrcpy(type_name, TEXT(" (remote)"));
//			break;
//		case DRIVE_CDROM:
//			lstrcpy(type_name, TEXT(" (cd-rom)"));
//			break;
//		case DRIVE_RAMDISK:
//			lstrcpy(type_name, TEXT(" (virtual)"));
//			break;
//		default:
//			lstrcpy(type_name, TEXT(" (unknown)"));
//			break;
//		}
//		TCHAR temp[32];
//		lstrcpy(temp, b_ptr);
//		lstrcat(temp, type_name);
//		SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(temp));
//		b_ptr = b_ptr + wcslen(b_ptr) + 1;
//	}
//
//
//	return TRUE;
//}
//
//
//INT_PTR CALLBACK GetLogicalDrivers::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
//		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
//	}
//	return FALSE;
//}