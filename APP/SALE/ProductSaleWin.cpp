/*! \file    ProductSaleWin.cpp
   \brief    awe4000r���۳�������Ʒ���۴���
   \author   Yu Yan
   \version  1.0
   \date     2007-11-28
 */


#include "ProductSaleWin.h"
//#include "VolSumInfoWin.h"
#include "printer.h"
#include "CaProgressBar.h"
#include "CClient.h"
#include "Scanner.h"
#include "beep.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

char title_arr[7][33];		//CProductSaleWin��Label�ı���


CProductSaleWin::CProductSaleWin():CaWindow()
{
	m_IfCancel = false;
	m_strSuffix = "";
}

int CProductSaleWin::Create(int iX,int iY,int iW,int iH)
{
	int curH;
	char title[OBJ_TITLE_MAX_LEN + 1];
//	string curtime = TDateTime::CurrentDateTime().FormatString(YYYYMMDDHHMMSS);
	string curtime = TDateTime::CurrentDate().FormatString(YYYYMMDD);
	curtime += "  ";
    int titleLen=0;
	
    m_iBtnW = (SCREEN_W/2 - 0 ) ;	//Label�Ŀ��
	m_iColW = m_iBtnW + 0;			//Label���п�
    
	m_pFrame->RegsiterWin(this,PRODUCT_SALE_WIN);
   
	CaWindow::Create(iX,iY,iW,iH); // creat a window
	//����һ����ǩ ��һ��
	label[0] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH = SCREEN_TOP_OFFSET;
	label[0]->Create(0,curH, SCREEN_W, CHAR_H);
	label[0]->SetTitle(title_arr[0], strlen(title_arr[0]));

	//����һ����ǩ �ڶ���
	label[1] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[1]->Create(0,curH, SCREEN_W, CHAR_H); //����������
	label[1]->SetTitle(title_arr[1], strlen(title_arr[1]));
    
	//����һ����ǩ ������
	label[2] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[2]->Create(0,curH, m_iBtnW, CHAR_H); //����������
	label[2]->SetTitle(title_arr[2], strlen(title_arr[2]));

	//����һ����ǩ ������
	label[3] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[3]->Create(m_iColW,curH, m_iBtnW, CHAR_H);
	label[3]->SetTitle(title_arr[3], strlen(title_arr[3]));

    //����һ����ǩ ������
	label[4] = new CaLabel(false,CaObject::ALIGN_LEFT);
	curH += LINE_H;
	label[4]->Create(0,curH, m_iBtnW, CHAR_H); //����������
	label[4]->SetTitle(title_arr[4], strlen(title_arr[4]));

	//����һ����ǩ ������
	label[5] = new CaLabel(false,CaObject::ALIGN_LEFT);
	label[5]->Create(m_iColW,curH, m_iBtnW, CHAR_H);
	label[5]->SetTitle(title_arr[5], strlen(title_arr[5]));
	
   	curH += LINE_H;
	strcpy(title, "[����]");
	titleLen = strlen(title) * CHAR_W;
	m_pInput2=new CaInput(CaObject::ON_LEFT,titleLen);
	m_pInput2->Create(0,curH,SCREEN_W,LINE_H);	
	m_pInput2->SetTitle(title,titleLen / CHAR_W);	
	m_pInput2->SetMaxLen(PAYER_NAME_LEN);

	this->End();
	return 0;
}

