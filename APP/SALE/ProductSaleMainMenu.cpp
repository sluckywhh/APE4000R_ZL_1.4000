/*! \file    ProductSaleMainMenu.cpp
\brief    awe4000r���۳�������Ʒ���۵�������
\author   Yu Yan
\version  1.0
\date     2007-11-28
*/


#include "ProductSaleMainMenu.h"
#include "beep.h"
#include "CClient.h"
#include "Scanner.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include <string>

CProductSaleMainMenu::CProductSaleMainMenu():CaWindow()
{
	if( pSaleData == NULL )
	{
		pSaleData = new SaleData;
		DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL "));
	}	
	m_strSuffix = "";
}

CProductSaleMainMenu::~CProductSaleMainMenu()
{
	if( pSaleData != NULL )
	{
		delete pSaleData;
        pSaleData = NULL;
	}
}


int CProductSaleMainMenu::Create(int iX,int iY,int iW,int iH)
{
	DBG_PRINT(("����CProductSaleMainMenu::Create����"));
	
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
	//	string curtime = TDateTime::CurrentDateTime().FormatString(YYYYMMDDHHMMSS);
	string curtime = TDateTime::CurrentDate().FormatString(YYYYMMDD);

	//curtime += "  ";
    int titleLen=0;
	
    m_iBtnW = (SCREEN_W/2 - 20) ;	//Label�Ŀ��
	m_iColW = m_iBtnW+5;			//Label���п�
	
	m_pFrame->RegsiterWin(this,PRODUCT_SALE_MAIN_MENU);
	
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	//����һ����ǩ ��һ��,��ǰʱ��
	label[0] = new CaLabel(false,CaObject::ALIGN_RIGHT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H);
	label[0]->SetTitle(curtime.c_str(), curtime.size());
	
	
	//����һ����ǩ  �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	
	//����һ����ǩ  ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	
	//����һ����ǩ  ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[3]->Create(0,curH, m_iBtnW, CHAR_H);
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	//����һ����ǩ  ������
	label[4] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[4]->Create(m_iColW,curH, m_iBtnW+40, CHAR_H);
	label[4]->SetTitle(title_array[4], strlen(title_array[4]));
	
	//����һ��Input  ������
	strcpy(title, "[����]");
	titleLen = strlen(title) * CHAR_W;
	curH += LINE_H;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(PAYER_NAME_LEN);
	
	OnActive = S_OnActive;
	
	this->End();
	
	DBG_PRINT(("�˳�CProductSaleMainMenu::Create����"));
	return SUCCESS;
}

