//// file_dialog.cpp
//#include "file_dialog.h"
//
//#ifdef _WIN32
//std::string showSaveDialog(const char* title, const char* filter, const char* defaultExt) {
//    OPENFILENAME ofn = {};
//    char path[MAX_PATH] = "";
//
//    ofn.lStructSize = sizeof(ofn);
//    ofn.lpstrFilter = filter;
//    ofn.lpstrDefExt = defaultExt;
//    ofn.lpstrFile = path;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
//    ofn.lpstrTitle = title;
//
//    if (GetSaveFileName(&ofn)) {
//        return std::string(path);
//    }
//    return "";
//}
//#else
//// Fallback for non-Windows: return empty (no dialog)
//std::string showSaveDialog(const char*, const char*, const char*) {
//    return "";
//}
//#endif