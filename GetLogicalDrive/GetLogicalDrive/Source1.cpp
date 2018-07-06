#include<Windows.h>
#include<tchar.h>
#include<windowsx.h>
#include<string>
#include"resource.h"

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hCombo;
namespace disk
{
	DWORD Drives = GetLogicalDrives();//получаем битовую маску доступных дисков, в том числе и съемных
	int n; int d;
	char letter[1];
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpzsCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}


BOOL OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	hCombo = GetDlgItem(hWnd, IDC_COMBO1);
	size_t i = 0;
	while (i < 26)//26 букв
	{
		disk::n = ((disk::Drives >> i) & 0x00000001);//сдвигаемся по битам
		if (disk::n == 1)
		{
			disk::letter[0] = char(65 + i);//буквы в таблице начинаются с 65 символа( A )
										   //определим размер памяти, необходимый для хранения Unicode-строки
			int length = MultiByteToWideChar(CP_ACP, 0, disk::letter, -1, NULL, 0);
			wchar_t *ptr = new wchar_t[length + 1];
			// конвертируем ANSI-строку в Unicode-строку
			MultiByteToWideChar(CP_ACP, 0, disk::letter, -1, ptr, length);
			wchar_t str[30];
			_tcscpy_s(str, 2, ptr);
			str[1] = '\0';
			delete[] ptr;
			_tcscat_s(str, 4, L":\\");
			disk::d = GetDriveType(str);
			if (disk::d == DRIVE_UNKNOWN)
			{
				_stprintf_s(str, L"%s (неизвестен)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_NO_ROOT_DIR)
			{
				_stprintf_s(str, L"%s (такого диска нет)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_REMOVABLE)
			{
				_stprintf_s(str, L"%s (съемный)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_FIXED)
			{
				_stprintf_s(str, L"%s (локальный)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_REMOTE)
			{
				_stprintf_s(str, L"%s (удаленный)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_CDROM)
			{
				_stprintf_s(str, L"%s (CD-ROM)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
			if (disk::d == DRIVE_RAMDISK)
			{
				_stprintf_s(str, L"%s (RAM drive)", str);
				SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(str));
			}
		}
		++i;
	}
	return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	switch (mes)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDialog);
	}
	return FALSE;
}
