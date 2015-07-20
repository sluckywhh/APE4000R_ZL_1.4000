#ifndef __CGLOBAL_ARG_H
#define __CGLOBAL_ARG_H

#include "IncludeMe.h"
#include "CMachine.h"
#include "COperator.h"
#include "CInvVol.h"
#include "CUserInfo.h"
#include "SysMacDef.h"
#include "TemplateDataDesign.h"
#include "TDateTime.h"
#include "CUserMore.h"
#include "CInvKind.h"
#include "CPrnInfo.h"

class CGlobalArg;

/*! ϵͳ���ò����������������Ӧ�ó�����һ�� */
extern CGlobalArg *g_globalArg;


/**
 *@class CGlobalArg 
 *@brief ����ȫ�ֱ�����ϵͳ����
 *@brief �����ڳ��������Ժ�ֻ�����һ��ȫ�ֶ���
 *@brief ����ĳ�Ա��������Ӧ�ó����õ�ȫ�ֱ�����ϵͳ������
 */
class CGlobalArg
{
public:

	/**
	 * brief ��ʼ����������ֵ
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitGlobalArg(void);
	/**
	 * brief �����걨���ڵ���Ʊ����Ʊ�ۼƽ���Ʊ������Ʊ�ۼƽ��
	 * @param void
	 * @return UINT8 
	 */
	UINT8 CalculateSum(void);

	/**
	 * brief ��ȡ��ӡģ��
	 * @param UINT8 *TemplateBuf ģ�建����
	 * @param UINT8 TemplateNo ģ���
	 * @param UINT32 len ģ�峤��
	 * @return static UINT8 
	 */
	static UINT8 ReadPrintTemplate(UINT8 *TemplateBuf, UINT8 TemplateNo, UINT32 len);

	/**
	 * brief ����Ƿ���Ҫ�����ս��׻���
	 * @param UINT32 date
	 * @return UINT8 
	 */
//	UINT8 CheckDaySum(UINT32 date);

	/**
	 * brief �ս��׻��ܺ���
	 * @param UINT32 uDate
	 * @return static UINT8 
	 */
//	static UINT8 DaySum(UINT32 uDate);

	/**
	 * brief �õ�CGlobalArg��Ψһ����
	 * @param void
	 * @return static CGlobalArg* 
	 */
	static CGlobalArg* GetInstance(void);

	/**
	 * brief ��ʼ������ϵͳֵ
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitSysArg(void);

	/**
	 * brief ��ʾ��Ϣ��
	 * @param[in] strInfo  ��ʾ����Ϣ��Ϣ
	 */
	void ShowMsg(string strInfo);

	/**
	 * brief ���ϵͳ��־��¼
	 * @param[in]  Eventtype �¼����ͺ�
	 * @param[in]  EventResult  �¼����
	 * @param[in]  Backup ��ע��Ϣ
	 * @return 1: SUCCESS, 0: FAILURE
	 */
	static UINT8 SysLog(UINT8 Eventtype, UINT32 EventResult, string Backup = "");

	/**
	 * brief ϵͳ��־����
	 * @return 1: SUCCESS, 0: FAILURE
	 */
	UINT8 SysLogRoll();
	
	/**
	 * brief �ж��Ƿ񳬹�����ʱ������
	 * @param[in]  pEndDate  ���߿�Ʊ��ֹ����
	 * @return 1: SUCCESS���ǣ�, 0: FAILURE����
	 */
	UINT8 IfExceedSvTime(TDateTime *pEndDate = NULL);

	/**
	 * brief �����ת��������
	 */
	INT32 OnLineTest(string &strErr);

	


	//-----------------------------------
	// ϵͳ������
	//-----------------------------------
	UINT8  m_initFlag;			/**< ��ʼ����־ */
	UINT32 m_forbidDaySum;		/**< �ս��׷�����־ */
	UINT32 m_initDate;			/**< ������ʼ������ */
	UINT32 m_updateDate;			/**< ����Ȩ������ */
//	UINT8  m_invFormat;			/**< ��Ʊ��ʽ */
	UINT8  m_invDeliverFlag;	/**< ������־ */
	UINT8  m_decFlag;			/**< �걨��־ */
//	UINT8  m_allDecFlag;		/**< ����걨��־ */
	UINT32 m_startDecDate;		/**< �걨��ʼ���� */
	UINT32 m_decDate;			/**< �걨��ֹ���� */
//	UINT8  m_taxID[TAX_ID_NUM];	/**< ˰��˰Ŀ������ */

	UINT8  m_decMedium;			/**< �걨���� */
	UINT8  m_bidirection;		/**< ˫���ӡ���� */
	UINT8  m_saleMode;			/**< Ĭ������ģʽ */
	UINT8  m_decAlarm;			/**< �걨�������� */
	UINT8  m_curTemplateNo;		/**< ��ǰ��ӡģ��� */

	
	UINT32  m_perReccount;    /**< ÿ������*/
	