//---------------------------------------------------------------------------------
//�����¼�
//---------------------------------------------------------------------------------
int CProductSaleWin::ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen)
{
	UINT8 ret;
	double ii;
	char *content;
	string code = "";
	UINT32 deptNo;
	UINT8 IfInvSum = 0;
	INT32 dotNum = 0;
	INT32 nWin;
	INT32 nLen  = 0;
	UINT8 nIndex = 0;
	UINT32 nCurDate;
	string strErr("");

	switch(iEvent) 
	{
	case ENTER_KEY:
		m_strSuffix = "";

		nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);

		//�ж�װ��ֽ�ʷ�Ʊ	
		if (isPaper() != 0)
		{
			DBG_PRINT(("û��ֽ�ʷ�Ʊ"));
			return(ErrMsgBox(NO_PAPER));
		}
		content = (char*)(m_pInput2->m_contentBuf);
		ii = atof(content);
		m_pInput2->Clear();
		ret = CashShow(ii);
		if (ret != SUCCEED) 
		{
			return(ErrMsgBox(ret));
		}	
		ChangeTitle();
		ReFresh();
		
		if (m_IfCancel)		//֮ǰ������Ʒȡ����
		{
			pSaleData->NoCancelGoods();
			m_IfCancel = false;
			m_strSuffix = "";
		}
		DBG_PRINT(("*****����ģʽ******��%u", g_globalArg->pSaveTemplateInfo->workMode));
 		ret = pSaleData->PayByCash(IfInvSum);
		DBG_PRINT(("IfInvSum == %u", IfInvSum));
		if ((ret == NO_GOODS)||(ret == DB_FULL))
		{
			ErrMsgBox(ret);
			ChangeWin(PRODUCT_SALE_MAIN_MENU); //�������۵�������
			return SUCCESS;
		}

		if (ret != SUCCEED) 
		{
			ErrMsgBox(ret);
			switch(ret) 
			{
				case GET_FISCAL_CODE_ERROR://ȡ˰����ʧ��
					break;
				case UPDATE_INV_VOL_ERROR://д���ݿ�ʧ��
					break;
				case DB_SAVE_ERROR://д���ݿ�ʧ��
					break;
				case MALLOC_MEM_ERROR:
					break;
				case INV_SUM_ERROR:
					break;
				case MUST_RE_LOGIN:
					break;
				case HAVE_ROLLED:
					break;
				case NM_EXCEED_MIN:   //��Ʊ������,�˻ص�����������ʾ���ȴ��ٴν���
				case NO_PAPER: //ûֽ���˻ص�����������ʾ���ȴ��ٴν���
					DeptSaleShow();
					ChangeTitle();
					ReFresh();
					return FAILURE;
					break;
				case INV_LIB_ERR:
					break;
				case GX_SV_NUM_EXCEED:
					break;
				case GX_SV_TIME_EXCEED:
					break;
				case GX_SV_SUM_EXCEED: 
					break;
				default:
					return FAILURE;//������Ʒ���۽���
			}
		}
		else
		{
			DBG_PRINT(("������Ǯ��"));
			MoneyBox_Open();
		}

		if (pSaleData->m_returnOther == 1)
		{
			pSaleData->m_returnOther = 0;
//			ScannerRelease();//ֹͣɨ��ǹɨ��
//			g_winNo = 3;//��ӦINV_MANAGE_MENU����
			nWin = INV_MANAGE_MENU;
		}
		else
		{
//			g_winNo = 2;//��ӦINV_MANAGE_MENU����
			nWin = PRODUCT_SALE_MAIN_MENU;
		}
// 		if (1==IfInvSum) 
// 		{
// 			InvSumShowPrn();//��ʾ����ܲ���ӡ
// 		}
// 		else
// 		{
			ChangeWin(nWin); //�������۵�������
//		}

		return SUCCESS;
		break;

    case DISCOUNT_KEY:

		if ((pSaleData->m_tmpGoodsNum>=(MAX_GOODS_LINE-1))&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
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
// 		CaMsgBox::ShowMsg("�ݲ�֧�ִ˹���");
// 		return SUCCESS;
		break;

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

	case HELP_KEY:
		return(RemarksInputProc());
		break;

	case CANCEL_GOODS:
		
		if (m_IfCancel)//֮ǰ������Ʒȡ����
		{
			pSaleData->NoCancelGoods();
			m_IfCancel = false;
			m_strSuffix = "";
			DeptSaleShow();
		}
		else
		{
			if (pSaleData->m_tmpGoodsNum==0)//����Ʒ��ȡ��
			{
				ErrMsgBox(NO_GOODS_CANCEL);	
				ChangeWin(PRODUCT_SALE_MAIN_MENU);
				return SUCCESS;
			}
			pSaleData->CancelGoods();
			m_IfCancel = true;
			m_strSuffix = "<��>";
			CancelGoodsShow();
		}		
		ChangeTitle();
	    ReFresh();
		return SUCCESS;
		break;

	case PLUS_KEY:
		return(PlusProc());
		break;

	case TOTAL_CANCEL:
		if (m_IfCancel)//֮ǰ������Ʒȡ����
		{
			pSaleData->NoCancelGoods();
			m_IfCancel = false;
			m_strSuffix = "";
		}
		return(TotalCancelProc());
		break;

	case PLU_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		code = "";
        nLen = GOODS_CODE_LEN - strlen(content);
		if (nLen > 0)//����13λ����ǰ���㵽13λ
		{
			while(nLen > 0)
			{
				code += "0";
				nLen--;
			}
		}		
		code += content;
		ret = pSaleData->DeptSale(0, code);
		m_pInput2->Clear();
		if (m_IfCancel&&(ret == NO_SUCH_GOODS))//����Ʒȡ������,δ�ڷ�Ʊ��ϸ���ҵ�����Ʒ
		{
			ErrMsgBox(ret);
			pSaleData->NoCancelGoods();
			m_IfCancel = false;
			m_strSuffix = "";
			DeptSaleShow();
			ChangeTitle();
			ReFresh();
			return SUCCESS;
		}
		if (ret != SUCCEED) 
	   {
			m_strSuffix = "";
		   return(ErrMsgBox(ret));
	   }
	   //���ʵ�����ݵ����ĺ��� 
	   DeptSaleShow();
	   ChangeTitle();
	   ReFresh();	
	   //�л�����Ʒ���۽���
	   ChangeWin(PRODUCT_SALE_WIN);
	   return SUCCESS;
		break;
	
	case SHIFT_PLU_KEY: //��ʱ������Ʒ����
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		ret = pSaleData->PLUSale(content, strErr);			
		if (m_IfCancel&&(ret == NO_SUCH_GOODS))//����Ʒȡ������,δ�ڷ�Ʊ��ϸ���ҵ�����Ʒ
		{
			ErrMsgBox(ret);
			pSaleData->NoCancelGoods();
			m_IfCancel = false;
			m_strSuffix = "";
			DeptSaleShow();
			ChangeTitle();
			ReFresh();
			return SUCCESS;
		}
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
	   ChangeTitle();
	   ReFresh();	
	   //�л�����Ʒ���۽���
	   ChangeWin(PRODUCT_SALE_WIN);
	   return SUCCESS;
		break;
	
// 	case SCANNER_EVENT_KEY:
// 		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
// 		{
// 			CaMsgBox::ShowMsg("��Ʒ��������");
// 			ClearScannerBuf();
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
// 		m_pInput2->Clear();
// 		if (m_IfCancel&&(ret == NO_SUCH_GOODS))//����Ʒȡ������,δ�ڷ�Ʊ��ϸ���ҵ�����Ʒ
// 		{
// 			ErrMsgBox(ret);
// 			ClearScannerBuf();
// 			pSaleData->NoCancelGoods();
// 			m_IfCancel = false;
// 			m_strSuffix = "";
// 			DeptSaleShow();
// 			ChangeTitle();
// 			ReFresh();
// 			return SUCCESS;
// 		}
// 		if (ret != SUCCEED) 
// 	   {
// 			ErrMsgBox(ret);
// 			ClearScannerBuf();
// 			return FAILURE;
// 	   }
// 	   //���ʵ�����ݵ����ĺ��� 
// 	   DeptSaleShow();
// 	   ChangeTitle();
// 	   ReFresh();	
// 	   //�л�����Ʒ���۽���
// 	   ChangeWin(PRODUCT_SALE_WIN);
// 	   return SUCCESS;
// 		break;

	case CHANGE_DEPT_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		content = (char*)(m_pInput2->m_contentBuf);
		deptNo = atoi(content);
		m_pInput2->Clear();
		return(DeptSaleProc(deptNo));
		break;	

	case DEPT1_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		if (QuickSaleProc()!=SUCCESS)
		{
			return FAILURE;
		}
		return(DeptSaleProc(1));
	    break;

	case DEPT2_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
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
	   
	case DEPT3_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
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
	   
	case DEPT4_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
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

	case DEPT5_KEY:
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
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
		
	case RETURN_MAIN_MENU:  //return to SYSTEMMENU
		if (pSaleData->m_tmpGoodsNum==0)
		{
			ChangeWin(PRODUCT_SALE_MAIN_MENU);
		}
		else
		{
			CaMsgBox::ShowMsg("��Ʒ�������㣬���ܷ���");
		}
		return SUCCESS;
		break;

	case GOODSREDUCT_KEY:
/*
		if ((pSaleData->m_tmpGoodsNum>=MAX_GOODS_LINE)&&(!m_IfCancel)) 
		{
			CaMsgBox::ShowMsg("��Ʒ��������");
			return FAILURE;
		}
		GoodesReductProc();*/
		CaMsgBox::ShowMsg("�ݲ�֧�ִ˹���");
		return SUCCESS;
		break;
		
	default:
		break;
	}
	
	return CaWindow::ProcEvent(iEvent,pEventData,iDataLen);
}

