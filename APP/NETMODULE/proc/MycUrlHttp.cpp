#include "MycUrlHttp.h"

/************************************************************************
err
����״̬���롢״̬������˵����
1.1xx����Ϣ�������յ�����������
2.2xx���ɹ�����Ϊ���ɹ��ؽ��ܡ����Ͳ���
3.3xx���ض���Ϊ��������󣬱����һ��ִ�еĶ���
4.4xx���ͻ��˴�����������﷨������������޷�ʵ��
5.5xx�����������󣬷���������ʵ��һ��������Ч������
�±���ʾÿ����Ӧ�뼰�京�壺
100         ����
101         ���齻��Э
200         OK
201         ������
202         ������
203         ����Ȩ��Ϣ
204         ������
205         ��������
206         ��������
300         ��ѡ��
301         ���õش���
302         �ҵ�
303         �μ�����
304         δ�Ķ�
305         ʹ�ô���
307         ��ʱ�ض���
400         ��������
401         δ��Ȩ
402         Ҫ�󸶷�
403         ��ֹ
404         δ�ҵ�
405         ������ķ���
406         ��������
407         Ҫ�������Ȩ
408         ����ʱ
409         ��ͻ
410         ���ڵ�
411         Ҫ��ĳ���
412         ǰ�᲻����
413         ����ʵ��̫��
414         ����URI̫��
415         ��֧�ֵ�ý������
416         �޷����������Χ
417         ʧ�ܵ�Ԥ��
500         �ڲ�����������
501         δ��ʹ��
502         ���ش���
503         �����õķ���
504         ���س�ʱ
505         HTTP�汾δ��֧��
************************************************************************/

MemoryStruct::MemoryStruct()
{
	this->memory = NULL;
	this->size = 0;
}

WriteThis::WriteThis()
{
	this->readptr = NULL;
	this->sizeleft = 0;
}

curlconfig::curlconfig()
{
	this->proxy="";
	this->url="";
	this->username = "";
	this->userpwd = "";
	this->proxy_protocol = Proxy_protocol_NO;
	this->connect_timeout = 0;
}

static void *myrealloc(void *ptr, size_t size);

static void *myrealloc(void *ptr, size_t size)
{
  if(ptr)
    return realloc(ptr, size);
  else
    return malloc(size);
}

static size_t 
ReadMemoryCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;

  if(size*nmemb < 1)
    return 0;

  size_t res;
  if (pooh->sizeleft > 0)
  {
	  pooh->sizeleft -= nmemb;
	  if (pooh->sizeleft >= 0)
	  {
		res = nmemb;
		memcpy(ptr, pooh->readptr, res);
		pooh->readptr += res;
	  }
	  else
	  {
		res = pooh->sizeleft+nmemb;
		pooh->sizeleft = 0;
		memcpy(ptr, pooh->readptr, res);
	  }
	  
	  return res;
  }

  return 0;                          /* no more data left to deliver */
}

static size_t
GetContentParmCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
	memcpy(&(mem->memory[mem->size]), ptr, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	}
	return realsize;
}


static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;

  mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory) {
    memcpy(&(mem->memory[mem->size]), ptr, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
  }
  return realsize;
}


//TCUrlModel* TCUrlModel::g_instance_curl = NULL;


TCUrlModel::TCUrlModel()
{
	m_pcurl = NULL;
	m_pslist = NULL;
	m_chunk.memory = NULL;
	m_chunk.size = 0;
	m_strSessionId = "";
	m_cookiefile = "/usr/app/cookie.txt";
}

TCUrlModel::~TCUrlModel()
{
	this->curlCleanUp();
}

