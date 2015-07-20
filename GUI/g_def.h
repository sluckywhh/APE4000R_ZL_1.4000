#ifndef G_DEF_H
#define G_DEF_H

#ifdef WIN32
#define WIN_MMI
#endif
#define LINE_H (CHAR_H + 1) //��һ�������ϱ߿򵽵ڶ��������ϱ߿�ľ���
#define SCREEN_H 64
#define SCREEN_W 192
#define SCREEN_LEFT_OFFSET 4
#define SCREEN_TOP_OFFSET 0

#define PAGE_NUM_W (CHAR_W*6)
#define PAGE_NUM_X (SCREEN_W - PAGE_NUM_W - 2)
#define PAGE_NUM_Y (SCREEN_H - CHAR_H - 2)

//���õ�ҳ��
#define PAGE_NUM_X_2 PAGE_NUM_X
#define PAGE_NUM_Y_2 SCREEN_TOP_OFFSET

#define MAX_TITLE_LEN 40

#define INPUT_MAX_TITLE_LEN  64

#define PAGE_UP_KEY 0x49
#define PAGE_DOWN_KEY 0x51
#define PRE_SCREEN_KEY 0x42   //F8

#define PRE_WIN 0x27

#define INPUT_FIRST_ITEM 0X3B		//F1
#define INPUT_SECOND_ITEM 0X3C		//F2
#define INPUT_THIRD_ITEM 0X3D		//F3
#define INPUT_FOURTH_ITEM 0X3E		//F4
#define INPUT_FIFTH_ITEM 0X3F		//F5

/*#define RETURN_MAIN_MENU 0x40		//F6*/

#define PRINT_KEY 'p'



//����ԱȨ��
#define SYSTEMMANAGER				2      //ϵͳ����Ա
#define SYSTEMDIRECTOR				0      //����Ա
#define SYSTEMOPERATOR				1      //��ƱԱ

#define ONE_QUERY_UPPER_LIMIT_NUM 200

//һ����࿪�ٵĲ�ѯ����ռ�(256*1024 / sizeOf(invtaxhead) )
#define MAX_RESULT_LINES  64 /*һ��Ҫ��4�ı�������Ȼҳ����ʾ����ȷ ���Ϊ256*1024/116 */

#define FAILURE_PRN		0						//��ӡʧ��
#define SUCCESS_PRN		1                       //��ӡ�ɹ�

//#define GOODS_LINE_MAX_PRN_COUNT          8     //��Ʊ��Ʒ��������  
#define GOODSDETAIL_LINE_MAX_PRN_COUNT    25    //��ϸ�б���һҳ��Ʒ����

#define MAX_INV_VOLUME  50 /*��ǰ��˰���еķ�Ʊ����>= MAX_INV_VOLUMEʱ�Ͳ������ٵ��뷢Ʊ*/

//��������
//#define  _TEST_DEBUG 

//���ۡ������ȸ����������С��λ����
#define MAX_DECIMAL_LEN_IN_APP 14

//˰�������������
#define  MAX_TAX_ERROR_RANGE 1.27
//���ݿⱣ�������µķ�Ʊ����
#define  BACK_MONTHS_OF_INV_DATA  12
//�����ַ�֧�ֵ���󳤶�
#define SPECIAL_CH_MAX_LEN 2
//�����ַ�������
#define SPECIAL_CH_LIMITED 40
//ÿ����ʾ�����ַ�����
#define CH_PER_LINE 8
//���ٱ����������ַ�����
#define MIN_SPECIAL_CH_LEFT 1

//for debug on the linux platform 
#define RETURN_MAIN_MENU	ESC_KEY	

#endif

