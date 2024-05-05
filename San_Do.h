//////************************ san do *********************************
void XUAT_PHAT_SAN_DO()
{
	TocDoToiDaCoKhi = 75;
	RESET_ENCODER();

	robotRunAngle(-900, 60, 0, 0.1);
	while (ENCODER_TONG() < 2000)
		vTaskDelay(1);
	
	robotRunAngle(-800, 60, 0, 0.1);
	while (ENCODER_TONG() < 4000)
		vTaskDelay(1);

	robotRunAngle(-500, 60, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue > 40)
			vTaskDelay(1);

	robotRunAngle(-200, 60, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue > 20)
			vTaskDelay(1);

	RESET_ENCODER();
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	robotRunAngle(0, 60, 0, 0.1);
	while (ENCODER_TONG() < 2000)
		vTaskDelay(1);

	robotRunAngle(0, 45, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue < 35)
			vTaskDelay(1);

	RESET_ENCODER();

	robotRunAngle(0, 30, 0, 0.1);
	while (ENCODER_TONG() < 600)
		vTaskDelay(1);

	// len doc
	robotStop(0);
	RESET_ENCODER();

	// chay ngan
	robotRunAngle(-920, 40, 0, 0.1);
	while (ENCODER_TONG() < 1800)
		vTaskDelay(1);
	Truc_X_Target = Truc_X_Gap_Bong;
	while (ENCODER_TONG() < 3200)
		Bam_thanh_laser_phai_lui(40, 0, ViTriLazeThaBong[2], 5);

	// chay xuong kho bong
	RESET_ENCODER();
	
	robotRunAngle(1800, 15, 0, 0.1);
	while (ENCODER_TONG() < 300)
		vTaskDelay(1);

	robotStop(0);
	TocDoToiDaCoKhi = 250;
}

void retry_sando(void)
{
	TocDoToiDaCoKhi = 75;
	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 1200)
		{
			Bam_thanh_laser_phai(40, 0, 8, 5);
			vTaskDelay(1);
		};
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 5000)
		{
			Bam_thanh_laser_phai(40, 0, 3, 5);
			vTaskDelay(1);
		};
	

	robotRunAngle(0, 45, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue < 25)
			vTaskDelay(1);

	RESET_ENCODER();

	robotRunAngle(0, 30, 0, 0.1);
	while (ENCODER_TONG() < 600)
		vTaskDelay(1);
	// len doc
	robotStop(0);
	RESET_ENCODER();

	robotRunAngle(-920, 40, 0, 0.1);
	while (ENCODER_TONG() < 2000)
		vTaskDelay(1);
	Truc_X_Target = Truc_X_Gap_Bong;
	ChuanBiCoCauLayBong();
	while (ENCODER_TONG() < 3500)
		Bam_thanh_laser_phai_lui(40, 0, ViTriLazeThaBong[2], 5);
	robotStop(0);
	robotRunAngle(1800, 10, 0, 0.1);
	while (ENCODER_TONG() < 3900)
		vTaskDelay(1);
	vTaskDelay(1);
	TocDoToiDaCoKhi = 250;
}
//---------------------------------------------------------------------------------------------
void ChayLenNeThanh_Do(int tocdo)
{
	if (lazePhaiValue < 25)
		robotRunAngle(450, tocdo - 15, 0, 1.5);
	else if (lazeTraiValue < 50)
		robotRunAngle(-450, tocdo - 15, 0, 1.5);
	else
		robotRunAngle(0, tocdo, 0, 1.5);
}
//----------------------------------------------------------------------

