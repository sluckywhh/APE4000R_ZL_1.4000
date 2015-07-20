

drop table IF EXISTS MACHINE;
drop table IF EXISTS USERINFO;
drop table IF EXISTS USER_MORE;
drop table IF EXISTS DEPT;
drop table IF EXISTS CLIENT;
drop table IF EXISTS INV_VOL;
drop table IF EXISTS INV_HEAD;
drop table IF EXISTS INV_DET;
drop table IF EXISTS RT_INV;
drop table IF EXISTS CB_HZ;
drop table IF EXISTS OPERATOR;
drop table IF EXISTS SYSLOG;
drop table IF EXISTS SYSARG;
drop table IF EXISTS INV_SERV;
drop table IF EXISTS INV_KIND;
drop table IF EXISTS PRN_INFO;
drop table IF EXISTS INV_SUM;
drop table IF EXISTS INV_SORT; 
drop table IF EXISTS TAX;
drop table IF EXISTS NETPARA;

--#########������Ʊ����Ϣ��###################
--#     �������                varchar(16)          
--#     ��������                date
--#     Ӳ���汾��              varchar(18)
--#     ����汾��              varchar(18)
--############################################
--
-- Table structure for table `MACHINE`
--

CREATE TABLE MACHINE (
	M_NO		varchar(16) 	NOT NULL,
	P_DATE		date        	NOT NULL,
	H_VER		varchar(18) 	NOT NULL,
	S_VER		varchar(18) 	NOT NULL
);

--
-- Dumping data for table `MACHINE`
--
--for_initProc_20150506linzihao
--#########������ҵ��Ϣ��#####################
--#     ��˰��ʶ���					varchar(30)
--#     ��˰������            varchar(200) 
--#     ��Ʊ������							varchar(50)
--#     ���ֻ���־					varchar(50)
--#     ��˰����ҵ����							varchar(6)
--#     ��ҵ����			varchar(40)
--#     ��˰���豸��							char
--#     ���̵ǼǺ�						char
--#     ��������			char
--#     �����˺�				char
--#     �Ǽ�ע���ַ					varchar(2)
--#     ����˰����ش���				char
--#     ����˰���������						varchar(50)
--#     ��Ʊ��Ȩ˰�ʸ���     				varchar(200)
--#     ��Ʊ������						int
--#     ����						int
--############################################
--
-- Table structure for table `USERINFO`
--

CREATE TABLE USERINFO (
  NSRSBH		varchar(25)		NOT NULL,
  NSRMC			varchar(200)		NOT NULL,
  KPJHM                 int                     NOT NULL,
  ZFFLAG                char			NOT NULL,
  QY_LX                 varchar(3)			NOT NULL,
  JSPSBH                varchar(12)		NOT NULL,
  GSDJH                 varchar(50),
  KHYH                  varchar(100),
  KHZH                  varchar(50),
  DJZCDZ                varchar(100),
  SWJGDM		varchar(20),		
  SWJGMC		varchar(100),
  SLGS                  int			NOT NULL,
  KPJSL			int			NOT NULL,
  QYSJ			varchar(14),
  BACKUP	        varchar(20)
);

--
-- Dumping data for table `USERINFO`
--

--#########���������û���Ϣ��#################
--#		����1		varchar(20)
--#		����2		varchar(20)
--#		����3		varchar(20)
--#		����4		varchar(20)
--#		����5		varchar(20)
--#		����6		varchar(20)
--#		����7		varchar(20)

--############################################
--
-- Table structure for table `USER_MORE`
--

CREATE TABLE USER_MORE (
	BACKUP1	 varchar(20),
	BACKUP2	 varchar(20),
	BACKUP3	 varchar(20),
	BACKUP4	 varchar(20),
	BACKUP5	 varchar(20),
	BACKUP6	 varchar(20),
	BACKUP7	 varchar(20)	
) ;
--
-- Dumping data for table `USER_MORE`
--

--#########�������������ñ�###################
--#     ��������          int   
--#     ������ֹ         	int
--#     ��Ʊ��ֹ����			int
--############################################
--
-- Table structure for table `SSQ_SZ`
--

--CREATE TABLE SSQ_SZ (
--	SSQ		int		NOT NULL,
--	SSQ_Q		int		NOT NULL,
--	SSQ_Z		int		NOT NULL,
--	KPJZRQ		int		NOT NULL,
--	PRIMARY KEY(SSQ)
--);