	string m_defaultPayerName;	/**< Ĭ�ϸ��������� */
	UINT32 m_com1BaudRate;		/**< ����1������ */
	UINT32 m_com2BaudRate;		/**< ����2������ */
	UINT32 m_zhqcomBaudRate;		/**< ת�������ڲ����� */
	UINT8  m_printer;			/**< �����ӡ�� */
//	UINT32 m_dataTransMedium;	/**< ���ݴ������ */
	UINT8  m_itemNameLen;		/**< ��Ʒ������󳤶� */
	UINT8  m_payerCorpLen;		/**< ������/�տ���������󳤶� */
	UINT8  m_netOn;            /**< ��¼��֤�Ƿ�ɹ� 1���ɹ���0��ʧ�� */

	//-----------------------------------
	// �����޶������
	//-----------------------------------
	INT64  m_normalSum;			/**< �걨����Ʊ�ۼƽ�� */
	INT64  m_returnSum;			/**< �걨�ں�Ʊ�ۼƽ�� */
	INT64  m_normalVolSum;		/**< ��Ʊ����Ʊ�ۼƽ�� */
	INT64  m_returnVolSum;		/**< ��Ʊ���Ʊ�ۼƽ�� */
	
	//-----------------------------------
	// ����������
	//-----------------------------------
	UINT8		m_bootStatus;	/**< ����������״̬ */
	CMachine	*m_machine;		/**< ������Ϣ */
	COperator	*m_operator;	/**< ����Ա��Ϣ */
	CInvVol		*m_curInvVol;	/**< ��ǰ����Ϣ */
	CUserInfo	*m_corpInfo;	/**< ��˰����Ϣ */
	CUserMore   *m_usermore;    /**< ��˰��������Ϣ*/
	CInvKind    *m_invKind;     /**< Ʊ����Ϣ*/
	CPrnInfo    *m_prnInfo;     /**< ��ӡƱ����Ϣ*/
	UINT8        m_IngSegPoint;  /**< �������ĸ��Ŷβ�����0����Ʊ������1����Ʊ�˻�*/
	UINT8		m_sendInvFlag;	/**< �ϴ���Ʊ��־ */
	
	UINT8		m_declareLimitFlag;  /**< �걨���Ƿ񳬹�100�죬 1���ǣ�0���� */
	string      m_pydm;        /**< Ʊ������ */
	string      m_kindFlag;    /**< ͬһ��ƱԴ��ʾ ����Ʊ��������м�2λ */
	string      m_sjbsfs;      /**< ���ݱ��ͷ�ʽ */
	UINT8       m_allowIssue;  /**< �Ƿ��ж�Ӧ��ӡģ�忪ƱȨ�ޣ�1���ǣ�0����*/

	UINT8       m_threadIn;		/**< ���������̴߳��Ͳ��� 0��������1������*/
	string      m_strMsg;       /**< �м��������Ϣ*/
	UINT8       m_ifMsg;        /**< ���߳��Ƿ��д�����Ϣ,0=�ޣ�1=��*/
	UINT32      m_InvServNum;        /**< ��ǰ���淢Ʊ���� */
	INT64       m_InvServSum;		/**< ��ǰ���淢Ʊ��� */


	// ģ�巽��
	TSaveTemplateInfo *pSaveTemplateInfo;   /**< �豣���ģ������ */
	UINT8 *m_templateBuffer;	/**< ģ�建���� */
	
	// ������
//	INT8		*m_sq_wm;  /**< ������ָ�� */

	//��˰�̷���
//	CJSKInfoFunc *m_jskInfoFunc;

	//-----------------------------------
	// ����������
	//-----------------------------------
	INT32 m_invCount;			/**< INV_HEAD��ĵ�ǰ��¼���� */
	INT32 m_rtInvCount;			/**< RT_INV��ĵ�ǰ��¼���� */
	INT32 m_invSumCount;		/**< INV_SUM��ĵ�ǰ��¼���� */

	INT32 m_clientCount;		/**< CLIENT��ĵ�ǰ��¼���� */
	INT32 m_operatorCount;		/**< OPERATOR��ĵ�ǰ��¼���� */
	INT32 m_pluCount;			/**< PLU��ĵ�ǰ��¼���� */

	//-----------------------------------
	// ˰���豸������
	//-----------------------------------
	
	string  m_strZskl;          /**< ֤����� */
	string  m_strSksbkl;        /**< ˰���豸(��˰��)���� */


	UINT8  m_pthreadFlag;		/**< ���߳����б�־ 1������  0ֹͣ */
	string m_pthreadErr;		/**< ���̷߳��ش��� */
	string m_pthreadNsrsbh;
	string m_pthreadJqbh;
	string m_pthreadSksbbh;
	string m_pthreadSksbkl;
	string m_pthreadFplxdm;
	string m_pthreadKpjh;


private:
	/**
	 * CGlobalArg
	 * @return 
	 */
	CGlobalArg();

	/**
	 * ~CGlobalArg
	 * @return 
	 */
	~CGlobalArg();
	
	static CGlobalArg *m_globalArg;	/**< CGlobalArg���󣬾�̬ */
	
};



/*! ϵͳ���ò����������������Ӧ�ó�����һ�� */
extern CGlobalArg *g_globalArg;


#endif
