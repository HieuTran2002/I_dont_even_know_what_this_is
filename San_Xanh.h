//////************************ san xanh *********************************
void XUAT_PHAT_SAN_XANH(void)
{
	TocDoToiDaCoKhi = 75;
	RESET_ENCODER();
	robotRunAngle(900, 60, 0, 0.1);
	while (ENCODER_TONG() < 2500)
		vTaskDelay(1);
	XI_LANH_KEP_THA_BONG_OFF;
	robotRunAngle(800, 60, 0, 0.1);
	while (ENCODER_TONG() < 4000)
		vTaskDelay(1);

	robotRunAngle(700, 40, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazeTraiValue > 100)
			vTaskDelay(1);

	RESET_ENCODER();
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 1200)
		{
			Bam_thanh_laser_trai(40, 0, 22, 5);
			vTaskDelay(1);
		};

	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 3500)
		{
			Bam_thanh_laser_trai(40, 0, 17, 5);
			vTaskDelay(1);
		};

	robotRunAngle(0, 45, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazeTraiValue < 35)
			vTaskDelay(1);

	RESET_ENCODER();

	robotRunAngle(0, 30, 0, 0.1);
	while (ENCODER_TONG() < 600)
		vTaskDelay(1);
	robotStop(0);

	// len doc
	RESET_ENCODER();
	robotRunAngle(920, 40, 0, 0.1);
	while (ENCODER_TONG() < 1800)
		vTaskDelay(1);

	

	Truc_X_Target = Truc_X_Gap_Bong;
	while (ENCODER_TONG() < 3200)
		Bam_thanh_laser_trai_lui(40, 0, ViTriLazeThaBong[2], 5);

	// robotRunAngle(900,15,0,0.1);
	// while(ENCODER_TONG() < 1000 || lazeTraiValue > ViTriLazeThaBong[2]) vTaskDelay(1);

	// chay cham cho den khi thay bong
	// robotRunAngle(1450, 10, -450, 0.3);
	// while ((TAM_X == 0 || abs(TAM_Y - 18) > 10))
	// 	vTaskDelay(100);

	//-----------------------------
	TocDoToiDaCoKhi = 250;
	robotStop(0);
}

void retry_sanxanh(void)
{
	//	robotRunAngle(550,30,0,0.1);
	//	for(i=0;i<50;i++)	while(lazeTraiValue > 40 ) vTaskDelay(1);

	//	robotStop(0);
	//	RESET_ENCODER();

	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 1200)
		{
			Bam_thanh_laser_trai(40, 0, 22, 5);
			vTaskDelay(1);
		};

	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 5000)
		{
			Bam_thanh_laser_trai(40, 0, 17, 5);
			vTaskDelay(1);
		};

	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	Truc_X_Target = Truc_X_Bo_Bong;
	XI_LANH_KEP_THA_BONG_OFF;

	robotRunAngle(0, 45, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazeTraiValue < 35)
			vTaskDelay(1);

	RESET_ENCODER();

	robotRunAngle(0, 30, 0, 0.1);
	while (ENCODER_TONG() < 600)
		vTaskDelay(1);
	robotStop(0);

	// len doc
	RESET_ENCODER();
	robotRunAngle(920, 40, 0, 0.1);
	while (ENCODER_TONG() < 1800)
		vTaskDelay(1);

	while (ENCODER_TONG() < 3500)
		Bam_thanh_laser_trai_lui(40, 0, ViTriLazeThaBong[2], 5);

	robotRunAngle(1800, 10, 0, 0.1);
	while (ENCODER_TONG() < 3900)
		vTaskDelay(1);

	// robotRunAngle(900,15,0,0.1);
	// while(ENCODER_TONG() < 1000 || lazeTraiValue > ViTriLazeThaBong[2]) vTaskDelay(1);
	robotStop(0);
}