--
-- Dumping data for table `SSQ_SZ`
--

--#########������Ʒ��Ϣ��#####################
--#     ����           				varchar(16)          
--#     ����           				varchar(100)
--#     ����      					double
--#		˰��						float
--#		��λ						varchar(50)
--#		�����						int
--#		���						varchar(6)
--#		���						varchar(50)
--#		����ƷĿ���루˰Ŀ��		varchar(4)
--#     ������           			float
--#     �ۿ���						float
--############################################
--
-- Table structure for table `DEPT`
--

CREATE TABLE DEPT (
	SP_BM			varchar(16)  		NOT NULL,
	SP_MC			varchar(100)		NOT NULL,
	SP_DJ			double			NOT NULL,
	SP_SL			float			NOT NULL,
	SP_DW			varchar(10),
	BLH				int        NOT NULL,
	SP_JM			varchar(6),
	SP_GG			varchar(50),
	ZSPM_DM			varchar(4),
	SP_ZSL			float,
	D_RATE			float			NOT NULL,
	PRIMARY KEY(SP_BM)
);

--
-- Dumping data for table `DEPT`
--

--#########�����ͻ���Ϣ��#################          
--#     ���ر��			varchar(16)
--#     ����				varchar(20)
--#     ������			varchar(4)
--#     ����				varchar(100)
--#     ˰��				varchar(30)
--############################################
--
-- Table structure for table `CLIENT`
--

CREATE TABLE CLIENT (
	KH_BH			varchar(16)			NOT NULL,
	KH_DM			varchar(20)			NOT NULL,
	KH_JM		varchar(4)			NOT NULL,
	KH_MC		varchar(100)			NOT NULL,
	KH_SH		varchar(30),
	PRIMARY KEY(KH_BH)
);

--
-- Dumping data for table `CLIENT`
--

--#########������˰�˷�Ʊ������Ϣ��#################
--#     ����       					INTEGER
--#     ��Ʊ����         		varchar(20)
--#     ��Ʊ��ʼ����        varchar(10)	
--#     ��Ʊ��ֹ����				varchar(10)
--#     ʣ�����						int
--#     ʹ�ñ�־						char
--#     �����־						char
--#     ����						int
--############################################
--
-- Table structure for table `INV_VOL`
--

CREATE TABLE INV_VOL (
	NO				INTEGER 		PRIMARY KEY,
	INV_TYPE	        char		        NOT NULL,
	CODE			varchar(20)		NOT NULL,
	IS_NO			int				NOT NULL,
	IE_NO			int				NOT NULL,
	REMAIN			int				NOT NULL,
	FPZFS			int				NOT NULL,
	USED_FLAG		char			NOT NULL,
	OVER_FLAG		char			NOT NULL,
	RQ              int,
	FPLXDM			char(3),
	BACKUP1         int,
	BACKUP2         varchar(10),
	UNIQUE  (CODE,IS_NO)
);

--
-- Dumping data for table `INV_VOL`
--

--#########������Ʊ���߱�#################	
--#     ����					INTEGER
--#     ��Ʊ����				varchar(20)    
--#     ��Ʊ����				int
--#		��Ʊ����				int              
--#     ��Ʊʱ��				int
--#     ��Ʊ����				char
--#     ��Ʊ�ϼƽ��			Big int  
--#     ˰��					Big int       
--#     ԭ��Ʊ����				varchar(20)
--#     ԭ��Ʊ����				int			
--#     ���λ      			varchar(200)	
--#     ���λ˰��ʶ���      varchar(20)
--#		�տ�Ա					varchar(30)
--#		��Ʒ������				int		
--#		��α˰����				varchar(32)	
--#		Ʊ�����				varchar(5)
--#		�ϴ���־				char
--#		Ʊ������				varchar(5)
--#		��ע��չ				varchar(4)//��ʱע��20150507linzihao
--#		�Ƿ���Կ��ߺ�Ʊ		varchar(4)//��ʱע��20150507linzihao
--#		�����ֶ�1				varchar(20)
--#		CAǩ��					varchar(200)
--############################################
--
-- Table structure for table `INV_HEAD`
--