const char * TCUrlModel::get_strerror(CURLcode error)
{
	switch (error) {
	case CURLE_OK:
	return "�޴���";

	case CURLE_UNSUPPORTED_PROTOCOL:
	return "��֧�ֵ�Э��";

	case CURLE_FAILED_INIT:
	return "��ʼ��ʧ��";

	case CURLE_URL_MALFORMAT:
	return "��ַ��ʽ�Ƿ�";

	case CURLE_COULDNT_RESOLVE_PROXY:
	return "�޷�������������";

	case CURLE_COULDNT_RESOLVE_HOST:
	return "�޷�������������";

	case CURLE_COULDNT_CONNECT:
	return "�޷����ӵ�������";

	case CURLE_REMOTE_ACCESS_DENIED:
	return "�ܾ����ʵ�Զ����Դ";

	case CURLE_HTTP_RETURNED_ERROR:
	return "HTTP��Ӧ�����ʾ����";

	case CURLE_WRITE_ERROR:
	return "û���յ�������д�뵽����/Ӧ��";

	case CURLE_UPLOAD_FAILED:
	return "�ϴ�ʧ��";

	case CURLE_READ_ERROR:
	return "�޷���/��ȡ���ص������ļ�/Ӧ��";

	case CURLE_OUT_OF_MEMORY:
	return "�ڴ治��";

	case CURLE_OPERATION_TIMEDOUT:
	return "��ʱ";

	case CURLE_RANGE_ERROR:
	return "���󳬳��˷������ṩ�ķ�Χ";

	case CURLE_BAD_DOWNLOAD_RESUME:
	return "���ָܻ�����";

	case CURLE_TOO_MANY_REDIRECTS :
	return "�ض���ﵽ�����";

	case CURLE_GOT_NOTHING:
	return "�����������ޱ��⣬������";

	case CURLE_SEND_ERROR:
	return "��������ʧ��";

	case CURLE_RECV_ERROR:
	return "��������ʧ��";

	case CURLE_BAD_CONTENT_ENCODING:
	return "�޷�ʶ���HTTP���ݱ���";

	case CURLE_LOGIN_DENIED:
	return "��¼ʧ��";

	case CURLE_AGAIN:
	return "Socketû��׼���÷���/����";

	/* error codes not used by current libcurl */
	default:
	break;
	}
	return curl_easy_strerror(error);
}

int TCUrlModel::curlInit()
{
	m_pcurl = curl_easy_init();
	if (NULL == m_pcurl)
	{
		return -1;
	}
	
	return 0;
}

void TCUrlModel::curlCleanUp()
{
	if (m_chunk.memory)
	{
		free(m_chunk.memory);
		m_chunk.memory = NULL;
	}
	m_chunk.size = 0;
	
	if (m_pslist)
	{
		curl_slist_free_all(m_pslist);
		m_pslist = NULL;
	}

	if (m_pcurl)
	{
		curl_easy_cleanup(m_pcurl);
		m_pcurl = NULL;
	}	
	
	return;
}

void TCUrlModel::SetCurlConfig(curlconfig config)
{
	this->m_curlconfig = config;
}

int TCUrlModel::dogetbuff(string &errstr)
{
	errstr = "";
	
	curlCleanUp();
	if (0 != curlInit())
	{
		errstr="CURL��ʼ��ʧ��!";
		return -1;
	}
	
	if (0 != curlSetOpt(errstr, NULL))
	{
		curlCleanUp();
		return -1;
	}
	
	CURLcode res = curl_easy_perform(m_pcurl);
	if (0 != procCurlRes(errstr, res))
	{
		errstr += ",�����������ò���������!";
		curlCleanUp();
		return -1;
	}
	
	if (m_chunk.size <= 0)
	{
		errstr = "�������ݳ���Ϊ��!";
		curlCleanUp();
		return -1;
	}
	
	return 0;
}