//bool CProductSaleWin::IsCurWin()
//{
//	return true;
//}

int CProductSaleWin::ReFresh()
{
	ReFreshTitle();
	CaGroup::ReFresh();
	if(m_pCurObj != NULL )
	{
 		m_pCurObj->SetFocusIn();
	}
	LCDRedraw();

	return 1;
}

int CProductSaleWin::ChangeTitle()
{
	label[0]->SetTitle(title_arr[0], strlen(title_arr[0]));
	label[1]->SetTitle(title_arr[1], strlen(title_arr[1]));
	label[2]->SetTitle(title_arr[2], strlen(title_arr[2]));
	label[3]->SetTitle(title_arr[3], strlen(title_arr[3]));
	label[4]->SetTitle(title_arr[4], strlen(title_arr[4]));
	label[5]->SetTitle(title_arr[5], strlen(title_arr[5]));

	return 1;
}

int CProductSaleWin::ErrMsgBox(UINT8 ret)
{
	string pText;
	switch(ret)
	   {
	   case MONEY_NOT_ENOUGH:
		    pText = "�ֽ����";
			break;
	   case MONEY_EXCEED:
		    pText = "�ֽ����";
			break;
	   case NO_PAPER:
		    pText = "û��ֽ�ʷ�Ʊ";
			break;
	   case PRN_INV_ERROR:
		   pText = "��Ʊʧ��";
			break;
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
	   case UPDATE_INV_VOL_ERROR:
		    pText = "���·�Ʊ������Ϣ��ʧ��";
			break;
	   case GET_FISCAL_CODE_ERROR:
		    //pText = "ȡ˰����ʧ��";
		    pText = "���ɷ�α��ʧ��";
			break;
	   case DB_SAVE_ERROR:
		    pText = "�����ݿ�ʧ��";
			break;
	   case MALLOC_MEM_ERROR:
		    pText = "���붯̬�ڴ�ʧ��";
			break;
	   case INV_SUM_ERROR:
			pText = "�����ʧ��";
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
			pText = "�������ܼ۽��";
			break;
		case EXCEED_AMOUNT:
			pText = "��������";
			break;
		case NO_GOODS:
			pText = "û����Ʒ";
			break;
		case MUST_RE_LOGIN:
			pText = "��Ʊ�������꣬\n�����ص�¼";
			break;
		case NO_GOODS_CANCEL:
			pText = "����Ʒ��ȡ��";
			break;
		case ILLEGAL_AMOUNT:
			pText = "�����Ƿ�";
			break;
		case RETURN_GOODS_EXCEED:
			pText = "�˻����跢Ʊ��������1";
			break;
		case DB_FULL:
			pText = "�洢�ռ��������޷���Ʊ �뾡���걨";
			break;
		case HAVE_ROLLED:
			pText = "��Ϣ����ɹ�";
			break;
		case REDUCT_EXCEED:
			pText = "���ý�����Ʒ�н��";
			break;
		case NO_REDUCT:
			pText = "����ͨ��Ʒ�У���������";
			break;
		case MONEY_ZERO:
			pText = "��Ʒ���Ϊ0�����ÿ���";
			break;
		case INV_ZERO:
			pText = "�޿��÷�Ʊ��";
			break;
		case DISCOUNT_MONEY_ZERO:
			pText = "�ۿ��н��Ϊ��";
			break;
		case REDUCT_MONEY_SMALL:
			pText = "���ý���С";
			break;
		case ONE_INV:
			pText = "����һ�ŷ�Ʊ�������Ʒ����";
			break;
		case NO_NET:
			pText = "û����������";
			break;
 		case INV_LIB_ERR:
 	//		pText = "��Ʊ�ϴ�ʧ��";
			pText = g_globalArg->m_strMsg;
			g_globalArg->m_strMsg = "";
 			break; 
		case GX_SV_NUM_EXCEED:
			pText = "���߿�Ʊ��������";
			break;
		case GX_SV_SUM_EXCEED:
			pText = "���߿�Ʊ����";
			break;
		case GX_SV_TIME_EXCEED:
			pText = "���߿�Ʊʱ�䳬��";
			break;
		case NM_EXCEED_MIN:
			pText =  "�ܽ�������С��Ʊ���";
			break;
	   default:;
	   }
	   
		CaMsgBox::ShowMsg(pText);
	
		return FAILURE;
}