CREATE TABLE INV_HEAD (
	NO				INTEGER			PRIMARY KEY,
	FPDM			varchar(20)		NOT NULL,
	FPHM			int				NOT NULL,
	KPRQ			int				NOT NULL,
	KPSJ			int				NOT NULL,
	KPLX			char			NOT NULL,
	KPHJJE			Big int			NOT NULL,
	KPSE			Big int			NOT NULL,
	YFPDM			varchar(20),
	YFPHM			int				NOT NULL,
	FKDW			varchar(200)	NOT NULL,
	FKDWSH		varchar(20)		NOT NULL,
	SKY				varchar(30),
	SPHSL			int				NOT NULL,
	FWM				varchar(32)		NOT NULL,
	FPLB			char,
	SCBZ			char,
	BACKUP1			varchar(20),

	UNIQUE  (FPDM,FPHM)
);

--
-- Dumping data for table `INV_HEAD`
--

--#########������Ʊ������ϸ��#################
--#     ����					INTEGER          
--#     ��Ʊ����			varchar(20)
--#			��Ʊ����			int		
--#     ��Ʊ����				char
--#     ����ԱID      char
--#			��Ʒ�����		int
--#			��Ʊ����			int					
--#			��Ʊʱ��			int						
--#		��Ʒ����			varchar(16)
--#			��Ʒ����			varchar(100)
--#			��Ʒ����			double
--#			��Ʒ����			double
--#			��Ʒ���			Big int
--#			��Ʒ˰��			Big int
--#			˰��					float
--#		����(����˰)		double
--#		���(����˰)		Big int
--#     ��Ʒ������    char
--#     ��Ʒ��λ			varchar(10)
--#		�����ֶ�			varchar(20)	
--############################################
--
-- Table structure for table `INV_DET `
--

CREATE TABLE INV_DET (
	NO		INTEGER				PRIMARY KEY,
	FPDM		varchar(20)			NOT NULL,
	FPHM		int				NOT NULL,
	KPLX		char			NOT NULL,
	SKY		    varchar(30), 
	SPHXH		int				NOT NULL,
	KPRQ		int				NOT NULL,
	KPSJ		int				NOT NULL,
	SPBM		varchar(16)  			NOT NULL,
	SPMC		varchar(100)			NOT NULL,
	SPDJ		double,
	SPSL		double,
	SPJE		Big int				NOT NULL,
	SPSE		Big int				NOT NULL,
	SL		float,
	DJ			double,
	JE			Big int,
	PROP		char				NOT NULL,
	SP_DW			varchar(10),
	BACKUP		varchar(20),
	UNIQUE(FPDM,FPHM,SPHXH)
);

--
-- Dumping data for table `INV_DET `
--

--#########������Ʊ��#########################
--#     ����						INTEGER
--#     ��Ʊ����				varchar(20)
--#     ��Ʊ����			int(8)
--############################################
--
-- Table structure for table `RT_INV`
--

CREATE TABLE RT_INV (
     NO     		INTEGER 		PRIMARY KEY,
     FPDM		varchar(20)		NOT NULL,
     FPHM		int			NOT NULL,
     UNIQUE  (FPDM,FPHM)
);

--
-- Dumping data for table `RT_INV`
--

--#########�����������ܱ�####################
--#			���				INTEGER	
--#			������				int
--#			��������			int
--#			������ֹ			int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ϸ���			int
--#			��Ͽ�Ʊ���			Big int
--#			�հ׷�Ʊ����			int
--#			��������			int
--#			�����ɹ�����			int
--#			ʧ��ԭ��			varchar(100)
--#			��������			char
--#			��˰�ɹ���־			char
--#			���ͽ��ʱ�־			char
--#			����δ�ϴ��ķ�Ʊ����		int
--############################################
--
-- Table structure for table `CB_HZ`
--

CREATE TABLE CB_HZ (
	NO			INTEGER				PRIMARY KEY,
	SSQ			int				NOT NULL,
	SSQ_Q			int				NOT NULL,
	SSQ_Z			int				NOT NULL,
	ZPFS			int				NOT NULL,
	ZPKPJE			Big int				NOT NULL,
	HPFS			int				NOT NULL,
	HPKPJE			Big int				NOT NULL,
	ZFFS			int				NOT NULL,
	ZFKPJE			Big int				NOT NULL,
	HFFS			int				NOT NULL,
	HFKPJE			Big int				NOT NULL,
	KBFPFS			int				NOT NULL,
	BSRQ			int				NOT NULL,
	BSCGRQ			int				NOT NULL,
	BSSBYY			varchar(100),
	BSLX			char				NOT NULL,
	BSCGBZ			char				NOT NULL,
	BSJZBZ			char				NOT NULL,
	WSCFPS			int				NOT NULL,
	UNIQUE (SSQ)
);

