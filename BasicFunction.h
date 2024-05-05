int ViTriLazeThaBong[5];
int khoangCach = 1000;
int viTriThaBong = 0;
int lazeApSatBoBong = 150;
int i;
int TimViTri_Bo_Bong_Khac(int viTriThaBongHienTai, int ChoChonSilo);

void USART_SendSTRING(void)
{
	USART_SendData(USART3, 255); // bat dau gui du lieu
	vTaskDelay(10);
	//------------------------------------------
	USART_SendData(USART3, (uint16_t)MauSan);
	vTaskDelay(10);
	USART_SendData(USART3, (uint16_t)RobotMode); // 1- lay bong tai kho; 2- lay bong tu do; 5-quan sat ro bong
	vTaskDelay(10);
	USART_SendData(USART3, (uint16_t)Servo_Cam / 100);
	vTaskDelay(10);
	if (MauSan == 1)
		USART_SendData(USART3, (uint16_t)lazeTraiValue / 2);
	else
		USART_SendData(USART3, (uint16_t)lazePhaiValue / 2);
	vTaskDelay(10);
}

//---------------------------------------------------------------
int DO_BONG()
{
	int gapX = 20;
	int gapY = 10;
	int Y_TARGET = 70;
	int X_TARGET = 125;
	int speed = 100;
	int countOut = 0;
	int countBall = 0;

	TocDoToiDaCoKhi = 200;
	Servo_Cam = 1700;
	Truc_Y_Target = Truc_Y_Max;
	vTaskDelay(1000);

	countOut = 0;
	for (i = 0; i < 10; i++)
	{
		while (abs(TAM_X - X_TARGET) > gapX || abs(TAM_Y - Y_TARGET) > gapY)
		{
			countBall = 0;
			while (countBall < 100)
			{
				while (abs(TAM_X - X_TARGET) > gapX || abs(TAM_Y - Y_TARGET) > gapY)
				{
					countBall = 0;

					if (TAM_X < X_TARGET + gapX)
					{
						Mam_Xoay_Target -= 1 + absI(TAM_X - X_TARGET) / 10;
					}
					else if (TAM_X > X_TARGET - gapX)
					{
						Mam_Xoay_Target += 1 + absI(TAM_X - X_TARGET) / 10;
					}
					//-----------------------------------------
					if (TAM_Y < Y_TARGET + gapY)
					{
						Truc_X_Target -= 1 + absI(TAM_Y - Y_TARGET) / 5;
					}
					else if (TAM_Y > Y_TARGET - gapY)
					{
						Truc_X_Target += 1 + absI(TAM_Y - Y_TARGET) / 5;
					}

					if ((TAM_X == 0 && TAM_Y == 0) || Truc_X_Target <= Truc_X_Min || Truc_X_Target >= Truc_X_Max)
					{
						Mam_Xoay_Target = BienTroMamXoayValue;
						if (countOut++ > 20)
						{
							TocDoToiDaCoKhi = 250;
							return 0;
						}
					}
					vTaskDelay(400);
				}
				countBall++;
				vTaskDelay(10);
			}
		}
		vTaskDelay(100);
	}

	TocDoToiDaCoKhi = 250;
	return 1;
}

//---------------------------------------------------------------------------------------------
// void TimBongTuDo(int MauSan)
// {
// 	int rA = 0;
// 	int tocdo = 0;
// 	int lantimkiem = 1;
// 	ChuanBiCoCauLayBong();
// 	// Tim lan thu nhat
// BatDauDoBong:
// 	lantimkiem = 0;
// 	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
// 	Truc_Y_Target = Truc_Y_Max;
// 	RobotMode = 10;
// 	Servo_Cam = 1700;
// 	vTaskDelay(2000);
// 	RobotMode = 9;
// 	vTaskDelay(1000);

