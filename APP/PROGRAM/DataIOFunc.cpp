/*! \file    DataIOFunc.cpp
   \brief    awe4000r�����ӡ��Ӧ�ú���
   \author   Yu Yan
   \version  1.0
   \date     2008-4-1
 */


#include "DataIOFunc.h"
#include "CaProgressBar.h"
#include "keypad.h"
#include "CGlobalArg.h"
#include "CDept.h"
#include "CClient.h"
#include "USBMount.h"
#include "ReportFunc.h"

#ifndef WIN32
#include <sys/timeb.h>
#include "lcd_tiny.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#define IMPORT_DEPT_TXT_DIR "/mnt/importDept.txt"  //����Dept���txt�ļ�
#define IMPORT_CLIENT_TXT_DIR "/mnt/importClient.txt"  //����Client���txt�ļ�

#define IMPORT_DEPT_DIR "/mnt/importDept.sql"  //дDept���sql�ļ�
#define IMPORT_DEPT_CMD "../sqlite3 AWE < /mnt/importDept.sql"

#define EXPORT_DEPT_TXT_DIR "/mnt/exportDept.txt"  //����Dept���txt�ļ�
#define EXPORT_CLIENT_TXT_DIR "/mnt/exportClient.txt"  //����Client���txt�ļ�

#define EXPORT_DEPT_CMD "../sqlite3 AWE \".dump DEPT\" > /mnt/exportDept.sql"
#define EXPORT_CLIENT_CMD "../sqlite3 AWE \".dump CLIENT\" > /mnt/exportClient.sql"

#define SQL_VER 0    /**< ������ļ�����, 1: sql�ű��ļ��� 0: txt�ļ�*/

UINT8 DeptImportProc()
{
	DBG_PRINT(("DeptImportProc()!"));
	UINT8 nRet;
	nRet = YesNoMsgBox("�Ƿ�����Ʒ��Ϣ��");
	if (nRet==FAILURE)
	{
		return SUCCESS;
	}

#if SQL_VER	
	nRet = ImportHandle(2);  //��sql�ļ���Ϣ�������ݿ�
#else
	nRet = ImportTxtHandle(2);//��txt�ļ���Ϣ�������ݿ�
#endif

	return nRet;
}

UINT8 ClientImportProc()
{
	DBG_PRINT(("DeptImportProc()!"));
	UINT8 nRet;
	nRet = YesNoMsgBox("�Ƿ���ͻ���Ϣ��");
	if (nRet==FAILURE)
	{
		return SUCCESS;
	}

#if SQL_VER	
//	nRet = ImportHandle(3);  //�ú���δʵ�֣�����
#else
	nRet = ImportTxtHandle(3);//��txt�ļ���Ϣ�������ݿ�
#endif

	return nRet;
}

UINT8 ImportHandle(UINT8 nKind)
{
	DBG_PRINT(("ImportHandle()!"));
	UINT8 ret;
	
	string fileDir = "";
	string strCmd = "";
	switch(nKind) 
	{
	case 2:
		fileDir = IMPORT_DEPT_DIR;
		strCmd = IMPORT_DEPT_CMD;
		break;
	default:break;
	}

	//mount the USB disk
	ret = UsbDiskMount(NULL);
	if (SUCCESS != ret)
	{
		DBG_PRINT(("����U��ʧ�� ret = %u", ret));
		CaMsgBox::ShowMsg("����U��ʧ��");
		UsbDiskUnMount();
		return FAILURE;
	}

	//check the import file
	FILE *fp1; 
	if( (fp1=fopen(fileDir.c_str(),"r"))==NULL ) 
	{ 
		DBG_PRINT((" �����ļ��򿪴���"));
		CaMsgBox::ShowMsg("�����ļ��򿪴���");
		UsbDiskUnMount();
		return FAILURE;
	} 
	fclose(fp1);
	DBG_PRINT((" After fclose()"));

	//drop the existed table
	CaProgressBar proBar("��������...");
	proBar.ReFresh();
	CDept curDept;
	string strSql = "";
	DBG_PRINT(("��ձ�"));
	switch(nKind) 
	{
	case 2:
		if (curDept.Delete()!= SQLITE_OK)
		{
			CaMsgBox::ShowMsg("��ձ����");
			UsbDiskUnMount();
			DBG_RETURN(FAILURE);
		}
		break;
	default: break;
	}

	//import new table
	DBG_PRINT(("��������"));
//	POWOFF_DISABLE(); //���ε����ж�
	if ( system(strCmd.c_str()) != 0 )
	{
		CaMsgBox::ShowMsg("��������ʧ��");
		UsbDiskUnMount();
        return FAILURE;
	}
//	POWOFF_ENABLE();//�������ж�
	
	UsbDiskUnMount();
	curDept.Requery();
	curDept.LoadOneRecord();
	
	CaMsgBox::ShowMsg("�������ݳɹ�");
	return SUCCESS;
}

