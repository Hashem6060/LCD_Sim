//// file_dialog.h
//#pragma once
//#include <string>
//
//#ifdef _WIN32
//    // Define before including windows.h to reduce bloat/conflicts
//#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
//#include <windows.h>
//#include <commdlg.h>  // Now safe: windows.h is already included
//#endif
//
//// Show save dialog, return path or empty string if cancelled
//std::string showSaveDialog(const char* title, const char* filter, const char* defaultExt);