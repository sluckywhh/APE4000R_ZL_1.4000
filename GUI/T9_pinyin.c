/****************************************************************************************
*�ļ�˵��: ��������ʵ���ļ�
*ʹ��˵��:
     ���ļ���ƴ�����뷨��������ļ��������ַ���: abcdefghijklmnopqrstuvwxyz(Сд)
     ����ÿ���Ϸ����ַ���_pInput������unsigned char *GetPyIndex(unsigned char *_pInput)
     ������һ�������ַ�����մ�NULL;
     _pInputָ��Ŀռ�Ҫ������6���ֽڿռ䣬�����벻��6�ֽ�ʱ���ÿո�' '����
     ������ֻ��һ���ַ�ʱ����������5���Ը��ַ���ĸ�ĳ��ú���(��Ҳ�����������
     ����Ҫ���ַ������������������)�����ŵ�����Ϊ"zz",Ҳ�ɸı�{_PyMa_zz,"z}   "}�е�'z'
     ʹ�������Ҫ��
     _cByte�������¶��塣
��  �ߣ�  ���Ƿ�
��  �ڣ�  2004��9��27��
��  ����  0.9
-----------------------------------------------------------------------------------------
��ֲ˵����
	Ϊ��APEϵ����ʹ��T9���뷨���ʽ����δ�����ֲ��ADS���뻷���������ʵ�ɾ����
�޸����ݣ�	
	ɾ������������Һ����йصĴ��룬�ṹ�嶨�����뺺�ֲ����йص����ݳ�ԱҲȫ������ɾ����
	�޸��˶���ӿڶ��壬ֻ����T9_Inputһ���ӿں�����
���ߣ�	����
��  �ڣ�  2006��7��7��
****************************************************************************************/
//#define POS_DEBUG_TO_TTY

#include "T9_pinyin.h"
#include "VersionConfig.h"

#if (T9PINYIN_SWITCH == 1)

//#define T9_DEBUG	1

//��ĸ����
_cByte _YunMu_none[]="    ";
_cByte _YunMu_a   []="a   ";
_cByte _YunMu_o   []="o   ";
_cByte _YunMu_e   []="e   ";
_cByte _YunMu_ai  []="ai  ";
_cByte _YunMu_ou  []="ou  ";
_cByte _YunMu_ei  []="ei  ";
_cByte _YunMu_ao  []="ao  ";
_cByte _YunMu_an  []="an  ";
_cByte _YunMu_en  []="en  ";
_cByte _YunMu_ang []="ang ";
_cByte _YunMu_eng []="eng ";
_cByte _YunMu_ong []="ong ";
_cByte _YunMu_i   []="i   ";
_cByte _YunMu_ia  []="ia  ";
_cByte _YunMu_ie  []="ie  ";
_cByte _YunMu_iao []="iao "; 
_cByte _YunMu_iu  []="iu  ";
_cByte _YunMu_ian []="ian ";
_cByte _YunMu_in  []="in  ";
_cByte _YunMu_iang[]="iang";
_cByte _YunMu_ing []="ing ";
_cByte _YunMu_iong[]="iong";
_cByte _YunMu_u   []="u   ";
_cByte _YunMu_ua  []="ua  ";
_cByte _YunMu_ue  []="ue  ";
_cByte _YunMu_uo  []="uo  ";
_cByte _YunMu_uai []="uai ";
_cByte _YunMu_ui  []="ui  ";
_cByte _YunMu_uan []="uan ";
_cByte _YunMu_uang[]="uang";
_cByte _YunMu_un  []="un  ";
_cByte _YunMu_r   []="r   ";
_cByte _YunMu_v   []="v   ";
_cByte _YunMu_n   []="n   ";
_cByte _YunMu_ng  []="ng  ";
_cByte _YunMu_z   []="z   ";



//a��ͷ
_PyIndexType  PyIndex_a[]=
{
	{_YunMu_none},
	{_YunMu_i   },
	{_YunMu_n   },
	{_YunMu_ng },
	{_YunMu_o  },
	{NULL}
};

//b��ͷ
_PyIndexType  PyIndex_b[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_o   },
	{_YunMu_u   },
	{NULL}
};

