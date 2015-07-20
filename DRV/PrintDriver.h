/*! \file   PrintDriver.h
   \brief   ��ӡ����
   \author  Yin Chuntian
 */
#ifndef PRINT_DRIVER_H
#define PRINT_DRIVER_H

#include "comdatatype.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define PRINTER_INTERRUPT 		0
#define SIDA_PRINTER			1


/*!
@brief	    �򿪴�ӡ���豸�ļ�
@details	��ʼ�����ݰ���:�����ӡ���������ָ�Ĭ��ֵ��ѡ���ַ���1��ɾ���û������ַ�
@others		����(HEX)��1B  40  
*/
void OpenPrinterDEV();

/*!
@brief		���ӡ�����ͳ�ʼ������
@details	��ʼ�����ݰ���:�����ӡ���������ָ�Ĭ��ֵ��ѡ���ַ���1��ɾ���û������ַ�
@param[in]  bidirectionalPrint ��ӡ����  
@others		����(HEX)��1B  40 
*/
void PrinterIni(UINT8 bidirectionalPrint);

/*!
@brief		���뺺�ִ�ӡ����
@details	��ӡ�����յ���������󣬽���5��7����ASCII�ַ���ӡ״̬ת����16��16����ĺ��ִ�ӡ״̬�����ִ�����2�ֽڶ�Ӧһ�����ֵı�׼������
@others		����(HEX)��1C  26 
*/
void SetChineseMode(void);


/*!
@brief		�˳����ִ�ӡ����
@details	��ӡ��������������󣬽��Ӻ��ִ�ӡ״̬�л���5��7����ASCII�ַ���ӡ״̬����ʵ��16��16��������5��7����ASCII�ַ�ͬ�л�ϴ�ӡ 
@others		����(HEX)��1C  2E 
*/
void SetAsciiMode(void);


/*!
@brief		ִ��n������ֽ
@details	��ӡ�����յ������������ǰ��n���У�n��ֵ��1-255��Χ�ڡ������������س����У�Ҳ��Ӱ�����Ļ������
@param[in]	N ��ֽ�ĵ���
@others		����(HEX)��1B  4A  n
*/
void ForwardNPoint(UINT16 N);


/*!
@brief     ����N��
@param[in] N ���� 
*/
void ForwardNLine(UINT8 N);

/*!
@brief    ִ�к��ֱ����ӡ
@details  ��ӡ���ڽ��յ�������󣬴�ӡ�ĺ��ֽ��ں���Ŵ�һ�������򲻸ı䡣������FS DC4��CR��LF��������Զ�����֮�����˳����ֱ����ӡ����ÿ������ʽ��ִ����ౣ��һ�� 
@others   ����(HEX)��1C  0E 
*/
void SetDoubleChineseMode(void);


/*!
@brief    ȡ�����ֱ����ӡ
@details  ȡ����FS SO����ִ�еĺ��ֱ����ӡ��ʽ���ָ���׼���ִ�ӡ����ʵ�ֲ�ͬ��ȵĺ���ͬ�л�ϴ�ӡ
@oters    ����(HEX)��1C  0E 
*/
void CancelDoubleChineseMode(void);


/*!
@brief       ���� n���м��
@details     Ϊ����Ļ�����������n���м�࣬n��ֵ��0-255֮�䣬��ʹ��ESC K�����ӡ����ͼ��ʱ��ͨ������n=0���ı���ӡʱͨ������n=3
@param[in]   N  �м�����
@others      ����(HEX)��1B  31  n 
*/
void SetLineSpace(UINT8 N);


/*!
@brief      �س�
@details    ������һ��CR�����ӡ��ʱ���ڻ������е������ַ����ֶ�������ӡ����������ֽ��ǰ��һ�� 
@others     ����(HEX)��0D
*/
void CarriageReturn(void);


/*!
@brief     ����
@details   ��ӡ����ǰ��һ���ַ���
@others    ����(HEX)��0A  
*/
void LineFormard(void);


/*!
@brief     ���ڱ�ǰ��
@details   ���ӡ���յ����������ǰ��ֽ��ֱ����⵽�ڱ��ǰ��ʱֹͣ��ֽ 
@others    ����(HEX)��16
*/
void SeekForntBorderBlackMark(void);


/*!
@brief    ���ڱ����
@details  ��ӡ���յ����������ǰ��ֽ��ֱ����⵽�ڱ�ĺ���ʱֹͣ��ֽ������⵽�ڱ�ǰ��ʱ����ֹͣ��ֽ
@others   ����(HEX)��17  
*/
void SeekBackBorderBlackMark(void);


