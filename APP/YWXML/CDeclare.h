#ifndef __CDECLARE_H
#define __CDECLARE_H

#include "IncludeMe.h"

//#include "CTable.h"
//#include "CDB.h"


/**
 *@class CDeclare
 *@brief ���ݳ�����Ϣ���ܱ�
 *@brief 
 */
class CDeclare
{
public:
    
	/*!
	@brief ���캯��	
	*/ 
	CDeclare();

    	/*!
	@brief ��������	
	*/
	~CDeclare();
		
public:
	string m_sq;			//����
	string m_fpmx;			//��Ʊ��ϸ����
	string m_fpdxx;			//��Ʊ����Ϣ
	string m_fphz;			//˰���豸��������
	string m_szfphz;		//��ȫоƬ��������
	string m_qtxx;			//������Ϣ
	
};

#endif