int TCUrlModel::dogetbuff(OUT unsigned char *outBuf, IN OUT int& outBufLen, string &errstr)
{
	errstr = "";
	
	curlCleanUp();
	if (0 != curlInit())
	{
		errstr="CURL��ʼ��ʧ��!";
		return -1;
	}

	if (0 != curlSetOpt(errstr, NULL))
	{
		curlCleanUp();
		return -1;
	}

	CURLcode res = curl_easy_perform(m_pcurl);
	if (0 != procCurlRes(errstr, res))
	{
		errstr += ",�����������ò���������!";
		curlCleanUp();
		return -1;
	}

	if (m_chunk.size <= 0)
	{
		errstr = "�������ݳ���Ϊ��!";
		curlCleanUp();
		return -1;
	}

	if (outBufLen <= 0 || m_chunk.size > (size_t)(outBufLen-1))
	{
		errstr = "�������ݳ��ȴ�С�����������ݳ��ȴ�С!";
		curlCleanUp();
		return -1;
	}

	outBufLen = m_chunk.size;
	memcpy(outBuf, m_chunk.memory, m_chunk.size);
	outBuf[outBufLen] = '\0';

	return 0;
}

int  TCUrlModel::SetSessionID(string& strSessionID)
{
	if(strSessionID.empty())
	{
		m_strSessionId = "";
		return 0;
	}
	char buf[1024];
	memset(buf,sizeof(buf),0);
	sprintf(buf,"JSESSIONID=%s\r\n", strSessionID.c_str());
	m_strSessionId = buf;
	return 0;
}

//��ȡsessionid
bool  TCUrlModel::GetSessionID(string& strSessionID)
{
	return 0;
}

//��ȡcookie�ļ�����
string TCUrlModel::GetCookieFileName()
{
	return this->m_cookiefile;
}
//
int  TCUrlModel::getValue(char *sheader,char *sKeyWord,char* sValue)
{
	char * cont_len_pos=NULL;  
	unsigned long cont_length=0;  
	const char* header = sheader;  
	
	cont_len_pos =(char *)strstr(header,sKeyWord);  
	if(cont_len_pos == NULL)
	{
		//		 DBG_ASSERT_WARNING(false,("not found %s: !",sKeyWord));
		return -1;
	}
	char* pTmp  = (char *)strchr(cont_len_pos,';');  
	//     cont_len_pos++;  
	//    sscanf(cont_len_pos, "%ld", &cont_length);  
	cont_length = strlen(cont_len_pos)-strlen(pTmp)-strlen(sKeyWord);
	memcpy((void*)sValue,(void*)&cont_len_pos[strlen(sKeyWord)],cont_length);
	// sValue = cont_len_pos -sValue;
	return cont_length;  
}