/*!
@brief      ����ˮƽ���ֵ
@details    ����ˮƽ���λ��,n1 n2�ȵȣ�������Щ��Ӧ�ڸ��ͺŴ�ӡ����ͷ���п�֮�ڣ����磺n1=3,��ִ��ˮƽ���ʱ���ӵ������ַ�����ʼ��ӡ���ַ�
		    NUL������󣬱�ʾ������Ľ��������������ˮƽ�������,�������ø�������ESC D NUL��ʽ���
@others     ����(HEX)��1B  44  n1 n2 n3 �� 00
*/
void SetHT(void);

/*!
@brief      ִ��ˮƽ���
@details    ��ӡλ�ý��е���ESC D�������õ���һˮƽ���λ�á����û������ˮƽ���ֵ���ߵ�ǰ��ӡλ�õ��ڻ򳬹����һ��ˮƽ���ֵ��HT�����ִ��
@others     ����(HEX)��09 
*/
void ExecuteHT(void);


/*!
@brief    ���ִ�ӡһ���ַ�
@details  ��ӡλ�ý��е���ESC D�������õ���һˮƽ���λ�á����û������ˮƽ���ֵ���ߵ�ǰ��ӡλ�õ��ڻ򳬹����һ��ˮƽ���ֵ��HT�����ִ�� 
*/
void PrintChineseLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief       �����ӡһ���ַ�
@details     ��ӡλ�ý��е���ESC D�������õ���һˮƽ���λ�á����û������ˮƽ
		     ���ֵ���ߵ�ǰ��ӡλ�õ��ڻ򳬹����һ��ˮƽ���ֵ��HT�����ִ��
@param[in]   LineBuff ��ӡ������   BuffLen ��ӡ���ݵĳ���  
*/
void PrintDoubleChineseLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief      Ascii��ӡһ���ַ�
@details    ��ӡλ�ý��е���ESC D�������õ���һˮƽ���λ�á����û������ˮƽ
		    ���ֵ���ߵ�ǰ��ӡλ�õ��ڻ򳬹����һ��ˮƽ���ֵ��HT�����ִ��
@param[in]  LineBuff ��ӡ������   BuffLen ��ӡ���ݵĳ��� 
*/
void PrintAsciiLine(INT8 *LineBuff, UINT8 BuffLen);


/*!
@brief       �����ӡһ���ַ�
@details     ��ӡλ�ý��е���ESC D�������õ���һˮƽ���λ�á����û������ˮƽ
		     ���ֵ���ߵ�ǰ��ӡλ�õ��ڻ򳬹����һ��ˮƽ���ֵ��HT�����ִ��
@param[in]   LineBuff ��ӡ������   BuffLen ��ӡ���ݵĳ��� 
*/
void PrintReportLine(INT8 *LineBuff, UINT8 BuffLen);

/*!
@brief  ��ӡ���з�  
*/
void PrintSeparateLine(void);

#if SIDA_PRINTER == 1

/*!
@brief       ִ��n������ֽ
@details     ��ӡ�����յ������������ǰ��n���У�n��ֵ��1-255��Χ�ڡ������������س����У�Ҳ��Ӱ�����Ļ�������
@param[in]   N��ֽ�еĵ��� 
@others      ����(HEX)��1B  49  n
*/
void BackwardNPoint(UINT16 N);

/*!
@brief     ���� n���ּ��
@details   Ϊ����Ļ�����������n���м�࣬n��ֵ��0-255֮�䣬��ʹ��ESC K�����ӡ����ͼ��ʱ��ͨ������n=0���ı���ӡʱͨ������n=3
@param[in] N �ּ��ĵ���
@others    ����(HEX)��1B  32  n
*/
void SetWordSpace(UINT8 N);

/*!
@brief      ����˫���ӡ����
@details    Ϊ����Ļ�����������n���м�࣬n��ֵ��0-255֮�䣬��ʹ��ESC K���� ��ӡ����ͼ��ʱ��ͨ������n=0���ı���ӡʱͨ������n=3
@param[in]  N ˫���ӡ����  
@others     ����(HEX)��1B  33  n
*/
void SetBidirectionalPara(UINT8 N);

/*!
@brief     ��ѯ����״̬ 
@return    ���ػ���״̬
@others    ����(HEX)��1B  23
*/
UINT8 GetPrinterStatus(void);

/*!
@brief      ��ѯ������ʹ������
@return     ��ѯ������ʹ������
@others     ����(HEX)��1B  21
*/
UINT8 GetUsedLines(void);

/*!
@brief     ��ѯ������ʹ���ֽ���
@return    ��ѯ������ʹ������
@others    ����(HEX)��1B  24
*/
UINT16 GetUsedBytes(void);

void Code128Return(int n, int cmd);
void CodeTwo(int n, int cmd1, int cmd2);

/*!
@brief    ��ӡ��ά����
*/
int PrintBiznfo(unsigned char *input1,int VerticalNum,int HorizontalNum, int leftMargin);

int PrintBiznfo2(unsigned char *input1,unsigned char *input2,int VerticalNum,int HorizontalNum,int index);


#endif

#ifdef __cplusplus
}
#endif

#endif