// 	// Tim lan thu nhat
// 	rA = 0; // robotAngle();
// 	while (lantimkiem <= 10 && TAM_X == 0 && TAM_Y == 0)
// 	{
// 		if (lantimkiem % 2 == 0)
// 		{
// 			Servo_Cam = 1150;
// 			RobotMode = 10;
// 			vTaskDelay(1000);
// 			RobotMode = 9;
// 			vTaskDelay(3000);
// 		}
// 		else
// 		{
// 			Servo_Cam = 1700;
// 			RobotMode = 10;
// 			vTaskDelay(1000);
// 			RobotMode = 9;
// 			vTaskDelay(3000);
// 		}

// 		lantimkiem = lantimkiem + 1;
// 		if (TAM_X == 0 && TAM_Y == 0)
// 		{
// 			if (MauSan == 1)
// 				robotRotate(rA + 800, 0.5, 0);
// 			else
// 				robotRotate(rA - 800, 0.5, 0);

// 			while (TAM_X == 0 && TAM_Y == 0 && robotFixAngle())
// 			{
// 				vTaskDelay(1);
// 			}
// 		}
// 		robotStop(0);
// 		if (TAM_X == 0 && TAM_Y == 0)
// 		{
// 			if (MauSan == 1)
// 				robotRotate(rA - 800, 0.5, 0);
// 			else
// 				robotRotate(rA + 800, 0.5, 0);

// 			while (TAM_X == 0 && TAM_Y == 0 && robotFixAngle())
// 			{
// 				vTaskDelay(1);
// 			}
// 		}
// 		robotStop(0);
// 		if (TAM_X == 0 && TAM_Y == 0)
// 		{
// 			Servo_Cam = 1500;
// 			robotRotate(rA, 0.5, 0);
// 			while (robotFixAngle())
// 			{
// 				vTaskDelay(1);
// 			}
// 			robotStop(0);
// 			vTaskDelay(3000);
// 		}
// 	}

// 	robotStop(0);
// 	//--------------------------------------------------------
// 	while (absI(TAM_X - 125) > 10 && TAM_X != 255)
// 	{
// 		if (TAM_X < 125)
// 			robotRotateFree(-0.5, 0);
// 		else if (TAM_X > 125)
// 			robotRotateFree(0.5, 0);
// 		else
// 			robotRotateStop();

// 		if (TAM_X == 0 && TAM_Y == 0)
// 		{
// 			robotStop(0);
// 			goto BatDauDoBong;
// 		}
// 	}
// 	robotStop(0);
// 	//------------------------------------------------------------------
// 	while (Servo_Cam < 1700 || (Servo_Cam == 1700 && TAM_Y < 60) && TAM_X != 255)
// 	{
// 		while (Servo_Cam < 1700 || (Servo_Cam == 1700 && TAM_Y < 60) && TAM_X != 255)
// 		{
// 			if (TAM_Y > 70 && Servo_Cam < 1700)
// 			{
// 				if (Servo_Cam < 1450)
// 					Servo_Cam = Servo_Cam + 2;
// 				else
// 					Servo_Cam = Servo_Cam + 4;

// 				if (Servo_Cam > 1650)
// 					Servo_Cam = 1700;

// 				vTaskDelay(20);
// 			}

// 			if (TAM_X > 135)
// 				robotRotateFree(0.2, 0);
// 			else if (TAM_X < 115)
// 				robotRotateFree(-0.2, 0);
// 			else
// 				robotRotateStop();

// 			/*-------------------------------*/
// 			// tu chinh toc do
// 			tocdo = 25 - absI((Servo_Cam - 1150) / 25);
// 			if (tocdo < 7)
// 				tocdo = 7;

// 			if (TAM_X == 0 && TAM_Y == 0)
// 			{
// 				robotStop(0);
// 				goto BatDauDoBong;
// 			}

// 			robotRun(1800, tocdo);
// 		}
// 		robotStop(0);
// 		vTaskDelay(100);
// 	}
// 	robotStop(0);
// 	//-------------------------------------------------------
// 	vTaskDelay(1000);
// 	while (abs(TAM_X - 125) > 40 || abs(TAM_Y - 70) > 15)
// 	{

// 		while (abs(TAM_X - 125) > 40)
// 		{
// 			if (TAM_X > 120)
// 				robotRotateFree(0.2, 0);
// 			else if (TAM_X < 130)
// 				robotRotateFree(-0.2, 0);
// 			else
// 				robotRotateStop();