int TCUrlModel::curlSetOpt(string &errstr, struct WriteThis *pooh)
{
	errstr = "";
	if (m_curlconfig.url.length() <= 0)
	{
		errstr = "URL����Ϊ��!";
		return -1;
	}
	//����cookie 
	curl_easy_setopt(m_pcurl, CURLOPT_COOKIE,m_strSessionId.c_str());
	curl_easy_setopt(m_pcurl, CURLOPT_COOKIEJAR, m_cookiefile.c_str());		//����	
	curl_easy_setopt(m_pcurl, CURLOPT_COOKIEFILE, m_cookiefile.c_str());	//����

	/* First set the URL that is about to receive our POST. */
	curl_easy_setopt(m_pcurl, CURLOPT_URL,m_curlconfig.url.c_str());

	if (pooh != NULL)
	{
		/* Now specify we want to POST data */
		curl_easy_setopt(m_pcurl, CURLOPT_POST, 1L);
	}	

	if (m_curlconfig.proxy.length() != 0
		&& m_curlconfig.proxy_protocol != Proxy_protocol_NO)
	{
		curl_easy_setopt(m_pcurl, CURLOPT_PROXY, m_curlconfig.proxy.c_str());
			
		if (m_curlconfig.proxy_protocol == Proxy_protocol_HTTP)
		{
			//curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1);
			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
		}
		else if(m_curlconfig.proxy_protocol == Proxy_protocol_SOCKS5)
		{
			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
		}			
		else
		{
			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
		}
		char tmpuserpwdbuff[512];
		if (m_curlconfig.username.length() != 0)
 		{
			sprintf(tmpuserpwdbuff, "%s:%s", m_curlconfig.username.c_str(), m_curlconfig.userpwd.c_str());
			curl_easy_setopt(m_pcurl, CURLOPT_PROXYUSERPWD, tmpuserpwdbuff);
	  	}	
		else
		{
			if(m_curlconfig.proxy_protocol == Proxy_protocol_SOCKS5)
			{
				sprintf(tmpuserpwdbuff, "%s",":");
				curl_easy_setopt(m_pcurl, CURLOPT_PROXYUSERPWD, tmpuserpwdbuff);
			}
		}	
	}

	if (NULL != pooh)
	{
		/* �ϴ�����*/
		/* we want to use our own read function */
		curl_easy_setopt(m_pcurl, CURLOPT_READFUNCTION, ReadMemoryCallback);
		/* pointer to pass to our read function */
		curl_easy_setopt(m_pcurl, CURLOPT_READDATA, pooh);
		/* Set the expected POST size. If you want to POST large amounts of data,
		   consider CURLOPT_POSTFIELDSIZE_LARGE */
		curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE, (curl_off_t)pooh->sizeleft);
	}

	/*ȡ���ص�����*/
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, (void *)&m_chunk);

	/* get verbose debug output please */
	curl_easy_setopt(m_pcurl, CURLOPT_VERBOSE, 1L);

	if (0 != m_curlconfig.connect_timeout)
	{
		//curl_easy_setopt(m_pcurl, CURLOPT_CONNECTTIMEOUT, m_curlconfig.connect_timeout);
	//	curl_easy_setopt(m_pcurl, CURLOPT_TIMEOUT, m_curlconfig.connect_timeout*10);
		curl_easy_setopt(m_pcurl,CURLOPT_TIMEOUT,PROCTIMEOUT);
	}
	curl_easy_setopt(m_pcurl, CURLOPT_CONNECTTIMEOUT, CONNECT_TIME_OUT);

	m_pslist = curl_slist_append(m_pslist, "Content-Type:application/octet-stream;charset=gb18030"); 
	curl_easy_setopt(m_pcurl, CURLOPT_HTTPHEADER, m_pslist); 

	return 0;
}

int TCUrlModel::procCurlRes(string& errstr, CURLcode res)
{

	errstr = "";
	if (res == CURLE_OK)
	{
		long response;char errbuff[128];
		//δʹ�ô���
		curl_easy_getinfo(m_pcurl, CURLINFO_RESPONSE_CODE, &response);
		//ʹ�ô���ȡ��
		//curl_easy_getinfo(m_pcurl, CURLINFO_HTTP_CONNECTCODE, &response);
		switch(response/100)
		{
		case 1: 
			sprintf(errbuff, "%ld-��Ϣ�������յ�����������", response);
			errstr = errbuff;
			break;
		case 2:
			sprintf(errbuff, "%ld-�ɹ�����Ϊ���ɹ��ؽ��ܡ����Ͳ���", response);
			errstr = errbuff;
			break;
		case 3:
			sprintf(errbuff, "%ld-�ض���Ϊ��������󣬱����һ��ִ�еĶ���", response);
			errstr = errbuff;
			break;
		case 4:
			sprintf(errbuff, "%ld-�ͻ��˴�����������﷨������������޷�ʵ��", response);
			errstr = errbuff;
			break;
		case 5:
			sprintf(errbuff, "%ld-���������󣬷���������ʵ��һ��������Ч������", response);
			errstr = errbuff;
			break;
		default:
			sprintf(errbuff, "%ld-��������", response);
			errstr = errbuff;
			break;
		}
		
		if (200 != response)
		{
			return -1;
		}
	}
	else
	{
		string err(get_strerror(res));
		errstr = err;
		return -1;
	}

	return 0;
}

