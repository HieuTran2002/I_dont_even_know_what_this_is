//*****************************8 bien toan cuc *************************************
char bien_xi_lanh_nang, bien_xi_lanh_kep, Khoang_cach_1_vong = 16, bien_xl_nang_ha, bien_xl_mac_vong, bien_xl_chot, bien_xl_kep_vong, bien_xl_day, bien_xl_tru_giua, bien_xl_keo_loxo;
char vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0, Resetnangvong = 0;

int max_speed = 50;
int speed_temp = 0;
int en_tru = 60;
int RoboMode = 0;

int GAP_BONG(void);

// Hieu's copyright
void Quay_Mam(bool chieu, int speed);
void Di_Chuyen_Truc_X(bool chieu, int speed);

void Bam_thanh_laser_phai(int speed, int AngleHead, int lazer_stable_phai, int num_change_stable)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * 15;

	if (fix > 650)
		fix = 650;

	if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(0 - fix, speed, AngleHead, 0.1);
	}
	else if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(0 + fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(0, speed, AngleHead, 0.1);
}
void Bam_thanh_laser_phai_lui(int speed, int AngleHead, int lazer_stable_phai, int num_change_stable)
{
	int fix;
	fix = abs(lazePhaiValue - lazer_stable_phai) * 15;

	if (fix > 500)
		fix = 500;

	if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(-1800 + fix, speed, AngleHead, 0.1);
	}
	else if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(1800 - fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(1800, speed, AngleHead, 0.1);
}

void Bam_thanh_laser_trai(int speed, int AngleHead, int lazer_stable_trai, int num_change_stable)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_trai) * 15;

	if (fix > 500)
		fix = 500;

	if (lazeTraiValue - lazer_stable_trai > num_change_stable)
	{
		robotRunAngle(0 + fix, speed, AngleHead, 0.2);
	}
	else if (lazeTraiValue - lazer_stable_trai < num_change_stable)
	{
		robotRunAngle(0 - fix, speed, AngleHead, 0.2);
	}
	else
		robotRunAngle(0, speed, AngleHead, 0.2);
}

void Bam_thanh_laser_trai_lui(int speed, int AngleHead, int lazer_stable_trai, int num_change_stable)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_trai) * 15;

	if (fix > 500)
		fix = 500;

	if (lazeTraiValue - lazer_stable_trai > num_change_stable)
	{
		robotRunAngle(1800 - fix, speed, AngleHead, 0.2);
	}
	else if (lazeTraiValue - lazer_stable_trai < num_change_stable)
	{
		robotRunAngle(-1800 + fix, speed, AngleHead, 0.2);
	}
	else
		robotRunAngle(1800, speed, AngleHead, 0.2);
}

// Hieu's copyright