// 			if (TAM_X == 0 && TAM_Y == 0)
// 			{
// 				robotStop(0);
// 				goto BatDauDoBong;
// 			}
// 		}

// 		robotStop(0);

// 		while (abs(TAM_X - 125) <= 40 && abs(TAM_Y - 70) > 15)
// 		{
// 			if (TAM_Y < 70)
// 				robotRun(1800, 5);
// 			else if (TAM_Y > 70)
// 				robotRun(0, 5);
// 			else
// 				robotStop(0);

// 			if (TAM_X == 0 && TAM_Y == 0)
// 			{
// 				robotStop(0);
// 				goto BatDauDoBong;
// 			}
// 		}
// 		robotStop(0);
// 	}

// 	robotStop(0);
// 	if (!DO_BONG())
// 	{
// 		robotStop(0);
// 		goto BatDauDoBong;
// 	}

// 	robotStop(0);
// 	RobotMode = 10;
// 	if(!GAP_BONG()){
// 		robotStop(0);
// 		goto BatDauDoBong;
// 	}
// }

void TimBongTuDo(int MauSan)
{
	int rA = 0;
	int tocdo = 0;
	int lantimkiem = 1;
	ChuanBiCoCauLayBong();
	// Tim lan thu nhat
BatDauDoBong:
	XI_LANH_KEP_THA_BONG_OFF;

	lantimkiem = 0;
	Mam_Xoay_Target = Mam_Xoay_Gap_Bong;
	Truc_Y_Target = Truc_Y_Max;
	RobotMode = 10;
	RobotMode = 9;
	vTaskDelay(1000);

	// Tim lan thu nhat
	rA = 0; // robotAngle();
	while (lantimkiem <= 10 && TAM_X == 0 && TAM_Y == 0)
	{
		if (lantimkiem % 2 == 0)
		{
			Servo_Cam = 1120;
			RobotMode = 10;
			vTaskDelay(1000);
			RobotMode = 9;
			vTaskDelay(3000);
		}
		else
		{
			Servo_Cam = 1700;
			RobotMode = 10;
			vTaskDelay(1000);
			RobotMode = 9;
			vTaskDelay(3000);
		}

		lantimkiem = lantimkiem + 1;
		if (TAM_X == 0 && TAM_Y == 0)
		{
			if (MauSan == 1)
				robotRotate(rA + 800, 0.5, 0);
			else
				robotRotate(rA - 800, 0.5, 0);

			while (TAM_X == 0 && TAM_Y == 0 && robotFixAngle())
			{
				vTaskDelay(1);
			}
		}
		robotStop(0);
		if (TAM_X == 0 && TAM_Y == 0)
		{
			if (MauSan == 1)
				robotRotate(rA - 800, 0.5, 0);
			else
				robotRotate(rA + 800, 0.5, 0);

			while (TAM_X == 0 && TAM_Y == 0 && robotFixAngle())
			{
				vTaskDelay(1);
			}
		}
		robotStop(0);
		if (TAM_X == 0 && TAM_Y == 0)
		{
			Servo_Cam = 1500;
			robotRotate(rA, 0.5, 0);
			while (robotFixAngle())
			{
				vTaskDelay(1);
			}
			robotStop(0);
			vTaskDelay(3000);
		}
	}

	robotStop(0);
	//--------------------------------------------------------
	while (absI(TAM_X - 125) > 10 && TAM_X != 255)
	{
		if (TAM_X < 125)
			robotRotateFree(-0.5, 0);
		else if (TAM_X > 125)
			robotRotateFree(0.5, 0);
		else
			robotRotateStop();

		if (TAM_X == 0 && TAM_Y == 0)
		{
			robotStop(0);
			goto BatDauDoBong;
		}
	}
	robotStop(0);
	//------------------------------------------------------------------
	while (Servo_Cam < 1700 || (Servo_Cam == 1700 && TAM_Y < 70) && TAM_X != 255)
	{
		while (Servo_Cam < 1700 || (Servo_Cam == 1700 && TAM_Y < 70) && TAM_X != 255)
		{
			if (TAM_Y > 80 && Servo_Cam < 1700)
			{
				if (Servo_Cam < 1450)
					Servo_Cam = Servo_Cam + 2;
				else
					Servo_Cam = Servo_Cam + 4;

				if (Servo_Cam > 1650)
					Servo_Cam = 1700;

				vTaskDelay(20);
			}

			if (TAM_X > 135)
				robotRotateFree(0.2, 0);
			else if (TAM_X < 115)
				robotRotateFree(-0.2, 0);
			else
				robotRotateStop();

			/*-------------------------------*/
			// tu chinh toc do
			tocdo = 22 - absI((Servo_Cam - 1120) / 25);
			if (tocdo < 7)
				tocdo = 7;

			if (TAM_X == 0 && TAM_Y == 0)
			{
				robotStop(0);
				goto BatDauDoBong;
			}

			robotRun(1800, tocdo);
		}
		robotStop(0);
		vTaskDelay(100);
	}
	robotStop(0);
	//-------------------------------------------------------
	vTaskDelay(1000);
	while (abs(TAM_X - 125) > 40 || abs(TAM_Y - 70) > 15)
	{

		while (abs(TAM_X - 125) > 40)
		{
			if (TAM_X > 120)
				robotRotateFree(0.2, 0);
			else if (TAM_X < 130)
				robotRotateFree(-0.2, 0);
			else
				robotRotateStop();

			if (TAM_X == 0 && TAM_Y == 0)
			{
				robotStop(0);
				goto BatDauDoBong;
			}
		}

		robotStop(0);

		while (abs(TAM_X - 125) <= 40 && abs(TAM_Y - 70) > 15)
		{
			if (TAM_Y < 70)
				robotRun(1800, 5);
			else if (TAM_Y > 70)
				robotRun(0, 5);
			else
				robotStop(0);

			if (TAM_X == 0 && TAM_Y == 0)
			{
				robotStop(0);
				goto BatDauDoBong;
			}
		}
		robotStop(0);
	}

	robotStop(0);
	if (!DO_BONG())
	{
		robotStop(0);
		goto BatDauDoBong;
	}

	robotStop(0);
	RobotMode = 10;

	if (!GAP_BONG())
	{
		robotStop(0);
		goto BatDauDoBong;
	}
}

