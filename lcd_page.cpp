
/*
#include "lcd_page.h"


void Display_UI(void)
{
	Display_Operating_Prompt();
	{		
	Display_English_UI(); 
		
	}

}



void Display_Operating_Prompt(void)
{
	

	if (true)//手动操作提示
	{
		while (true)//手动键操作提示
		{

			if (true)
			{
				Display_Hz_Char("友情提醒", 88, Y_MAIN_L1, 1);

				Display_Hz_Char("按下START键可起动发动机!", 24, Y_MAIN_L2, 1);
			}
			else
			{
				Display_Hz_Char("TIPS", 104, Y_MAIN_L0, 1);
				Display_Hz_Char("Press the 'START' key to start", 0, Y_MAIN_L1, 1);
				Display_Hz_Char("the engine!", 0, Y_MAIN_L1 + 16, 1);
			}


			OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err); //延时100ms
		}

		
	}

	if (true)//起动操作提示
	{
		while (true)//起动键操作提示
		{


			if (true)
			{
				Display_Hz_Char("需要起动发动机,", 64, Y_MAIN_L1, 1);
				Display_Hz_Char("请先按下'MANUAL'按键!", 40, Y_MAIN_L2, 1);
			}
			else
			{
				Display_Hz_Char("To start the engine,press the", 0, Y_MAIN_L1, 1);
				Display_Hz_Char("'MANUAL' button first!", 0, Y_MAIN_L1 + 16, 1);
			}


			OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err); //延时100ms
		}
	}
}





void Display_English_UI(void)
{
	if (true)//历史故障记录
	{
		Display_English_Alarm_UI();
	}
	else if (true)//累计参数设置模式
	{
		Display_English_GrandTotal_UI();
	}
	else if (true)//校正参数设置模式
	{
		Display_English_CheckModify_UI();
	}
	else if (true)//设置模式
	{
		Display_English_Set_UI();
	}
	else//正常显示模式
	{
		if (true)
		{
			Display_english_row_Page_Teeth();
		}
		else
		{
			if (true)//当待机显示LOGO标志置位时，不执行本函数
			{
				Display_English_View_UI();
			}
		}
	}
}



void Display_English_Alarm_UI(void)
{
	Clear_Buffer_Set_Data(0x00);//清除缓冲区

	View_English_Alarm_Area_1();
	View_English_Alarm_Area_2();

	Write_Buffer_To_LCD();//缓冲区数据写入LCD
}


void View_English_Alarm_Area_1(void)
{
	uint8_t y_add, sy_add, disp_alaem_tmp, pos_tmp1;

	y_add = 0;//必须先清零
	sy_add = 0;//必须先清零

	if (key_alarm_status == 101)//报警记录一级菜单模式
	{
		Display_Hz_Char(FONT_EN_bjjl, 0, Y_MAIN_L0, 0);//第一行 标题栏

		for (disp_alaem_tmp = 0; disp_alaem_tmp < 5; disp_alaem_tmp++)//一屏内最多显示5行
		{
			if (ctr_status[eCTR_ALARM_RECORD] < 5)//一级菜单仅有两屏
			{
				pos_tmp1 = disp_alaem_tmp;//第一屏
			}
			else if (ctr_status[eCTR_ALARM_RECORD] < 10)
			{
				pos_tmp1 = disp_alaem_tmp + 5;//第二屏
			}
			else
			{
				if (disp_alaem_tmp > 3)
				{
					break;
				}
				pos_tmp1 = disp_alaem_tmp + 10;//第三屏
			}

			if (alarm_number[eALARM_NUMBER_num] == 0)
			{
				Display_Hz_Char(">>", 0, 22, 1);
				Display_Hz_Char(&display_english_row_alarm[0][0], 16, 22, 1);
			}
			else
			{
				if (pos_tmp1 == ctr_status[eCTR_ALARM_RECORD])
				{
					sy_add = (disp_alaem_tmp * 22) + 22;//历史故障选项地址
					Display_Hz_Char(">>", 0, sy_add, 1);
				}

				y_add += 22;

				if (alarm_record[pos_tmp1][eALARM_name] != 0)
				{
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					GUI_User_DispDec(pos_tmp1 + 1, XX);
					Display_Digit(16, y_add, 1);
					Display_Hz_Char(".", 32, y_add, 1);
					Display_Hz_Char(&display_english_row_alarm[alarm_record[pos_tmp1][eALARM_name]][6], 40, y_add, 1);
				}
			}
		}
	}
}



void View_English_Alarm_Area_2(void)
{
	if (key_alarm_status == 102)//报警记录二级菜单模式
	{
		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(ctr_status[eCTR_ALARM_RECORD] + 1, XX);
		Display_Digit(0, Y_MAIN_L0, 0);
		Display_Hz_Char(".", 16, Y_MAIN_L0, 0);
		Display_Hz_Char(&display_english_row_alarm[alarm_record[ctr_status[eCTR_ALARM_RECORD]][eALARM_name]][6], 24, Y_MAIN_L0, 0);//第一行 一级菜单名称

		if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
		{
			second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
			Display_Hz_Char("↑", 207, 22, 1);
			Display_Hz_Char("↓", 219, 22, 1);
		}

		if (ctr_status[eCTR_ALARM_RECORD_PAGE] == VIEW_PAGE0)
		{
			Display_Hz_Char("1/3", 215, Y_MAIN_L0, 0);
			View_English_Alarm_Data_Area_1(ctr_status[eCTR_ALARM_RECORD]);
		}
		if (ctr_status[eCTR_ALARM_RECORD_PAGE] == VIEW_PAGE1)
		{
			Display_Hz_Char("2/3", 215, Y_MAIN_L0, 0);
			View_English_Alarm_Data_Area_2(ctr_status[eCTR_ALARM_RECORD]);
		}
		if (ctr_status[eCTR_ALARM_RECORD_PAGE] == VIEW_PAGE2)
		{
			Display_Hz_Char("3/3", 215, Y_MAIN_L0, 0);
			View_English_Alarm_Data_Area_3(ctr_status[eCTR_ALARM_RECORD]);
		}
	}
}






void Display_English_GrandTotal_UI(void)
{
	Clear_Buffer_Set_Data(0x00);//清除缓冲区

	View_Grand_total_English_Area_1();

	Write_Buffer_To_LCD();//缓冲区数据写入LCD
}


void View_Grand_total_English_Area_1(void)
{
	uint32_t un_val, up_val;
	uint8_t point_mode;

	if ((key_mode_status >= 104) && (key_mode_status < 106))//二级菜单模式
	{
		Display_Hz_Char(FONT_EN_ljcs, 0, Y_MAIN_L0, 0);//第一行 标题栏

		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//第二行  设置编号
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&FONT_EN_acc_varry_first[set_num_val_array][0], 24, Y_MAIN_L1, 1);//第二行 设置内容

		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
		//显示设置编号
		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
		GUI_User_DispDec(6, XX);
		Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号

		if (key_mode_status == 104)//设置处于查看模式时，显示上下箭头
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char("↑", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("↓", 219, Y_MAIN_L1, 1);
			}
		}

		point_mode = acc_value_position[set_num_val_array][1];
		point_mode %= 10;//标志的个位为小数点

		un_val = 0;//下限
		up_val = acc_value_max[set_num_val_array];//上限

		if (set_tmp_check == U8_LOW)
		{
			Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//第四行  超限提示
		}
		else
		{
			Display5row_English_check_note(&display5rowCN_Grand_total_English_uint[acc_value_position[set_num_val_array][0]][0]);//第四行  设置注释
		}

		if (key_mode_status == 105)//参数修改模式
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//第五行  范围

			if (point_mode == 0)//整数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 60, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 142, Y_MAIN_L4, 1);//第四行
				//设置范围
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(un_val, X);
				Display_Digit(48, Y_MAIN_L4, 1);//第四行
				GUI_User_DispDec(up_val, XXXXXXXXX);
				Display_Digit(70, Y_MAIN_L4, 1);//第四行
			}
			else if (point_mode == 1)//小数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 60, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 150, Y_MAIN_L4, 1);//第四行
				//设置范围
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(un_val, X);
				Display_Digit(48, Y_MAIN_L4, 1);//第四行
				GUI_User_DispDec(up_val, XXXXXXXX_Y);
				Display_Digit(70, Y_MAIN_L4, 1);//第四行
			}
			else if (point_mode == 2)//小数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 84, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 126, Y_MAIN_L4, 1);//第四行
				//设置范围
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(10, X_YY);
				Display_Digit(48, Y_MAIN_L4, 1);//第四行
				GUI_User_DispDec(up_val, X_YY);
				Display_Digit(94, Y_MAIN_L4, 1);//第四行
			}
		}

		if (key_mode_status == 104)//参数查看模式
		{
			Set_Font_x(DIGITAL_MONOSPAC821_1216);//设置数字字体
			switch (set_num_val_array)
			{
			case 0:
				GUI_User_DispDec(count_val[eCOUNT_start], un_XXXXX);
				Display_Digit(148, Y_MAIN_L2, 1);//第二行
				break;
			case 1:
				GUI_User_DispDec(count_val[eCOUNT_crank], un_XXXXX);
				Display_Digit(148, Y_MAIN_L2, 1);//第二行
				break;
			case 2:
				GUI_User_DispDec(count_time, un_XXXXXXXX_Y);
				Display_Digit(100, Y_MAIN_L2, 1);//第二行
				break;
			case 3:
				GUI_User_DispDec(count_power_time, un_XXXXXXXX_Y);
				Display_Digit(100, Y_MAIN_L2, 1);//第二行
				break;
			case 4:
				GUI_User_DispDec(count_kwh, un_XXXXXXXXX);
				Display_Digit(100, Y_MAIN_L2, 1);//第二行
				break;
			case 5:
				GUI_User_DispDec(table_val[eTABLE_value], un_X_YY);
				Display_Digit(160, Y_MAIN_L2, 1);//第二行
				break;
			default:break;
			}
		}

		GUI_HLine(0, 49, 239, 1);
		GUI_HLine(0, 50, 239, 1);

		GUI_HLine(0, 105, 239, 1);
		GUI_HLine(0, 106, 239, 1);
	}
}


void  GUI_HLine(uint8_t x0, uint8_t y0, uint8_t x1, TCOLOR color)
{
	uint8_t  bak;

	if (x0 > x1) 						// 对x0、x1大小进行排列，以便画图
	{
		bak = x1;
		x1 = x0;
		x0 = bak;
	}

	do
	{
		GUI_Point(x0, y0, color);		// 逐点显示，描出垂直线
		x0++;
	} while (x1 >= x0);
}

uint8_t  GUI_Point(uint8_t x, uint8_t y, TCOLOR color)
{
	uint8_t   bak;

	// 参数过滤 
	if (x >= GUI_LCM_XMAX) return(0);
	if (y >= GUI_LCM_YMAX) return(0);

	// 设置相应的点为1或0 
	bak = LCM_ReadByte(x, y);
	if (0 == color)
	{
		bak &= (~DEC_HEX_TAB[y & 0x07]);
	}
	else
	{
		bak |= DEC_HEX_TAB[y & 0x07];
	}

	// 刷新显示 
	LCM_WriteByte(x, y, bak);
	return(1);
}

uint8_t  LCM_ReadByte(uint8_t x, uint8_t y)
{
	y = y >> 3;
	return(gui_disp_buf[y][x]);
}


//=========================================================================================================

void Display_English_CheckModify_UI(void)
{
	Clear_Buffer_Set_Data(0x00);//清除缓冲区

	View_English_Check_Area_1();

	View_English_Check_Area_2();

	Write_Buffer_To_LCD();//缓冲区数据写入LCD
}

void View_English_Check_Area_1(void)
{
	if (key_mode_status == 102)//输入密码模式
	{
		Display_Hz_Char(FONT_EN_cjzjljz, 0, Y_MAIN_L0, 0);//第一行 标题栏
		Display_Hz_Char(FONT_EN_SRMM, 0, Y_MAIN_L1, 1);//第二行 输入密码
		Display_Digital_Char(&position_dx[0], 80, Y_MAIN_L2, 5, 0);

		if (menu_passwoed_change == U8_LOW)//重新输入密码
		{
			Display_Hz_Char(FONT_EN_MMCW, 44, Y_MAIN_L3, 1);//第二行 输入密码
		}
	}
}

void View_English_Check_Area_2(void)
{
	uint16_t un_val, up_val;
	uint8_t point_mode;
	uint16_t tem, temp;

	if ((key_mode_status >= 104) && (key_mode_status < 106))//二级菜单模式
	{
		Display_Hz_Char(FONT_EN_cjzjljz, 0, Y_MAIN_L0, 0);//第一行 标题栏

		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//第二行  设置编号
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&FONT_EN_check_varry_first[set_num_val_array][0], 24, Y_MAIN_L1, 1);//第二行 设置内容

		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
		//显示设置编号
		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
		GUI_User_DispDec(24, XX);
		Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号

		if (key_mode_status == 104)//设置处于查看模式时，显示上下箭头
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char("↑", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("↓", 219, Y_MAIN_L1, 1);
			}
		}

		point_mode = Measured_value_position[set_num_val_array][2];
		point_mode %= 10;//标志的个位为小数点

		tem = val_u16n[Measured_value_position[menu_second_number][0]];
		temp = (uint16_t)(tem * 0.3);
		un_val = ABS(tem - temp);//下限
		up_val = tem + temp;//上限

		if (set_tmp_check == U8_LOW)
		{
			Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//第四行  超限提示
		}
		else
		{
			Display5row_English_check_note(&display5rowEN_Check_uint[Measured_value_position[set_num_val_array][1]][0]);//第四行  设置注释
		}

		if (key_mode_status == 105)//参数修改模式
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//第五行  范围

			if (point_mode == 0)//整数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 82, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 124, Y_MAIN_L4, 1);//第四行
				//设置范围
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(un_val, XXXX);
				Display_Digit(48, Y_MAIN_L4, 1);//第四行
				GUI_User_DispDec(up_val, XXXX);
				Display_Digit(92, Y_MAIN_L4, 1);//第四行
			}
			else//小数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//第四行
				//油压电压式传感器，显示特殊处理20201210
				if (set_num_val_array == 2) //为电压式油压传感器
				{
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					GUI_User_DispDec(un_val, un_X_YYY);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(up_val, un_X_YYY);
					Display_Digit(100, Y_MAIN_L4, 1);//第四行	
				}
				else
				{
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					GUI_User_DispDec(un_val, XXX_Y);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(up_val, XXX_Y);
					Display_Digit(100, Y_MAIN_L4, 1);//第四行				
				}
			}
		}
		//设置值
		Set_Font_x(DIGITAL_MONOSPAC821_1216);//设置数字字体
		if (point_mode == 0)//整数
		{
			GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_XXXX);
			Display_Digit(159, Y_MAIN_L2, 1);//第二行
		}
		else//小数
		{
			//油压电压式传感器，显示特殊处理20201210
			if (set_num_val_array == 2) //为电压式油压传感器
			{
				GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_X_YYY);
				Display_Digit(159, Y_MAIN_L2, 1);//第二行
			}
			else {
				GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_XXX_Y);
				Display_Digit(159, Y_MAIN_L2, 1);//第二行			
			}

		}

		GUI_HLine(0, 49, 239, 1);
		GUI_HLine(0, 50, 239, 1);

		GUI_HLine(0, 105, 239, 1);
		GUI_HLine(0, 106, 239, 1);
	}
}

//=========================================================================================================

void Display_English_Set_UI(void)
{
	Clear_Buffer_Set_Data(0x00);//清除缓冲区

	View_English_Set_Area_1();
	View_English_Set_Area_7();
	View_English_Set_Area_8();
	View_English_Set_Area_2();
	View_English_Set_Area_3();
	if (set_num_val_array == eSET_Zhiban_dates)
	{
		View_English_Set_Area_6();
	}
	else if ((set_num_val_array < eSET_User_RX_op) && (set_num_val_array != eSET_ECU_HideCode))//小于油压阻值曲线数176 且不等于ECU隐藏码
	{
		View_English_Set_Area_4();
	}
	else
	{
		View_English_Set_Area_5();
	}
	Write_Buffer_To_LCD();//缓冲区数据写入LCD
}


void View_English_Set_Area_7(void)
{
	uint8_t ton_temp, y_add, sy_add;

	y_add = 0;//必须先清零
	sy_add = 0;//必须先清零
	if (key_mode_status == 108)//选项语言
	{
		if (set_variable[eSET_sel_langule] == 3)
		{
			Display_Hz_Char(FONT_ES_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Idioma/语言", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
		}
		else if (set_variable[eSET_sel_langule] == 4)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Язык/语言", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
		}
		else if (set_variable[eSET_sel_langule] == 5)
		{
			Display_Hz_Char(FONT_TD_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("DIL SECIMI/语言", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
		}
		else
		{
			Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Language/语言", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
		}

		for (ton_temp = 0; ton_temp < set_min_max_tag_init[eSET_sel_langule][1] + 1; ton_temp++)
		{
			if (ton_temp < 5)
			{
				y_add += Y_MAIN_L0 + nDOT + 6;
				if (ctr_status[eCTR_SELECT_LANGUAGE] == ton_temp)
				{
					sy_add = (ctr_status[eCTR_SELECT_LANGUAGE] * (Y_MAIN_L0 + nDOT + 6)) + Y_MAIN_L0 + nDOT + 6;//语言选项地址
					Display_Hz_Char(">>", 0, sy_add, 1);
				}
				Display_Hz_Char(&display5row_set_selLANGE[ton_temp][0], 16, y_add, 1);
			}
			else
			{
				y_add += Y_MAIN_L0 + nDOT + 6;
				if (y_add > 120)
				{
					y_add = Y_MAIN_L0 + nDOT + 6;
				}
				if (ctr_status[eCTR_SELECT_LANGUAGE] == ton_temp)
				{
					sy_add = ((ctr_status[eCTR_SELECT_LANGUAGE] - 5) * (Y_MAIN_L0 + nDOT + 6)) + Y_MAIN_L0 + nDOT + 6;//语言选项地址
					Display_Hz_Char(">>", 120, sy_add, 1);
				}
				Display_Hz_Char(&display5row_set_selLANGE[ton_temp][0], 136, y_add, 1);
			}
		}
	}
}


void View_English_Set_Area_8(void)
{
	if (key_mode_status == 109)//查看控制器信息
	{
		if (set_variable[eSET_sel_langule] == 3)
		{
			Display_Hz_Char(FONT_ES_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Información", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
			Display_Hz_Char("Modelo:", 0, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 56, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char("Software:", 0, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 72, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char("Edicion:", 0, Y_MAIN_L3, 1);//第四行		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 64, Y_MAIN_L3, 1);//第四行		
		}
		else if (set_variable[eSET_sel_langule] == 4)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Информация", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
			Display_Hz_Char("модель:", 0, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 56, Y_MAIN_L1, 1);//第二行
			Display_Hz_Char("ПО:", 0, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 24, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char("Версия:", 0, Y_MAIN_L3, 1);//第四行		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 56, Y_MAIN_L3, 1);//第四行		
		}
		else if (set_variable[eSET_sel_langule] == 5)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("KONTROL BILGI", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
			Display_Hz_Char("MODEL:", 0, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 48, Y_MAIN_L1, 1);//第二行
			Display_Hz_Char("YAZILIM:", 0, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 64, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char("KONU:", 0, Y_MAIN_L3, 1);//第四行		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 40, Y_MAIN_L3, 1);//第四行		
		}
		else
		{
			Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
			Display_Hz_Char("Information", 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
			Display_Hz_Char("Model:", 0, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 48, Y_MAIN_L1, 1);//第二行  
			Display_Hz_Char("Version:", 0, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 64, Y_MAIN_L2, 1);//第三行
			Display_Hz_Char("Release time:", 0, Y_MAIN_L3, 1);//第四行		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 104, Y_MAIN_L3, 1);//第四行		
		}
		//暂时屏蔽		
		//		Display_Hz_Char("ID:",0,Y_MAIN_L4,1);//第五行
		//		Display_Hz_Char(dev_name,24,Y_MAIN_L4,1);
	}
}


void View_English_Set_Area_2(void)
{
	if (key_mode_status == 102)//输入密码模式
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
		Display_Hz_Char(FONT_EN_SRMM, 0, Y_MAIN_L1, 1);//第二行 输入密码
		Display_Digital_Char(&position_dx[0], 80, Y_MAIN_L2, 5, 0);

		if (menu_passwoed_change == U8_LOW)//重新输入密码
		{
			Display_Hz_Char(FONT_EN_MMCW, 36, Y_MAIN_L3, 1);//第二行 输入密码
		}
	}
}


void View_English_Set_Area_3(void)
{
	uint8_t ton_temp, y_add, sy_add;

	y_add = 0;//必须先清零
	sy_add = 0;//必须先清零

	if (key_mode_status == 103)//一级菜单模式
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏

		for (ton_temp = 0; ton_temp < 5; ton_temp++)
		{
			y_add += 22;
			if (lcm_menu[ton_temp][1] == U8_HIGH)
			{
				sy_add = (ton_temp * 22) + 22;//语言选项地址
				Display_Hz_Char(">>", 0, sy_add, 1);
			}
			Display_Hz_Char(&FONT_EN_set_varry_first[lcm_menu[ton_temp][0]][0], 16, y_add, 1);
		}
	}
}


void View_English_Set_Area_6(void)
{
	if (key_mode_status >= 104)//二级菜单模式
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏
		Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 80, Y_MAIN_L0, 0);//第一行 一级菜单名称

		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//第二行  设置编号
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//第二行 设置内容

		if (key_mode_status == 104)//设置处于查看模式时，显示上下箭头
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char("↑", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("↓", 219, Y_MAIN_L1, 1);
			}

			ZhiBan_date(0);
		}

		if (key_mode_status == 105)//参数修改模式
		{
			ZhiBan_date(zhiban_date_number);
		}

		//		GUI_HLine(0,21,239,1);
		//		GUI_HLine(0,22,239,1);

		GUI_HLine(0, 49, 239, 1);
		GUI_HLine(0, 50, 239, 1);
	}
}


void View_English_Set_Area_4(void)
{
	uint16_t disp_tmp, un_val, up_val;
	uint8_t point_mode, note_mode;
	if ((key_mode_status >= 104) && (key_mode_status < 106))//二级菜单模式
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏

		if (key_mode_status == 104)//设置处于查看模式时，显示上下箭头
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char("↑", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("↓", 219, Y_MAIN_L1, 1);
			}
		}
		//快速操作与详细操作切换
		if (ctr_status[eCTR_SET_SWITCH] == U8_HIGH)
		{
			if (menu_first_number > 8)//保证大于10的设置项可以去掉小数点显示
			{
				Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 70, Y_MAIN_L0, 0);//第一行 一级菜单名称
			}
			else
			{
				Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][2], 70, Y_MAIN_L0, 0);//第一行 一级菜单名称
			}

			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//显示设置编号
			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
			GUI_User_DispDec(menu_addar_number[menu_first_number][1] + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号
		}
		else
		{
			Display_Hz_Char("Fast Parameters", 70, Y_MAIN_L0, 0);//第一行
			set_num_val_array = Fast_Set_Parameter_Number[menu_second_number];//处理显示的数据

			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//显示设置编号
			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
			GUI_User_DispDec(MENU_FASTSET_NUM + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号
		}

		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//第二行  设置编号
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//第二行 设置内容


		point_mode = set_min_max_tag_init[set_num_val_array][2];
		point_mode %= 10;//标志的个位为小数点
		note_mode = set_min_max_tag_init[set_num_val_array][2];
		note_mode /= 10;//标志的模式


		//超过5位时显示值/10 存储范围为0-36000 表示0-3600秒
		if (key_mode_status == 105)//参数修改模式
		{
			disp_tmp = set_tmp_val;//显示参数值
		}
		else
		{
			if (set_num_val_array == eSET_Current_week) //特别处理：进入星期设置中，由于星期未存入存储器，故无法获得星期，进入后，直接取当前星期做为注释显示
			{
				disp_tmp = calendar.week;
			}
			else
			{
				disp_tmp = set_variable[set_num_val_array];//显示参数值
			}
		}

		un_val = set_min_max_tag_init[set_num_val_array][0];
		up_val = set_min_max_tag_init[set_num_val_array][1];
		if (ctr_status[eCTR_SET_SWITCH] == U8_LOW && set_num_val_array == eSET_ECU_HideCode) //快速设置时 ECU特殊报警码 菜单显示问题	
		{

		}
		else
		{
			if (set_tmp_check == U8_LOW)
			{
				Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//第四行  超限提示
			}
			else
			{
				Display_English_row_note(FONT_set5row_Interpretation, disp_tmp);//第四行  设置注释
			}
		}
		if (key_mode_status == 105)//参数修改模式
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			if ((set_num_val_array == eSET_Current_date) || (set_num_val_array == eSET_maintain_date))
			{
				Set_Font_x(DIGITAL_MONOSPAC821_1216);//设置数字字体
				GUI_User_DispDec(20, XX);
				Display_Digit(16, Y_MAIN_L2, 1);//第二行
			}
			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//第五行  范围

			if (point_mode == 0)//整数
			{
				if (note_mode == 9)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//第四行
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					GUI_User_DispDec(un_val, XX_XX);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(up_val, XX_XX);
					Display_Digit(100, Y_MAIN_L4, 1);//第四行
				}
				else if (set_num_val_array == eSET_Current_date)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行					
					Display_Hz_Char("-", 130, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char(")", 220, Y_MAIN_L4, 1);//第四行
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					Display_One(13, 80, Y_MAIN_L4, 1);//第四行
					Display_One(13, 104, Y_MAIN_L4, 1);//第四行
					Display_One(13, 172, Y_MAIN_L4, 1);//第四行
					Display_One(13, 196, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(2016, XXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(1, XX);
					Display_Digit(88, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(1, XX);
					Display_Digit(112, Y_MAIN_L4, 1);//第四行

					GUI_User_DispDec(2099, XXXX);
					Display_Digit(140, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(12, XX);
					Display_Digit(180, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(31, XX);
					Display_Digit(204, Y_MAIN_L4, 1);//第四行
				}
				else if (set_num_val_array == eSET_maintain_date)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行					
					Display_Hz_Char("-", 130, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char(")", 220, Y_MAIN_L4, 1);//第四行
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					Display_One(13, 80, Y_MAIN_L4, 1);//第四行
					Display_One(13, 104, Y_MAIN_L4, 1);//第四行
					Display_One(13, 172, Y_MAIN_L4, 1);//第四行
					Display_One(13, 196, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(2000, XXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(1, XX);
					Display_Digit(88, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(1, XX);
					Display_Digit(112, Y_MAIN_L4, 1);//第四行

					GUI_User_DispDec(2099, XXXX);
					Display_Digit(140, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(12, XX);
					Display_Digit(180, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(31, XX);
					Display_Digit(204, Y_MAIN_L4, 1);//第四行
				}
				else
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//第四行
					Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//第四行
					//设置范围
					Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
					GUI_User_DispDec(un_val, XXXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//第四行
					GUI_User_DispDec(up_val, XXXXX);
					Display_Digit(100, Y_MAIN_L4, 1);//第四行
				}
			}
			else//小数
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char("-", 98, Y_MAIN_L4, 1);//第四行
				Display_Hz_Char(")", 156, Y_MAIN_L4, 1);//第四行
				//设置范围
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(un_val, XXXX_Y);
				Display_Digit(48, Y_MAIN_L4, 1);//第四行
				GUI_User_DispDec(up_val, XXXX_Y);
				Display_Digit(108, Y_MAIN_L4, 1);//第四行	
			}
		}
		//设置值
		Set_Font_x(DIGITAL_MONOSPAC821_1216);//设置数字字体
		if (point_mode == 0)//整数
		{
			if ((note_mode == 9) && (set_num_val_array == eSET_Current_time))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(HM_Change_Dec(calendar.hour, calendar.minute), XX_XX);
					Display_Digit(159, Y_MAIN_L2, 1);//第二行
				}
			}
			else if ((note_mode == 10) && (set_num_val_array == eSET_Current_date))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(20, XX);
					Display_Digit(111, Y_MAIN_L2, 1);//第二行
					GUI_User_DispDec(YMD_Change_Dec(calendar.year, calendar.month, calendar.day), XX_XX_XX);
					Display_Digit(135, Y_MAIN_L2, 1);//第二行
				}
			}
			else if ((note_mode == 2) && (set_num_val_array == eSET_Current_week))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(calendar.week, XX);
					Display_Digit(135, Y_MAIN_L2, 1);//第二行
				}
			}
			else if ((note_mode == 10) && (set_num_val_array == eSET_maintain_date))//保养日期
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(20, XX);
					Display_Digit(111, Y_MAIN_L2, 1);//第二行
					GUI_User_DispDec(Date_Change_Dec(set_variable[set_num_val_array]), XX_XX_XX);
					Display_Digit(135, Y_MAIN_L2, 1);//第二行
				}
			}
			else if ((note_mode == 9) && (set_num_val_array != eSET_Current_time))
			{
				GUI_User_DispDec(set_variable[set_num_val_array], XX_XX);
				Display_Digit(159, Y_MAIN_L2, 1);//第二行
			}
			else if (set_num_val_array == eSET_user_password)//密码操作不需要消影
			{
				GUI_User_DispDec(set_variable[set_num_val_array], XXXXX);
				Display_Digit(159, Y_MAIN_L2, 1);//第二行
			}
			else
			{
				if (ctr_status[eCTR_SET_SWITCH] == U8_LOW && set_num_val_array == eSET_ECU_HideCode) //快速设置时 ECU特殊报警码 菜单显示问题	
				{

				}
				else
				{
					GUI_User_DispDec(set_variable[set_num_val_array], un_XXXXX);
					Display_Digit(159, Y_MAIN_L2, 1);//第二行				
				}
			}
		}
		else//小数
		{
			GUI_User_DispDec(set_variable[set_num_val_array], un_XXXX_Y);
			Display_Digit(151, Y_MAIN_L2, 1);//第二行
		}

		//		GUI_HLine(0,21,239,1);
		//		GUI_HLine(0,22,239,1);

		GUI_HLine(0, 49, 239, 1);
		GUI_HLine(0, 50, 239, 1);

		GUI_HLine(0, 105, 239, 1);
		GUI_HLine(0, 106, 239, 1);
	}
}

void View_English_Set_Area_5(void)
{
	if (key_mode_status >= 104)//二级菜单模式
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//第一行 标题栏

		if (ctr_status[eCTR_SET_SWITCH] == U8_LOW) //快速设置时 ECU特殊报警码 菜单显示问题
		{
			Display_Hz_Char("Fast Parameters", 70, Y_MAIN_L0, 0);//第一行
			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//显示设置编号
			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
			GUI_User_DispDec(MENU_FASTSET_NUM + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号
		}
		else
		{
			Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 80, Y_MAIN_L0, 0);//第一行 一级菜单名称
			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//显示设置编号
			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//第一行  设置编号
			GUI_User_DispDec(menu_addar_number[menu_first_number][1] + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//第一行  设置编号
		}
		Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//第二行  设置编号
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//第二行 设置内容
		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);

		if ((key_mode_status == 104) || (key_mode_status == 105))//设置处于查看模式时，显示上下箭头
		{
			if (second_blinking == U8_HIGH)//秒指示每秒闪烁一次
			{
				second_blinking = U8_LOW;//秒指示清零，等待下次闪烁
				Display_Hz_Char("↑", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("↓", 219, Y_MAIN_L1, 1);
			}
		}

		if (key_mode_status == 105 || key_mode_status == 106)//三级菜单模式
		{
			if (set_num_val_array == eSET_ECU_HideCode)
			{
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(menu_third_number + 1, XX);
				Display_Digit(16, Y_MAIN_L2, 1);//第三行  曲线点数编号
				Display_Hz_Char("group", 34, Y_MAIN_L2, 1);//第三行 
				Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
				switch (set_num_val_array)
				{
				case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECU隐藏码
				default:break;
				}
			}
			else
			{
				Display_Hz_Char("point", 16, Y_MAIN_L2, 1);//第三行 
				Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
				GUI_User_DispDec(menu_third_number + 1, XX);
				Display_Digit(56, Y_MAIN_L2, 1);//第三行  曲线点数编号
				Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
				switch (set_num_val_array)
				{
				case eSET_User_RX_op:English_Curve_modification_mode(rin_user_op_rx, menu_third_number); break;//油压阻值曲线
				case eSET_User_DX_op:English_Curve_modification_mode(rin_user_op_dx, menu_third_number); break;//油压电压曲线
				case eSET_User_RX_t:English_Curve_modification_mode(rin_user_t_rx, menu_third_number); break;//温度阻值曲线
				case eSET_User_RX_fl:English_Curve_modification_mode(rin_user_fl_rx, menu_third_number); break;//油位阻值曲线
				case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECU隐藏码
				default:break;
				}

				if (set_tmp_check == U8_LOW)
				{
					Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//第四行  超限提示
				}
				else
				{
					Display_English_row_note(FONT_set5row_Interpretation, 1);//第四行  设置注释
				}
			}
		}
		if (key_mode_status == 107)//三级菜单模式 ECU隐藏特殊报警码 14组
		{
			//			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			//			GUI_User_DispDec(menu_third_number+1,XX);
			//			Display_Digit(56,Y_MAIN_L2,1);//第三行  曲线点数编号
			//			Display_Hz_Char(".",72,Y_MAIN_L2,1);

			Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
			GUI_User_DispDec(menu_third_number + 1, XX);
			Display_Digit(16, Y_MAIN_L2, 1);//第三行  曲线点数编号
			Display_Hz_Char("group", 34, Y_MAIN_L2, 1);//第三行 
			Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
			switch (set_num_val_array)
			{
			case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECU隐藏特殊报警码
			default:break;
			}
		}
		//		GUI_HLine(0,21,239,1);
		//		GUI_HLine(0,22,239,1);

		GUI_HLine(0, 49, 239, 1);
		GUI_HLine(0, 50, 239, 1);

		GUI_HLine(0, 105, 239, 1);
		GUI_HLine(0, 106, 239, 1);
	}
}

//===================================================================================================


void Display_english_row_Page_Teeth(void)
{
	//格式示例 1
	Clear_Buffer_Data(0x00);//清除缓冲区

	Display_Hz_Char("Flywheel     teeth,", 44, Y_MAIN_L2, 1);
	Display_Hz_Char("saved successfully!", 44, Y_MAIN_L2 + 16, 1);

	Set_Font_x(DIGITAL_SYSTEM_0816);//设置数字字体
	GUI_User_DispDec(set_variable[eSET_teeth], un_XXX);
	Display_Digit(116, Y_MAIN_L2, 1);//第一行  设置编号
	Write_Buffer_To_LCD();//缓冲区数据写入LCD
}

//===================================================================================================

void Display_English_View_UI(void)
{
	if (display_logo_status == U8_HIGH)//写完LOGO后显示LOGO
	{
		Display_Logo_Page();
	}
	else
	{
		Clear_Buffer_Data(0x00);//清除缓冲区

		if (write_logo_status == U8_HIGH)//写入开机界面中
		{
			Display_english_row_Page_LOGO();
		}
		else if ((save_set_status == U8_HIGH) || (reset_set_status == U8_HIGH) || (clear_alarm_status == U8_HIGH))//保存参数设置
		{
			Display_english_row_Page_DATA();
		}
		//		else if((val_u16n[eVAL16_battery]==0x00)&&(ctr_status[eCTR_USB_STATUS]==U8_HIGH)&&(check_uint_variable[eCHECK_init_flag]==0xaaaa))//USB通信连接
		//		{
		//			Display_english_row_Page_USB();
		//		}
		else//正常显示
		{
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE0)
			{
				Display_english_row_Page_HOME();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE1)
			{
				Display_english_row_Page_ENGINE();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE2)
			{
				Display_english_row_Page_GENERATOR();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE3)
			{
				Display_english_row_Page_LOAD_ONE();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE4)
			{
				Display_english_row_Page_LOAD_TWO();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE5)
			{
				Display_english_row_Page_ECU_ONE();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE6)
			{
				Display_english_row_Page_ECU_TWO();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE7)
			{
				Display_english_row_Page_ECU_THREE();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE8)
			{
				Display_english_row_Page_COUNT();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE9)
			{
				Display_english_row_Page_DATE();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE10)
			{
				Display_english_row_Page_INOUT();
			}
#if Mode_GCS18X_2			
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE11)
			{
				Display_english_row_Page_MAIN();
			}
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE12)
			{
				Display_english_row_Page_FAULT();
			}
#elif Mode_GCS18X_0
			if (ctr_status[eCTR_DISP_NUM] == VIEW_PAGE11)
			{
				Display_english_row_Page_FAULT();
			}
#endif
			Display_english_row_Page_static();
		}

		Write_Buffer_To_LCD();//缓冲区数据写入LCD
	}
}
*/