UINT8 DeptExportProc()
{
	DBG_PRINT(("ExportDeptProc()!"));
	UINT8 nRet;
	nRet = YesNoMsgBox("�Ƿ񵼳���Ʒ��Ϣ��");
	if (nRet==FAILURE)
	{
		return SUCCESS;
	}
	
#if SQL_VER	
	nRet = ExportSqlHandle(EXPORT_DEPT_CMD); //�����ݿⲿ����Ϣ������sql�ļ�
#else
	nRet = ExportTxtHandle(2);//�����ݿⲿ����Ϣ������TXT�ļ�
#endif

	return nRet;	
}

UINT8 ClientExportProc()
{
	DBG_PRINT(("ExportDeptProc()!"));
	UINT8 nRet;
	nRet = YesNoMsgBox("�Ƿ񵼳��ͻ���Ϣ��");
	if (nRet==FAILURE)
	{
		return SUCCESS;
	}

#if SQL_VER	
	nRet = ExportSqlHandle(EXPORT_CLIENT_CMD); //�����ݿ�ͻ���Ϣ������sql�ļ�
#else
	nRet = ExportTxtHandle(3);//�����ݿ�ͻ���Ϣ������TXT�ļ�
#endif

	return nRet;	
}

UINT8 ExportSqlHandle(string strCmd)
{
	DBG_PRINT(("ExportSqlHandle()!"));
	UINT8 ret;

	ret = UsbDiskMount(NULL);
	if (SUCCESS != ret)
	{
		CaMsgBox::ShowMsg("����U��ʧ��");
		DBG_PRINT(("����U��ʧ�� ret = %u", ret));
		UsbDiskUnMount();
		return FAILURE;
	}
	
	CaProgressBar proBar("��������...");
	proBar.ReFresh();
	if ( system(strCmd.c_str()) != 0 )
	{
		CaMsgBox::ShowMsg("��������ʧ��");
		UsbDiskUnMount();
        return FAILURE;
	}
	
	UsbDiskUnMount();
	CaMsgBox::ShowMsg("�������ݳɹ�");
	return SUCCESS;

}

UINT8 ImportTxtHandle(UINT8 nKind)
{
	DBG_PRINT(("ImportTxtHandle()!"));

	FILE *fp;
	INT8 *chaBlank = " ";//�ո�
	UINT8 nRet;	
	string fileDir = "";
	
	switch(nKind) 
	{
	case 2:
		fileDir = IMPORT_DEPT_TXT_DIR;
		break;
	case 3:
		fileDir = IMPORT_CLIENT_TXT_DIR;
		break;
	default:break;
	}

	//mount the USB disk
	nRet = UsbDiskMount(NULL);
	if (SUCCESS != nRet)
	{
		DBG_PRINT(("����U��ʧ�� ret = %u", nRet));
		CaMsgBox::ShowMsg("����U��ʧ��");
		UsbDiskUnMount();
		return FAILURE;
	}

	//open the import file 
	if( (fp=fopen(fileDir.c_str(),"r"))==NULL ) 
	{ 
		DBG_PRINT((" �����ļ��򿪴���"));
		CaMsgBox::ShowMsg("�����ļ��򿪴���");
		UsbDiskUnMount();
		return FAILURE;
	} 

	CaProgressBar proBar("��������...");
	proBar.ReFresh();

	CDept curDept;
	CClient curClient;
	switch(nKind) 
	{
		case 2:
			if (SQLITE_OK != curDept.Delete())
			{
				CaMsgBox::ShowMsg("��ձ����");
				fclose(fp);
				UsbDiskUnMount();
				DBG_RETURN(FAILURE);
			}
			nRet = InsertOneDept(fp, chaBlank);
			break;
		case 3:
			if (SQLITE_OK != curClient.Delete())
			{
				CaMsgBox::ShowMsg("��ձ����");
				fclose(fp);
				UsbDiskUnMount();
				DBG_RETURN(FAILURE);
			}
			nRet = InsertOneClient(fp, chaBlank);
			break;
		default:break;
	}
	
	if (SUCCESS != nRet) 
	{
		CaMsgBox::ShowMsg("��������ʧ��");
		fclose(fp);
		UsbDiskUnMount();
        return FAILURE;
	}

	fclose(fp);
	UsbDiskUnMount();

//	curDept.Requery();
//	curDept.LoadOneRecord();
	
	CaMsgBox::ShowMsg("�������ݳɹ�");
	return SUCCESS;
}