--
-- Dumping data for table `CB_HZ`
--
--#########��������Ա��Ϣ��###################
--#     ����			char
--#     ����			varchar(10)
--#     ����			varchar(10)     
--#     ��ɫ			char
--############################################
--
-- Table structure for table `OPERATOR`
--

CREATE TABLE OPERATOR (
	OP_ID			char			NOT NULL,
	NAME			varchar(10)		NOT NULL,
	PASSWD			varchar(10)		NOT NULL,
	ROLE			char			NOT NULL,
	PRIMARY KEY(OP_ID)
);

--
-- Dumping data for table `OPERATOR`
--

--#########����ϵͳ������־��#################	
--#   ����							INTEGER
--#   ����							int
--#		ʱ��							int     			
--#		����Ա����				varchar(10)	
--#		��������					char
--#		�������					int	
--#											varchar(20)
--############################################
--
-- Table structure for table `SYSLOG`
--

CREATE TABLE SYSLOG (
	NO       	INTEGER 		NOT NULL,
	I_DATE		int			NOT NULL,
	I_TIME		int			NOT NULL, 
	OPERATOR	varchar(10)		NOT NULL,
	TYPE		char			NOT NULL,
	RESULT		int,
	BACKUP		varchar(20),
	PRIMARY KEY(NO)
);

--
-- Dumping data for table `SYSLOG`
--


--#########����ϵͳ������#################
--#		��������			char			
--#		��������			varchar(20)		
--#		��������ֵ		int			
--#		�����ı�ֵ		varchar(64)		
--#		��������ֵ		blob			
--############################################
--
-- Table structure for table `SYSARG`
--
CREATE TABLE SYSARG (
	SA_ID			char			NOT NULL,
	NAME			varchar(20) 		NOT NULL,
	V_INT			int,
	V_TEXT			varchar(64),
	V_BLOB			BLOB,
	PRIMARY KEY(SA_ID)
);

--
-- Dumping data for table `SYSARG`
--
--#########������Ʊ�����#################	
--#     ��Ʊ����		varchar(20)
--#     ��Ʊ����			int    
--#     ��Ʊ����			int
--#			��Ʊʱ��			int              
--#     ��Ʊ����			tinyint
--#     ��Ʊ�ܽ��		big int
--#     �ϴ���־      tinyint
--#     ���ϱ�־      tinyint
--#			CAǩ��			varchar(160)
--#			�����ֶ�			varchar(20)	
--############################################
--
-- Table structure for table `INV_SERV`
--

CREATE TABLE INV_SERV ( 
	NO        INTEGER PRIMARY KEY,
--	CODE		  varchar(20)				NOT NULL,
--	INV_NO		int(11)		NOT NULL, 
	FPDM		  varchar(20)				NOT NULL,
	FPHM		int(11)		NOT NULL,     
	I_DATE		int				NOT NULL,
	I_TIME		int				NOT NULL, 
	I_TYPE		char			NOT NULL,
	M_SUM		  big int		NOT NULL,
	UP_FLAG   char      NOT NULL,
	WST_FLAG  char      NOT NULL,
	CA_SIGN   varchar(160),
	BACKUP		varchar(20)
--	UNIQUE  (CODE_NO, INV_NO)
) ;
--
-- Dumping data for table `INV_SERV`
--

--for_initProc_20150506linzihao
--#########Ʊ����Ϣ��#################	
--#     ��Ʊ���ʹ���		varchar(10)
--#     ���������գ�ÿ�µĵڼ��죩	varchar(20)
--#     ���߿���ʱ�䣨��λСʱ��	varchar(20)
--#     ���ŷ�Ʊ�޶�		big int
--#     ����������Ʊ�ۼ��޶�	big int
--#	�����ֶ�		varchar(20)	
--############################################
--
-- Table structure for table `INV_KIND`
--

CREATE TABLE INV_KIND ( 
	NO        INTEGER PRIMARY KEY,
	FPLXDM		varchar(10)		NOT NULL,	
	LX_SSR      int			NOT NULL,
	LX_KJSJ     int			NOT NULL,
	MAX_SING	big int		NOT NULL,	
	MAX_SUM	    big int		NOT NULL,	
	BACKUP		varchar(20),
	UNIQUE  (FPLXDM)
) ;