void robotGamePadControl(void)
{

	int tocdo = 50, td_x = 30;
	float tocdoXoay = 0;
	int rJoy_LR = (RJOY_LR >= 5 && RJOY_LR <= 250) ? 1 : 0;
	int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

	if (UP && DOWN && RIGHT && LEFT && rJoy_LR && lJoy_LR && O)
	{				  // Khong dieu khien
		robotStop(0); // truot banh

		return;
	}
	/*_____________________________//___________________________*/

	/********************** TOC DO ****************************/
	/*_____________________________//___________________________*/
	if (!L1)
		tocdo = 35, tocdoXoay = 0.3;
	else
		tocdo = 10, tocdoXoay = 0.2;

	//--------- chay cac huong -----------
	if (!UP && DOWN && RIGHT && LEFT && L2)
		robotRun(0, tocdo);
	else if (UP && !DOWN && RIGHT && LEFT && L2)
		robotRun(1800, tocdo);
	else if (UP && DOWN && !RIGHT && LEFT && L2)
		robotRun(900, tocdo);
	else if (UP && DOWN && RIGHT && !LEFT && L2)
		robotRun(-900, tocdo);

	else if (!UP && DOWN && !RIGHT && LEFT && L2)
		robotRun(450, tocdo);
	else if (!UP && DOWN && RIGHT && !LEFT && L2)
		robotRun(-450, tocdo);
	else if (UP && !DOWN && !RIGHT && LEFT && L2)
		robotRun(1350, tocdo);
	else if (UP && !DOWN && RIGHT && !LEFT && L2)
		robotRun(-1350, tocdo);

	//-------------- Dang chay va Khong chay nua, chi xoay ----------------
	if (UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR && robotIsRun())
		robotStop(0);

	//-------------- Xoay ----------------
	if (rJoy_LR)
		robotRotateStop();
	else if ((RJOY_LR < 5) && L2)
	{
		if (robotIsRun())
			robotRotateFree(-0.3, 0);
		else
			robotRotateFree(-tocdoXoay, 0);
	}
	else if ((RJOY_LR > 250) && L2)
	{
		if (robotIsRun())
			robotRotateFree(0.3, 0);
		else
			robotRotateFree(tocdoXoay, 0);
	}

	else
		robotRotateStop();
}
//////-------------------------------------------------------------
void ADCValue_Control(void)
{
	// KHAI BAO LAZER
	static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0;
	static unsigned int lazeSauCouter = 0, lazeSau_SUM = 0;
	static unsigned int lazePhaiCouter = 0, lazePhai_SUM = 0;
	static unsigned int lazeTraiCouter = 0, lazeTrai_SUM = 0;

	// KHAI BAO BIEN TRO

	static unsigned int BientroTrucXCouter = 0, BientroTrucX_SUM = 0;
	static unsigned int BientroTrucYCouter = 0, BientroTrucY_SUM = 0;
	static unsigned int BientroMamXoayCouter = 0, BientroMamXoay_SUM = 0;
	////------------------------
	if (lazeTruocCouter++ < 200)
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		laze_nhan_banh_value = lazeTruoc_SUM / 200;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}

	if (lazeSauCouter++ < 100)
	{
		lazeSau_SUM += cam_bien_laze_sau;
	}
	else
	{
		lazeSauValue = lazeSau_SUM / 100;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}
	//

	if (lazePhaiCouter++ < 50)
	{
		lazePhai_SUM += cam_bien_laze_phai;
	}
	else
	{
		lazePhaiValue = lazePhai_SUM / 100;
		lazePhaiCouter = 0;
		lazePhai_SUM = 0;
	}

	if (lazeTraiCouter++ < 100)
	{
		lazeTrai_SUM += cam_bien_laze_trai;
	}
	else
	{
		lazeTraiValue = lazeTrai_SUM / 100;
		lazeTraiCouter = 0;
		lazeTrai_SUM = 0;
	}

	// BIEN TRO
	if (BientroTrucXCouter++ < 50)
	{
		BientroTrucX_SUM += bien_tro_nang_trucX;
	}
	else
	{
		BienTroTrucXValue = BientroTrucX_SUM / 50;
		BientroTrucXCouter = 0;
		BientroTrucX_SUM = 0;
	}

	if (BientroTrucYCouter++ < 50)
	{
		BientroTrucY_SUM += bien_tro_nang_trucY;
	}
	else
	{
		BienTroTrucYValue = BientroTrucY_SUM / 50;
		BientroTrucYCouter = 0;
		BientroTrucY_SUM = 0;
	}

	if (BientroMamXoayCouter++ < 50)
	{
		BientroMamXoay_SUM += bien_tro_xoay_mam;
	}
	else
	{
		BienTroMamXoayValue = BientroMamXoay_SUM / 50;
		BientroMamXoayCouter = 0;
		BientroMamXoay_SUM = 0;
	}
}