UINT8 InsertOneDept(FILE *fp, const INT8 *pchToken)
{
	CDept curDept;
	INT8 *chTemp;
	INT8 chBuf[512];
	memset((void*)chBuf, 0, sizeof(chBuf));	
	INT8 chStr[32];
	memset((void*)chStr, 0, sizeof(chStr));
	UINT32 nIndex = 0;
	CaProgressBar proBar("");

	fgets(chBuf, sizeof(chBuf), fp);
	while (fgets(chBuf, sizeof(chBuf), fp)) //��һ��������Ϣ��chBuf��
	{
		DBG_PRINT(("%s", chBuf));
		//�����
		if( (chTemp = strtok(chBuf, pchToken)) == NULL ) 
		{
			continue;
		}
		else
		{
			curDept.m_blh = atoi(chTemp);		
		}
		//����
		if( (chTemp = strtok(NULL, pchToken)) == NULL ) 
		{
			continue;
		}
		else
		{
			curDept.m_spmc = chTemp;
		}
		//��ӦPLU
		if( (chTemp = strtok(NULL, pchToken)) == NULL ) 
		{
			continue;
		}
		else
		{
			curDept.m_spbm = chTemp;
		}
		//����
		if( (chTemp = strtok(NULL, "\r")) == NULL ) 
		{
			continue;
		}
		else
		{
			curDept.m_spdj = atof(chTemp);
		}

		if ((curDept.m_blh < 0 )||(curDept.m_blh > 99))
		{
			CaMsgBox::ShowMsg("����ű�����0��99֮��");
			continue;
			//return FAILURE;
		}
		if( curDept.m_spmc.length() > GOODS_NAME_LEN )
		{
			CaMsgBox::ShowMsg("��Ʒ���Ʋ��ܳ���20�ֽ�");
			continue;
		}

		if (SQLITE_OK != curDept.AddNew()) //����һ��PLU��¼
		{
			return FAILURE;
		}
		nIndex++;
		sprintf(chStr, "������Ʒ������%u", nIndex);
		proBar.SetText(chStr);
		proBar.Show();		
	}

	if (0 != ferror(fp))
	{
		return FAILURE;//���ļ�ʧ��
	}

	if (0 == nIndex) 
	{
		return FAILURE;//һ��Ҳû����
	}
	return SUCCESS;
}