int TCUrlModel::dopostbuff(IN unsigned char *postBuf, IN int postBufLen, string &errstr)
{
	struct WriteThis postbuff;
	postbuff.readptr = (char *)postBuf;
	postbuff.sizeleft = postBufLen;
	
	errstr = "";
	
	curlCleanUp();
	if (0 != curlInit())
	{
		errstr="CURL��ʼ��ʧ��!";
		return -1;
	}
	
	if (0 != curlSetOpt(errstr, &postbuff))
	{
		curlCleanUp();
		return -1;
	}
	
	CURLcode res = curl_easy_perform(m_pcurl);
	if (0 != procCurlRes(errstr, res))
	{
		errstr += ",�����������ò���������!";
		curlCleanUp();
		return -1;
	}
	if (m_chunk.size <= 0)
	{
		errstr = "�������ݳ���Ϊ��!";
		curlCleanUp();
		return -1;
	}
	
	return 0;
}

int TCUrlModel::dopostbuff(IN unsigned char *postBuf, IN int postBufLen,
		OUT unsigned char *outBuf, IN OUT int outBufLen, string &errstr)
{
	struct WriteThis postbuff;
	postbuff.readptr = (char *)postBuf;
	postbuff.sizeleft = postBufLen;

	errstr = "";
	
	curlCleanUp();
	if (0 != curlInit())
	{
		errstr="CURL��ʼ��ʧ��!";
		return -1;
	}
	
	if (0 != curlSetOpt(errstr, &postbuff))
	{
		curlCleanUp();
		return -1;
	}
	
	CURLcode res = curl_easy_perform(m_pcurl);
	if (0 != procCurlRes(errstr, res))
	{
		errstr += ",�����������ò���������!";
		curlCleanUp();
		return -1;
	}
	
	if (m_chunk.size > outBufLen-1 || m_chunk.size <= 0)
	{
		errstr = "���ݳ��ȷǷ�";
		curlCleanUp();
		return -1;
	}
	
	outBufLen = m_chunk.size;
	memcpy(outBuf, m_chunk.memory, m_chunk.size);
	outBuf[outBufLen] = '\0';
	
	return 0;
}