//c��ͷ
_PyIndexType  PyIndex_c[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//d��ͷ
_PyIndexType  PyIndex_d[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_ing },
	{_YunMu_iu  },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//e��ͷ
_PyIndexType  PyIndex_e[]=
{
	{_YunMu_none},
	{_YunMu_n   },
	{_YunMu_r   },
	{NULL}
};

//f��ͷ
_PyIndexType  PyIndex_f[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_o   },
	{_YunMu_ou  },
	{_YunMu_u   },
	{NULL}
};

//g��ͷ��ƴ��
_PyIndexType  PyIndex_g[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_ua  },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//h��ͷ��ƴ��
_PyIndexType  PyIndex_h[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_ua  },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};


//j��ͷ
//�ֱ�������ָ���ʼ��_PyMa��_YunMu
_PyIndexType  PyIndex_j[]=
{
	{_YunMu_none},
	{_YunMu_i   },
	{_YunMu_ia  },
	{_YunMu_ian },
	{_YunMu_iang},
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iong},
	{_YunMu_iu  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_un  },
	{NULL}
};

//k��ͷ
_PyIndexType  PyIndex_k[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_ua  },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//l��ͷ
_PyIndexType  PyIndex_l[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iang},
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iu  },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{_YunMu_v   },
	{NULL}
};

//m��ͷ
_PyIndexType  PyIndex_m[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iu  },
	{_YunMu_o   },
	{_YunMu_ou  },
	{_YunMu_u   },
	{NULL}
};

//n��ͷ
_PyIndexType  PyIndex_n[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iang},
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iu  },
	{_YunMu_ong },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_uo  },
	{_YunMu_v   },
	{NULL}
};

//o��ͷ
_PyIndexType  PyIndex_o[]=
{
	{_YunMu_none},
	{_YunMu_u   },
	{NULL}
};

//p��ͷ
_PyIndexType  PyIndex_p[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_o   },
	{_YunMu_ou  },
	{_YunMu_u   },
	{NULL}
};

//q��ͷ��ƴ��
_PyIndexType  PyIndex_q[]=
{
	{_YunMu_none},
	{_YunMu_i   },
	{_YunMu_ia  },
	{_YunMu_ian },
	{_YunMu_iang},
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iong},
	{_YunMu_iu  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_un  },
	{NULL}
};

//r��ͷ��ƴ��
_PyIndexType  PyIndex_r[]=
{
	{_YunMu_none},
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//s��ͷ��ƴ��
_PyIndexType  PyIndex_s[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//t��ͷ��ƴ��
_PyIndexType  PyIndex_t[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ian },
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_ing },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//w��ͷ��ƴ��
_PyIndexType  PyIndex_w[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_o   },
	{_YunMu_u   },
	{NULL}
};

//x��ͷ��ƴ��
_PyIndexType  PyIndex_x[]=
{
	{_YunMu_none},
	{_YunMu_i   },
	{_YunMu_ia  },
	{_YunMu_ian },
	{_YunMu_iang},
	{_YunMu_iao },
	{_YunMu_ie  },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_iong},
	{_YunMu_iu  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_un  },
	{NULL}
};

//y��ͷ��ƴ��
_PyIndexType  PyIndex_y[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_i   },
	{_YunMu_in  },
	{_YunMu_ing },
	{_YunMu_o   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ue  },
	{_YunMu_un  },
	{NULL}
};

//z��ͷ��ƴ��
_PyIndexType  PyIndex_z[]=
{
	{_YunMu_none},
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_ei  },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uan },
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{_YunMu_z   },
	{NULL}
};

//ch��ͷ��ƴ��
_PyIndexType  PyIndex_ch[]=
{
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//sh��ͷ��ƴ��
_PyIndexType  PyIndex_sh[]=
{
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_ua  },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};

//zh��ͷ��ƴ��
_PyIndexType  PyIndex_zh[]=
{
	{_YunMu_a   },
	{_YunMu_ai  },
	{_YunMu_an  },
	{_YunMu_ang },
	{_YunMu_ao  },
	{_YunMu_e   },
	{_YunMu_en  },
	{_YunMu_eng },
	{_YunMu_i   },
	{_YunMu_ong },
	{_YunMu_ou  },
	{_YunMu_u   },
	{_YunMu_ua  },
	{_YunMu_uai },
	{_YunMu_uan },
	{_YunMu_uang},
	{_YunMu_ui  },
	{_YunMu_un  },
	{_YunMu_uo  },
	{NULL}
};