--
-- Dumping data for table `INV_KIND`
--
--#########��Ʊ��ӡ������Ϣ#################	
--#     �Զ�������1		  varchar(20)
--#     �Զ�������1			varchar(20)   
--#     �Զ�������2		  varchar(20)
--#     �Զ�������2		  varchar(20)
--#			��ע						varchar(30)              
--#			�����ֶ�			varchar(20)	
--############################################
--
-- Table structure for table `PRN_INFO`
--

CREATE TABLE PRN_INFO( 
	ZDY_TAB1		varchar(30)				,
	ZDY_CONT1		varchar(30)				,
	ZDY_TAB2		varchar(30)				,
	ZDY_CONT2		varchar(30)				,
  REMARKS     varchar(50)				,
	BACKUP		  varchar(20)
) ;
--
-- Dumping data for table `PRN_INFO`
--
--#########������ͳ����Ϣ��#############
--#     ��ʼ����       		int          
--#     ��ֹ����			int
--#     �ڳ�������        int
--#     �칺��Ʊ����		int
--#     �˻ط�Ʊ����		int          
--#     ��ĩ������		int
--#     ������Ʊ����        int
--#     ���Ϸ�Ʊ����        int
--#     ������Ʊ����        int
--#     ���Ϸ�Ʊ����        int
--#     �շϷ�Ʊ����        int
--#     ������Ʊ�ۼƽ��        int
--#     ������Ʊ�ۼ�˰��        int
--#     ���Ϸ�Ʊ�ۼƽ��        int
--#     ���Ϸ�Ʊ�ۼ�˰��        int
--#     ������Ʊ�ۼƽ��        int
--#     ������Ʊ�ۼ�˰��        int
--#     ���Ϸ�Ʊ�ۼƽ��        int
--#     ���Ϸ�Ʊ�ۼ�˰��        int
--############################################
--
-- Table structure for table `INV_SUM`
--

CREATE TABLE INV_SUM (
	NO				INTEGER PRIMARY KEY,
	QSRQ			int		NOT NULL,
	JZRQ			int		NOT NULL,
	QCKC			int		NOT NULL,
	BQXG		int		NOT NULL,
	BQTH		int		NOT NULL,
	QMKC		int		NOT NULL,
	ZSFS		int		NOT NULL,
	ZFFS		int		NOT NULL,
	FSFS		int		NOT NULL,
	FFFS		int		NOT NULL,
	KFFS		int		NOT NULL,

	ZSJE		big int		NOT NULL,
	ZSSE		big int		NOT NULL,
	ZFJE		big int		NOT NULL,
	ZFSE		big int		NOT NULL,
	FSJE		big int		NOT NULL,
	FSSE		big int		NOT NULL,
	FFJE		big int		NOT NULL,
	FFSE		big int		NOT NULL
);
--
-- Dumping data for table `INV_SUM`
--

--for_initProc_20150506linzihao
--#########˰�ʱ�###################
--#    ���          INTEGER
--#     ˰��         int
--#     ����		varchar(20)
--############################################
--
-- Table structure for table `TAX`
--
CREATE TABLE TAX(
	NO			INTEGER 		PRIMARY KEY,
	SL       	int,
	BACKUP		varchar(20)
);

--#########���������###################
--#	�Ƿ��Զ�����IP	char,
--#	����IP			varchar(20),
--#	��������		varchar(20),
--#	��������		varchar(20),
--#	DNS				varchar(20),
--#	������IP��ַ	varchar(20),
--#	�������˿ں�	varchar(6),
--#	����������·��	varchar(50),
--#	ftp��������ַ	varchar(20),
--#	ftp�˿ں�		varchar(6),
--#	�û���			varchar(16),
--#	����			varchar(16)
--############################################
CREATE TABLE NETPARA(
	ISDHCP		char,
	LOCIP		varchar(20),
	LOCGATE		varchar(20),
	LOCMASK		varchar(20),
	LOCDNS		varchar(20),
	SERVIP		varchar(20),
	SERVPORT	varchar(6),
	SERVADDR	varchar(50),
	FTPIP		varchar(20),
	FTPPORT		varchar(6),
	FTPUSER		varchar(16),
	FTPPWD		varchar(16)
);