//---------------------------------------------------------------------------------------------
void Di_Chuyen_Ngang_SiLo(int viTriSilo, int BoBong)
{
	int viTriLazeThaBong = ViTriLazeThaBong[viTriSilo];
	int tocDo = 20;
	int bienDoLech = 0;

	if (MauSan == 1) //  xanh
	{
		for (i = 0; i < 50; i++)
		{
			while (absI(lazeTraiValue - viTriLazeThaBong) > 3)
			{
				if (viTriLazeThaBong > lazeTraiValue)
				{
					if (BoBong)
					{
						robotRunAngle(-900, 10, 0, 0.9);
					}
					else
					{
						tocDo = absI(lazeTraiValue - viTriLazeThaBong);
						if (tocDo > 30)
							tocDo = 30;

						bienDoLech = absI(lazeSauValue - lazeApSatBoBong) * 10;
						if (lazeSauValue > lazeApSatBoBong)
							robotRunAngle(-900 + bienDoLech, 5 + tocDo, 0, 0.9);
						else
							robotRunAngle(-900 - bienDoLech, 5 + tocDo, 0, 0.9);
					}
				}
				else if (viTriLazeThaBong < lazeTraiValue)
				{
					if (BoBong)
					{
						robotRunAngle(900, 10, 0, 0.9);
					}
					else
					{

						tocDo = absI(lazeTraiValue - viTriLazeThaBong);
						if (tocDo > 30)
							tocDo = 30;

						bienDoLech = absI(lazeSauValue - lazeApSatBoBong) * 10;
						if (lazeSauValue > lazeApSatBoBong)
							robotRunAngle(900 - bienDoLech, 5 + tocDo, 0, 0.9);
						else
							robotRunAngle(900 + bienDoLech, 5 + tocDo, 0, 0.9);
					}
				}
				else
				{
					robotStop(0);
				}
			}
			vTaskDelay(1);
		}
	}
	else if (MauSan == 2) // do
	{
		for (i = 0; i < 50; i++)
		{
			while (absI(lazePhaiValue - viTriLazeThaBong) > 3)
			{
				if (viTriLazeThaBong > lazePhaiValue)
				{
					if (BoBong)
					{
						robotRunAngle(900, 10, 0, 0.9);
					}
					else
					{
						tocDo = absI(lazePhaiValue - viTriLazeThaBong) * 2;
						if (tocDo > 30)
							tocDo = 30;

						bienDoLech = absI(lazeSauValue - lazeApSatBoBong) * 10;
						if (lazeSauValue > lazeApSatBoBong)
							robotRunAngle(900 - bienDoLech, 5 + tocDo, 0, 0.9);
						else
							robotRunAngle(900 + bienDoLech, 5 + tocDo, 0, 0.9);
					}
				}
				else if (viTriLazeThaBong < lazePhaiValue)
				{
					if (BoBong)
					{
						robotRunAngle(-900, 10, 0, 0.9);
					}
					else
					{

						tocDo = absI(lazePhaiValue - viTriLazeThaBong) * 2;
						if (tocDo > 30)
							tocDo = 30;

						bienDoLech = absI(lazeSauValue - lazeApSatBoBong) * 10;
						if (lazeSauValue > lazeApSatBoBong)
							robotRunAngle(-900 + bienDoLech, 5 + tocDo, 0, 0.9);
						else
							robotRunAngle(-900 - bienDoLech, 5 + tocDo, 0, 0.9);
					}
				}
				else
				{
					robotStop(0);
				}
			}
			vTaskDelay(1);
		}
	}
	robotStop(0);
}