//������������ָ������
_PyIndexType *PyIndexPointer[]=
{
	PyIndex_a,
	PyIndex_b,
	PyIndex_c,
	PyIndex_d,
	PyIndex_e,
	PyIndex_f,
	PyIndex_g,
	PyIndex_h,
	PyIndex_i,
	PyIndex_j,
	PyIndex_k,
	PyIndex_l,
	PyIndex_m,
	PyIndex_n,
	PyIndex_o,
	PyIndex_p,
	PyIndex_q,
	PyIndex_r,
	PyIndex_s,
	PyIndex_t,
	PyIndex_u,
	PyIndex_v,
	PyIndex_w,
	PyIndex_x,
	PyIndex_y,
	PyIndex_z
};



//---------------------------------------------------------------------------
static unsigned char KeyNum[PY_MAX_LENGTH];            //�������뻺����
static unsigned char PYBuf_bak[12][PY_MAX_LENGTH];        //ƴ����ϻ�����

static char* MatchPinyin;    //ƥ����ĺϷ�ƴ���б�
static int PinyinLength=0;   //ƴ���ַ�������

#if (POS_TYPE == POS_APE3000R)
static struct _KeyBuf KeyCombination[9]=         //�������ַ���Ӧ
{
	{1,""},{2,"abc"}, {3,"def"},{4,"ghi"},{5,"jkl"},
	{6,"mno"},{7,"pqrs"},{8,"tuv"}, {9,"wxyz"}    
};
#else //POS_TYPE

#if (KEYPAD_TYPE == 1)
static struct _KeyBuf KeyCombination[9]=         //�������ַ���Ӧ
{
	{1,""},{2,"abc"}, {3,"def"},{4,"ghi"},{5,"jkl"},
	{6,"mno"},{7,"pqrs"},{8,"tuv"}, {9,"wxyz"}    
};
#else
static struct _KeyBuf KeyCombination[9]=         //�������ַ���Ӧ
{
	{1,"pqrs"},{2,"tuv"}, {3,"wxyz"},{4,"ghi"},
	{5,"jkl"},{6,"mno"},{7,""},{8,"abc"}, {9,"def"}    
};
#endif
#endif //POS_TYPE
//**********************************************************************************
void PYBuf_clear(unsigned char (*PYBuf)[8])	//ƴ����ϻ���������
{
	unsigned char i,j;
	
	for(i=0;i<12;i++)
	{
		for(j=0;j<8;j++)
		{
			PYBuf_bak[i][j] = PYBuf[i][j];
			PYBuf[i][j] = 0;
		}
	}
}


