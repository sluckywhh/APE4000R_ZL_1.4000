#include "keypad.h"
#include "vfd.h"
#include "PowerOffData.h"
#include "VersionConfig.h"
#include "CaProgressBar.h"
#include "CDB.h"
#include "CGlobalArg.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


struct TYWPwOffData YW_PowerOffData;
struct TYWPwOffData *g_YW_PowerOffData = &YW_PowerOffData;  /**< ���籣���ṹ��ָ�� */


void pw_handler(int x)
{
#if (LANGCHAO_LIB==0)
	bool ret;
	FILE * fp;

	DBG_PRINT(("��������źŴ���"));
	if ((fp= fopen(POWOFF_DIR, "w+")) == NULL)
	{
		DBG_PRINT(("can't open file"));
		DBG_PRINT(("д�������ݴ��󣡣�������"));
	}
	else
	{
		if(fwrite(g_YW_PowerOffData,sizeof(TYWPwOffData), 1, fp) != 1)
		{
			DBG_PRINT(("File write erro"));
		}
		fclose(fp);
	}

// 	if (GetPowerOffFlag() == 1)
// 	{
// 		CGlobalArg::SysLog(EVENT_POWER_OFF, SUCCESS, "");
// 	}
	
	DBG_PRINT(("�洢�������ݽ���"));
	
// 	ret = CDB::GetInstance()->Close();
	CDB *m_db = CDB::GetInstance();
	ret = m_db->Close();
	if ( ret != true)
	{
		DBG_PRINT(("close database false"));
	}
	else
	{
		DBG_PRINT(("SUCCESS in pw_handler"));
	}


	KeyDisable();
	SPI_Release();

	DBG_PRINT(("pw_headler end"));
	exit(0);
#endif
}

void PowOff_init()
{
#if (LANGCHAO_LIB==0)
	FILE *fp;
	int flag=0;
	printf("PowOff_init start \n");
	//�����ļ����ݶ����ڴ棬��ɺ�������ļ�
	if ((fp = fopen(POWOFF_DIR, "r")) != NULL)
	{
		if ( fread(g_YW_PowerOffData, sizeof(TYWPwOffData), 1 , fp) != 1)
		{
// 			CaProgressBar info("");
// 			info.SetText("���������ݴ���");
// 			info.ReFresh();
			BAR_DEF();
			BAR_SHOW("���������ݴ���");
		}
		fclose(fp);
		flag = 1;
	}
	
	
	POWOFF_DISABLE();

	// ��ʼ������������
	powOff_init_drv();

	//����ļ�
	if (flag == 1)
	{
		if (remove(POWOFF_DIR) != 0)
		{
			BAR_DEF();
			BAR_SHOW("����������ݴ���");
		}			
	}
	
	POWOFF_ENABLE();

#endif	
}

void PowOff_release()
{
#if (LANGCHAO_LIB==0)
	powOff_release_drv();
#endif
}

