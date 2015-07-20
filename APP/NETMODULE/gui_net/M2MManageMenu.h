/**
 @file  M2MManageMenu.h
 @brief �����ļ���M2M����˵�
*/
#ifndef M2M_MANAGE_MENU_H
#define M2M_MANAGE_MENU_H

#include "IncludeMe.h"
#include "MultiBtnCommonWin.h"
#include "CaLabel.h"
#include "CaButton.h"

class CM2MManageMenu : public CMultiBtnCommonWin
{
public:
	
	CM2MManageMenu();
	int Create(int iX,int iY,int iW,int iH);
	int ProcEvent(int iEvent,unsigned char *pEventData, int iDataLen);
	
	
private:
	
	void OnButton1(int iEvent, unsigned char * pEventData, int iDataLen);
	void OnButton2(int iEvent, unsigned char * pEventData, int iDataLen);

};


#endif
