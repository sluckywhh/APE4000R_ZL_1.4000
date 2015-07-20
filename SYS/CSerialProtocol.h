/*! \file    CSerialProtocol.h
   \brief    ˰�ؿ�����괮��ͨѶЭ���ඨ��
   \author   zl
 */

#ifndef __SERIALPORT_COMMUNICATION_H
#define __SERIALPORT_COMMUNICATION_H

#include "SYSModuleHeader.h"
#include "comdatatype.h"
#include "SerialPort.h"

#if (USE_SERIAL_PROTOCOL!=0)


#define SERIAL_MAX_BUFFER	255	
#define CMD_MAX_NO			30
#define SERIAL_OVERTIME_MAX	1000000UL
#define SERIAL_NODATA_MAX	50000UL
#define SERIAL_ERRNUM_MAX	0x40


#define REVPACK_HEAD_LENGTH	5
#define RSPPACK_HEAD_LENGTH	4

enum ByteOrder
{
    WEB_BYTEORDER		= 0x00,
	PC_BYTEODER			= 0x01
};

//error code define
#define	SERCMD_SUCCESS				0x0				//���������ȷ
#define	SERCMD_NO_DATA				0xF0			//��ʱΪδ�յ�����
#define	SERCMD_NOT_LASTPACK			0xF1			//���յİ����ǽ�����
#define SERCMD_CRC_ERR				0x1f			//����CRC��
#define	SERCMD_CMDNO_ERR			0x20			//������޷�ʶ��
#define SERCMD_PACKLEN_ERR			0x22			//����ȴ���
#define SERCMD_OVERTIME_ERR			0x30			//������ܳ�ʱ


#define FISCAL_CARD_RESET_ERR		0x01   		/* ˰�ؿ��ϵ���󣨸�λ�� 		*/
#define USER_CARD_RESET_ERR			0x02		/* �û����ϵ���󣨸�λ��			*/
#define MANAGE_CARD_RESET_ERR		0x03		/* ���鿨�ϵ���󣨸�λ��			*/
#define USER_CARD_NONE_ERR			0x04		/* ���û���							*/
#define FISCAL_CARD_NONE_ERR		0x05		/* ��˰�ؿ�							*/
#define MANAGE_CARD_NONE_ERR		0x06		/* �޻��鿨							*/

#define FISCAL_CARD_READ_ERR		0x07		/* ��˰�ؿ���						*/
#define USER_CARD_READ_ERR  		0x08		/* ���û�����  						*/
#define MANAGE_CARD_READ_ERR		0x09		/* ��������						*/
#define FISCAL_CARD_WRITE_ERR		0x0A		/* д˰�ؿ���						*/
#define USER_CARD_WRITE_ERR  		0x0B		/* д�û�����  						*/
#define MANAGE_CARD_WRITE_ERR		0x0C		/* д���鿨��						*/
#define FISCAL_CARD_ILLEGAL_ERR		0x0d		/* �Ƿ�˰�ؿ�						*/	
#define USER_CARD_ILLEGAL_ERR		0x0e		/* �Ƿ��û���						*/
#define MANAGE_CARD_ILLEGAL_ERR		0x0f		/* �Ƿ����鿨						*/

#define	SYSTEM_NO_INIT				0x10		/* û��ʼ��							*/
#define  FISCALCARD_CODE_NOT_MATCH_MACHINE_CODE     0x15    //˰�ؿ���ע�����˰������ע��Ų�һ��
#define  UNVAILD_TAX_ITEM                           0x19    //�Ƿ�˰��˰Ŀ
#define  DECLARE_DATE_BIGGER_THAN_CURRENT_DATE      0x1A    //�걨�������ڴ��ڵ�ǰ����
#define  DECLARE_DATE_LITTLE_THAN_LAST_DATE         0x1B    //�걨��������С���ϴ��걨����
#define  SYS_INITIALIZED                            0x1E    //˰�����ѳ�ʼ�������ٴγ�ʼ��
#define  TAX_MEM_ERR                                0x25    //˰�ش洢���쳣
#define  FISCAL_CARD_INITIALIZED                    0x27    //˰�ؿ���ע��

