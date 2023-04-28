#include "screenshot.h"
#include <iostream>
#include <string>

    Screenshot::Screenshot(std::string path){
        this->path = path;
        hDC = GetDC(NULL); //crea schermo
        set_display_size(hDC);
    }
    
    Screenshot::~Screenshot(){
        ReleaseDC(NULL, hDC);
    }

    bool Screenshot::take_screenshot(){
        INT x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        INT y = GetSystemMetrics(SM_YVIRTUALSCREEN);

        set_headers();

        hMemDC = CreateCompatibleDC(hDC);
        hBitmap = CreateDIBSection(hDC, &bInfo, DIB_RGB_COLORS, (VOID **)&bBits, NULL, 0);
        SelectObject(hMemDC, hBitmap);
        BitBlt(hMemDC, 0, 0, lWidth, lHeight, hDC, x, y, SRCCOPY);

        bool res = save_screenshot();

        DeleteDC(hMemDC);
        DeleteObject(hBitmap);

        return res;
    }

    void Screenshot::set_display_size(HDC hDC){
        BITMAP bAllDesktops;
        HGDIOBJ hTempBitmap;

        ZeroMemory(&bAllDesktops, sizeof(BITMAP));

        hTempBitmap = GetCurrentObject(hDC, OBJ_BITMAP); //ottieni una bitmap dallo schermo
        GetObjectW(hTempBitmap, sizeof(BITMAP), &bAllDesktops); //ottiene info sulla bitmap hTempBitmap

        this->lWidth = bAllDesktops.bmWidth;
        this->lHeight = bAllDesktops.bmHeight;

        DeleteObject(hTempBitmap);
    }

    void Screenshot::set_headers(){
        ZeroMemory(&bfHeader, sizeof(BITMAPFILEHEADER));
        ZeroMemory(&biHeader, sizeof(BITMAPINFOHEADER));
        ZeroMemory(&bInfo, sizeof(BITMAPINFO));

        bfHeader.bfType = (WORD)('B' | ('M' << 8));
        bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        biHeader.biSize = sizeof(BITMAPINFOHEADER);
        biHeader.biBitCount = 24;
        biHeader.biCompression = BI_RGB;
        biHeader.biPlanes = 1;
        biHeader.biWidth = this->lWidth;
        biHeader.biHeight = this->lHeight;

        bInfo.bmiHeader = biHeader;
    }

    std::string Screenshot::generate_file_name(){
        std::string name = std::to_string(this->seed);
        std::string estensione = ".bmp";
        std::string res = this->path + name + estensione;

        this->seed++;
        return res;
    }

    bool Screenshot::save_screenshot(){
        DWORD cbBits = (((24 * lWidth + 31)&~31) / 8) * lHeight;
        DWORD dwWritten = 0;

        std::string file_name = generate_file_name();
        HANDLE hFile = CreateFileA(file_name.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if(INVALID_HANDLE_VALUE == hFile)
        {
            std::cout << "Errore screenshot non creato: "<< file_name << std::endl << std::endl;
            return FALSE;
        }
        WriteFile(hFile, &bfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
        WriteFile(hFile, &biHeader, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
        WriteFile(hFile, bBits, cbBits, &dwWritten, NULL);
        FlushFileBuffers(hFile);
        CloseHandle(hFile);

        std::cout << "Screenshot creato al path "<< file_name << std::endl << std::endl;
        return TRUE;
    }