//---------------------------------------------------------------------------------------------
void Tha_Bong_Vao_Silo(int viTriThaBong)
{
	RESET_ENCODER();
	XI_LANH_NANG_BONG_ON;

	Di_Chuyen_Ngang_SiLo(viTriThaBong, 1);

	robotStop(0);

	robotRun(0, 10);
	for (i = 0; i < 50; i++)
		while (CB_CHAM_THANH == 1)
			vTaskDelay(10);

	XI_LANH_KEP_THA_BONG_OFF;
	RobotMode = viTriThaBong;
	vTaskDelay(1000);
	RobotMode = 5;
	vTaskDelay(1000);
	viTriThaBong = ViTriLazeThaBong[viTriThaBong];
	//-------------------------------------------------------
	if (MauSan == 1) //  xanh
	{
		while (absI(lazeTraiValue - viTriThaBong) > 1)
		{
			if (viTriThaBong > lazeTraiValue)
			{
				robotRun(-900, 5);
			}
			else if (viTriThaBong < lazeTraiValue)
			{
				robotRun(900, 5);
			}
			else
			{
				robotStop(0);
			}
		}
	}
	else if (MauSan == 2) // do
	{
		while (absI(lazePhaiValue - viTriThaBong) > 1)
		{
			if (viTriThaBong > lazePhaiValue)
			{
				robotRun(900, 5);
			}
			else if (viTriThaBong < lazePhaiValue)
			{
				robotRun(-900, 5);
			}
			else
			{
				robotStop(0);
			}
		}
	}
	robotStop(0);
	vTaskDelay(3000);
	Truc_X_Target = Truc_X_Max;
}

//==================================================================