#define	NO_PRINT_TEMPLATE_ERR				0x40		/* �޴�ӡģ�� */
#define ERR_CONNECT_PACK					0x41		/* ���ְ����� */


/*!
@struct rev_cmdStruct
@brief ����������սṹ��
*/
typedef struct
{
	UINT8 Len;
	UINT8 PackNo;
	UINT8 Para[SERIAL_MAX_BUFFER*2];
}rev_cmdStruct;


/*!
@struct rsp_cmdStruct
@brief ��������Ӧ��ṹ�塣��rev_cmdStruct��ͬ
@see rev_cmdStruct
*/
typedef rev_cmdStruct rsp_cmdStruct;


/*!
@struct _Ser_ErrMsg
@brief ������Ϣ�ṹ��
*/
typedef struct _Ser_ErrMsg
{
	INT32 errNo;
	string errMsg;
	
	_Ser_ErrMsg(INT32 No, const char *msg){
		errNo = No;
		errMsg = msg;
	};
}Ser_ErrMsg;


/*!
@class CSerialProtocol
@brief ���괮��ͨѶЭ����
*/
class CSerialProtocol
{														 
public:
	rev_cmdStruct m_cRevCmd;			/**< ��������ṹ	*/
	rev_cmdStruct *m_revCmd;			/**< ��������ṹָ��	*/
	rsp_cmdStruct m_cRspCmd;			/**< Ӧ������ṹ	*/
	rsp_cmdStruct *m_rspCmd;			/**< Ӧ������ṹָ��	*/

private:
	UINT8 m_revBuf[SERIAL_MAX_BUFFER];		/**< ���ջ���	*/
	UINT8 m_rspBuf[SERIAL_MAX_BUFFER];		/**< Ӧ�𻺴�	*/

	INT16 m_CmdNO;					/**< �����������	*/
	
	UINT8 m_RegCmdSum;				/**< ��ǰ�ܹ�ע���������	*/

	typedef void (*ONCMD_FUN)(void *obj, CSerialProtocol *serComm);		/**< �������ָ�룬���ڻص�	*/

	/*!
	@struct _cmdReg[]
	@brief �������飬���ڴ����ע���������Ϣ
	*/
	struct _cmdReg{
		void *obj;
		INT16 CmdNO;
		ONCMD_FUN OnCmdFUN;
	}m_cmdReg[CMD_MAX_NO];			

	SerialPort *m_Serial, m_cSerial;	/**< ���ڲ������	*/

	static Ser_ErrMsg m_errMsg[];		/**< ������Ϣ	*/

	UINT8 m_fill_count;				/**< ��ǰ����д�Ĳ����ֽ���	*/
	UINT8 m_get_count;				/**< ��ǰ��ȡ�õĲ����ֽ���	*/

public:
	/*!
	@brief ע��һ����������	
	@param[in] obj   ������ָ��
	@param[in] CmdNO   �������
	@param[in] cmdFUN   ������Ӧ����
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	INT8 Add_CMD(void *obj, INT16 CmdNO, ONCMD_FUN cmdFUN);

	/*!
	@brief �ȴ�����һ�����ݰ�
	@return  SERCMD_SUCCESS��������ɣ�SERCMD_NOT_LASTPACK��������ɣ����������һ����
			 ����������ʧ��
	*/
	INT8 Wait_Cmd_Pack();

	/*!
	@brief �ȴ�����һ��NP��
	@return  SERCMD_SUCCESS��������ɣ�
			 ����������ʧ��
	*/
	INT8 Wait_NP_Pack();

	/*!
	@brief Ӧ��һ���޲�����OK��
	*/
	void Rsp_OK();

