#ifndef __VERSION_CONFIG_H
#define __VERSION_CONFIG_H


//////////////////////////////////////////////////////////////////////////
//  ����汾����
//////////////////////////////////////////////////////////////////////////

#define SOFTWARE_VERSION		1.400020		//����汾��(��Ӧdebug�汾�ţ�1.110013)

#define RELEASE_VER				0  /**< 1: �����汾��0: ���԰汾 */

//////////////////////////////////////////////////////////////////////////
//  ����ͺŶ���
//////////////////////////////////////////////////////////////////////////

#define 	POS_APE3000R  1
#define     POS_APE4000R  2
#define 	POS_APE4020R  3
#define 	POS_APE5020R  4


#define 	POS_TYPE	POS_APE4000R     //�������

#if (POS_TYPE == POS_APE4020R)
#define UART				UART2
#define UART_DEV_NAME		UART2_DEV_NAME
#else
#define UART				UART3
#define UART_DEV_NAME		UART3_DEV_NAME
#endif

#define	KEYPAD_TYPE				1	/**< ����Ӳ���汾��1: �°���̣�shift�벿��5�Ե���T9���뷨��λ��������0: �ϰ���� */

#if (POS_TYPE !=POS_APE4000R)		//��4000R����KEYPAD_TYPE����Ϊ1 ���ɸ���
#undef KEYPAD_TYPE
#define	KEYPAD_TYPE				1
#endif

//////////////////////////////////////////////////////////////////////////
//  һЩҵ�����͵ĺ궨��
//////////////////////////////////////////////////////////////////////////

#define	CORP_NAME_LEN_TPYE		0	/**< ��˰�����Ƴ������� 1: 200�ֽڣ�0: 40�ֽ� */
#define ON_LINE                 0   /**< 1:�����߿�Ʊģʽ   0���������߿�Ʊģʽ */    



#define PRN_ADDR_TEL            1   /**< 1: ֧�ִ�ӡ�տλ��ַ�͵绰 0: ��֧��*/
#define VOL_INV_PRN             1   /**< 1: ��Ʊ��ӡ  0: ƽ��Ʊ��ӡ*/
#endif
