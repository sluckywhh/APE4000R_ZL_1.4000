// SelDefWin.h: interface for the CSelDefWin class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ___SELDEF_WIN
#define ___SELDEF_WIN


#include "CaWindow.h"
#include "CaInput.h"
#include "MultiInputCommonWin.h"
#include "CPrnInfo.h"

/**
 *@class CSelDefWin 
 *@brief ¼��Ʊ���ӡ�ġ��Զ��塱���ݵĽ���
 */
class CSelDefWin : public CMultiInputCommonWin 
{
private:
	CPrnInfo m_prnInfo;

public:
	CSelDefWin();

	~CSelDefWin();

	/*!
	@brief ��������	
	@param iX ���ϽǺ�����
	@param iY ���Ͻ�������
	@param iW ���
	@param iH �߶�
	@return 1 ���ɹ���������ʧ��
	*/
	int Create(int iX,int iY,int iW,int iH);

	/*!
	@brief �����¼�	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);

	/*!
	@brief ˢ�´�����ʾ	
	@return 1: SUCCESS
	*/
	virtual int ReFresh();
	
	/*!
	@brief Input�ؼ��İ�����Ӧ	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	void OnInput1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput2(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput3(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput4(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnInput5(int iEvent, unsigned char * pEventData, int iDataLen);

	/*!
	@brief button�ؼ��İ�����Ӧ	
	@param[in] iEvent �¼����
	@param[in] pEventData �¼�����
	@param[in] iDataLen �¼����ݳ���
	@return   1  �Ѵ��� 0 �޷�����
	*/
	void OnBtn1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnBtn2(int iEvent, unsigned char * pEventData, int iDataLen);
	
	static void S_OnActive(CaWindow *obj);
	void DoActive(); 

	/*!
	@brief ��ʾinput��Ӧ������	
	@return   
	*/
	void DispPrnInfo();

	UINT8 CheckInputValid(string &strErr);

	/*!
	@brief ���Input��ʾ������	
	@return   
	*/
	void ClearPrnInfoWin();
};

#endif