//�ж�������ַ����Ƿ�Ϊ��Ч��ƴ���ַ��������򷵻�1�����򷵻�0
//����char* _pInputΪ�������ַ���
char IsPyStr(unsigned char* _pInput)
{
       //
       // p1ָ��PyIndex_a~zh[]�����о������Ŀ��Ϊ�Ѿ���������ƴ������Ӧ��ĸ
       // p2ָ��_pInput����ĸ����Ӧ�ĺ������
       // �ڱȽϹ����У��ȱȽ���ĸ��Ȼ��Ƚ���ĸ��������ͬ�򷵻�1
       //

       _PyIndexType  *p1=0,*p2=0;
       size_t complen=0;
       if(strlen((const char*)_pInput)==0)     //�жϺϷ���
       {
                return 0;
       }
       if (_pInput[0]=='i' || _pInput[0]=='u' || _pInput[0]=='v')
       {    
                return 0;    //���Ϸ���ƴ��
       }
           
       if(strlen((const char*)_pInput)==1)
       {
                if(_pInput[0]!='i' || _pInput[0]!='u' || _pInput[0]!='v')
                        return 1;
       }
       //˳�����У��õ�������P2��ʱָ��
       p2= PyIndexPointer[_pInput[0]-'a'];
                                                                                                                                               
       if(_pInput[1]=='h')
       {
                switch(_pInput[0])
                {
                case 'c':
                        p2= PyIndex_ch;
                        _pInput++;
                        break;
                case 's':
                        p2= PyIndex_sh;
                        _pInput++;
                        break;
                case 'z':
                        p2= PyIndex_zh;
                        _pInput++;
                       break;
                }
        }
        //����Ϊ��ĸ�Ƚϣ�����Ϊ��ĸ�Ƚ�
        //���ƴ��Ϊ������ĸʱ��Ӧ������
        if(p2==PyIndex_ch||p2==PyIndex_sh||p2==PyIndex_zh)
        {
                complen=strlen((const char*)_pInput)-1;
        }
        else
        {
                complen=strlen((const char*)_pInput)-1;
        }
        p1=p2;
        //��õ�һ����ĸ

        while(p1->_YunMu!=NULL)
       {
                if(p1->_YunMu[0]==_pInput[1])
                {
                        break;
                }
                else
                        p1++;
        }
        while(p1->_YunMu!=NULL)
        {
                if( strncmp((const char*)p1->_YunMu, (const char *)(_pInput+1), complen)==0)
                {
	                        return 1;       //����Ҫ��
                }
                else
                        p1++;
        }
        if(p1->_YunMu == NULL)
                p1=p2;
        return 0;
}
 

