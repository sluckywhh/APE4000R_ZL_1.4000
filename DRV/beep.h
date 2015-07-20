/*! \file    beep.h
   \brief    ����������
   \author   
 */

#ifndef BUZZER_POS_H
#define BUZZER_POS_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef WIN32
#define BUZZER_MAGIC 'q'
#define BUZZER_INIT				_IO(BUZZER_MAGIC, 0)
#define BUZZER_SET_FREQUENCE  	_IOW(BUZZER_MAGIC, 1, int)
#define BUZZER_SET_TIMES 		_IOW(BUZZER_MAGIC, 2, int)
#define BUZZER_ALARM			_IO(BUZZER_MAGIC, 3)

 #define MONEYBOX_INIT			_IO(BUZZER_MAGIC, 4)
 #define MONEYBOX_OPEN			_IO(BUZZER_MAGIC, 5)

#define BUZZER_MAXNR 6
#endif

/*!
@brief ������ʼ�� 
*/
void Beep_Ini(void);

/*!
@brief ��������  
*/
void Beep_On(void);

/*!
@brief Ǯ���ʼ�� 
*/
void MoneyBox_Init(void);


/*!
@brief Ǯ�俪��  
*/
void MoneyBox_Open(void);



#ifdef __cplusplus
}
#endif

#endif
