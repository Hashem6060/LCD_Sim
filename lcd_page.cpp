

#include "lcd_page.h"


//void Display_UI(void)
//{
//	Display_Operating_Prompt();
//	{		
//	Display_English_UI(); 
//		
//	}
//
//}



//void Display_Operating_Prompt(void)
//{
//	
//
//	if (true)//ÊÖ¶¯²Ù×÷ÌáÊ¾
//	{
//		while (true)//ÊÖ¶¯¼ü²Ù×÷ÌáÊ¾
//		{
//
//			if (true)
//			{
//				Display_Hz_Char("ÓÑÇéÌáÐÑ", 88, Y_MAIN_L1, 1);
//
//				Display_Hz_Char("°´ÏÂSTART¼ü¿ÉÆð¶¯·¢¶¯»ú!", 24, Y_MAIN_L2, 1);
//			}
//			else
//			{
//				Display_Hz_Char("TIPS", 104, Y_MAIN_L0, 1);
//				Display_Hz_Char("Press the 'START' key to start", 0, Y_MAIN_L1, 1);
//				Display_Hz_Char("the engine!", 0, Y_MAIN_L1 + 16, 1);
//			}
//
//
//			OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err); //ÑÓÊ±100ms
//		}
//
//		
//	}
//
//	if (true)//Æð¶¯²Ù×÷ÌáÊ¾
//	{
//		while (true)//Æð¶¯¼ü²Ù×÷ÌáÊ¾
//		{
//
//
//			if (true)
//			{
//				Display_Hz_Char("ÐèÒªÆð¶¯·¢¶¯»ú,", 64, Y_MAIN_L1, 1);
//				Display_Hz_Char("ÇëÏÈ°´ÏÂ'MANUAL'°´¼ü!", 40, Y_MAIN_L2, 1);
//			}
//			else
//			{
//				Display_Hz_Char("To start the engine,press the", 0, Y_MAIN_L1, 1);
//				Display_Hz_Char("'MANUAL' button first!", 0, Y_MAIN_L1 + 16, 1);
//			}
//
//
//			OSTimeDlyHMSM(0, 0, 0, 100, OS_OPT_TIME_HMSM_STRICT, &err); //ÑÓÊ±100ms
//		}
//	}
//}

// display_prompt.cpp - FIXED VERSION
void Display_Operating_Prompt(LCDEmulator& g_lcd) {
	g_lcd.clear();
	
	 // Manual Key Prompt
		if (true) {  // English
			g_lcd.displayText("TIPS", 104, Y_MAIN_L0, true);
			g_lcd.displayText("Press the 'START' key to start" , 0, Y_MAIN_L1, true);  // ← Shorter!
			g_lcd.displayText("the engine!", 0, Y_MAIN_L1 + 16, true);
		}
	
	  // Start Key Prompt
		if (false) {  // English
			g_lcd.displayText("To start engine, press", 0, Y_MAIN_L1, true);  // ← Shorter!
			g_lcd.displayText("'MANUAL' button first!", 0, Y_MAIN_L1 + 16, true);
		}
}

