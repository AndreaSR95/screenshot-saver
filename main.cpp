#include <iostream>
#include <windows.h>
#include "shortcuts.h"

using namespace std;


int main(){
    cout << "START" << endl;

    string path = "...insert_default_path...";

    cout << "Default Path: "<< path << endl;
    cout << "Shift+a -> screenshot" << endl;
    cout << "Shift+w -> cambia path" << endl;
    cout << "Shift+q -> esci" << endl;

    map<int,UINT> buttons = get_buttons_map();
    if(!shortcut_registration(buttons))
        return -1;

    bool flag = true;
    MSG msg;

    while(flag){
        if(GetMessage(&msg,NULL,0,0) == false){
            continue;
        }
        if(msg.message != WM_HOTKEY){
            continue;
        }

        UINT button = buttons.at(msg.wParam);
        switch (button)
        {
        case 0x41://tasto a
            shift_a(path);
            break;

        case 0x51://tasto q
            flag = shift_q();
            break;

        case 0x57://tasto w
            path = shift_w();
            break;
        
        default:
            break;
        }
    }

    cout << "END" << endl;
    return 0;
}