//--------------------------------------------------------------
//��Label��ʾ�����ӡ����
//--------------------------------------------------------------
UINT8 CProductSaleWin::CashShow(double cash)
{
	DBG_PRINT(("ENTER --CashShow-- FUNCTION!!!"));
	
	string strTemp = "";
	UINT8 ret;
    double payback = 0.0;
	INT32 nCurrentInvNo = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
	double moneySum = ((double)(pSaleData->m_singleInvInfo->m_kphjje))/SUM_EXTENSION;

	DBG_PRINT(("nCurrentInvNo == %d", nCurrentInvNo));
	DBG_PRINT(("cash == %f", cash));

	//���������ֽ�ֵ
	if( (cash<-MINIMUM_PRECISION) || (cash>MINIMUM_PRECISION) )
	{
		if (cash<moneySum)
		{
			ret = MONEY_NOT_ENOUGH;	
			return ret;
		}
		if(cash > MAX_MONEY)
		{
			ret = MONEY_EXCEED;
			return ret;
		}	
		payback = cash - moneySum; //�һ��ֽ�
	}
	//��δ�����ֽ�ֵ
	else
	{
		cash = moneySum;
	}
	
	DBG_PRINT(("�ϼ� == %f", moneySum));
	
	DBG_PRINT(("g_globalArg->m_curInvVol->m_curInvNo= %u",g_globalArg->m_curInvVol->m_curInvNo));
    sprintf(title_arr[0], "��ǰ��Ʊ��: %08d", g_globalArg->m_curInvVol->m_curInvNo);

	if ((pSaleData->m_invtype==RETURN_INV)||(pSaleData->m_invtype==RET_MANUAL_INV)||(pSaleData->m_invtype==RET_SPECIAL_INV)) 
	{
		sprintf(title_arr[1], "�ϼ�:-%.2lf", moneySum);
		sprintf(title_arr[2], "ʵ��:");
		sprintf(title_arr[3], "�һ�:", payback);	
	}
	else
	{
		sprintf(title_arr[1], "�ϼ�:%.2lf", moneySum);
		sprintf(title_arr[2], "ʵ��:%.2lf", cash);
		sprintf(title_arr[3], "�һ�:%.2lf", payback);

	}

#if 0
	   DBG_PRINT(("g_globalArg->m_invKind->m_nNum = %u",g_globalArg->m_invKind->m_nNum));
		if(0 == g_globalArg->m_invKind->m_nNum)
		{
         	strcpy(title_arr[4], "��Ʊ��Ϣ�ϴ���");
		}
		else
		{
          	strcpy(title_arr[4], "��Ʊ��Ϣ��ӡ��");
		}
#endif

	//strcpy(title_arr[4], "��Ʊ��Ϣ��ӡ��");
	strcpy(title_arr[5], "......");
    
	ret = SUCCEED;
	return ret;
}