/*


void Display_English_UI(void)
{
	if (true)//ÀúÊ·¹ÊÕÏ¼ÇÂ¼
	{
		Display_English_Alarm_UI();
	}
	else if (true)//ÀÛ¼Æ²ÎÊýÉèÖÃÄ£Ê½
	{
		Display_English_GrandTotal_UI();
	}
	else if (true)//Ð£Õý²ÎÊýÉèÖÃÄ£Ê½
	{
		Display_English_CheckModify_UI();
	}
	else if (true)//ÉèÖÃÄ£Ê½
	{
		Display_English_Set_UI();
	}
	else//Õý³£ÏÔÊ¾Ä£Ê½
	{
		if (true)
		{
			Display_english_row_Page_Teeth();
		}
		else
		{
			if (true)//µ±´ý»úÏÔÊ¾LOGO±êÖ¾ÖÃÎ»Ê±£¬²»Ö´ÐÐ±¾º¯Êý
			{
				Display_English_View_UI();
			}
		}
	}
}



void Display_English_Alarm_UI(void)
{
	Clear_Buffer_Set_Data(0x00);//Çå³ý»º³åÇø

	View_English_Alarm_Area_1();
	View_English_Alarm_Area_2();

	Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
}


void View_English_Alarm_Area_1(void)
{
	uint8_t y_add, sy_add, disp_alaem_tmp, pos_tmp1;

	y_add = 0;//±ØÐëÏÈÇåÁã
	sy_add = 0;//±ØÐëÏÈÇåÁã

	if (key_alarm_status == 101)//±¨¾¯¼ÇÂ¼Ò»¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_bjjl, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		for (disp_alaem_tmp = 0; disp_alaem_tmp < 5; disp_alaem_tmp++)//Ò»ÆÁÄÚ×î¶àÏÔÊ¾5ÐÐ
		{
			if (ctr_status[eCTR_ALARM_RECORD] < 5)//Ò»¼¶²Ëµ¥½öÓÐÁ½ÆÁ
			{
				pos_tmp1 = disp_alaem_tmp;//µÚÒ»ÆÁ
			}
			else if (ctr_status[eCTR_ALARM_RECORD] < 10)
			{
				pos_tmp1 = disp_alaem_tmp + 5;//µÚ¶þÆÁ
			}
			else
			{
				if (disp_alaem_tmp > 3)
				{
					break;
				}
				pos_tmp1 = disp_alaem_tmp + 10;//µÚÈýÆÁ
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
					sy_add = (disp_alaem_tmp * 22) + 22;//ÀúÊ·¹ÊÕÏÑ¡ÏîµØÖ·
					Display_Hz_Char(">>", 0, sy_add, 1);
				}

				y_add += 22;

				if (alarm_record[pos_tmp1][eALARM_name] != 0)
				{
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
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
	if (key_alarm_status == 102)//±¨¾¯¼ÇÂ¼¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(ctr_status[eCTR_ALARM_RECORD] + 1, XX);
		Display_Digit(0, Y_MAIN_L0, 0);
		Display_Hz_Char(".", 16, Y_MAIN_L0, 0);
		Display_Hz_Char(&display_english_row_alarm[alarm_record[ctr_status[eCTR_ALARM_RECORD]][eALARM_name]][6], 24, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ

		if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
		{
			second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
			Display_Hz_Char("¡ü", 207, 22, 1);
			Display_Hz_Char("¡ý", 219, 22, 1);
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
	Clear_Buffer_Set_Data(0x00);//Çå³ý»º³åÇø

	View_Grand_total_English_Area_1();

	Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
}


void View_Grand_total_English_Area_1(void)
{
	uint32_t un_val, up_val;
	uint8_t point_mode;

	if ((key_mode_status >= 104) && (key_mode_status < 106))//¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_ljcs, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  ÉèÖÃ±àºÅ
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&FONT_EN_acc_varry_first[set_num_val_array][0], 24, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÉèÖÃÄÚÈÝ

		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
		//ÏÔÊ¾ÉèÖÃ±àºÅ
		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		GUI_User_DispDec(6, XX);
		Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ

		if (key_mode_status == 104)//ÉèÖÃ´¦ÓÚ²é¿´Ä£Ê½Ê±£¬ÏÔÊ¾ÉÏÏÂ¼ýÍ·
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char("¡ü", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("¡ý", 219, Y_MAIN_L1, 1);
			}
		}

		point_mode = acc_value_position[set_num_val_array][1];
		point_mode %= 10;//±êÖ¾µÄ¸öÎ»ÎªÐ¡Êýµã

		un_val = 0;//ÏÂÏÞ
		up_val = acc_value_max[set_num_val_array];//ÉÏÏÞ

		if (set_tmp_check == U8_LOW)
		{
			Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//µÚËÄÐÐ  ³¬ÏÞÌáÊ¾
		}
		else
		{
			Display5row_English_check_note(&display5rowCN_Grand_total_English_uint[acc_value_position[set_num_val_array][0]][0]);//µÚËÄÐÐ  ÉèÖÃ×¢ÊÍ
		}

		if (key_mode_status == 105)//²ÎÊýÐÞ¸ÄÄ£Ê½
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//µÚÎåÐÐ  ·¶Î§

			if (point_mode == 0)//ÕûÊý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 60, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 142, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÉèÖÃ·¶Î§
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(un_val, X);
				Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
				GUI_User_DispDec(up_val, XXXXXXXXX);
				Display_Digit(70, Y_MAIN_L4, 1);//µÚËÄÐÐ
			}
			else if (point_mode == 1)//Ð¡Êý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 60, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 150, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÉèÖÃ·¶Î§
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(un_val, X);
				Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
				GUI_User_DispDec(up_val, XXXXXXXX_Y);
				Display_Digit(70, Y_MAIN_L4, 1);//µÚËÄÐÐ
			}
			else if (point_mode == 2)//Ð¡Êý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 84, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 126, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÉèÖÃ·¶Î§
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(10, X_YY);
				Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
				GUI_User_DispDec(up_val, X_YY);
				Display_Digit(94, Y_MAIN_L4, 1);//µÚËÄÐÐ
			}
		}

		if (key_mode_status == 104)//²ÎÊý²é¿´Ä£Ê½
		{
			Set_Font_x(DIGITAL_MONOSPAC821_1216);//ÉèÖÃÊý×Ö×ÖÌå
			switch (set_num_val_array)
			{
			case 0:
				GUI_User_DispDec(count_val[eCOUNT_start], un_XXXXX);
				Display_Digit(148, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				break;
			case 1:
				GUI_User_DispDec(count_val[eCOUNT_crank], un_XXXXX);
				Display_Digit(148, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				break;
			case 2:
				GUI_User_DispDec(count_time, un_XXXXXXXX_Y);
				Display_Digit(100, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				break;
			case 3:
				GUI_User_DispDec(count_power_time, un_XXXXXXXX_Y);
				Display_Digit(100, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				break;
			case 4:
				GUI_User_DispDec(count_kwh, un_XXXXXXXXX);
				Display_Digit(100, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				break;
			case 5:
				GUI_User_DispDec(table_val[eTABLE_value], un_X_YY);
				Display_Digit(160, Y_MAIN_L2, 1);//µÚ¶þÐÐ
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

	if (x0 > x1) 						// ¶Ôx0¡¢x1´óÐ¡½øÐÐÅÅÁÐ£¬ÒÔ±ã»­Í¼
	{
		bak = x1;
		x1 = x0;
		x0 = bak;
	}

	do
	{
		GUI_Point(x0, y0, color);		// ÖðµãÏÔÊ¾£¬Ãè³ö´¹Ö±Ïß
		x0++;
	} while (x1 >= x0);
}

uint8_t  GUI_Point(uint8_t x, uint8_t y, TCOLOR color)
{
	uint8_t   bak;

	// ²ÎÊý¹ýÂË 
	if (x >= GUI_LCM_XMAX) return(0);
	if (y >= GUI_LCM_YMAX) return(0);

	// ÉèÖÃÏàÓ¦µÄµãÎª1»ò0 
	bak = LCM_ReadByte(x, y);
	if (0 == color)
	{
		bak &= (~DEC_HEX_TAB[y & 0x07]);
	}
	else
	{
		bak |= DEC_HEX_TAB[y & 0x07];
	}

	// Ë¢ÐÂÏÔÊ¾ 
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
	Clear_Buffer_Set_Data(0x00);//Çå³ý»º³åÇø

	View_English_Check_Area_1();

	View_English_Check_Area_2();

	Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
}

void View_English_Check_Area_1(void)
{
	if (key_mode_status == 102)//ÊäÈëÃÜÂëÄ£Ê½
	{
		Display_Hz_Char(FONT_EN_cjzjljz, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
		Display_Hz_Char(FONT_EN_SRMM, 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÊäÈëÃÜÂë
		Display_Digital_Char(&position_dx[0], 80, Y_MAIN_L2, 5, 0);

		if (menu_passwoed_change == U8_LOW)//ÖØÐÂÊäÈëÃÜÂë
		{
			Display_Hz_Char(FONT_EN_MMCW, 44, Y_MAIN_L3, 1);//µÚ¶þÐÐ ÊäÈëÃÜÂë
		}
	}
}

void View_English_Check_Area_2(void)
{
	uint16_t un_val, up_val;
	uint8_t point_mode;
	uint16_t tem, temp;

	if ((key_mode_status >= 104) && (key_mode_status < 106))//¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_cjzjljz, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  ÉèÖÃ±àºÅ
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&FONT_EN_check_varry_first[set_num_val_array][0], 24, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÉèÖÃÄÚÈÝ

		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
		//ÏÔÊ¾ÉèÖÃ±àºÅ
		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		GUI_User_DispDec(24, XX);
		Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ

		if (key_mode_status == 104)//ÉèÖÃ´¦ÓÚ²é¿´Ä£Ê½Ê±£¬ÏÔÊ¾ÉÏÏÂ¼ýÍ·
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char("¡ü", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("¡ý", 219, Y_MAIN_L1, 1);
			}
		}

		point_mode = Measured_value_position[set_num_val_array][2];
		point_mode %= 10;//±êÖ¾µÄ¸öÎ»ÎªÐ¡Êýµã

		tem = val_u16n[Measured_value_position[menu_second_number][0]];
		temp = (uint16_t)(tem * 0.3);
		un_val = ABS(tem - temp);//ÏÂÏÞ
		up_val = tem + temp;//ÉÏÏÞ

		if (set_tmp_check == U8_LOW)
		{
			Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//µÚËÄÐÐ  ³¬ÏÞÌáÊ¾
		}
		else
		{
			Display5row_English_check_note(&display5rowEN_Check_uint[Measured_value_position[set_num_val_array][1]][0]);//µÚËÄÐÐ  ÉèÖÃ×¢ÊÍ
		}

		if (key_mode_status == 105)//²ÎÊýÐÞ¸ÄÄ£Ê½
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//µÚÎåÐÐ  ·¶Î§

			if (point_mode == 0)//ÕûÊý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 82, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 124, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÉèÖÃ·¶Î§
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(un_val, XXXX);
				Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
				GUI_User_DispDec(up_val, XXXX);
				Display_Digit(92, Y_MAIN_L4, 1);//µÚËÄÐÐ
			}
			else//Ð¡Êý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÓÍÑ¹µçÑ¹Ê½´«¸ÐÆ÷£¬ÏÔÊ¾ÌØÊâ´¦Àí20201210
				if (set_num_val_array == 2) //ÎªµçÑ¹Ê½ÓÍÑ¹´«¸ÐÆ÷
				{
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					GUI_User_DispDec(un_val, un_X_YYY);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(up_val, un_X_YYY);
					Display_Digit(100, Y_MAIN_L4, 1);//µÚËÄÐÐ	
				}
				else
				{
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					GUI_User_DispDec(un_val, XXX_Y);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(up_val, XXX_Y);
					Display_Digit(100, Y_MAIN_L4, 1);//µÚËÄÐÐ				
				}
			}
		}
		//ÉèÖÃÖµ
		Set_Font_x(DIGITAL_MONOSPAC821_1216);//ÉèÖÃÊý×Ö×ÖÌå
		if (point_mode == 0)//ÕûÊý
		{
			GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_XXXX);
			Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ
		}
		else//Ð¡Êý
		{
			//ÓÍÑ¹µçÑ¹Ê½´«¸ÐÆ÷£¬ÏÔÊ¾ÌØÊâ´¦Àí20201210
			if (set_num_val_array == 2) //ÎªµçÑ¹Ê½ÓÍÑ¹´«¸ÐÆ÷
			{
				GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_X_YYY);
				Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ
			}
			else {
				GUI_User_DispDec(val_u16n[Measured_value_position[set_num_val_array][0]], un_XXX_Y);
				Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ			
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
	Clear_Buffer_Set_Data(0x00);//Çå³ý»º³åÇø

	View_English_Set_Area_1();
	View_English_Set_Area_7();
	View_English_Set_Area_8();
	View_English_Set_Area_2();
	View_English_Set_Area_3();
	if (set_num_val_array == eSET_Zhiban_dates)
	{
		View_English_Set_Area_6();
	}
	else if ((set_num_val_array < eSET_User_RX_op) && (set_num_val_array != eSET_ECU_HideCode))//Ð¡ÓÚÓÍÑ¹×èÖµÇúÏßÊý176 ÇÒ²»µÈÓÚECUÒþ²ØÂë
	{
		View_English_Set_Area_4();
	}
	else
	{
		View_English_Set_Area_5();
	}
	Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
}


void View_English_Set_Area_7(void)
{
	uint8_t ton_temp, y_add, sy_add;

	y_add = 0;//±ØÐëÏÈÇåÁã
	sy_add = 0;//±ØÐëÏÈÇåÁã
	if (key_mode_status == 108)//Ñ¡ÏîÓïÑÔ
	{
		if (set_variable[eSET_sel_langule] == 3)
		{
			Display_Hz_Char(FONT_ES_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("Idioma/ÓïÑÔ", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
		}
		else if (set_variable[eSET_sel_langule] == 4)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("§Á§Ù§í§Ü/ÓïÑÔ", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
		}
		else if (set_variable[eSET_sel_langule] == 5)
		{
			Display_Hz_Char(FONT_TD_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("DIL SECIMI/ÓïÑÔ", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
		}
		else
		{
			Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("Language/ÓïÑÔ", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
		}

		for (ton_temp = 0; ton_temp < set_min_max_tag_init[eSET_sel_langule][1] + 1; ton_temp++)
		{
			if (ton_temp < 5)
			{
				y_add += Y_MAIN_L0 + nDOT + 6;
				if (ctr_status[eCTR_SELECT_LANGUAGE] == ton_temp)
				{
					sy_add = (ctr_status[eCTR_SELECT_LANGUAGE] * (Y_MAIN_L0 + nDOT + 6)) + Y_MAIN_L0 + nDOT + 6;//ÓïÑÔÑ¡ÏîµØÖ·
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
					sy_add = ((ctr_status[eCTR_SELECT_LANGUAGE] - 5) * (Y_MAIN_L0 + nDOT + 6)) + Y_MAIN_L0 + nDOT + 6;//ÓïÑÔÑ¡ÏîµØÖ·
					Display_Hz_Char(">>", 120, sy_add, 1);
				}
				Display_Hz_Char(&display5row_set_selLANGE[ton_temp][0], 136, y_add, 1);
			}
		}
	}
}


void View_English_Set_Area_8(void)
{
	if (key_mode_status == 109)//²é¿´¿ØÖÆÆ÷ÐÅÏ¢
	{
		if (set_variable[eSET_sel_langule] == 3)
		{
			Display_Hz_Char(FONT_ES_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("Informaci¨®n", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			Display_Hz_Char("Modelo:", 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 56, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char("Software:", 0, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 72, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char("Edicion:", 0, Y_MAIN_L3, 1);//µÚËÄÐÐ		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 64, Y_MAIN_L3, 1);//µÚËÄÐÐ		
		}
		else if (set_variable[eSET_sel_langule] == 4)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("§ª§ß§æ§à§â§Þ§Ñ§è§Ú§ñ", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			Display_Hz_Char("§Þ§à§Õ§Ö§Ý§î:", 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 56, Y_MAIN_L1, 1);//µÚ¶þÐÐ
			Display_Hz_Char("§±§°:", 0, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 24, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char("§£§Ö§â§ã§Ú§ñ:", 0, Y_MAIN_L3, 1);//µÚËÄÐÐ		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 56, Y_MAIN_L3, 1);//µÚËÄÐÐ		
		}
		else if (set_variable[eSET_sel_langule] == 5)
		{
			Display_Hz_Char(FONT_PY_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("KONTROL BILGI", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			Display_Hz_Char("MODEL:", 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 48, Y_MAIN_L1, 1);//µÚ¶þÐÐ
			Display_Hz_Char("YAZILIM:", 0, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 64, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char("KONU:", 0, Y_MAIN_L3, 1);//µÚËÄÐÐ		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 40, Y_MAIN_L3, 1);//µÚËÄÐÐ		
		}
		else
		{
			Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
			Display_Hz_Char("Information", 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			Display_Hz_Char("Model:", 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char(MODULE_MODEL_DISPLAY, 48, Y_MAIN_L1, 1);//µÚ¶þÐÐ  
			Display_Hz_Char("Version:", 0, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char(MODULE_VERSION_DISPLAY, 64, Y_MAIN_L2, 1);//µÚÈýÐÐ
			Display_Hz_Char("Release time:", 0, Y_MAIN_L3, 1);//µÚËÄÐÐ		
			Display_Hz_Char(MODULE_UPDATA_DATE_DISPLAY, 104, Y_MAIN_L3, 1);//µÚËÄÐÐ		
		}
		//ÔÝÊ±ÆÁ±Î		
		//		Display_Hz_Char("ID:",0,Y_MAIN_L4,1);//µÚÎåÐÐ
		//		Display_Hz_Char(dev_name,24,Y_MAIN_L4,1);
	}
}


void View_English_Set_Area_2(void)
{
	if (key_mode_status == 102)//ÊäÈëÃÜÂëÄ£Ê½
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
		Display_Hz_Char(FONT_EN_SRMM, 0, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÊäÈëÃÜÂë
		Display_Digital_Char(&position_dx[0], 80, Y_MAIN_L2, 5, 0);

		if (menu_passwoed_change == U8_LOW)//ÖØÐÂÊäÈëÃÜÂë
		{
			Display_Hz_Char(FONT_EN_MMCW, 36, Y_MAIN_L3, 1);//µÚ¶þÐÐ ÊäÈëÃÜÂë
		}
	}
}


void View_English_Set_Area_3(void)
{
	uint8_t ton_temp, y_add, sy_add;

	y_add = 0;//±ØÐëÏÈÇåÁã
	sy_add = 0;//±ØÐëÏÈÇåÁã

	if (key_mode_status == 103)//Ò»¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		for (ton_temp = 0; ton_temp < 5; ton_temp++)
		{
			y_add += 22;
			if (lcm_menu[ton_temp][1] == U8_HIGH)
			{
				sy_add = (ton_temp * 22) + 22;//ÓïÑÔÑ¡ÏîµØÖ·
				Display_Hz_Char(">>", 0, sy_add, 1);
			}
			Display_Hz_Char(&FONT_EN_set_varry_first[lcm_menu[ton_temp][0]][0], 16, y_add, 1);
		}
	}
}


void View_English_Set_Area_6(void)
{
	if (key_mode_status >= 104)//¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸
		Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ

		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  ÉèÖÃ±àºÅ
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÉèÖÃÄÚÈÝ

		if (key_mode_status == 104)//ÉèÖÃ´¦ÓÚ²é¿´Ä£Ê½Ê±£¬ÏÔÊ¾ÉÏÏÂ¼ýÍ·
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char("¡ü", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("¡ý", 219, Y_MAIN_L1, 1);
			}

			ZhiBan_date(0);
		}

		if (key_mode_status == 105)//²ÎÊýÐÞ¸ÄÄ£Ê½
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
	if ((key_mode_status >= 104) && (key_mode_status < 106))//¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		if (key_mode_status == 104)//ÉèÖÃ´¦ÓÚ²é¿´Ä£Ê½Ê±£¬ÏÔÊ¾ÉÏÏÂ¼ýÍ·
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char("¡ü", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("¡ý", 219, Y_MAIN_L1, 1);
			}
		}
		//¿ìËÙ²Ù×÷ÓëÏêÏ¸²Ù×÷ÇÐ»»
		if (ctr_status[eCTR_SET_SWITCH] == U8_HIGH)
		{
			if (menu_first_number > 8)//±£Ö¤´óÓÚ10µÄÉèÖÃÏî¿ÉÒÔÈ¥µôÐ¡ÊýµãÏÔÊ¾
			{
				Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 70, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			}
			else
			{
				Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][2], 70, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			}

			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//ÏÔÊ¾ÉèÖÃ±àºÅ
			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
			GUI_User_DispDec(menu_addar_number[menu_first_number][1] + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		}
		else
		{
			Display_Hz_Char("Fast Parameters", 70, Y_MAIN_L0, 0);//µÚÒ»ÐÐ
			set_num_val_array = Fast_Set_Parameter_Number[menu_second_number];//´¦ÀíÏÔÊ¾µÄÊý¾Ý

			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//ÏÔÊ¾ÉèÖÃ±àºÅ
			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
			GUI_User_DispDec(MENU_FASTSET_NUM + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		}

		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  ÉèÖÃ±àºÅ
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÉèÖÃÄÚÈÝ


		point_mode = set_min_max_tag_init[set_num_val_array][2];
		point_mode %= 10;//±êÖ¾µÄ¸öÎ»ÎªÐ¡Êýµã
		note_mode = set_min_max_tag_init[set_num_val_array][2];
		note_mode /= 10;//±êÖ¾µÄÄ£Ê½


		//³¬¹ý5Î»Ê±ÏÔÊ¾Öµ/10 ´æ´¢·¶Î§Îª0-36000 ±íÊ¾0-3600Ãë
		if (key_mode_status == 105)//²ÎÊýÐÞ¸ÄÄ£Ê½
		{
			disp_tmp = set_tmp_val;//ÏÔÊ¾²ÎÊýÖµ
		}
		else
		{
			if (set_num_val_array == eSET_Current_week) //ÌØ±ð´¦Àí£º½øÈëÐÇÆÚÉèÖÃÖÐ£¬ÓÉÓÚÐÇÆÚÎ´´æÈë´æ´¢Æ÷£¬¹ÊÎÞ·¨»ñµÃÐÇÆÚ£¬½øÈëºó£¬Ö±½ÓÈ¡µ±Ç°ÐÇÆÚ×öÎª×¢ÊÍÏÔÊ¾
			{
				disp_tmp = calendar.week;
			}
			else
			{
				disp_tmp = set_variable[set_num_val_array];//ÏÔÊ¾²ÎÊýÖµ
			}
		}

		un_val = set_min_max_tag_init[set_num_val_array][0];
		up_val = set_min_max_tag_init[set_num_val_array][1];
		if (ctr_status[eCTR_SET_SWITCH] == U8_LOW && set_num_val_array == eSET_ECU_HideCode) //¿ìËÙÉèÖÃÊ± ECUÌØÊâ±¨¾¯Âë ²Ëµ¥ÏÔÊ¾ÎÊÌâ	
		{

		}
		else
		{
			if (set_tmp_check == U8_LOW)
			{
				Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//µÚËÄÐÐ  ³¬ÏÞÌáÊ¾
			}
			else
			{
				Display_English_row_note(FONT_set5row_Interpretation, disp_tmp);//µÚËÄÐÐ  ÉèÖÃ×¢ÊÍ
			}
		}
		if (key_mode_status == 105)//²ÎÊýÐÞ¸ÄÄ£Ê½
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char(">>", 0, Y_MAIN_L2, 1);
			}

			if ((set_num_val_array == eSET_Current_date) || (set_num_val_array == eSET_maintain_date))
			{
				Set_Font_x(DIGITAL_MONOSPAC821_1216);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(20, XX);
				Display_Digit(16, Y_MAIN_L2, 1);//µÚ¶þÐÐ
			}
			Display_Digital_Char(&position_dx[0], 40, Y_MAIN_L2, position_length, point_mode);

			Display_Hz_Char(FONT_EN_FW, 0, Y_MAIN_L4, 1);//µÚÎåÐÐ  ·¶Î§

			if (point_mode == 0)//ÕûÊý
			{
				if (note_mode == 9)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//µÚËÄÐÐ
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					GUI_User_DispDec(un_val, XX_XX);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(up_val, XX_XX);
					Display_Digit(100, Y_MAIN_L4, 1);//µÚËÄÐÐ
				}
				else if (set_num_val_array == eSET_Current_date)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ					
					Display_Hz_Char("-", 130, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char(")", 220, Y_MAIN_L4, 1);//µÚËÄÐÐ
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					Display_One(13, 80, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 104, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 172, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 196, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(2016, XXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(1, XX);
					Display_Digit(88, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(1, XX);
					Display_Digit(112, Y_MAIN_L4, 1);//µÚËÄÐÐ

					GUI_User_DispDec(2099, XXXX);
					Display_Digit(140, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(12, XX);
					Display_Digit(180, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(31, XX);
					Display_Digit(204, Y_MAIN_L4, 1);//µÚËÄÐÐ
				}
				else if (set_num_val_array == eSET_maintain_date)
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ					
					Display_Hz_Char("-", 130, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char(")", 220, Y_MAIN_L4, 1);//µÚËÄÐÐ
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					Display_One(13, 80, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 104, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 172, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_One(13, 196, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(2000, XXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(1, XX);
					Display_Digit(88, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(1, XX);
					Display_Digit(112, Y_MAIN_L4, 1);//µÚËÄÐÐ

					GUI_User_DispDec(2099, XXXX);
					Display_Digit(140, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(12, XX);
					Display_Digit(180, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(31, XX);
					Display_Digit(204, Y_MAIN_L4, 1);//µÚËÄÐÐ
				}
				else
				{
					Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char("-", 90, Y_MAIN_L4, 1);//µÚËÄÐÐ
					Display_Hz_Char(")", 140, Y_MAIN_L4, 1);//µÚËÄÐÐ
					//ÉèÖÃ·¶Î§
					Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
					GUI_User_DispDec(un_val, XXXXX);
					Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
					GUI_User_DispDec(up_val, XXXXX);
					Display_Digit(100, Y_MAIN_L4, 1);//µÚËÄÐÐ
				}
			}
			else//Ð¡Êý
			{
				Display_Hz_Char("(", 40, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char("-", 98, Y_MAIN_L4, 1);//µÚËÄÐÐ
				Display_Hz_Char(")", 156, Y_MAIN_L4, 1);//µÚËÄÐÐ
				//ÉèÖÃ·¶Î§
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(un_val, XXXX_Y);
				Display_Digit(48, Y_MAIN_L4, 1);//µÚËÄÐÐ
				GUI_User_DispDec(up_val, XXXX_Y);
				Display_Digit(108, Y_MAIN_L4, 1);//µÚËÄÐÐ	
			}
		}
		//ÉèÖÃÖµ
		Set_Font_x(DIGITAL_MONOSPAC821_1216);//ÉèÖÃÊý×Ö×ÖÌå
		if (point_mode == 0)//ÕûÊý
		{
			if ((note_mode == 9) && (set_num_val_array == eSET_Current_time))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(HM_Change_Dec(calendar.hour, calendar.minute), XX_XX);
					Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				}
			}
			else if ((note_mode == 10) && (set_num_val_array == eSET_Current_date))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(20, XX);
					Display_Digit(111, Y_MAIN_L2, 1);//µÚ¶þÐÐ
					GUI_User_DispDec(YMD_Change_Dec(calendar.year, calendar.month, calendar.day), XX_XX_XX);
					Display_Digit(135, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				}
			}
			else if ((note_mode == 2) && (set_num_val_array == eSET_Current_week))
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(calendar.week, XX);
					Display_Digit(135, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				}
			}
			else if ((note_mode == 10) && (set_num_val_array == eSET_maintain_date))//±£ÑøÈÕÆÚ
			{
				if (set_view_modify != U8_HIGH)
				{
					GUI_User_DispDec(20, XX);
					Display_Digit(111, Y_MAIN_L2, 1);//µÚ¶þÐÐ
					GUI_User_DispDec(Date_Change_Dec(set_variable[set_num_val_array]), XX_XX_XX);
					Display_Digit(135, Y_MAIN_L2, 1);//µÚ¶þÐÐ
				}
			}
			else if ((note_mode == 9) && (set_num_val_array != eSET_Current_time))
			{
				GUI_User_DispDec(set_variable[set_num_val_array], XX_XX);
				Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ
			}
			else if (set_num_val_array == eSET_user_password)//ÃÜÂë²Ù×÷²»ÐèÒªÏûÓ°
			{
				GUI_User_DispDec(set_variable[set_num_val_array], XXXXX);
				Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ
			}
			else
			{
				if (ctr_status[eCTR_SET_SWITCH] == U8_LOW && set_num_val_array == eSET_ECU_HideCode) //¿ìËÙÉèÖÃÊ± ECUÌØÊâ±¨¾¯Âë ²Ëµ¥ÏÔÊ¾ÎÊÌâ	
				{

				}
				else
				{
					GUI_User_DispDec(set_variable[set_num_val_array], un_XXXXX);
					Display_Digit(159, Y_MAIN_L2, 1);//µÚ¶þÐÐ				
				}
			}
		}
		else//Ð¡Êý
		{
			GUI_User_DispDec(set_variable[set_num_val_array], un_XXXX_Y);
			Display_Digit(151, Y_MAIN_L2, 1);//µÚ¶þÐÐ
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
	if (key_mode_status >= 104)//¶þ¼¶²Ëµ¥Ä£Ê½
	{
		Display_Hz_Char(FONT_EN_SZZ, 0, Y_MAIN_L0, 0);//µÚÒ»ÐÐ ±êÌâÀ¸

		if (ctr_status[eCTR_SET_SWITCH] == U8_LOW) //¿ìËÙÉèÖÃÊ± ECUÌØÊâ±¨¾¯Âë ²Ëµ¥ÏÔÊ¾ÎÊÌâ
		{
			Display_Hz_Char("Fast Parameters", 70, Y_MAIN_L0, 0);//µÚÒ»ÐÐ
			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//ÏÔÊ¾ÉèÖÃ±àºÅ
			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
			GUI_User_DispDec(MENU_FASTSET_NUM + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		}
		else
		{
			Display_Hz_Char(&FONT_EN_set_varry_first[menu_first_number][3], 80, Y_MAIN_L0, 0);//µÚÒ»ÐÐ Ò»¼¶²Ëµ¥Ãû³Æ
			Display_Hz_Char("/", 215, Y_MAIN_L0, 0);
			//ÏÔÊ¾ÉèÖÃ±àºÅ
			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			GUI_User_DispDec(menu_second_number + 1, XX);
			Display_Digit(199, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
			GUI_User_DispDec(menu_addar_number[menu_first_number][1] + 1, XX);
			Display_Digit(223, Y_MAIN_L0, 0);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
		}
		Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
		GUI_User_DispDec(menu_second_number + 1, XX);
		Display_Digit(0, Y_MAIN_L1, 1);//µÚ¶þÐÐ  ÉèÖÃ±àºÅ
		Display_Hz_Char(".", 16, Y_MAIN_L1, 1);
		Display_Hz_Char(&display5row_set_tips[set_num_val_array][0], 24, Y_MAIN_L1, 1);//µÚ¶þÐÐ ÉèÖÃÄÚÈÝ
		Display_Hz_Char("/", 215, Y_MAIN_L0, 0);

		if ((key_mode_status == 104) || (key_mode_status == 105))//ÉèÖÃ´¦ÓÚ²é¿´Ä£Ê½Ê±£¬ÏÔÊ¾ÉÏÏÂ¼ýÍ·
		{
			if (second_blinking == U8_HIGH)//ÃëÖ¸Ê¾Ã¿ÃëÉÁË¸Ò»´Î
			{
				second_blinking = U8_LOW;//ÃëÖ¸Ê¾ÇåÁã£¬µÈ´ýÏÂ´ÎÉÁË¸
				Display_Hz_Char("¡ü", 207, Y_MAIN_L1, 1);
				Display_Hz_Char("¡ý", 219, Y_MAIN_L1, 1);
			}
		}

		if (key_mode_status == 105 || key_mode_status == 106)//Èý¼¶²Ëµ¥Ä£Ê½
		{
			if (set_num_val_array == eSET_ECU_HideCode)
			{
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(menu_third_number + 1, XX);
				Display_Digit(16, Y_MAIN_L2, 1);//µÚÈýÐÐ  ÇúÏßµãÊý±àºÅ
				Display_Hz_Char("group", 34, Y_MAIN_L2, 1);//µÚÈýÐÐ 
				Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
				switch (set_num_val_array)
				{
				case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECUÒþ²ØÂë
				default:break;
				}
			}
			else
			{
				Display_Hz_Char("point", 16, Y_MAIN_L2, 1);//µÚÈýÐÐ 
				Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
				GUI_User_DispDec(menu_third_number + 1, XX);
				Display_Digit(56, Y_MAIN_L2, 1);//µÚÈýÐÐ  ÇúÏßµãÊý±àºÅ
				Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
				switch (set_num_val_array)
				{
				case eSET_User_RX_op:English_Curve_modification_mode(rin_user_op_rx, menu_third_number); break;//ÓÍÑ¹×èÖµÇúÏß
				case eSET_User_DX_op:English_Curve_modification_mode(rin_user_op_dx, menu_third_number); break;//ÓÍÑ¹µçÑ¹ÇúÏß
				case eSET_User_RX_t:English_Curve_modification_mode(rin_user_t_rx, menu_third_number); break;//ÎÂ¶È×èÖµÇúÏß
				case eSET_User_RX_fl:English_Curve_modification_mode(rin_user_fl_rx, menu_third_number); break;//ÓÍÎ»×èÖµÇúÏß
				case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECUÒþ²ØÂë
				default:break;
				}

				if (set_tmp_check == U8_LOW)
				{
					Display_Hz_Char(FONT_EN_CX, 0, Y_MAIN_L3, 1);//µÚËÄÐÐ  ³¬ÏÞÌáÊ¾
				}
				else
				{
					Display_English_row_note(FONT_set5row_Interpretation, 1);//µÚËÄÐÐ  ÉèÖÃ×¢ÊÍ
				}
			}
		}
		if (key_mode_status == 107)//Èý¼¶²Ëµ¥Ä£Ê½ ECUÒþ²ØÌØÊâ±¨¾¯Âë 14×é
		{
			//			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			//			GUI_User_DispDec(menu_third_number+1,XX);
			//			Display_Digit(56,Y_MAIN_L2,1);//µÚÈýÐÐ  ÇúÏßµãÊý±àºÅ
			//			Display_Hz_Char(".",72,Y_MAIN_L2,1);

			Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
			GUI_User_DispDec(menu_third_number + 1, XX);
			Display_Digit(16, Y_MAIN_L2, 1);//µÚÈýÐÐ  ÇúÏßµãÊý±àºÅ
			Display_Hz_Char("group", 34, Y_MAIN_L2, 1);//µÚÈýÐÐ 
			Display_Hz_Char(".", 72, Y_MAIN_L2, 1);
			switch (set_num_val_array)
			{
			case eSET_ECU_HideCode:English_ECU_modification_mode(ECU_Hide_Code, menu_third_number); break;//ECUÒþ²ØÌØÊâ±¨¾¯Âë
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
	//¸ñÊ½Ê¾Àý 1
	Clear_Buffer_Data(0x00);//Çå³ý»º³åÇø

	Display_Hz_Char("Flywheel     teeth,", 44, Y_MAIN_L2, 1);
	Display_Hz_Char("saved successfully!", 44, Y_MAIN_L2 + 16, 1);

	Set_Font_x(DIGITAL_SYSTEM_0816);//ÉèÖÃÊý×Ö×ÖÌå
	GUI_User_DispDec(set_variable[eSET_teeth], un_XXX);
	Display_Digit(116, Y_MAIN_L2, 1);//µÚÒ»ÐÐ  ÉèÖÃ±àºÅ
	Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
}

//===================================================================================================

void Display_English_View_UI(void)
{
	if (display_logo_status == U8_HIGH)//Ð´ÍêLOGOºóÏÔÊ¾LOGO
	{
		Display_Logo_Page();
	}
	else
	{
		Clear_Buffer_Data(0x00);//Çå³ý»º³åÇø

		if (write_logo_status == U8_HIGH)//Ð´Èë¿ª»ú½çÃæÖÐ
		{
			Display_english_row_Page_LOGO();
		}
		else if ((save_set_status == U8_HIGH) || (reset_set_status == U8_HIGH) || (clear_alarm_status == U8_HIGH))//±£´æ²ÎÊýÉèÖÃ
		{
			Display_english_row_Page_DATA();
		}
		//		else if((val_u16n[eVAL16_battery]==0x00)&&(ctr_status[eCTR_USB_STATUS]==U8_HIGH)&&(check_uint_variable[eCHECK_init_flag]==0xaaaa))//USBÍ¨ÐÅÁ¬½Ó
		//		{
		//			Display_english_row_Page_USB();
		//		}
		else//Õý³£ÏÔÊ¾
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

		Write_Buffer_To_LCD();//»º³åÇøÊý¾ÝÐ´ÈëLCD
	}
}
*/