//--------------------------------------------------------------------------------------
//�����¼�
//--------------------------------------------------------------------------------------
int CProductSaleMainMenu::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	DBG_PRINT(("����CProductSaleMainMenu::ProcEvent����"));
	
	UINT8 ret = 0;
	double ii;
	UINT32 deptNo;
	char *content;
	char *blank = "";
	string code = "";
	INT32 dotNum;//С��λ��
	UINT8 *chScan;
	INT32 nLen  = 0;
	UINT8 nIndex = 0;
	string strErr("");
	
	//-----------------------------------------------------
	//�û�ÿ��һ�μ����ʹ���һ���¼���
	//-----------------------------------------------------
	switch( iEvent )
	{
	case OPEN_CASH_BOX:
		DBG_PRINT(("������Ǯ��"));
		MoneyBox_Open();
		break;
		
	case DISCOUNT_KEY:
		content = (char*)(m_pInput2->m_contentBuf);
		if (strlen(content)==0)
		{
			CaMsgBox::ShowMsg("���������ۿ���");
			return SUCCESS;
		}		
		ii = atof(content);
		ii = (INT32)ii;//����ȡ��
		m_pInput2->Clear();
		ret = pSaleData->Discount(ii);
		if (ret != SUCCESS) 
		{
			return(ErrMsgBox(ret));
		}
		ReFresh();
		return SUCCESS;
		break;
		//	CaMsgBox::ShowMsg("�ݲ�֧�ִ˹���");
		//	return SUCCESS;
		//	break;
		
	case PRICE_INPUT:
		return(PriceInputProc());
		break;
		
	case SUM_INPUT:
		return(SumInputProc());
		break;
		
	case CLIENT_NAME_INPUT:		
		return(ClientInputProc());
		break;
		
	case FIND_KEY:
		return(ClientCodeInputProc());
		break;
		
	case PLUS_KEY:
		return(PlusProc());
		break;
		
		//�ֶ�������Ʒ����
	case PLU_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		code = "";
        nLen = GOODS_CODE_LEN - strlen(content);
		if (nLen > 0)	//����16λ����ǰ���㵽16λ
		{
			while(nLen > 0)
			{
				code += "0";
				nLen--;
			}
		}
		code += content;
		//ret = pSaleData->PLUSale(code);
		ret = pSaleData->DeptSale(0, code);
		m_pInput2->Clear();
		if (ret != SUCCEED) 
		{
			m_strSuffix = "";
			return(ErrMsgBox(ret));
		}
		//���ʵ�����ݵ����ĺ��� 
		DeptSaleShow();
		pPSWin = (CProductSaleWin*)m_pFrame->GetWin(PRODUCT_SALE_WIN);
		if (pPSWin!=NULL)
		{
			pPSWin->ChangeTitle();
			pPSWin->ReFresh();
		}
		//�л�����Ʒ���۽���
		ChangeWin(PRODUCT_SALE_WIN);
		return SUCCESS;
		break;
	case SHIFT_PLU_KEY: //��ʱ������Ʒ����
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		ret = pSaleData->PLUSale(content, strErr);	
		if (ret != SUCCEED) 
		{
			m_strSuffix = "";
			if (FAILURE == ret) 
			{
				CaMsgBox::ShowMsg(strErr);
				strErr = "";
			}
			else
			{
				ErrMsgBox(ret);
			}		
			return FAILURE;
		}
		m_pInput2->Clear();
		//���ʵ�����ݵ����ĺ��� 
		DeptSaleShow();
		pPSWin = (CProductSaleWin*)m_pFrame->GetWin(PRODUCT_SALE_WIN);
		if (pPSWin!=NULL)
		{
			pPSWin->ChangeTitle();
			pPSWin->ReFresh();
		}
		//�л�����Ʒ���۽���
		ChangeWin(PRODUCT_SALE_WIN);
		return SUCCESS;
		break;
		
	case CHANGE_DEPT_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		deptNo = atoi(content);
		m_pInput2->Clear();
		return(DeptSaleProc(deptNo));
		break;
		
		//����1
	case DEPT1_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		//QuickSaleProc������������
		if( QuickSaleProc() != SUCCESS )
		{
			DBG_PRINT(("QuickSaleProc����ִ��ʧ�ܡ��˳�CProductSaleMainMenu::ProcEvent����"));
			return FAILURE;
		}
		DBG_PRINT(("case DEPT1_KEY:"));
		return(DeptSaleProc(1));
		break;
		
		//����2
	case DEPT2_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		if (QuickSaleProc()!=SUCCESS)
		{
			return FAILURE;
		}
		return(DeptSaleProc(2));
		break;
		
		//����3
	case DEPT3_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		if (QuickSaleProc()!=SUCCESS)
		{
			return FAILURE;
		}
		return(DeptSaleProc(3));
		break;
		
		//����4
	case DEPT4_KEY:
		if( pSaleData->m_tmpGoodsNum >= MAX_GOODS_LINE ) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		if (QuickSaleProc()!=SUCCESS)
		{
			return FAILURE;
		}
		return(DeptSaleProc(4));
		break;
		
		//����5
	case DEPT5_KEY:
		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		if (QuickSaleProc()!=SUCCESS)
		{
			return FAILURE;
		}
		return(DeptSaleProc(5));
		break;
		
		// 	case SCANNER_EVENT_KEY:
		// 		DBG_PRINT((" SCANNER_EVENT_KEY ɨ��ǹ������"));
		// 		if (pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE) 
		// 		{
		// 			CaMsgBox::ShowMsg("��Ʒ��������");
		// 			return FAILURE;
		// 		}
		// 		content = (char*)ScannerCode();
		// 		DBG_PRINT((" ɨ��ǹ������PLU�룺%s", content));
		// 		code = "";
		//         nLen = GOODS_CODE_LEN - strlen(content);
		// 		if (nLen > 0)//����13λ����ǰ���㵽13λ
		// 		{
		// 			while(nLen > 0)
		// 			{
		// 				code += "0";
		// 				nLen--;
		// 			}
		// 		}
		// 		code += content;
		// 		//ret = pSaleData->PLUSale(code);
		// 		ret = pSaleData->DeptSale(0, code);
		// 		if (ret != SUCCEED) 
		// 	   {
		// 			DBG_PRINT((" ���� ret = %u", ret));
		// 			ErrMsgBox(ret);
		// 			ClearScannerBuf();
		// 			return FAILURE;
		// 	   }
		// 	   //���ʵ�����ݵ����ĺ��� 
		// 	   DeptSaleShow();
		// 	   pPSWin = (CProductSaleWin*)m_pFrame->GetWin(PRODUCT_SALE_WIN);
		// 	   if (pPSWin!=NULL)
		// 	   {
		// 		   pPSWin->ChangeTitle();
		// 		   pPSWin->ReFresh();
		// 	   }
		// 	   //�л�����Ʒ���۽���
		// 	   ChangeWin(PRODUCT_SALE_WIN);
		// 	   return SUCCESS;
		// 		break;
		
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		ret = SYSTEM_MAIN_MENU;
		if ((pSaleData->m_invtype==RETURN_INV)||(pSaleData->m_invtype==RET_MANUAL_INV)||
			(pSaleData->m_invtype==RET_SPECIAL_INV))
		{
			ret = INV_MANAGE_MENU;
		}
		//		ScannerRelease();						//ֹͣɨ��ǹɨ��
		pSaleData->InitSaleData(1);				//������Ϣ��ʼ��
		pSaleData->InitInvHead();				//���ŷ�Ʊ��Ϣ��ʼ��
		pSaleData->m_workState = WORK_COMPLETE; //����״̬��ʼ��
		ChangeWin(ret);
		
		return SUCCESS;
		
		
	case FORWARD_KEY:
		return(ForwardKeyProc());
		break;
		
	case BACKWARD_KEY:
		ret = BackwardPaper();
		if (ret != SUCCESS) 
		{
			return(ErrMsgBox(NO_PAPER));
		}
		return SUCCESS;
		break;
		
	case CASH_KEY:
		//if (0 == g_globalArg->m_curInvVol->m_remain)
		if (0==g_globalArg->m_curInvVol->m_curInvNo)
		{
			return(ErrMsgBox(INV_ZERO));	
		}
		pSaleData->InitSaleData(0);//��ԭ������ر���
		CaMsgBox::ShowMsg("δ�����κ���Ʒ");
		return SUCCESS;	
		break;
		
	case CANCEL_GOODS:
		CaMsgBox::ShowMsg("δ�����κ���Ʒ");
		return SUCCESS;	
		break;
		
	case TOTAL_CANCEL:
		CaMsgBox::ShowMsg("δ�����κ���Ʒ");
		return SUCCESS;	
		break;
		
	case GOODSREDUCT_KEY:
		//	CaMsgBox::ShowMsg("δ�����κ���Ʒ");
		CaMsgBox::ShowMsg("�ݲ�֧�ִ˹���");
		return SUCCESS;	
		break;
		
	default: break;		
	}
	
	DBG_PRINT(("�˳�CProductSaleMainMenu::ProcEvent����"));
 	  
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

