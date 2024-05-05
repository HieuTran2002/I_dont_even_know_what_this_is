void xuat_phat(int MauSan)
{
	if (MauSan == 1)
	{
		XUAT_PHAT_SAN_XANH();
	}
	else
	{
		XUAT_PHAT_SAN_DO_COPY();
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


void ThaBong(int mausan)
{
	if (mausan == 1)
	{
		ThaBong_Xanh();
	}
	else
	{
		ThaBong_Do();
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
		ThaBong(MauSan);
		Ve_gap_bong(MauSan);
		vTaskDelay(3000);
	}
	permanentStop();
}