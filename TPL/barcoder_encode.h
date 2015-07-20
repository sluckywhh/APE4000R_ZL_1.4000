/*! \file    barcoder_encode.h
\brief    ��ά���ӡ���뺯��
\author   gaoyang
 */
#ifndef  __BARCODER_ENCODE_H__   
#define __BARCODER_ENCODE_H__

#define MAIN_VERSION_MAJOR      1
#define MAIN_VERSION_MINOR      2
#define MAIN_VERSION_PATCH      0

//#if (PRINT_BIZNFO!=0)


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BRAENCODE_EXTERN extern

//��������
#define CS_ENCODE   1
#define QR_ENCODE   2
#define DM_ENCODE   3


/*uclinux������
CS�� ���汾 20
QR�� ���汾 12 �����������ֽ�300
DM�� ���汾 15
*/
    

/*barcoder_encode
param
    itype:
        ��������. ������ 1 QR�� 2 DataMatrix(DM)�� 3
    version:
        ��ά��汾.�汾Խ�߿���������Խ��
    ecl:
        ��ά�����ȼ�. �������QR��Ϊ1-4�ĸ��ȼ�. DM��û�о�������
    pixel:
        һ��ģ����pixel x pixel���������ݾ������
    imgData: 
        Ϊ��ʱ,���ص�ǰ������Ϣ����������ͼ����Ҫ���ܴ�С
        ��Ϊ��ʱ,imgDataSizeΪimgData��С
    imgDataSize:
        ����imgData���ֽڴ�С
    imgWidth:
        �������ͼ��Ŀ�
    imgHeight:
        �������ͼ��ĸ�
return > 0 �ɹ�
      -1 �����������ȷ
      -2 ����汾����
*/
BRAENCODE_EXTERN int barcoder_encode(int encode_type, int version, int ecl, int pixel, unsigned char* data, int data_len, 
              unsigned char* imgData, int imgDataSize, int* imgWidth, int* imgHeight);

#ifdef __cplusplus
}  /* end of extern "C" */
#endif /* __cplusplus */

//endif		//#if (PRINT_BIZNFO!=0)


#endif