int CProductSaleMainMenu::ReFresh()
{   
	DBG_PRINT(("����ReFresh����"));
	ReFreshTitle();
	CaGroup::ReFresh();
	if(m_pCurObj != NULL )
	{
		m_pCurObj->SetFocusIn();
	}
	LCDRedraw();
	
	return 1;
	DBG_PRINT(("�˳�ReFresh����"));
}

UINT8 CProductSaleMainMenu::ErrMsgBox(UINT8 ret)
{
	DBG_PRINT(("����ErrMsgBox����"));
	
	string pText;
	switch(ret)
	{
	   case NO_SUCH_GOODS:
		   pText = "δ�ҵ�����Ʒ";
		   break;
	   case EXCEED_PRICE:
		   pText = "���۳���";
		   break;
	   case SHORT_OF_INV:
		   pText = "����ʣ�෢Ʊ����";
		   break;
	   case TAX_ID_ILLEGAL:
		   pText = "˰��˰Ŀ����";
		   break;
	   case TAX_UNAUTHORIZED:
		   pText = "˰��δ��Ȩ";
			break;	
	   case NM_EXCEED:
		   pText = "���ſ�Ʊ����";
		   break;
	   case NM_SUM_EXCEED:
		   pText = "��Ʊ�ۼƽ���";
		   break;
	   case RM_SUM_EXCEED:
		   pText = "��Ʊ�ۼƽ���";
		   break;
	   case NVM_SUM_EXCEED:
		   pText = "������Ʊ�ۼƽ���";
		   break;
	   case RVM_SUM_EXCEED:
		   pText = "�����Ʊ�ۼƽ���";
		   break;
	   case MONEY_NOT_ENOUGH:
		   pText = "�ֽ����";
		   break;
	   case REBATE_ERROR:
		   pText = "�ۿ��ʳ���";
		   break;
	   case PRICE_NOT_ENOUGH:
		   pText = "�۸񲻵�С��0.01";
		   break;
	   case EXCEED_NAME_LEN:
		   pText = "���������ƹ���";
		   break;
	   case NO_NAME:
		   pText = "δ���븶��������";
		   break;
	   case MUST_INPUT_SUM:
		   DBG_PRINT(("Please input total money!"));
		   pText = "�������ܼ۽��";
		   break;
	   case EXCEED_AMOUNT:
		   pText = "��������";
		   break;
	   case ILLEGAL_AMOUNT:
		   pText = "�����Ƿ�";
		   break;
	   case NO_PAPER:
		   pText = "û��ֽ�ʷ�Ʊ";
		   break;
	   case MONEY_ZERO:
		   pText = "��Ʒ���Ϊ0,���ÿ���";
		   break;
	   case INV_ZERO:
		   pText = "�޿��÷�Ʊ��";
		   break;
	   case DISCOUNT_MONEY_ZERO:
		   pText = "�ۿ��н��Ϊ��";
		   break;
	   default:;
	}  
	
	CaMsgBox::ShowMsg(pText);
	
	DBG_PRINT(("�˳�ErrMsgBox����"));
	return FAILURE;	
}