	/*!
	@brief Ӧ��һ��ERR��
	@param[in] err   ������
	*/
	void Rsp_ERR(UINT8 err);

	/*!
	@brief Ӧ��һ��WT��
	*/
	void Rsp_WT();

	/*!
	@brief Ӧ��һ��NP��
	*/
	void Rsp_NP();

	/*!
	@brief Ӧ��һ����������OK��
	@param[in] packNo   �����
	@param[in] packLen  ������
	*/
	void Rsp_OK(UINT8 packNo, UINT8 packLen);

	/*!
	@brief Ӧ��һ���򻯵�ER��
	*/
	void Rsp_ER();
	

	/*!
	@brief ��Ӧ���������һ�����ֽڲ���
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	INT8 FillParament(UINT8 byte);

	/*!
	@brief ��Ӧ���������һ�����β���
	@param[in] x   ����ֵ
	@param[in] len  ���ȣ���λ�ֽ�
	@param[in] order   �ֽ���
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	INT8 FillParament(INT64 x, UINT8 len, bool order);

	/*!
	@brief ��Ӧ���������һ���ֽ�������
	@param[in] buf   �ֽ���
	@param[in] len  ���ȣ���λ�ֽ�
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	INT8 FillParament(UINT8 *buf, UINT8 len);

	/*!
	@brief ��Ӧ���������һ��string���͵��ֽ�������
	@param[in] str   �ֽ���
	@param[in] len  ���ȣ���λ�ֽ�
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	INT8 FillParament(string str, UINT8 len);

	/*!
	@brief �ӽ��հ��л��һ�����ֽڲ���
	@return  ����ֵ
	*/
	UINT8 GetParament_BYTE();

	/*!
	@brief �ӽ��հ��л��һ�����β���
	@param[in] len  ���ȣ���λ�ֽ�
	@param[in] order   �ֽ���
	@return  ����ֵ
	*/
	INT64 GetParament_INT(UINT8 len, bool order);

	/*!
	@brief �ӽ��հ��л��һ��BCD�Ͳ���
	@param[in] len  ���ȣ���λ�ֽ�
	@return  ����ֵ
	*/
	INT64 GetParament_BCD(UINT8 len);

	/*!
	@brief �ӽ��հ��л��һ���ֽ�������
	@param[in] len  ָ����ȡ�ֽ����ĳ��ȣ���λ�ֽ�
	@param[out] buf   ����ֽ���
	*/
	void GetParament_BUF(UINT8 len, UINT8 *buf);

	/*!
	@brief ��ʼ��һ������
	@param[in] portnr  �˿ں�
	@param[in] baud  ������
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	bool InitPort (int portnr, int baud);

	/*!
	@brief �ͷŵ�ǰ����
	@return  SUCCESS-�ɹ�; FAILUR-ʧ��
	*/
	bool ReleasePort ();

	/*!
	@brief �������ת��Ϊ��������
	@param[in] errNo  �����
	@param[out] errStr   ��������
	*/
	void getErrMsg(string &errStr, UINT8 errNo);

	/*!
	@brief ��ʱ��������׼ȷ��
	@param[in] Msecs  ��λ����ԼΪ1����
	*/
	void ser_delay(UINT32 Msecs);

	
	/*!
	@brief ���캯��
	*/
	CSerialProtocol();

	/*!
	@brief ��������
	*/
	~CSerialProtocol();

private:
	// function for send & rev
	INT8 Rev_Pack(const char *pack_start);
	void Send_Pack();
	
	// function for serial operate
	INT32 GetReceiveCount();
	UINT8 GetChar();
	void PutChar(UINT8 *byte);

	//common function
	UINT16 Cal_CRC(UINT8 *ptr, UINT8 len);
};


#endif	//USE_SERIAL_PROTOCOL

#endif	//__SERIALPORT_COMMUTION_H