UINT8 InsertOneClient(FILE *fp, const INT8 *pchToken)
{
	CClient curClient;
	INT8 *chTemp;
	INT8 chBuf[512];
	memset((void*)chBuf, 0, sizeof(chBuf));	
	INT8 chStr[32];
	memset((void*)chStr, 0, sizeof(chStr));
	UINT32 nIndex = 0;
	CaProgressBar proBar("");

	fgets(chBuf, sizeof(chBuf), fp);
	while (fgets(chBuf, sizeof(chBuf), fp)) //��һ��������Ϣ��chBuf��
	{
		DBG_PRINT(("%s", chBuf));
		//�ͻ����
		if( (chTemp = strtok(chBuf, pchToken)) == NULL ) 
		{
			continue;
		}
		else
		{
			curClient.m_khbh = chTemp;		
		}
		//�ͻ�����
//		if( (chTemp = strtok(NULL, pchToken)) == NULL ) 
//		{
//			continue;
//		}
//		else
//		{
//			curClient.m_khdm = chTemp;		
//		}
		//�������
//		if( (chTemp = strtok(NULL, pchToken)) == NULL ) 
//		{
//			continue;
//		}
//		else
//		{
//			curClient.m_khjm = chTemp;		
//		}
		//�ͻ�����
		if( (chTemp = strtok(NULL, "\r")) == NULL ) 
		{
			continue;
		}
		else
		{
			curClient.m_khmc = chTemp;
		}
	
		INT32 ret =curClient.AddNew();
		DBG_PRINT(("ret= %d",ret));
		if (SQLITE_OK != ret) //����һ���ͻ���¼
		{
			return FAILURE;
		}
		
		nIndex++;
		sprintf(chStr, "���븶���˸�����%u", nIndex);
		proBar.SetText(chStr);
		proBar.Show();		
	}

	if (0 != ferror(fp))
	{
		return FAILURE;//���ļ�ʧ��
	}
	
	if (0 == nIndex) 
	{
		return FAILURE;//һ��Ҳû����
	}
	return SUCCESS;
}
INT8 ComposeClientTxt(const CClient *pClient, string &strTxt)
{
	DBG_ASSERT_EXIT((pClient != NULL), (" pClient == NULL!"));
	
	//��װд������Ϣ��ָ��
    strTxt = "";
	strTxt += pClient->m_khbh;
	strTxt += " ";
//	strTxt += pClient->m_khdm;
//	strTxt += " ";
//	strTxt += pClient->m_khjm;
// 	strTxt += " ";
	strTxt += pClient->m_khmc;
	strTxt += "\r\n";

	return SUCCESS;
}

INT8 ComposeDeptTxt(const CDept *pDept, string &strTxt)
{
	DBG_ASSERT_EXIT((pDept != NULL), (" pDept == NULL!"));
	
	INT8 chValue[256];
	//��װд������Ϣ��ָ��
	memset((void*)chValue, 0, sizeof(chValue));
	sprintf(chValue, "%u %s %s %.2f", pDept->m_blh, 
		pDept->m_spmc.c_str(), pDept->m_spbm.c_str(),
		pDept->m_spdj);

	strTxt = "";
	strTxt += chValue;
	strTxt += "\r\n";
	DBG_PRINT(("strTxt = %s", strTxt.c_str()));

	return SUCCESS;
}

