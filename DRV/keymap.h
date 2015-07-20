
/*! \file   keymap.h 
   \brief   AWE4000���̶���
   \author  zl 
 */

#ifndef __KEYMAP_H__
#define __KEYMAP_H__

#include "VersionConfig.h"

#define	ESC_KEY				0x80		//���ؼ�
#define FORWARD_KEY			0x81		//��ֽ
#define BACKWARD_KEY		0x82		//��ֽ

#define PAGEUP_KEY			0x83		//�Ϸ�
#define PAGEDOWN_KEY		0x84		//�·�

#if (POS_TYPE == POS_APE3000R)
#define UP_KEY		    	0x85		//��
#define DOWN_KEY			0x86		//��
#define LEFT_KEY			0x87		//��
#define RIGHT_KEY			0x88		//��
#else 
#define UP_KEY				DIGIT8		//��
#define DOWN_KEY			DIGIT2		//��
#define LEFT_KEY			DIGIT4		//��
#define RIGHT_KEY			DIGIT6		//��
#endif

#define SHITF_KEY			0x89		//shift
#define BACKSPACE_KEY		0x8A		//�˸�
#define CLEAR_KEY			0x8B		//���


//������plu��
#define DEPT1_KEY			0x90
#define DEPT2_KEY			0x91
#define DEPT3_KEY			0x92
#define DEPT4_KEY			0x93
#define DEPT5_KEY			0x94

#define CHANGE_DEPT_KEY		0x95        //����
#define	PLU_KEY				0x96        //PLU
#define CANCEL_GOODS		0x97		//��Ʒȡ��	
#define CLIENT_NAME_INPUT	0x98		//������
#define INPUT_METHOD		0x99		//���뷨


//����
#define PLUS_KEY			0xA0		//��/ʱ
#define SUM_INPUT			0xA1	    //�ܼ�
#define PRICE_INPUT			0xA2	    //����
#define TOTAL_CANCEL		0xA4		//����ȡ��
#define FIND_KEY			0xA5		//��ѯ(����)
#define HELP_KEY			0xA6		//����
#define CASH_KEY			0xA7		//�ֽ�


//���˹��ܼ�
#define	LOCKED_KEY			0xB0		//����
#define OPEN_CASH_BOX		0xB1		//��Ǯ��
#define PAYMENT_MODE_KEY	0xB2		//��ѯ
#define CHARGE_KEY			0xB3		//�����
#define GOODSREDUCT_KEY		0xB4		//����
#define DISCOUNT_KEY		0xB5		//�ۿ�


#define F1_FUNCTION_KEY		0xBA		//F1���ܼ�
#define F2_FUNCTION_KEY		0xBB		//F2���ܼ�
#define F3_FUNCTION_KEY		0xBC		//F3���ܼ�
#define F4_FUNCTION_KEY		0xBD		//F4���ܼ�
#define F5_FUNCTION_KEY		0xBE		//F5���ܼ�

//���ּ�
#define DIGIT0			'0'
#define DIGIT1			'1'
#define DIGIT2			'2'
#define DIGIT3			'3'
#define DIGIT4			'4'
#define DIGIT5			'5'
#define DIGIT6			'6'
#define DIGIT7			'7'
#define DIGIT8			'8'
#define DIGIT9			'9'

#define DIGIT00			0xD0

#define DOT_KEY			'.'             /*С����*/
#define POUND_KEY		'#'             /*����*/


//�������ܼ�
#define	SCANNER_EVENT_KEY	0xF0		//ɨ��ǹ�¼�
#define EXIT_APP_KEY		0xF1		//�˳�Ӧ�ã������ã�
#define	SHIFT_PLU_KEY	    0xF2      //��ʱ¼����Ʒ���Ƶ�

#if (POS_TYPE == POS_APE3000R)
#define TAB_KEY				DOWN_KEY
#else
#define TAB_KEY				0xF3		//TAB_KEY���ݾɳ���
#endif

//�ַ���
#define	LETTER_A		DEPT1_KEY
#define	LETTER_B		DEPT2_KEY
#define	LETTER_C		DEPT3_KEY
#define	LETTER_D		DEPT4_KEY
#define	LETTER_E		DEPT5_KEY

#if (POS_TYPE == POS_APE3000R)
#define	LETTER_F			OPEN_CASH_BOX
#define	LETTER_G			PAYMENT_MODE_KEY
#define	LETTER_H			CHARGE_KEY
#define	LETTER_I			GOODSREDUCT_KEY
#define	LETTER_J			DISCOUNT_KEY
#else //POS_TYPE
#define	LETTER_F		CHANGE_DEPT_KEY
#define	LETTER_G		PLU_KEY
#define	LETTER_H		CANCEL_GOODS
#define	LETTER_I		CLIENT_NAME_INPUT
#define	LETTER_J		INPUT_METHOD
#endif //POS_TYPE

typedef struct TKeyMap
{
    int  keyValue;                //����ֵ
	char  *keyStr;          	    //���̺��ַ���            
	
};

#endif /*  __KEYMAP_H__  */