int Chay_Bo_Bong(int viTriThaBong, int ChoChonSilo)
{
	int Lazer_Siolo = ViTriLazeThaBong[viTriThaBong];

	for (i = 0; i < 50; i++)
	{

		if (MauSan == 1)
		{ // 1: san xanh; 2: san do
			while (lazeSauValue > lazeApSatBoBong)
			{
				if (lazeSauValue > lazeApSatBoBong + 30)
					Bam_thanh_laser_trai(30, 0, Lazer_Siolo, 2);
				else
					Bam_thanh_laser_trai(15, 0, Lazer_Siolo, 2);
			}
		}
		else
		{
			while (lazeSauValue > lazeApSatBoBong)
			{
				if (lazeSauValue > lazeApSatBoBong + 30)
					Bam_thanh_laser_phai(30, 0, Lazer_Siolo, 2);
				else
					Bam_thanh_laser_phai(15, 0, Lazer_Siolo, 2);
			}
		}
		vTaskDelay(5);
	}

	// kiem tra silo co bong chua
	viTriThaBong = TimViTri_Bo_Bong_Khac(viTriThaBong, ChoChonSilo);
	if (viTriThaBong == 10)
	{ // ko tim thay dc vi tri
		RESET_ENCODER();
		robotRun(1800, 10);
		while (ENCODER_TONG() < 1000)
			vTaskDelay(10);

		robotStop(0);
		while (1)
			vTaskDelay(1000);
	}
	Lazer_Siolo = ViTriLazeThaBong[viTriThaBong];

	robotStop(0);
	//=============================
	Mam_Xoay_Target = Mam_Xoay_Bo_Bong;

	XI_LANH_NANG_BONG_ON;
	vTaskDelay(3000);

	if (MauSan == 1)
	{ // 1: san xanh; 2: san do
		while (CB_CHAM_THANH == 1)
			Bam_thanh_laser_trai(15, 0, Lazer_Siolo, 2);
	}
	else
	{
		while (CB_CHAM_THANH == 1)
			Bam_thanh_laser_phai(15, 0, Lazer_Siolo, 2);
	}

	robotStop(0);
	robotRun(0, 10);
	vTaskDelay(3000);
	robotStop(0);
	SEND_UART(1, 'a');
	vTaskDelay(1000);

	return viTriThaBong;
}

//=============================================================================

int KiemTra_CoBong()
{
	int BienDoKiemTra = 15;
	Mam_Xoay_Target = Mam_Xoay_Bo_Bong - BienDoKiemTra;
	while (absI(BienTroMamXoayValue - Mam_Xoay_Target) > 5)
	{
		if (laze_nhan_banh_value < 700)
		{
			Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
			return 1;
		}
	}

	Mam_Xoay_Target = Mam_Xoay_Bo_Bong + BienDoKiemTra;
	while (absI(BienTroMamXoayValue - Mam_Xoay_Target) > 5)
	{
		if (laze_nhan_banh_value < 700)
		{
			Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
			return 1;
		}
	}

	Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
	return 0;
}

int TimViTri_Bo_Bong_Khac(int viTriThaBongHienTai, int ChoChonSilo)
{
	int viTriThaBongMoi = 2;

	while (1)
	{
		Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
		Di_Chuyen_Ngang_SiLo(viTriThaBongHienTai, 0);
		if (!KiemTra_CoBong())
			return viTriThaBongHienTai;
		//=======================================================
		viTriThaBongMoi = viTriThaBongHienTai + 1;
		while (viTriThaBongMoi < (ChoChonSilo ? 5 : 4))
		{
			Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
			Di_Chuyen_Ngang_SiLo(viTriThaBongMoi, 0);
			if (!KiemTra_CoBong())
				return viTriThaBongMoi;
			viTriThaBongMoi++;
		}

		// ================================================================
		viTriThaBongMoi = viTriThaBongHienTai - 1;
		while (viTriThaBongMoi >= (ChoChonSilo ? 0 : 1))
		{
			Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
			Di_Chuyen_Ngang_SiLo(viTriThaBongMoi, 0);
			if (!KiemTra_CoBong())
				return viTriThaBongMoi;
			viTriThaBongMoi--;
		}

		viTriThaBongHienTai = 1;
	}
	return 10;
}

void InitialPosition()
{
	Truc_X_Target = Truc_X_Bat_Dau;
	Mam_Xoay_Target = Mam_Xoay_Bat_Dau;
	XI_LANH_KEP_THA_BONG_ON;
}
void trangThaiThaSilo(){
	Truc_X_Target = Truc_X_Bo_Bong;
	Truc_Y_Target = Truc_Y_Max;
	Mam_Xoay_Target = Mam_Xoay_Bo_Bong;
	XI_LANH_KEP_THA_BONG_ON;
	XI_LANH_NANG_BONG_ON;
	Servo_Cam = 900;
}