//---------------------------------------------------------------------------------------------
void ChayLenNeThanh_Xanh(int tocdo)
{
	if (lazePhaiValue < 25)
		robotRunAngle(450, tocdo - 15, 0, 1.5);
	else if (lazeTraiValue < 50)
		robotRunAngle(-450, tocdo - 15, 0, 1.5);
	else
		robotRunAngle(0, tocdo, 0, 1.5);
}
//---------------------------------------------------------------------------------------------
void ThaBong_Xanh(int ChoChonSilo)
{
	int KhoangCach = 999;
	int SoFrameNhanSilo = 0;
	int SiloDaChon = 10;
	int HuongLaBan = 0;

	Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
	Truc_X_Target = Truc_X_Bo_Bong;

	RESET_ENCODER();

	robotRunAngle(HuongLaBan, 60, HuongLaBan, 1.5);
	while (absI(robotAngle()) > 100)
		vTaskDelay(1);

	for (i = 0; i < 30; i++)
	{
		while (!CB_QUANG_TRAI && !CB_QUANG_PHAI)
		{
			ChayLenNeThanh_Xanh(60);
			vTaskDelay(1);
		}
		vTaskDelay(5);
	}

	RESET_ENCODER();
	for (i = 0; i < 50; i++)
	{
		while (ENCODER_TONG() < 2000)
		{
			ChayLenNeThanh_Xanh(60);
			vTaskDelay(1);
		}
	}

	for (i = 0; i < 30; i++)
	{
		while (lazePhaiValue < 250)
		{
			ChayLenNeThanh_Xanh(35);
			vTaskDelay(1);
		}
		vTaskDelay(5);
	}
	RL_DEN_CAM_ON;
	Servo_Cam = 900;
	robotStop(10);

	viTriThaBong = 2;
	for (i = 1; i < 4; i++)
	{
		if (absI(lazeTraiValue - ViTriLazeThaBong[i]) < KhoangCach)
		{
			KhoangCach = absI(lazeTraiValue - ViTriLazeThaBong[i]);
			viTriThaBong = i;
		}
	}

	// ve vi tri giua
	while (absI(lazeTraiValue - ViTriLazeThaBong[viTriThaBong]) > 5)
	{
		if (ViTriLazeThaBong[viTriThaBong] > lazeTraiValue)
		{
			// robotRunAngle(-300, 30, 0, 0.9);
			robotRunAngle(-300, 30, 0, 0.9);
		}
		else if (ViTriLazeThaBong[viTriThaBong] < lazeTraiValue)
		{
			robotRunAngle(300, 30, 0, 0.9);
		}
	}

	//-------------------------------

	for (i = 0; i < 50; i++)
	{
		while (BienTroMamXoayValue < Mam_Xoay_Target - 10 && BienTroMamXoayValue > Mam_Xoay_Target + 10)
		{
			vTaskDelay(1);
		}
		vTaskDelay(5);
	}

	for (i = 0; i < 30; i++)
	{
		while (lazeSauValue > 250)
		{
			if (lazeSauValue > 400)
				robotRunAngle(0, 30, 0, 0.9);

			else
				robotRunAngle(0, 20, 0, 0.9);
		}
		vTaskDelay(5);
	}

	RobotMode = 8;
	robotStop(0);
	// kiem tra gia tri silo tu raspberry pi
	if (ChoChonSilo)
	{

		while (SoFrameNhanSilo < 300)
		{
			if (SiloDaChon == SILO_THA_BONG)
				SoFrameNhanSilo += 1;
			else
			{
				SoFrameNhanSilo = 0;
				SiloDaChon = SILO_THA_BONG;
			}
			vTaskDelay(10);
		}
		robotRunAngle(0, 15, 0, 0.9);
		while (lazeSauValue > lazeApSatBoBong)
		{
			while (SILO_THA_BONG > 4 && lazeSauValue > lazeApSatBoBong)
			{
				vTaskDelay(10);
			}
			vTaskDelay(1);
		}

		if (SILO_THA_BONG >= 0 && SILO_THA_BONG < 5)
			viTriThaBong = SILO_THA_BONG;
	}
	Servo_Cam = 700;
	RobotMode = 7;

	viTriThaBong = Chay_Bo_Bong(viTriThaBong, ChoChonSilo);
	Tha_Bong_Vao_Silo(viTriThaBong);

	robotStop(0);
	RL_DEN_CAM_OFF;

	// while(1);
}

//---------------------------------------------------------------------------------------------
//----------------------------------quay ve lay bong--------------------------------------
void Ve_gap_bong_xanh(void)
{
	int viTriLazeVeLayBong = 0;

	viTriLazeVeLayBong = ViTriLazeThaBong[2];
	Truc_X_Target = Truc_X_Max;

	robotRun(1800, 50);

	// lui lai
	for (i = 0; i < 30; i++)
	{
		while (lazeSauValue < 50)
			vTaskDelay(1);
		vTaskDelay(5);
	}

	// thu tay
	XI_LANH_NANG_BONG_OFF;
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;

	// tim vi tri dung
	while (absI(lazeTraiValue - viTriLazeVeLayBong) > 3)
	{
		// if (lazeSauValue < 200)
		// {
		// 	XI_LANH_NANG_BONG_OFF;
		// 	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
		// 	Truc_X_Target = Truc_X_Max;
		// }

		if (viTriLazeVeLayBong > lazeTraiValue)
		{
			robotRunAngle(-1500 + absI((viTriLazeVeLayBong - lazeTraiValue) * 3), 50, 0, 0.3);
		}
		else if (viTriLazeVeLayBong < lazeTraiValue)
		{
			robotRunAngle(1500 - absI((viTriLazeVeLayBong - lazeTraiValue) * 3), 50, 0, 0.3);
		}
	}

	robotRunAngle(1800, 50, 0, 0.3);

	for (i = 0; i < 30; i++)
	{
		while (lazeSauValue < 450)
			;
		vTaskDelay(1);
		vTaskDelay(5);
	}

	RESET_ENCODER();
	robotRunAngle(1800, 30, 0, 0.3);

	while (ENCODER_TONG() < 1500)
		vTaskDelay(1);

	ChuanBiCoCauLayBong();
	robotStop(10);
	vTaskDelay(2000);
}

void XUAT_PHAT_SAN_XANH_2(void)
{
	XUAT_PHAT_SAN_XANH();
	while ((TAM_X == 0 || abs(TAM_Y - 18) > 10))
		robotRun(1800, 7);
	vTaskDelay(100);
}