void bam_Thanh_Lazer_Trai_0do(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
{
	if (lazeTraiValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(0 + angle_fix, speed, AngleHead, 0.3);
	}
	else if (lazeTraiValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(0 - angle_fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(0, speed, AngleHead, 0.1);
}

void bam_Thanh_Lazer_Trai_SAN_XANH(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
{
	if (lazeTraiValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(600 - angle_fix, speed, AngleHead, 0.1);
	}
	else if (lazeTraiValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(600 + angle_fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(600, speed, AngleHead, 0.1);
}

void bam_Thanh_Lazer_Trai(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
{
	if (lazeTraiValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(0 + angle_fix, speed, AngleHead, 0.1);
	}
	else if (lazeTraiValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(0 - angle_fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(0, speed, AngleHead, 0.1);
}

void bam_Thanh_Lazer_Phai(int speed, int angle_fix, int AngleHead, int lazer_stable_truoc, int num_change_stable)
{
	if (lazePhaiValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(0 + angle_fix, speed, AngleHead, 0.1);
	}
	else if (lazePhaiValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(0 - angle_fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(0, speed, AngleHead, 0.1);
}

void test_cylinder(void)
{
	//***********************************************************************************
	if (!NUT_3 == 0)
	{
		bien_xi_lanh_nang = ~bien_xi_lanh_nang;
		while (!NUT_3)
			vTaskDelay(1);
	}
	if (bien_xi_lanh_nang == 0)
		XI_LANH_NANG_BONG_ON;
	else
		XI_LANH_NANG_BONG_OFF;
}

void giu_Mam_Xoay()
{
	if (BienTroTrucYValue < Truc_Y_Max - 200)
	{
		Mor_Mam = 2;
		return;
	}

	if (Mam_Xoay_Target < Mam_Xoay_Min)
		Mam_Xoay_Target = Mam_Xoay_Min;
	if (Mam_Xoay_Target > Mam_Xoay_Max)
		Mam_Xoay_Target = Mam_Xoay_Max;

	if (BienTroMamXoayValue < Mam_Xoay_Min)
	{
		Mor_Mam_nghich;
		Mor_Mam = 10;
		return;
	}
	if (BienTroMamXoayValue > Mam_Xoay_Max)
	{
		Mor_Mam_thuan;
		Mor_Mam = 10;
		return;
	}

	if (abs(BienTroMamXoayValue - Mam_Xoay_Target) > 5)
	{
		if (BienTroMamXoayValue > Mam_Xoay_Target)
			Mor_Mam_thuan;
		else
			Mor_Mam_nghich;

		speed_temp = abs(BienTroMamXoayValue - Mam_Xoay_Target);
		if (speed_temp > (TocDoToiDaCoKhi > 100 ? 100 : TocDoToiDaCoKhi / 2))
			speed_temp = (TocDoToiDaCoKhi > 100 ? 100 : TocDoToiDaCoKhi / 2);
		if (speed_temp < 20)
			speed_temp = (TocDoToiDaCoKhi <= 200 ? 5 : 20);

		Mor_Mam = speed_temp;
	}
	else
		Mor_Mam = 2;
}
//******************************* dieu khien truc Y **************************************************************
void Giu_Truc_Y()
{
	if (Truc_Y_Target < Truc_Y_Min)
		Truc_Y_Target = Truc_Y_Min;
	if (Truc_Y_Target > Truc_Y_Max)
		Truc_Y_Target = Truc_Y_Max;

	if (BienTroTrucYValue < Truc_Y_Min)
	{
		Mor_TrucY_len;
		Mor_TrucY = 50;
		return;
	}
	if (BienTroTrucYValue > Truc_Y_Max)
	{
		Mor_TrucY_xuong;
		Mor_TrucY = 50;
		return;
	}

	if (abs(BienTroTrucYValue - Truc_Y_Target) > 5)
	{
		if (BienTroTrucYValue > Truc_Y_Target)
			Mor_TrucY_xuong;
		else
			Mor_TrucY_len;

		speed_temp = absI(BienTroTrucYValue - Truc_Y_Target) * 2;

		if (speed_temp > TocDoToiDaCoKhi)
			speed_temp = TocDoToiDaCoKhi;
		else if (speed_temp < 15)
			speed_temp = 15;

		Mor_TrucY = speed_temp;
	}
	else
		Mor_TrucY = 2;
}

void Nang_ha_Y(void)
{
	if ((LJOY_UD > 250) && (Truc_Y_Target > Truc_Y_Min))
		Truc_Y_Target--, vTaskDelay(200);
	else if ((LJOY_UD < 5) && (Truc_Y_Target < Truc_Y_Max))
		Truc_Y_Target++, vTaskDelay(200);
}

//******************************* dieu khien truc X **************************************************************
void Giu_Truc_X(void)
{
	if (Truc_X_Target < Truc_X_Min)
		Truc_X_Target = Truc_X_Min;
	if (Truc_X_Target > Truc_X_Max)
		Truc_X_Target = Truc_X_Max;

	if (BienTroTrucXValue < Truc_X_Min)
	{
		Mor_TrucX_ra;
		Mor_TrucX = 50;
		return;
	}
	if (BienTroTrucXValue > Truc_X_Max)
	{
		Mor_TrucX_vao;
		Mor_TrucX = 50;
		return;
	}

	if (absI(BienTroTrucXValue - Truc_X_Target) > 2)
	{
		if (BienTroTrucXValue > Truc_X_Target)
			Mor_TrucX_vao;
		else
			Mor_TrucX_ra;

		speed_temp = absI(BienTroTrucXValue - Truc_X_Target) * 2;
		if (speed_temp > TocDoToiDaCoKhi)
			speed_temp = TocDoToiDaCoKhi;
		if (speed_temp < 30)
			speed_temp = 5;
		Mor_TrucX = speed_temp;
	}
	else
		Mor_TrucX = 2;
}

int GAP_BONG(void)
{
	int daGapBong = 0;
	XI_LANH_KEP_THA_BONG_ON;
	XI_LANH_NANG_BONG_OFF;

	Truc_Y_Target = Truc_Y_Min;
	vTaskDelay(1500);

	while (BienTroTrucYValue > Truc_Y_Min + 10)
	{
		if (BienTroTrucYValue < Truc_Y_Min + 75)
			XI_LANH_KEP_THA_BONG_ON;
	}

	vTaskDelay(3000);
	Truc_Y_Target = Truc_Y_Max;
	while (BienTroTrucYValue < Truc_Y_Max - 50)
		vTaskDelay(1);
	// Thay Quy
	
	for (i = 0; i < 50; i++)
	{
		if (laze_nhan_banh_value < 250)
		{
			daGapBong = 1;
		}
		else 
		{
			daGapBong = 0;
		}
		vTaskDelay(5);
	}
	return daGapBong;
}

void ChuanBiCoCauLayBong(void)
{
	Truc_Y_Target = Truc_Y_Max - 10;
	Truc_X_Target = Truc_X_Gap_Bong;
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	Servo_Cam = Servo_Cam_Tim_Bong; // Servo_Cam = 1100;
	Servo_Bong = 1900;				// 800: 0 do					1900:90 do
	XI_LANH_KEP_THA_BONG_OFF;
	XI_LANH_NANG_BONG_OFF;
}
void testCam()
{
	Servo_Cam = 1700;
	while (1)
	{
		Servo_Cam -= 100;
		if (Servo_Cam > 1000)
		{
			Servo_Cam = 1700;
			vTaskDelay(3000);
		}
		vTaskDelay(200);
	}
}

void permanentStop()
{
	robotStop(0);
	while (1)
		vTaskDelay(1000);
}