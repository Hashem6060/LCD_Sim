#pragma once
#define nLINE 5//共显示N行 5行 6行
#if (nLINE==5)
#define nDOT 16//信息行点数
#define nNULL 12//空格行点数
#define nSTART 0//首行起始点
#define nDOWN 0//单位显示下移量
#else
#define nDOT 16//信息行点数
#define nNULL 6//空格行点数
#define nSTART 2//首行起始点
#define nDOWN 0//单位显示下移量
#endif

#define Y_MAIN_L0 nSTART
#define Y_UNIT_L0 Y_MAIN_L0+nDOWN

#define Y_MAIN_L1 Y_MAIN_L0+nDOT+nNULL
#define Y_UNIT_L1 Y_MAIN_L1+nDOWN

#define Y_MAIN_L2 Y_MAIN_L1+nDOT+nNULL
#define Y_UNIT_L2 Y_MAIN_L2+nDOWN

#define Y_MAIN_L3 Y_MAIN_L2+nDOT+nNULL
#define Y_UNIT_L3 Y_MAIN_L3+nDOWN

#define Y_MAIN_L4 Y_MAIN_L3+nDOT+nNULL
#define Y_UNIT_L4 Y_MAIN_L4+nDOWN

#define Y_MAIN_L5 Y_MAIN_L4+nDOT+nNULL
#define Y_UNIT_L5 Y_MAIN_L5+nDOWN