UINT8 ExportTxtHandle(UINT8 nKind)
{
	DBG_PRINT(("ExportTxtHandle()!"));

	FILE *fp;
	INT8 *chaBlank = " ";//�ո�
	UINT8 nRet;	
	string fileDir = "";
	
	switch(nKind) 
	{
	case 2:
		fileDir = EXPORT_DEPT_TXT_DIR;
		break;
	case 3:
		fileDir = EXPORT_CLIENT_TXT_DIR;
		break;
	default:break;
	}

	//mount the USB disk
	nRet = UsbDiskMount(NULL);
	if (SUCCESS != nRet)
	{
		DBG_PRINT(("����U��ʧ�� ret = %u", nRet));
		CaMsgBox::ShowMsg("����U��ʧ��");
		UsbDiskUnMount();
		return FAILURE;
	}

	//create and open the export file 
	if( (fp=fopen(fileDir.c_str(),"w"))==NULL ) 
	{ 
		DBG_PRINT((" �����ļ��򿪴���"));
		CaMsgBox::ShowMsg("�����ļ��򿪴���");
		UsbDiskUnMount();
		return FAILURE;
	} 

	CaProgressBar proBar("��������...");
	proBar.ReFresh();

	CDept curDept;
	CClient curClient;
	switch(nKind) 
	{
		case 2:
			nRet = OutputOneDept(fp);
			break;
		case 3:
			nRet = OutputOneClient(fp);
			break;
		default:break;
	}

	if (SUCCESS != nRet) 
	{
		CaMsgBox::ShowMsg("��������ʧ��");
		fclose(fp);
		UsbDiskUnMount();
        return FAILURE;
	}

//	fflush(fp); //ˢ���ļ���С
	fclose(fp);
	UsbDiskUnMount();
	
	CaMsgBox::ShowMsg("�������ݳɹ�");
	return SUCCESS;

}
UINT8 OutputOneDept(FILE *fp)
{
	INT32 errorcode;
	CDept curDept;
	string strSql = "";
	INT32 nRealLen, nLen;
	UINT32 nIndex = 0;
	CaProgressBar proBar("");
	INT8 chBuf[128];
	memset((void*)chBuf, 0, sizeof(chBuf));

	strSql = "�����(3) ��Ʒ����(20) ��Ʒ����(3) ��Ʒ����(11)\r\n";
	nRealLen = strSql.length();
	//fwrite(strSql.c_str(),1, nRealLen,fp);
	fwrite(strSql.c_str(),nRealLen,1, fp);

	//read Dept and write it to file one by one
	curDept.Requery();
    errorcode = curDept.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		strSql = "";
		ComposeDeptTxt(&curDept, strSql);	
		nRealLen = strSql.length();
		nLen = 0;
		//nLen = fwrite(strSql.c_str(),1, nRealLen,fp); 
		nLen = fwrite(strSql.c_str(),nRealLen,1, fp); 
// 		if (nLen!=nRealLen) 
// 		{
// 			curDept.MoveEnd();
// 			sprintf(chBuf, "������%d����Ʒ����!", nIndex+1);
// 			CaMsgBox::ShowMsg(chBuf);		
// 			return FAILURE;
// 		}
		if(0 != fflush(fp))//������������д��Ӳ���ļ�
		{
			curDept.MoveEnd();
			return FAILURE;
		}
		nIndex++;
		sprintf(chBuf, "������Ʒ������%u", nIndex);
		proBar.SetText(chBuf);
		proBar.Show();		
		errorcode = curDept.MoveNext(); // read next plu
	}
	curDept.MoveEnd();

	if (errorcode!=SQLITE_DONE) 
	{		
		CaMsgBox::ShowMsg("��ѯ���ݿ����");
		return FAILURE;			
	}

	if (0 == nIndex) 
	{
		CaMsgBox::ShowMsg("����Ʒ��Ϣ�ɵ���");
		return FAILURE;
	}

	return SUCCESS;
}

UINT8 OutputOneClient(FILE *fp)
{
	INT32 errorcode;
	CClient curClient;
	string strSql = "";
	INT32 nRealLen, nLen;
	UINT32 nIndex = 0;
	CaProgressBar proBar("");
	INT8 chBuf[128];
	memset((void*)chBuf, 0, sizeof(chBuf));

	strSql = "�ͻ����(3) �ͻ�����(80)\r\n";
	nRealLen = strSql.length();
	//fwrite(strSql.c_str(),1, nRealLen,fp);
	fwrite(strSql.c_str(),nRealLen,1, fp);

	//read Dept and write it to file one by one
	curClient.Requery();
    errorcode = curClient.MoveFirst();
	while (errorcode == SQLITE_ROW)
	{
		strSql = "";
		ComposeClientTxt(&curClient, strSql);	
		nRealLen = strSql.length();
		nLen = 0;
		//nLen = fwrite(strSql.c_str(),1, nRealLen,fp);//д���ļ������� 
		nLen = fwrite(strSql.c_str(),nRealLen,1, fp);//д���ļ������� 
// 		if (nLen!=nRealLen) 
// 		{
// 			curClient.MoveEnd();
// 			sprintf(chBuf, "������%d���ͻ�����!", nIndex+1);
// 			CaMsgBox::ShowMsg(chBuf);		
// 			return FAILURE;
// 		}
		if(0 != fflush(fp))//������������д��Ӳ���ļ�
		{
			curClient.MoveEnd();
			return FAILURE;
		}
		nIndex++;
		sprintf(chBuf, "�����ͻ�������%u", nIndex);
		proBar.SetText(chBuf);
		proBar.Show();		
		errorcode = curClient.MoveNext(); // read next plu
	}
	curClient.MoveEnd();
	if (errorcode!=SQLITE_DONE) 
	{		
		CaMsgBox::ShowMsg("��ѯ���ݿ����");
		return FAILURE;			
	}

	if (0 == nIndex) 
	{
		CaMsgBox::ShowMsg("�޿ͻ���Ϣ�ɵ���");
		return FAILURE;
	}

	return SUCCESS;
}