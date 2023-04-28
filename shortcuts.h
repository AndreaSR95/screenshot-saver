#include <windows.h>
#include <map>

std::map<int,UINT> get_buttons_map();
int shortcut_registration(std::map<int,UINT> buttons);

void shift_a(std::string path);
bool shift_q();
std::string shift_w();