// int TCUrlModel::dopostbuff(void *pconfig)
// {
// 	CURLcode res;
// 	struct WriteThis pooh;
// 	bool errflag = false;
// 
// 	curlconfig *config_p = (curlconfig *)pconfig;
// 	config_p->res = 0;
// 	config_p->resstr="";
// 
// 	curlCleanUp();
// 	if (0 != curlInit())
// 	{
// 		config_p->resstr="CURL��ʼ��ʧ��!";
// 		return -1;
// 	}
// 
// 	pooh.readptr = config_p->m_writeThis.readptr;
// 	pooh.sizeleft = config_p->m_writeThis.sizeleft;
// 
// 	/* First set the URL that is about to receive our POST. */
// 	curl_easy_setopt(m_pcurl, CURLOPT_URL,config_p->url.c_str());
// 	/* Now specify we want to POST data */
// 	curl_easy_setopt(m_pcurl, CURLOPT_POST, 1L);
// 
// 	if (config_p->proxy.length() != 0
// 		&& config_p->proxy_protocol != Proxy_protocol_NO)
// 	{
// 		curl_easy_setopt(m_pcurl, CURLOPT_PROXY, config_p->proxy.c_str());
// 			
// 		if (config_p->proxy_protocol == Proxy_protocol_HTTP)
// 		{
// 			//curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1);
// 			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
// 		}
// 		else if(config_p->proxy_protocol == Proxy_protocol_SOCKS5)
// 		{
// 			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
// 		}			
// 		else
// 		{
// 			curl_easy_setopt(m_pcurl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
// 		}
// 		char tmpuserpwdbuff[512];
// 		if (config_p->username.length() != 0)
//  		{
// 			sprintf(tmpuserpwdbuff, "%s:%s", config_p->username.c_str(), config_p->userpwd.c_str());
// 			//sprintf(tmpuserpwdbuff, "%s:", config_p->username.c_str());
// 			curl_easy_setopt(m_pcurl, CURLOPT_PROXYUSERPWD, tmpuserpwdbuff);
// 	  	}	
// 		else
// 		{
// 			if(config_p->proxy_protocol == Proxy_protocol_SOCKS5)
// 			{
// 				sprintf(tmpuserpwdbuff, "%s",":");
// 				curl_easy_setopt(m_pcurl, CURLOPT_PROXYUSERPWD, tmpuserpwdbuff);
// 			}
// 		}	
// 	}
// 
// 	m_pslist = curl_slist_append(m_pslist, "Content-Type:application/octet-stream;charset=gb18030"); 
// 	curl_easy_setopt(m_pcurl, CURLOPT_HTTPHEADER, m_pslist); 
// 
// 	/* �ϴ�����*/
// 	/* we want to use our own read function */
// 	curl_easy_setopt(m_pcurl, CURLOPT_READFUNCTION, ReadMemoryCallback);
// 	/* pointer to pass to our read function */
// 	curl_easy_setopt(m_pcurl, CURLOPT_READDATA, &pooh);
// 
// 	/*ȡ���ص�����*/
// 	curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
// 	curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, (void *)&m_chunk);
// 
// 	/* get verbose debug output please */
// 	curl_easy_setopt(m_pcurl, CURLOPT_VERBOSE, 1L);
// 
// 	/* Set the expected POST size. If you want to POST large amounts of data,
// 	   consider CURLOPT_POSTFIELDSIZE_LARGE */
// 	curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE, (curl_off_t)pooh.sizeleft);
// 
// 
// 	/* Perform the request, res will get the return code */
// 	res = curl_easy_perform(m_pcurl);
// 
// 	if (res == CURLE_OK)
// 	{
// 		long response;char errbuff[128];
// 		//δʹ�ô���
// 		curl_easy_getinfo(m_pcurl, CURLINFO_RESPONSE_CODE, &response);
// 		//ʹ�ô���ȡ��
// 		//curl_easy_getinfo(m_pcurl, CURLINFO_HTTP_CONNECTCODE, &response);
// 		config_p->res = response;
// 		
// 		switch(response/100)
// 		{
// 		case 1: 
// 			sprintf(errbuff, "%ld-��Ϣ�������յ�����������", response);
// 			config_p->resstr = errbuff;
// 			break;
// 		case 2:
// 			sprintf(errbuff, "%ld-�ɹ�����Ϊ���ɹ��ؽ��ܡ����Ͳ���", response);
// 			config_p->resstr = errbuff;
// 			break;
// 		case 3:
// 			sprintf(errbuff, "%ld-�ض���Ϊ��������󣬱����һ��ִ�еĶ���", response);
// 			config_p->resstr = errbuff;
// 			break;
// 		case 4:
// 			sprintf(errbuff, "%ld-�ͻ��˴�����������﷨������������޷�ʵ��", response);
// 			config_p->resstr = errbuff;
// 			break;
// 		case 5:
// 			sprintf(errbuff, "%ld-���������󣬷���������ʵ��һ��������Ч������", response);
// 			config_p->resstr = errbuff;
// 			break;
// 		default:
// 			sprintf(errbuff, "%ld-��������", response);
// 			config_p->resstr = errbuff;
// 		  break;
// 		}
// 
// 		if (200 != response)
// 		{
// 			errflag = true;
// 			goto err_end;
// 		}
// 	}
// 	else
// 	{
// 		string err(get_strerror(res));
// 		config_p->resstr = err;errflag = true;
// 		goto err_end;
// 	}
// 
// 	if (m_chunk.size > G_RESBUFF_LEN || m_chunk.size <= 0)
// 	{
// 		config_p->resstr = "���ݳ��ȷǷ�";
// 		errflag = true;
// 	}
// 	else
// 	{
// 		//////////////////////////////////////////////////////////////////////////
// 		//�����ָ����ô���ͷ�Ȼ��������
// 		//////////////////////////////////////////////////////////////////////////
// 		
// 		config_p->m_writeThis.sizeleft = m_chunk.size>(G_RESBUFF_LEN-1)?(G_RESBUFF_LEN-1):m_chunk.size;
// 		memcpy(config_p->m_writeThis.readptr, m_chunk.memory, config_p->m_writeThis.sizeleft);
// 		config_p->m_writeThis.readptr[config_p->m_writeThis.sizeleft] = '\0';
// 	}
// 	
// err_end:
//  	if(m_chunk.memory)
// 	{
// 		free(m_chunk.memory);
// 		m_chunk.memory = NULL;
// 	}
// 	
// 	/* always cleanup */
// 	curl_slist_free_all(m_pslist);
// 	curl_easy_cleanup(m_pcurl);
// 	m_pslist = NULL;
//  	m_pcurl = NULL;
// 	if (errflag)
// 	{
// 		config_p->resstr += ",�����������ò���������!";
// 		return -1;
// 	}
// 
// 	return 0;
// }