--����������
CREATE index HEAD_NO		on 		INV_HEAD(FPDM, FPHM);
CREATE index HEAD_DATE		on 		INV_HEAD(KPRQ);
CREATE index DET_NO		on 		INV_DET(FPHM);
CREATE index DET_DATE		on 		INV_DET(KPRQ);
CREATE index DEPT_PLU	on DEPT(SP_BM);

--
-- Table structure for table `dept` 
--
INSERT INTO dept VALUES ('0000000000000001', '������Ʒ1', 10.0, 0.03, '��', 1, '001', '001', '1', 1.11, 100.0);
INSERT INTO dept VALUES ('0000000000000002', '������Ʒ2', 20.0, 0.17, '��', 2, '002', '002', '1', 1.22, 100.0);
INSERT INTO dept VALUES ('0000000000000003', '������Ʒ3', 30.0, 0.00, '��', 3, '003', '003', '1', 1.33, 100.0);


--
-- init sysarg
--
insert into sysarg values(0,'',1,'',0);
insert into sysarg values(1,'',0,'����',0);
insert into sysarg values(2,'',9600,'',0);
insert into sysarg values(3,'',9600,'',0);
insert into sysarg values(4,'',0,'',0);
insert into sysarg values(5,'',1,'',0);
insert into sysarg values(6,'',3,'',0);
insert into sysarg values(11,'',9600,'',0);

insert into sysarg values(50,'',0,'',0);
insert into sysarg values(51,'',0,'',0);
insert into sysarg values(52,'',0,'',0);
insert into sysarg values(53,'',0,'',0);
insert into sysarg values(54,'',0,'',0);
insert into sysarg values(55,'',0,'',0);
insert into sysarg values(56,'',0,'',0);
insert into sysarg values(57,'',0,'',0);
insert into sysarg values(58,'',0,'20140101020010',0);
insert into sysarg values(59,'',0,'',0);

insert into sysarg values(100,'',0,'88888888',0);
insert into sysarg values(101,'',0,'23456789',0);

--insert into sysarg values(20,'',0,'192.168.5.128',0);
--insert into sysarg values(21,'',0,'7001',0);
--insert into sysarg values(22,'',2,'',0);
--insert into sysarg values(26,'',0,'',0);
--insert into sysarg values(27,'',0,'',0);
--insert into sysarg values(32,'',1,'',0);


insert into sysarg values(201,'',1,'',0);
insert into sysarg values(202,'',10,'',0);
insert into sysarg values(203,'',0,'',0);
insert into sysarg values(204,'',0,'192.168.2.153',0);
insert into sysarg values(205,'',0,'255.255.255.0',0);
insert into sysarg values(206,'',0,'192.168.2.1',0);
insert into sysarg values(207,'',0,'192.168.204.2',0);
insert into sysarg values(208,'',0,'',0);
insert into sysarg values(209,'',0,'',0);
insert into sysarg values(210,'',1,'',0);
insert into sysarg values(211,'',0,'card',0);
insert into sysarg values(212,'',0,'card',0);
insert into sysarg values(213,'',0,'',0);
insert into sysarg values(214,'',0,'CMNET',0);
insert into sysarg values(215,'',0,'*99***1#',0);
insert into sysarg values(216,'',0,'',0);
insert into sysarg values(217,'',0,'',0);
insert into sysarg values(218,'',0,'',0);
insert into sysarg values(219,'',2,'',0);

insert into sysarg values(231,'',0,'192.168.0.104',0);
insert into sysarg values(232,'',0,'8002',0);
insert into sysarg values(233,'',0,'',0);

--
-- init Operator
--
INSERT INTO operator values(200, 'ϵͳ', '198402', '1');
INSERT INTO operator values(0, '����', '123456', '2');
INSERT INTO operator values(99, 'ѧϰ', '123456', '4');

--
-- init Machine
--
INSERT INTO machine values('222222222222', '20110101', 'hver1.0', 'sver1.0');

--
-- init TAX
-- for test 20150508_linzihao
-- INSERT INTO TAX values(1, 17, NULL);
-- INSERT INTO TAX values(2, 3, NULL);

--
-- init Client
--
--INSERT INTO client values('9', '������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾������Ϣ�ɷ����޹�˾1234567890!@#sefeted');
insert into NETPARA values(1,'192.168.2.134','192.168.2.1','255.255.255.0','','192.168.0.104','8008','','','','','');
