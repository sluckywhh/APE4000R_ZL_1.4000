#ifndef CAIMEWIN_H
#define CAIMEWIN_H

#include "IncludeMe.h"
#include "g_def.h"
#include "CaInput.h"
#include "CaLabel.h"
#include "CaLableSelect.h"
#include "CaWindow.h"

extern "C"
{
#include "phrase.h"
#include "T9_pinyin.h"
};

#define IMEWIN_X 0
#define IMEWIN_Y (SCREEN_H - LINE_H*2 - 4)
#define IMEWIN_H (LINE_H*2 + 2)
#define IMEWIN_W (SCREEN_W - 1)

#define PINYIN_BUF_LEN	12
#define PINYIN_X		0
#define PINYIN_Y		16


#define PINYIN_CHN_BUF_LEN  31
#define PINYIN_PAGE_SIZE  6
#define WB_MAX_DIS_LEN 24

#define PINYIN_OUT_LEN  512
#define PINYIN_IN_LEN  32
#define MAX_PINYIN_LEN 6

#define T9ASC_DELAY_TIME	700

#define HW_REV_EVENT		0xee

#define	LENOVO_MAX_DIS_LEN	24
#define	T9_MAX_DIS_LEN		19

extern UINT8 g_nHWType;

/*! @brief �����������ַ����ձ�
*/
typedef struct				   
{
	unsigned char key;
	char *list;
}ASC_Key_List;
	

/*! @brief ���������뷨����
	���뷨���ֳ��ȹ̶�Ϊ2�����ֳ�
*/
class CaIMEWin :public CaWindow
{
public:
	/** 
     * @enum IME_TYPE
     * @brief ���뷨�����
     */
	typedef enum{//IME_DEFAULT=0, /**< ȱʡֵ		*/  
				IME_PIN_YIN=0,	/**< ƴ��		*/
				IME_LOWER_CASE,	/**< Сд��ĸ	*/
				IME_UPPER_CASE,	/**< ��д��ĸ	*/
				IME_BI_HUA,		/**< �ʻ�		*/	 
				IME_QU_WEI,		/**< ��λ		*/
				IME_HAND_WRITE, /**< ��д		*/
				//IME_WU_BI,		/**< ���		*/
				//IME_T9_PINYIN,	/**< ���ƴ��	*/
				//IME_T9_BIHUA,	/**< ��ʱʻ�	*/
				IME_DISABLE		/**< ���ܴ����뷨��ֻ����ȱʡ����*/
	}IME_TYPE; 
	static char *s_ImeNames[9];
	 
	static ASC_Key_List s_ascKeyList[9];

private:
	int m_IMEType;
	CaLabel *m_pIMELabel;
	CaInput *m_pPYDisInput;
	CaLabelSelect *m_T9Label;
	bool m_bIMEInputFocused;

	int m_iCurHZIndex;
	int m_iHZMaxLen;
	int m_iPinyinLen;
	unsigned char m_caPinyin_ChnBuf[PINYIN_CHN_BUF_LEN];//��ʾ�����ֵĺ�ѡ����
	wchar_t m_caPinyin_out[PINYIN_OUT_LEN];//�洢����ƴ��������ĺ���
	unsigned char m_caPinyin_in[PINYIN_IN_LEN];//��¼�����ƴ��
	unsigned char m_RandLenBuf[/*PHRASE_BUFFER_SIZE*/64];//���ڼ�¼������ÿ�еĵ�����
	int m_iLineIndex;//���ڼ�¼��ҳʱ��ҳ��������
	unsigned char m_chHwBuf[64];//������д�����ݻ���

	int m_iMaxWordsSize;//ÿҳ�����ֻ�ʵĸ���  ���

	int m_iQwLen;
	unsigned char m_caQwBuf[4];//��¼�������λ

	int m_caT9PYLen;							//��¼T9���������
	unsigned char m_caT9PYBuf[PINYIN_BUF_LEN];	//��¼t9��
	unsigned char PYBuf[12][PY_MAX_LENGTH];
	unsigned char PY_num;						//���ϵ�ǰ�����ƴ����
	int PY_CurPos;								//ѡ��ƴ��������λ��
	int m_T9state;	
	int m_T9LenovoState;	//T9����״̬��1-ѡ�����뺺�� 0-��������ƴ��

	int m_T9ASC_lastkey;		//��¼�ϴΰ�����ֵ
	int m_T9ASC_clickCount;		//��¼�������ٰ�������
	UINT64 m_T9ASC_lastTime;	//��¼�ϴΰ���ʱ��
	
	UINT8 T9BH_Pageup_Could;
	UINT8 T9BH_Pagedown_Could;
	UINT8 T9BH_state;		//T9�ʻ�״̬��1-ѡ���� 0-����ʻ�

	int m_handwrite_flag;		//��¼��д״̬��1���д�ѡ���֣�0����

	//ƴ�����뷨
	void BeginChn();
	int RecPinyin(int iEvent, unsigned char *pEventData, int iDataLen);

	//T9ƴ��
	int RecT9py(int iEvent, unsigned char *pEventData, int iDataLen);
	void BeginT9py();
	unsigned char InputT9PY(unsigned char *key, unsigned char enterNum, 
							unsigned char *outNum, unsigned char (*PYBuf)[PY_MAX_LENGTH]);
	
	//T9�ַ�
	void BeginT9ASC();
	int ProcDirectInput(int iEvent, unsigned char *pEventData, int iDataLen);

	//T9�ʻ�
	void BeginT9Bihua();
	int RecT9Bihua(int iEvent, unsigned char *pEventData, int iDataLen);

	//������뷨
	void BeginWB();
	int RecWB(int iEvent, unsigned char *pEventData, int iDataLen);
	
	//��λ���뷨
	void BeginQW();
	int RecQW(int iEvent, unsigned char *pEventData, int iDataLen);
	
	//��д����
	/*!
	@brief ������д���¼�����������д�壩	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	int RecHandWrite(int iEvent, unsigned char *pEventData, int iDataLen);
		
	/*!
	@brief ������д���¼���ʤ��ͨ������д�壩	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	int RecScreenHandWrite(int iEvent, unsigned char *pEventData, int iDataLen);
		
	//������������ (��Ϊƴ���Ľӿ�û�к�wbͳһ������ֻ�ܵ�������)
	bool m_bLenovoOn;//�Ƿ�����������
	int LenovoProc(int iEvent, unsigned char *pEventData, int iDataLen);

	//��ʾT9ƴ��ѡ����
	void DisT9py(void);
	void ClearT9py(void);

	
	void ChangeFocus(int iEvent, unsigned char *pEventData, int iDataLen);
	
public:
	CaInput *m_pIMEInput;
	bool m_bRecurSpecChar;//��ֹ�����ַ�win��ime�ĵݹ����
public:
	CaIMEWin();
	~CaIMEWin();
    virtual	int ReFresh();
    virtual int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	void Show();
// 	IME_TYPE ImeType(){return m_IMEType;}
//  void ImeType(IME_TYPE itype){m_IMEType=itype;}
	virtual bool IsCurWin();

	//�������뷨����ʱ����һЩ����
	void EndProcess();
	//�任���뷨
	void ChangeInputMethod();


};
#endif