//////////////////////////////////////////////////////////////////////////
/*
 * Parse URL and fill in the relevant members of the connection struct.
 */
//static CURLcode ParseURLAndFillConnection(struct SessionHandle *data,
//                                          struct connectdata *conn)
//{
//  char *at;
//  char *tmp;
//  char *path = data->state.path;
//  int rc;
//
//  /*************************************************************
//   * Parse the URL.
//   *
//   * We need to parse the url even when using the proxy, because we will need
//   * the hostname and port in case we are trying to SSL connect through the
//   * proxy -- and we don't know if we will need to use SSL until we parse the
//   * url ...
//   ************************************************************/
//  if((2 == sscanf(data->change.url, "%15[^:]:%[^\n]",
//                  conn->protostr,
//                  path)) && Curl_raw_equal(conn->protostr, "file")) {
//    if(path[0] == '/' && path[1] == '/') {
//      /* Allow omitted hostname (e.g. file:/<path>).  This is not strictly
//       * speaking a valid file: URL by RFC 1738, but treating file:/<path> as
//       * file://localhost/<path> is similar to how other schemes treat missing
//       * hostnames.  See RFC 1808. */
//
//      /* This cannot be done with strcpy() in a portable manner, since the
//         memory areas overlap! */
//      memmove(path, path + 2, strlen(path + 2)+1);
//    }
//    /*
//     * we deal with file://<host>/<path> differently since it supports no
//     * hostname other than "localhost" and "127.0.0.1", which is unique among
//     * the URL protocols specified in RFC 1738
//     */
//    if(path[0] != '/') {
//      /* the URL included a host name, we ignore host names in file:// URLs
//         as the standards don't define what to do with them */
//      char *ptr=strchr(path, '/');
//      if(ptr) {
//        /* there was a slash present
//
//           RFC1738 (section 3.1, page 5) says:
//
//           The rest of the locator consists of data specific to the scheme,
//           and is known as the "url-path". It supplies the details of how the
//           specified resource can be accessed. Note that the "/" between the
//           host (or port) and the url-path is NOT part of the url-path.
//
//           As most agents use file://localhost/foo to get '/foo' although the
//           slash preceding foo is a separator and not a slash for the path,
//           a URL as file://localhost//foo must be valid as well, to refer to
//           the same file with an absolute path.
//        */
//
//        if(ptr[1] && ('/' == ptr[1]))
//          /* if there was two slashes, we skip the first one as that is then
//             used truly as a separator */
//          ptr++;
//
//        /* This cannot be made with strcpy, as the memory chunks overlap! */
//        memmove(path, ptr, strlen(ptr)+1);
//      }
//    }
//
//    strcpy(conn->protostr, "file"); /* store protocol string lowercase */
//  }
//  else {
//    /* clear path */
//    path[0]=0;
//
//    if(2 > sscanf(data->change.url,
//                   "%15[^\n:]://%[^\n/]%[^\n]",
//                   conn->protostr,
//                   conn->host.name, path)) {
//
//      /*
//       * The URL was badly formatted, let's try the browser-style _without_
//       * protocol specified like 'http://'.
//       */
//      if(1 > (rc = sscanf(data->change.url, "%[^\n/]%[^\n]",
//                          conn->host.name, path)) ) {
//        /*
//         * We couldn't even get this format.
//         * djgpp 2.04 has a sscanf() bug where 'conn->host.name' is
//         * assigned, but the return value is EOF!
//         */
//#if defined(__DJGPP__) && (DJGPP_MINOR == 4)
//        if (!(rc == -1 && *conn->host.name))
//#endif
//        {
//          failf(data, "<url> malformed");
//          return CURLE_URL_MALFORMAT;
//        }
//      }
//
//      /*
//       * Since there was no protocol part specified, we guess what protocol it
//       * is based on the first letters of the server name.
//       */
//
//      /* Note: if you add a new protocol, please update the list in
//       * lib/version.c too! */
//
//      if(checkprefix("FTP.", conn->host.name))
//        strcpy(conn->protostr, "ftp");
//      else if(checkprefix("DICT.", conn->host.name))
//        strcpy(conn->protostr, "DICT");
//      else if(checkprefix("LDAP.", conn->host.name))
//        strcpy(conn->protostr, "LDAP");
//      else {
//        strcpy(conn->protostr, "http");
//      }
//
//      conn->protocol |= PROT_MISSING; /* not given in URL */
//    }
//  }
//
//  /* We search for '?' in the host name (but only on the right side of a
//   * @-letter to allow ?-letters in username and password) to handle things
//   * like http://example.com?param= (notice the missing '/').
//   */
//  at = strchr(conn->host.name, '@');
//  if(at)
//    tmp = strchr(at+1, '?');
//  else
//    tmp = strchr(conn->host.name, '?');
//
//  if(tmp) {
//    /* We must insert a slash before the '?'-letter in the URL. If the URL had
//       a slash after the '?', that is where the path currently begins and the
//       '?string' is still part of the host name.
//
//       We must move the trailing part from the host name and put it first in
//       the path. And have it all prefixed with a slash.
//    */
//
//    size_t hostlen = strlen(tmp);
//    size_t pathlen = strlen(path);
//
//    /* move the existing path plus the zero byte forward, to make room for
//       the host-name part */
//    memmove(path+hostlen+1, path, pathlen+1);
//
//     /* now copy the trailing host part in front of the existing path */
//    memcpy(path+1, tmp, hostlen);
//
//    path[0]='/'; /* prepend the missing slash */
//
//    *tmp=0; /* now cut off the hostname at the ? */
//  }
//  else if(!path[0]) {
//    /* if there's no path set, use a single slash */
//    strcpy(path, "/");
//  }
//
//  /* If the URL is malformatted (missing a '/' after hostname before path) we
//   * insert a slash here. The only letter except '/' we accept to start a path
//   * is '?'.
//   */
//  if(path[0] == '?') {
//    /* We need this function to deal with overlapping memory areas. We know
//       that the memory area 'path' points to is 'urllen' bytes big and that
//       is bigger than the path. Use +1 to move the zero byte too. */
//    memmove(&path[1], path, strlen(path)+1);
//    path[0] = '/';
//  }
//
//  if (conn->host.name[0] == '[') {
//    /* This looks like an IPv6 address literal.  See if there is an address
//       scope.  */
//    char *percent = strstr (conn->host.name, "%25");
//    if (percent) {
//      char *endp;
//      unsigned long scope = strtoul (percent + 3, &endp, 10);
//      if (*endp == ']') {
//        /* The address scope was well formed.  Knock it out of the hostname.  */
//        memmove(percent, endp, strlen(endp)+1);
//        if (!data->state.this_is_a_follow)
//          /* Don't honour a scope given in a Location: header */
//          conn->scope = (unsigned int)scope;
//      } else
//        infof(data, "Invalid IPv6 address format\n");
//    }
//  }
//
//  if (data->set.scope)
//    /* Override any scope that was set above.  */
//    conn->scope = data->set.scope;
//
//  /*
//   * So if the URL was A://B/C,
//   *   conn->protostr is A
//   *   conn->host.name is B
//   *   data->state.path is /C
//   */
//  (void)rc;
//  return CURLE_OK;
// }