UINT8 CProductSaleWin::DeptSaleShow()
{
	string strTemp = "";
	INT32 nCurrentInvNo = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
	INT8 tmp[16];

    DBG_PRINT(("g_globalArg->m_curInvVol->m_curInvNo= %u",g_globalArg->m_curInvVol->m_curInvNo));
    sprintf(title_arr[0], "��ǰ��Ʊ��: %08d", g_globalArg->m_curInvVol->m_curInvNo);
	
	//���ۿ�
	if( (DETAIL_GOODS_DISCOUNT == pSaleData->m_invDet->m_property) && (0 == m_strSuffix.length()) ) 
	{
		m_strSuffix = "<��>";
	}
	strTemp = "��Ʒ: ";
    strTemp.append(pSaleData->m_invDet->m_spmc);
	strTemp.append(m_strSuffix);
    m_strSuffix = "";
    strcpy(title_arr[1], (strTemp.c_str()));

	sprintf(title_arr[2], "����:%.2lf", pSaleData->m_invDet->m_spdj);
	sprintf(tmp, "����:%%.%luf", pSaleData->m_invDet->m_dotNum); //�����������
	sprintf(title_arr[3], tmp, pSaleData->m_invDet->m_spsl);
	if (((pSaleData->m_invtype==RETURN_INV)||(pSaleData->m_invtype==RET_MANUAL_INV)||(pSaleData->m_invtype==RET_SPECIAL_INV))
		&&(0!=pSaleData->m_singleInvInfo->m_kphjje)) 
	{
		sprintf(title_arr[4], "�ϼ�:-%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	else
	{
		sprintf(title_arr[4], "�ϼ�:%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	
	sprintf(title_arr[5], "��Ʒ����:%u", pSaleData->m_tmpGoodsNum);
	
	if (m_IfCancel)
	{	
		m_IfCancel = false;
	}

	return SUCCESS;	
}

UINT8 CProductSaleWin::ClientShow()
{
	string strTemp = "������: ";
	
    strTemp.append(pSaleData->m_singleInvInfo->m_fkdw); 
	strncpy(title_arr[1], (strTemp.c_str()), OBJ_TITLE_MAX_LEN);//�����˽ϳ���ֻ����ʾ����
	sprintf(title_arr[2], "");
	sprintf(title_arr[3], "");	
	
	return SUCCESS;	
}

UINT8 CProductSaleWin::ClientCodeShow()
{
	string strTemp = "������˰��: ";
	
    strTemp.append(pSaleData->m_singleInvInfo->m_fkdwsh); 
	strncpy(title_arr[1], (strTemp.c_str()), OBJ_TITLE_MAX_LEN);//�����˽ϳ���ֻ����ʾ����
	sprintf(title_arr[2], "");
	sprintf(title_arr[3], "");	
	
	return SUCCESS;	
}

UINT8 CProductSaleWin::CancelGoodsShow()
{
	string strTemp = "";
	INT32 nCurrentInvNo = g_globalArg->m_curInvVol->m_ieno + 1 - g_globalArg->m_curInvVol->m_remain;
	
    DBG_PRINT(("g_globalArg->m_curInvVol->m_curInvNo= %u",g_globalArg->m_curInvVol->m_curInvNo));
    sprintf(title_arr[0], "��ǰ��Ʊ��: %08d <��Ʒȡ��>", g_globalArg->m_curInvVol->m_curInvNo);
	sprintf(title_arr[1], "");
	sprintf(title_arr[2], "");
	sprintf(title_arr[3], "");
	sprintf(title_arr[5], "��Ʒ����:%u", pSaleData->m_tmpGoodsNum);
	
	if ((pSaleData->m_invtype==RETURN_INV)||(pSaleData->m_invtype==RET_MANUAL_INV)||(pSaleData->m_invtype==RET_SPECIAL_INV)) 
	{
		sprintf(title_arr[4], "�ϼ�:-%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	else
	{
		sprintf(title_arr[4], "�ϼ�:%.2lf", (pSaleData->m_singleInvInfo->m_kphjje)/100.0);
	}
	return SUCCESS;	
}

UINT8 CProductSaleWin::TotalCancelProc()
{
	UINT8 ret;
	CaMsgBox msgBox("�Ƿ�����ȡ��?",CaMsgBox::MB_YESNO);
	msgBox.ShowBox();
	if ((msgBox.m_iStatus == NO_PRESSED)||(msgBox.m_iStatus == CANCEL_PRESSED))
	{
		return SUCCESS;
	}
	
	if(msgBox.m_iStatus == OK_PRESSED)
	{
		this->ReFresh();
		ret = pSaleData->TotalCancel();
		if (ret != SUCCESS) 
		{
		   return(ErrMsgBox(ret));
		}
		m_strSuffix = "";
		m_pInput2->Clear();
		ChangeWin(PRODUCT_SALE_MAIN_MENU); //�������۵�������
	}
	return SUCCESS;
}

UINT8 CProductSaleWin::DeptSaleProc(UINT32 deptNo)
{
	UINT8 ret;
	DBG_PRINT(("����CProductSaleWin::DeptSaleProc����"));
	DBG_PRINT(("deptNo == %u", deptNo));
	ret = pSaleData->DeptSale(deptNo, "");
	
	if (m_IfCancel&&(ret == NO_SUCH_GOODS))//����Ʒȡ������,δ�ڷ�Ʊ��ϸ���ҵ�����Ʒ
	{
		ErrMsgBox(ret);
		pSaleData->NoCancelGoods();
		m_IfCancel = false;
		m_strSuffix = "";
		DeptSaleShow();
		ChangeTitle();
		ReFresh();
		return SUCCESS;
	}
	if (ret != SUCCEED) 
	{
		m_strSuffix = "";
	   return(ErrMsgBox(ret));
	}
	//���ʵ�����ݵ����ĺ��� 
	DeptSaleShow();
	ChangeTitle();
	ReFresh();
	//�л�����Ʒ���۽���
	ChangeWin(PRODUCT_SALE_WIN);
	DBG_PRINT(("�˳�CProductSaleWin::DeptSaleProc����"));
	return SUCCESS;
}

UINT8 CProductSaleWin::InvSumShowPrn(void)
{	

// 	g_codeNo = g_globalArg->m_curInvVol->m_code;//��Ʊ�������
// 	g_invNo = g_globalArg->m_curInvVol->m_isno;//��Ʊ���� 
// 	ChangeWin(VOL_SUM_INFO_WIN);//ʱ��λ��ܽ���

	return SUCCESS;
}

UINT8 CProductSaleWin::ClientInputProc(void)
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
		ret = pSaleData->ClientNameInput(client.m_khmc.c_str(),client.m_khsh.c_str());		
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
	strcpy(title_arr[1], blank);
	strcpy(title_arr[2], blank);
	strcpy(title_arr[3], blank);
	ChangeTitle();
	return SUCCESS;
}

UINT8 CProductSaleWin::ClientCodeInputProc(void)
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
	strcpy(title_arr[1], blank);
	strcpy(title_arr[2], blank);
	strcpy(title_arr[3], blank);
	ChangeTitle();
	return SUCCESS;
}

UINT8 CProductSaleWin::RemarksInputProc(void)
{
	char *content;
	UINT8 ret;
	char *blank = "";
	INT8 chValue[128];
	memset((void*)chValue, 0, sizeof(chValue));
	string srrErr("");

	content = (char*)(m_pInput2->m_contentBuf);
//	if ('.' == *content) 
//	{
//		CClient client;
//		sprintf(chValue, "where ID = '%s'", (content+1));
//		client.m_filter = chValue;
//		client.Requery();
//		if(client.LoadOneRecord()!= SQLITE_OK)
//		{
//			CaMsgBox::ShowMsg("û�ж�Ӧ�ĸ�����");
//			return FAILURE;
//		}
//		ret = pSaleData->ClientNameInput(client.m_khmc.c_str());		
//	}
//	else
//	{
		ret = pSaleData->RemarksInput(content,srrErr);
//	}
	
	if (ret != SUCCESS) 
	{
		CaMsgBox::ShowMsg(srrErr);
		return FAILURE;
	}
	m_pInput2->Clear();
//	ClientShow();
//	ChangeTitle();
	ReFresh();
	return SUCCESS;
}

UINT8 CProductSaleWin::GoodesReductProc(void)
{
	char *content;
	double reductMoney;
	UINT8 ret;

	if(m_pInput2->IsEmpty())
	{
		CaMsgBox::ShowMsg("δ�������ý��");
		return FAILURE;
	}
	content = (char*)(m_pInput2->m_contentBuf);
	reductMoney = atof(content);
	m_pInput2->Clear();
	ret = pSaleData->GoodsReduct(reductMoney);
	if (ret != SUCCESS) 
	{
	   return(ErrMsgBox(ret));
	}
	DeptSaleShow();
	ChangeTitle();
	ReFresh();
	return SUCCESS;	
}

UINT8 CProductSaleWin::PriceInputProc(void)
{	
	UINT8 ret;
	double ii;
	char *content;
	INT32 dotNum = 0;//С��λ��
	
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
	return SUCCESS;
}

UINT8 CProductSaleWin::SumInputProc(void)
{
	UINT8 ret;
	double ii;
	char *content;
	INT32 dotNum = 0;//С��λ��
	
	content = (char*)(m_pInput2->m_contentBuf);
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
	return SUCCESS;
}

UINT8 CProductSaleWin::PlusProc(void)
{
	UINT8 ret;
	double ii;
	char *content;
	INT32 dotNum = 0;//С��λ��
	
	content = (char*)(m_pInput2->m_contentBuf);
	ii = atof(content);
    DBG_PRINT(("ii= %lf",ii));

// 	if(ii > MAX_MONEY)
// 	{
// 		CaMsgBox::ShowMsg("��������");
// 		return FAILURE;
// 	}	
	m_pInput2->Clear();
	ret = pSaleData->Plus(ii);
	if (ret != SUCCESS) 
	{
	   return(ErrMsgBox(ret));
	}
	ReFresh();
	return SUCCESS;
}

UINT8 CProductSaleWin::QuickSaleProc(void)
{
	UINT8 ret;

	if(m_pInput2->IsEmpty())
	{
		return SUCCESS;
	}

	switch(g_globalArg->m_saleMode) 
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
	return ret;	
}