UINT8 CProductSaleMainMenu::DeptSaleShow()
{
	string strTemp = "";
	INT32 nCurrentInvNo = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
	INT8 tmp[16];
	
    sprintf(title_arr[0], "��ǰ��Ʊ��: %08d", g_globalArg->m_curInvVol->m_curInvNo);
	
	if ((DETAIL_GOODS_DISCOUNT == pSaleData->m_invDet->m_property) && (0 == m_strSuffix.length()))//���ۿ� 
	{
		m_strSuffix = "<��>";
	}
	
	strTemp = "��Ʒ: ";
    strTemp.append(pSaleData->m_invDet->m_spmc);
	strTemp.append(m_strSuffix);
    m_strSuffix = "";
    strcpy(title_arr[1], (strTemp.c_str()));
	
	sprintf(title_arr[2], "����:%.2lf", pSaleData->m_invDet->m_spdj);
	sprintf(tmp, "����:%%.%luf", pSaleData->m_invDet->m_dotNum);		//�����������
	sprintf(title_arr[3], tmp, pSaleData->m_invDet->m_spsl);
	if ((pSaleData->m_invtype==RETURN_INV)||(pSaleData->m_invtype==RET_MANUAL_INV)||(pSaleData->m_invtype==RET_SPECIAL_INV)) 
	{
		sprintf(title_arr[4], "�ϼ�:-%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	else
	{
		sprintf(title_arr[4], "�ϼ�:%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	
	sprintf(title_arr[5], "��Ʒ����:%u", pSaleData->m_tmpGoodsNum);
	
	return SUCCESS;	
}

void CProductSaleMainMenu::S_OnActive(CaWindow *obj)
{
	((CProductSaleMainMenu *)obj)->DoActive();
}


void CProductSaleMainMenu::DoActive()
{
	DBG_PRINT(("����CProductSaleMainMenu::DoActive����"));
	DBG_ENTER("CProductSaleMainMenu::DoActive()");

	// 	if (ScannerInit()!=SUCCESS)
	// 	{
	// 		CaMsgBox::ShowMsg("ɨ��ǹ��ʼ��ʧ��");
	// 	}
	
	if (pSaleData == NULL)
	{
		pSaleData = new SaleData;
		DBG_ASSERT_EXIT((pSaleData != NULL), (" pSaleData == NULL "));
	}
	
	UpdateSaleValue();	//�������۱����ж�Ӧȫ�ֱ�����ֵ
	
	m_strSuffix = "";
	m_pInput2->Clear();	//���Input�������

	NormalShow();
	
	ChangeTitle();

	//ÿ���һ��ʱ�����û�����
	if (1 == g_globalArg->m_curInvVol->m_curInvNo%DEFAULTE_VOL_NUM)
	{
	//	CaMsgBox::ShowMsg("��ȷ��ֽ�ʷ�Ʊ���뵱ǰ��Ʊ�Ŷ�Ӧ!");
	}
	
	ReFresh();
	DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
	DBG_PRINT(("�˳�CProductSaleMainMenu::DoActive����"));
}

int CProductSaleMainMenu::ChangeTitle()
{
	DBG_PRINT(("����ChangeTitle����"));
	
	string curtime = TDateTime::CurrentDate().FormatString(YYYYMMDD);
	//curtime += "  ";
	label[0]->SetTitle(curtime.c_str(), curtime.size());
	label[1]->SetTitle(title_array[1], strlen(title_array[1]));
	label[2]->SetTitle(title_array[2], strlen(title_array[2]));
	label[3]->SetTitle(title_array[3], strlen(title_array[3]));
	label[4]->SetTitle(title_array[4], strlen(title_array[4]));
	return 1;
	DBG_PRINT(("�˳�ChangeTitle����"));
}

UINT8 CProductSaleMainMenu::ClientShow()
{
	string strTemp = "������: ";
    strTemp.append(pSaleData->m_singleInvInfo->m_fkdw); 
    strncpy(title_array[2], (strTemp.c_str()), OBJ_TITLE_MAX_LEN);//�����˽ϳ���ֻ����ʾ����
	
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::ClientCodeShow()
{
	string strTemp = "������˰��: ";
    strTemp.append(pSaleData->m_singleInvInfo->m_fkdwsh); 
    strncpy(title_array[2], (strTemp.c_str()), OBJ_TITLE_MAX_LEN);//�����˽ϳ���ֻ����ʾ����
	
	return SUCCESS;
}

//������ʾ
UINT8 CProductSaleMainMenu::NormalShow()
{
	DBG_PRINT(("����NormalShow����"));
	string strErr;
	UINT8 ret = SUCCESS;
	INT32 nCurrentInvNo  = 0;
	UINT8 uFlag =0;
	
	//��ǰ��Ʊ��
	if (g_globalArg->m_operator->m_role==DEMO_ROLE) 
	{
		nCurrentInvNo = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
		sprintf(title_array[1], "��ǰ��Ʊ��: %08d", nCurrentInvNo);
	}
	else
	{
 		if (0 == g_globalArg->m_curInvVol->m_curInvNo) //���ⷴ������
		 		{
		 			ret = SALE_GetCurInv(g_globalArg->m_curInvVol,strErr);
		 			DBG_PRINT(("strErr= %s",strErr.c_str()));
		 			if (ret ==FAILURE)
		 			{
		 				uFlag=1;
		 				sprintf(title_array[1], strErr.c_str()); //����
		 			} 	
		 		}
		if (0 == uFlag)
		{
			
			sprintf(title_array[1], "%s  %08u", 
				g_globalArg->m_curInvVol->m_code.c_str(), g_globalArg->m_curInvVol->m_curInvNo);
		}
		
	}
	
	DBG_PRINT((" g_globalArg->m_curInvVol->m_ieno = %u !", g_globalArg->m_curInvVol->m_ieno));
	DBG_PRINT((" g_globalArg->m_curInvVol->m_remain = %u !", g_globalArg->m_curInvVol->m_remain));
	
	//��һ��
	if( 0 == g_globalArg->m_curInvVol->m_curInvNo) 
	 	{
 		sprintf(title_array[1], "��ǰ��Ʊ��: ���޷�Ʊ���빺��");		
	 	}
		else
		{
		sprintf(title_array[1], "��ǰ��Ʊ��: %08d", g_globalArg->m_curInvVol->m_curInvNo);
	 	}
	
	
	
	//�ڶ���
	strcpy(title_array[2], "");
	
	//������
	if (g_globalArg->m_operator->m_role==DEMO_ROLE) 
	{
		strcpy(title_array[3], "ģʽ: ѵ��");		
	}
	else
	{
		strcpy(title_array[3], "ģʽ: ����");
	}
	
	sprintf(title_array[4], "����Ա: %s", g_globalArg->m_operator->m_name.c_str());
	
	DBG_PRINT(("�˳�NormalShow����"));
	return SUCCESS;	
}

UINT8 CProductSaleMainMenu::ForwardKeyProc()
{
	UINT8 ret;
	
	if (g_globalArg->pSaveTemplateInfo->markFlag == 1)//���Һڱ�
	{
		CaMsgBox msgBox("�Ƿ��ֽ?",CaMsgBox::MB_YESNO);
		msgBox.ShowBox();
		if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
		{
			return SUCCESS;
		}
		
		if(msgBox.m_iStatus == OK_PRESSED)
		{
			this->ReFresh();
			ret = ForwardPaper();
			if (ret != SUCCESS) 
			{
				return(ErrMsgBox(NO_PAPER));
			}		
		}
	}
	else 
	{
		ret = ForwardPaper();
		if (ret != SUCCESS) 
		{
			return(ErrMsgBox(NO_PAPER));
		}		
	}
	
	ReFresh();
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::DeptSaleProc(UINT32 deptNo)
{
	UINT8 ret;
	DBG_PRINT(("����CProductSaleMainMenu::DeptSaleProc����"));
	DBG_PRINT(("deptNo==%u", deptNo));
	
	ret = pSaleData->DeptSale(deptNo, "");
	if( ret != SUCCEED ) 
	{
		m_strSuffix = "";
		DBG_PRINT(("׼���˳�DeptSaleProc����"));
		return(ErrMsgBox(ret));
	}
	//���ʵ�����ݵ����ĺ��� 
	DeptSaleShow();
	pPSWin = (CProductSaleWin*)m_pFrame->GetWin(PRODUCT_SALE_WIN);
	if (pPSWin!=NULL)
	{
		pPSWin->ChangeTitle();
		pPSWin->ReFresh();
	}
	//�л�����Ʒ���۽���
	ChangeWin(PRODUCT_SALE_WIN);
	
	DBG_PRINT(("�˳�CProductSaleMainMenu::DeptSaleProc����"));
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::ClientInputProc(void)
{
	char *content;
	UINT8 ret;
	char *blank = "";
	INT8 chValue[128];
	memset((void*)chValue, 0, sizeof(chValue));
	
	content = (char*)(m_pInput2->m_contentBuf);
	if ('.' == *content) 
	{
		CClient client;
		sprintf(chValue, "where KH_BH = '%s'", (content+1));
		client.m_filter = chValue;
		client.Requery();
		if(client.LoadOneRecord()!= SQLITE_OK)
		{
			CaMsgBox::ShowMsg("û�ж�Ӧ�ĸ�����");
			return FAILURE;
		}
		ret = pSaleData->ClientNameInput(client.m_khmc.c_str(), client.m_khsh.c_str());		
	}
	else
	{
		ret = pSaleData->ClientNameInput(content);
	}
	
	m_pInput2->Clear();
	if (ret != SUCCESS) 
	{
		return(ErrMsgBox(ret));
	}
	ClientShow();
	ChangeTitle();
	ReFresh();
	strcpy(title_array[2], blank);
	ChangeTitle();
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::ClientCodeInputProc(void)
{
	char *content;
	UINT8 ret;
	char *blank = "";
	INT8 chValue[128];
	memset((void*)chValue, 0, sizeof(chValue));
	string srrErr("");
	
	content = (char*)(m_pInput2->m_contentBuf);

	ret = pSaleData->ClientCodeInput(content,srrErr);

	m_pInput2->Clear();
	if (ret != SUCCESS) 
	{
		CaMsgBox::ShowMsg(srrErr);
		return FAILURE;
	}

	ClientCodeShow();
	ChangeTitle();
	ReFresh();
	strcpy(title_array[2], blank);
	ChangeTitle();
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::PriceInputProc(void)
{
	DBG_PRINT(("����CProductSaleMainMenu::PriceInputProc����"));
	UINT8 ret = 0;
	double ii;
	char *content;
	INT32 dotNum;//С��λ��
	
	content = (char*)(m_pInput2->m_contentBuf);
	ii = atof(content);
	DBG_PRINT(("ii= %lf",ii));
 	if(ii > MAX_MONEY)
	{
			CaMsgBox::ShowMsg("�����������ֵ");
	 		return FAILURE;
 	}	
	dotNum = CheckFloatBit(ii);
	if (dotNum>3) 
	{
		DBG_PRINT(("--------ii = %f--------", ii));
		DBG_PRINT(("--------dotNum = %d--------", dotNum));
		CaMsgBox::ShowMsg("С��λ�����ó�����λ");
		return FAILURE;
	}
	m_pInput2->Clear();
	ret = pSaleData->PriceInput(ii);
	if (ret != SUCCESS) 
	{
		return(ErrMsgBox(ret));
	}
	ReFresh();
	DBG_PRINT(("�˳�CProductSaleMainMenu::PriceInputProc����"));
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::SumInputProc(void)
{
	UINT8 ret = 0;
	double ii;
	char *content;
	INT32 dotNum;//С��λ��
	
	DBG_PRINT(("����SumInputProc����"));
	
	content = (char*)(m_pInput2->m_contentBuf);		//m_pInput2�����û�������ܼ�
	ii = atof(content);
	DBG_PRINT(("ii= %lf",ii));
	 if(ii > MAX_MONEY)
	 {
			CaMsgBox::ShowMsg("�����������ֵ");
	 		return FAILURE;
 	}	
	dotNum = CheckFloatBit(ii);
	if (dotNum>2) 
	{
		DBG_PRINT(("--------ii = %f--------", ii));
		DBG_PRINT(("--------dotNum = %d--------", dotNum));
		CaMsgBox::ShowMsg("С��λ�����ó�����λ");
		return FAILURE;
	}
	m_pInput2->Clear();
	ret = pSaleData->SumInput(ii);
	if (ret != SUCCESS) 
	{
		return(ErrMsgBox(ret));
	}
	ReFresh();
	DBG_PRINT(("�˳�SumInputProc����"));
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::PlusProc(void)
{
	DBG_PRINT(("����PlusProc����"));
	UINT8 ret = 0;
	double ii;
	char *content;
	INT32 dotNum;//С��λ��
	
	content = (char*)(m_pInput2->m_contentBuf);
	ii = atof(content);
	DBG_PRINT(("ii= %lf",ii));
	if(ii > MAX_MONEY)
 	{
 		CaMsgBox::ShowMsg("��������");
 		return FAILURE;
}
	m_pInput2->Clear();
	ret = pSaleData->Plus(ii);
	if (ret != SUCCESS) 
	{
		return(ErrMsgBox(ret));
	}
	ReFresh();
	DBG_PRINT(("�˳�PlusProc����"));
	return SUCCESS;
}

UINT8 CProductSaleMainMenu::QuickSaleProc(void)
{
	UINT8 ret;
	DBG_PRINT(("����QuickSaleProc����"));
	
	if( m_pInput2->IsEmpty() )
	{
		DBG_PRINT(("�˳�QuickSaleProc����"));
		return SUCCESS;
	}
	
	//����Ĭ������ģʽѡ��ͬ�ĺ���ִ�С�
	DBG_PRINT(("g_globalArg->m_saleMode == %d", g_globalArg->m_saleMode));
	switch( g_globalArg->m_saleMode ) 
	{
	case 0:
		ret = SumInputProc();
		break;
	case 1:
		ret = PriceInputProc();
		break;
	case 2:
		ret = PlusProc();
		break;
	default:
		break;
	}
	
	DBG_PRINT(("ret == %d", ret));
	DBG_PRINT(("�˳�QuickSaleProc����"));
	return ret;	
}

//----------------------------------------------------------
//��������������ж�Ӧȫ�ֱ�����ֵ
//----------------------------------------------------------
UINT8 CProductSaleMainMenu::UpdateSaleValue(void)
{
	DBG_PRINT(("����UpdateSaleValue����"));
	pSaleData->m_singleInvInfo->m_fkdw = g_globalArg->m_defaultPayerName;	//����������
	pSaleData->m_singleInvInfo->m_fkdwsh = "";	//���λ˰��
	pSaleData->m_singleInvInfo->m_sky = g_globalArg->m_operator->m_name;	//�տ�Ա
	//	pSaleData->m_singleInvInfo->m_skyid = g_globalArg->m_operator->m_opid;	//�տ�ԱID
	
	DBG_PRINT(("pSaleData->m_singleInvInfo->m_sky == %s", pSaleData->m_singleInvInfo->m_sky.c_str()));
	//	DBG_PRINT(("pSaleData->m_singleInvInfo->m_skyid == %u", pSaleData->m_singleInvInfo->m_skyid));
	
	pSaleData->m_saleMode = g_globalArg->m_saleMode;						//����ģʽ���ܼۡ���ʱ�ۣ�����	
	DBG_PRINT(("�˳�UpdateSaleValue����"));
	
	return SUCCESS;
}

