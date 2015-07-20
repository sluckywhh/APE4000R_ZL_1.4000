#ifndef __SERIAL_CONFIG_H
#define __SERIAL_CONFIG_H

//#include "error_code.h"

#define SERIAL_DEVICE						"/dev/uart3"
#define SERIAL_BAUDRATE						9600

#define SERIAL_BUFFER_MAX_LEN				65535UL							//����Buf��󳤶�	
#define BUSINESS_DATA_BUF_MAX_LEN			10*1024						//ҵ�񻺳�������

#define SERIAL_PACKAGE_ZC_MAX_LEN			255								//�ܲ�Э�����ݰ���󳤶�
#define SERIAL_PACKAGE_AISINO_MAX_LEN		SERIAL_BUFFER_MAX_LEN			//�����Զ������ݰ���󳤶�

#define SERIAL_OVERTIME_MAX					30000000UL
#define SERIAL_NODATA_MAX					50000UL
#define SERIAL_ERRNUM_MAX					0x40

#define CRC_LEN								2								//CRCУ��λ����
#define SENDPACK_ZC_HEAD_LENGTH				5								//�ܲ�Э��������ݰ���ͷ����
#define RSPPACK_ZC_HEAD_LENGTH				4								//�ܲ�Э����Ӧ���ݰ���ͷ����
#define SENDPACK_AISINO_HEAD_LENGTH			6								//����Э��������ݰ���ͷ����
#define RSPPACK_AISINO_HEAD_LENGTH			5								//����Э����Ӧ���ݰ���ͷ����

enum ProtocolType
{
	ZC_PROTOCOL			= 0x10,				//�ܲ�Э���ͷ����
	XML_PROTOCOL		= 0x20,				//XML���ݰ�ͷ����
	CA_PROTOCOL			= 0x30,				//CAҵ�����ݰ�ͷ����
	PRN_PROTOCOL		= 0x40				//��ӡ���ݰ�ͷ����
};

typedef struct
{
	UINT8 cmdType;		//��������
	UINT8 cmdNo;		//�����
	UINT8 PackNo;		//�����
	UINT16 cmdLen;		//��������
	UINT32 dataLen;		//ҵ�����ݳ��ȣ��ۼ�
	UINT8 *sendData;
} send_cmdStruct;

typedef struct
{
	UINT8 head[2];
	UINT8 PackNo;
	UINT8 multiPackages;
	UINT16 cmdLen;
	UINT32 dataLen;		//ҵ�����ݳ��ȣ��ۼ�
	UINT8 *rspData;
} rsp_cmdStruct;

enum ByteOrder
{
	WEB_BYTEORDER		= 0x00,
	PC_BYTEODER			= 0x01
};

//error code define
#define	SERCMD_SUCCESS				0x00			//���������ȷ
#define	SERCMD_NO_DATA				0xF0			//��ʱΪδ�յ�����
#define	SERCMD_NOT_LASTPACK			0xF1			//���յİ����ǽ�����
#define SERCMD_HEAD_ERR				0x11			//��ͷ���ݸ�ʽ����
#define SERCMD_HEAD_PARA_ERR		0x12			//��ͷ���ݲ�������
#define SERCMD_CRC_ERR				0x1f			//����CRC��
#define	SERCMD_CMDNO_ERR			0x20			//������޷�ʶ��
#define SERCMD_PACKLEN_ERR			0x22			//����ȴ���
#define SERCMD_OVERTIME_ERR			0x30			//������ܳ�ʱ

#define BUSINESS_COMMON_TYPE		0x10			//�ܲδ���ͨ������
#define BUSINESS_XML_TYPE			0x20			//xml���ݴ�������
#define BUSINESS_CA_TYPE			0x30			//CA����ͨ������
#define BUSINESS_PRINT_TYPE			0x40			//��ӡ���ݴ�������

#define NP_PACKAGE_TYPE				0x01
#define OK_PACKAGE_TYPE				0x02
#define ER_PACKAGE_TYPE				0x03
#define WT_PACKAGE_TYPE				0x04

#define WAIT_TIME					600				//���ڵȴ�ʱ�� ��
#define REV_TIME					300				

#endif
