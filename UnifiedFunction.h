void xuat_phat(int MauSan)
{
	if (MauSan == 1)
	{
		XUAT_PHAT_SAN_XANH_2();
	}
	else
	{
		XUAT_PHAT_SAN_DO_2();
	}

}

void retry(int MauSan)
{
	if(MauSan == 1)
	{
		retry_sanxanh();	
	}
	else
	{
		retry_sando();
	}
}


void ThaBong(int mausan, int ChoChonSilo)
{
	if (mausan == 1)
	{
		ThaBong_Xanh(ChoChonSilo);
	}
	else
	{
		ThaBong_Do(ChoChonSilo);
	}
}

void Ve_gap_bong(int mausan)
{
	if (mausan == 1)
	{
		Ve_gap_bong_xanh();
	}
	else
	{
		Ve_gap_bong_do();
	}
}

void chay_vung_3(int MauSan)
{

	while(1)
	{
		TimBongTuDo(MauSan);
		ThaBong(MauSan, 0);
		Ve_gap_bong(MauSan);
	}
	permanentStop();
}