void ThaBong_Do()
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

	for (i = 0; i < 50; i++)
	{
		while (CB_QUANG_TRAI && CB_QUANG_PHAI)
		{
			// toc do - 20
			ChayLenNeThanh_Do(60);
			vTaskDelay(1);
		}
	}

	// robotRunAngle(HuongLaBan, 60, HuongLaBan, 1.5);
	RESET_ENCODER();
	for (i = 0; i < 50; i++)
	{
		while (ENCODER_TONG() < 2000)
		{
			ChayLenNeThanh_Do(60);
			vTaskDelay(1);
		}
	}

	for (i = 0; i < 50; i++)
	{
		while (lazeTraiValue < 330)
		{
			ChayLenNeThanh_Do(35);
			vTaskDelay(1);
		}
	}

	robotStop(0);
	RL_DEN_CAM_ON;
	Servo_Cam = 930;

	viTriThaBong = 2;
	for (i = 1; i < 4; i++)
	{
		if (absI(lazePhaiValue - ViTriLazeThaBong[i]) < KhoangCach)
		{
			KhoangCach = absI(lazePhaiValue - ViTriLazeThaBong[i]);
			viTriThaBong = i;
		}
	}

	// ve vi tri giua
	while (lazeSauValue > 240)
	{
		Bam_thanh_laser_phai(15, 0, ViTriLazeThaBong[viTriThaBong], 2);
	}

	robotStop(0);
	// Chinh goc robot
	// robotStop(0);
	// robotRotate(0, 0.5, 0);
	// while (robotFixAngle())
	// {
	// 	vTaskDelay(1);
	// }
	// robotStop(0);

	// for (i = 0; i < 50; i++)
	// {
	// 	while (BienTroMamXoayValue < Mam_Xoay_Target - 10 && BienTroMamXoayValue > Mam_Xoay_Target + 10)
	// 	{
	// 		vTaskDelay(1);
	// 	}
	// 	vTaskDelay(5);
	// }

	// while (lazeSauValue > 250)
	// {
	// 	if (lazeSauValue > 400)
	// 	{
	// 		robotRunAngle(0, 30, 0, 0.9);
	// 	}
	// 	else
	// 	{
	// 		robotRunAngle(0, 20, 0, 0.9);
	// 	}
	// 	vTaskDelay(10);
	// }

	RobotMode = 8;
	robotStop(0);
	// kiem tra gia tri silo tu raspberry pi

	while(SoFrameNhanSilo < 300)
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

	// robotRunAngle(0, 15, 0, 0.9);
	// while (lazeSauValue > lazeApSatBoBong)
	// {
	// 	while (SILO_THA_BONG > 4 && lazeSauValue > lazeApSatBoBong)
	// 	{
	// 		vTaskDelay(10);
	// 	}
	// 	vTaskDelay(1);

	// }

	if (SILO_THA_BONG >= 0 && SILO_THA_BONG < 5)
		viTriThaBong = SILO_THA_BONG;		


	// robotStop(0);
	// while (1)
	// {
	// 	vTaskDelay(1);
	// }

	Servo_Cam = 700;
	RobotMode = 7;

	viTriThaBong = Chay_Bo_Bong(viTriThaBong);
	Tha_Bong_Vao_Silo(viTriThaBong);
	RL_DEN_CAM_OFF;

	robotStop(0);
}
//---------------------------------ve gap boong do-----------------------------
void Ve_gap_bong_do(void)
{
	int viTriLazeVeLayBong = 0;
	int fix=0;

	viTriLazeVeLayBong = ViTriLazeThaBong[2];
	Truc_X_Target = Truc_X_Max;

	robotRun(1800, 50);
	for (i = 0; i < 30; i++)
	{
		while (lazeSauValue < 50)
			vTaskDelay(1);
		vTaskDelay(5);
	}
	// Thu tay
	XI_LANH_NANG_BONG_OFF;
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;

	while (absI(lazePhaiValue - viTriLazeVeLayBong) > 5)
	{
		Bam_thanh_laser_phai_lui(50, 0, viTriLazeVeLayBong, 2);
	}

	robotRunAngle(1800, 50, 0, 0.3);

	for (i = 0; i < 30; i++)
	{
		while (lazeSauValue < 450)
			vTaskDelay(1);
		vTaskDelay(5);
	}

	RESET_ENCODER();

	robotRunAngle(1800, 30, 0, 0.3);
	while (ENCODER_TONG() < 1500)
		vTaskDelay(1);

	ChuanBiCoCauLayBong();
	robotStop(20);
	vTaskDelay(2000);
}

void XUAT_PHAT_SAN_DO_2()
{
	XUAT_PHAT_SAN_DO();
	robotRun(1800, 7);
	while ((TAM_X == 0 || TAM_Y == 0))
		vTaskDelay(100);
}

void XUAT_PHAT_SAN_DO_COPY(void)
{
	TocDoToiDaCoKhi = 75;
	RESET_ENCODER();
	robotRunAngle(-900, 60, 0, 0.1);
	while (ENCODER_TONG() < 2500)
		vTaskDelay(1);
	XI_LANH_KEP_THA_BONG_OFF;
	robotRunAngle(-800, 60, 0, 0.1);
	while (ENCODER_TONG() < 4000)
		vTaskDelay(1);

	// bam thanh
	robotRunAngle(-700, 50, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue > 140)
			vTaskDelay(1);

	RESET_ENCODER();
	ChuanBiCoCauLayBong();

	for (i = 0; i < 50; i++)
		while (ENCODER_TONG() < 3500)
		{
			Bam_thanh_laser_phai(40, 0, 17, 5);
			vTaskDelay(1);
		};

	robotRunAngle(0, 45, 0, 0.1);
	for (i = 0; i < 50; i++)
		while (lazePhaiValue < 60)
			vTaskDelay(1);

	RESET_ENCODER();

	robotRunAngle(0, 30, 0, 0.1);
	while (ENCODER_TONG() < 600)
		vTaskDelay(1);
	robotStop(0);

	// len doc
	RESET_ENCODER();
	robotRunAngle(-920, 50, 0, 0.1);
	while (ENCODER_TONG() < 1800)
		vTaskDelay(1);


	while (ENCODER_TONG() < 3200)
		Bam_thanh_laser_phai_lui(40, 0, ViTriLazeThaBong[2], 3);

	// robotRunAngle(900,15,0,0.1);
	// while(ENCODER_TONG() < 1000 || lazeTraiValue > ViTriLazeThaBong[2]) vTaskDelay(1);

	// chay cham cho den khi thay bong
	// robotRunAngle(1450, 10, -450, 0.3);
	// while ((TAM_X == 0 || abs(TAM_Y - 18) > 10))
	// 	vTaskDelay(100);

	//-----------------------------

	robotStop(0);
	TocDoToiDaCoKhi = 250;
}