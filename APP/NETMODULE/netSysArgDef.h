/**
 @file  netSysArgDef.h
 @brief ���ļ���������ģ����������ݿ�SYSARG�ꡣ
 */
#ifndef __NET_SYS_ARG_DEF_H
#define __NET_SYS_ARG_DEF_H


/*! ����ģʽ������0-�ޣ�1-��������2-ADSl��3-3g��4-M2MWMMP��5-M2MAPN */
#define SYS_NET_MODE						201	


/*! �ڶ�������ģʽ������0-�ޣ�10-VPN�� */
#define SYS_NET_MODE_L2						202


/*! ������DHCPģʽ��0-DHCP�أ�1-DHCP�� */
#define SYS_LAN_DYNAMIC_IP					203

/*! ������IP */
#define SYS_LAN_IP							204

/*! �������������� */
#define SYS_LAN_MASK						205

/*! ���������� */
#define SYS_LAN_GATEWAY						206

/*! ������DNS */
#define SYS_LAN_DNS							207



/*! ADSL �û��� */
#define SYS_ADSL_USER						208

/*! adsl ���� */
#define SYS_ADSL_PWD						209



/*! 3g ��Ӫ�� */
#define SYS_3G_CARRIER						210

/*! 3g �û��� */
#define SYS_3G_USER							211

/*! 3g ���� */
#define SYS_3G_PWD							212



/*! M2M ģ�鼤��ѡ�0-��ִ�м��������1-ִ�м������ */
#define SYS_M2M_ACT_STATE					213

/*! M2M APN ����� */
#define SYS_M2M_APN_ACCPOINT				214

/*! M2M APN ���� */
#define SYS_M2M_APN_NUMBER					215



/*! VPN ������IP */
#define SYS_VPN_SEVER_IP					216

/*! VPN �û��� */
#define SYS_VPN_USER						217

/*! VPN ���� */
#define SYS_VPN_PWD							218


/*! �����Զ�����ѡ�� 0-�Զ�VPN���ţ�1-�Զ���VPN���ţ�2-�ֶ�����*/
#define SYS_AUTO_DIAL						219



/*! ҵ�������IP */
#define SYS_APP_SERVER_IP					231

/*! ҵ�������PORT */
#define SYS_APP_SERVER_PORT					232

/*! ҵ���������·���ļ� */
#define SYS_APP_SERVER_FILE					233

/*! ʱ�������IP */
#define SYS_TIME_SERVER_IP					234

/*! ʱ�������PORT */
#define SYS_TIME_SERVER_PORT				235

/*! ʱ���������·���ļ� */
#define SYS_TIME_SERVER_FILE				236




#endif