//---------------------------------------------------------------------------
//T9���뷨�����㷨
unsigned char T9_Input(unsigned char *key, unsigned char *num, unsigned char (*PYBuf)[PY_MAX_LENGTH]) 	//������Ӧ����ĸ��������ϳ���Ч��ƴ�� 
{
	int PinyinNum;	//��ʾ�����˼���ƴ���ַ�

	//���أ�ָ��PYBuf�Ķ�ά���飬PYBuf[i][7]=1�����ƴ�������Ч
	unsigned char  i,j,k;
	unsigned char  c0=0,c1=0,c2=0,c3=0,c4=0,c5=0;  //���ܵ��ַ���ciΪ��i�ε��ַ�
	unsigned char  ABC_Array[6][5];    // ���仺��,��Ű�����Ӧ���ַ���,��1��Ӧ"abc"

	PYBuf_clear(PYBuf);		//ƴ����ϻ���������
	memcpy(KeyNum, key, sizeof(KeyNum));

	for(i=0;i<6;i++)	//���̷��仺������
	{
		for(j=0;j<5;j++)
		{
			ABC_Array[i][j]=0;
		}
	}

    //���հ���������˳�򣬽���Ӧ���ַ�������ABC[k]
	PinyinNum=strlen((char *)KeyNum);
	if(PinyinNum==0)    //ƴ������Ϊ0
	{
		return FAILURE;
	}

    for( k=0; k<PinyinNum; k++ )
    {
		//if ( (KeyCombination[KeyNum[k]-1]).KeyStr != NULL )
			strcpy((char*)ABC_Array[k],(KeyCombination[KeyNum[k]-1]).KeyStr);
		//printf("the string is %s   \n",(char*)ABC_Array[k]);
    }
	i=0;   //i��ʾƥ���������Чƴ����Ŀ
    k--;
                                  

    //ƥ�������Чƴ��
	for(c0=0; ABC_Array[0][c0]!=0; c0++)
	{		
		if(ABC_Array[0][c0]=='i'||ABC_Array[0][c0]=='u'||ABC_Array[0][c0]=='v') //��һ��ƴ���ϲ����ܵ���ĸ
			continue;
		PYBuf[i][0]=ABC_Array[0][c0];		//��һλƴ����ĸ
                
		if(k>=1)			//��2��ƴ��ʱ
		{
		 	for(c1=0; ABC_Array[1][c1]!=0; c1++)
		 	{			
		  		PYBuf[i][1]=ABC_Array[1][c1];	//�ڶ�λƴ����ĸ
		  		if(k>=2)			//��3��ƴ��ʱ
		  		{
		   			for(c2=0;ABC_Array[2][c2]!=0;c2++)
		   			{			
		    			PYBuf[i][2]=ABC_Array[2][c2];
		    			if(k>=3)			//��4��ƴ��ʱ
		    			{
		     				for(c3=0;ABC_Array[3][c3]!=0;c3++)
		     				{			
		      					PYBuf[i][3]=ABC_Array[3][c3];
		      					if(k>=4)			//��5��ƴ��ʱ
		      					{
		       						for(c4=0;ABC_Array[4][c4]!=0;c4++)
		       						{			
		        						PYBuf[i][4]=ABC_Array[4][c4];
		        						if(k==5)		//��6��ƴ��ʱ
		        						{
		         							for(c5=0;ABC_Array[5][c5]!=0;c5++)
		         							{			
		          								PYBuf[i][5]=ABC_Array[5][c5];
		          								if(IsPyStr((unsigned char*)PYBuf[i]))   //���Ϊ��Чƴ�����򷵻�1
		          								{
                                                    for(j=0;j<8;j++)
														PYBuf[i+1][j]=PYBuf[i][j];  //����������Чƴ����ֵ����һ��PYBuf��
                                                    PYBuf[i][7]=1;   //��PyBuf���һ��Ԫ����Ϊ1
                                                    i++;
                                                    PinyinLength+=strlen((char*)PYBuf[j])+3;
                                                }
                                            }
                                        }
		        						else if(IsPyStr((unsigned char*)PYBuf[i]))	//��5��ƴ��ʱ
		        						{
	                                        for(j=0;j<8;j++)
	                                                PYBuf[i+1][j]=PYBuf[i][j];
	                                        PYBuf[i][7]=1;
	                                        i++;
	                                        PinyinLength+=strlen((char*)PYBuf[j])+3;
                                        }
		       						}
		      					}
		      					else if(IsPyStr((unsigned char*)PYBuf[i]))	//��4��ƴ��ʱ
		      					{
                                    for(j=0;j<8;j++)
                                            PYBuf[i+1][j]=PYBuf[i][j];
                                    PYBuf[i][7]=1;
                                    i++;
                                    PinyinLength+=strlen((char*)PYBuf[j])+3;
                                }
                        	}
		    			}
		    		    else if(IsPyStr((unsigned char*)PYBuf[i]))	//��3��ƴ��ʱ
						{
                            for(j=0;j<8;j++)
                                    PYBuf[i+1][j]=PYBuf[i][j];
                            PYBuf[i][7]=1;
                            i++;
                            PinyinLength+=strlen((char*)PYBuf[j])+3;
                        }
		   			}
		  		}
		  		else if(IsPyStr((unsigned char*)PYBuf[i]))	//��2��ƴ��ʱ
				{
					if (PYBuf[i][0] != PYBuf[i][1])
					{
						for(j=0;j<8;j++)
								PYBuf[i+1][j]=PYBuf[i][j];
						PYBuf[i][7]=1;
						i++;
						PinyinLength+=strlen((char*)PYBuf[j])+3;
					}
            	}
		 	}
		}
		else if(IsPyStr((unsigned char*)PYBuf[i]))	 //��1��ƴ��ʱ
		{
            for(j=0;j<8;j++)
                    PYBuf[i+1][j]=PYBuf[i][j];
            PYBuf[i][7]=1;
            i++;
            PinyinLength+=strlen((char*)PYBuf[j])+3;
        }
	}
	
	for(j=0;j<8;j++)      //������µ�ƴ��
	{
        PYBuf[i][j]=0;
    }

#ifdef T9_DEBUG 
	j = 0;
	while(1)
	{
		if (PYBuf[j][7] == 0)
			break;
		j++;
	}
#endif

	if (i != 0)			//�з��ϵ�ƴ����������ĸ��д
	{
		j = 0;			
		while(1)
		{
			if (PYBuf[j][7] == 0)
				break;
			PYBuf[j][0] = PYBuf[j][0] - 0x20;
			j++;
		}
		*num = i;
	}
	else				//�޷��ϵ�ƴ�����ָ�ԭƴ��
	{
		for(j=0; j<8; j++)
		{
			memset(PYBuf[j], 0, sizeof(PYBuf[j]));
		}	
		*num = 0;
	}


		
	return SUCCESS;
}

#endif //T9PINYIN_SWITCH

