#include <windows.h>
#include <iostream>

class Screenshot{
public:
    int seed = 0;
    std::string path;
    
    Screenshot(std::string path);
    ~Screenshot();
    bool take_screenshot();

private:

    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;
    BITMAPINFO bInfo;

    HBITMAP hBitmap;
    HDC hDC, hMemDC;
    LONG lWidth, lHeight;
    BYTE *bBits = NULL;

    void set_display_size(HDC hDC);
    void set_headers();
    std::string generate_file_name();
    bool save_screenshot();
};