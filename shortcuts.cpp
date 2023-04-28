#include <iostream>
#include "shortcuts.h"
#include "screenshot.h"

using namespace std;
Screenshot *s = NULL;

//assegna un id ad univoco ogni tasto
std::map<int,UINT> get_buttons_map(){
    int button_code = 1;
    map<int,UINT> buttons = map<int,UINT>();

    buttons.insert(pair<int,UINT>(button_code++,0x41));//tasto a - screenshot
    buttons.insert(pair<int,UINT>(button_code++,0x51));//tasto q - quit
    buttons.insert(pair<int,UINT>(button_code++,0x57));//tasto w - change directory

    return buttons;
}

//registra le shortcut a partire da un insieme di tasti
int shortcut_registration(map<int,UINT> buttons){
    for(pair<int,UINT> b : buttons){
        if(RegisterHotKey(NULL,b.first,MOD_SHIFT,b.second) == 0){
            cout << "Errore registrazione" << endl;
            return false;
        }
    }
    return true;
}

void shift_a(std::string path){
    cout << "Shift + a:" << endl;
    if(s == NULL){
        s = new Screenshot(path);
    }
    s->take_screenshot();
}

bool shift_q(){
    cout << "Shift + q:" << endl;
    delete s;
    return false;
}

std::string shift_w(){
    std::string path;
    cout << "Shift + w:" << endl;

    cout << "Inserire il nuovo path: ";
    cin >> path;

    if(s != NULL){
        s->path = path;
        s->seed = 0;
    }
    cout << "Path modificato" << endl;
    return path;
}