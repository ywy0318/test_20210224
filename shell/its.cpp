#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/time.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define TIME 1
#ifdef __cplusplus
extern "C"{
#endif //
//#include "reccommondefine.h"
//#include "trade_public_def.h"
#include "libvfs.h"
#include "libtdfs.h"
#include "DbBusiness.h"
//#include "libstdfs.h"
#include "vfs.h"
#define FEDOG 1
#if FEDOG
#define PICESECNUM 5 //per second insert count
//#define DISKTAILCOUNT 153600
#define DISKTAILCOUNT 10

//????ͷ????
#define CMDHEAD1    0xfe
#define CMDHEAD2    0xfc
#define CMDHEAD3    0xfb
#define COM_IDEN_SET_DEV_NO         0x85        //?????�??
#define COM_DEV         "/dev/fpcom"
#define COM_SPEED           9600
static volatile bool g_blFpFlg = false;
static int g_iComErrCnt = 0;

//????ι???�??
typedef struct
{
    unsigned char m_ucCmdHeand1;    //??????0xfe
    unsigned char m_ucCmdHeand2;    //??????0xfc
    unsigned char m_ucCmdHeand3;    //??????0xfb
    unsigned char m_ucIdentifier;   //??ʶ??
    unsigned char m_Code1;          //??ֵ??һ???ֽ?
    unsigned char m_Code2;          //??ֵ?ڶ????ֽ?
    unsigned char m_Code3;          //??ֵ???????ֽ?
    unsigned char m_Checkout;       //У???ֽ?
} TComProtocol;
static void GuiFrontPanelPduProc(const TComProtocol *_pArg);

typedef struct
{
    char* m_pu8Dev;     //?????豸ȫ�??
    int m_iFdCom;           //?򿪴????�???ļ?????
    int m_iSpeed;           //???ڲ?????
    int m_iDatabits;        //????????λ
    int m_iParity;          //????У??λ
    int m_iStopbits;        //????ֹͣλ

    void (*PduProc)(const TComProtocol *_ptPdu);

} TComOpt;

static TComOpt GUIComCommand = {
GUIComCommand.m_pu8Dev   = (char *)COM_DEV,  //?????豸ȫ�??
GUIComCommand.m_iFdCom   = -1,        //?򿪴????�???ļ?????
GUIComCommand.m_iSpeed   = COM_SPEED,    //???ڲ?????
GUIComCommand.m_iDatabits    = 8,        //????????λ
GUIComCommand.m_iParity  = 'n',
GUIComCommand.m_iStopbits    = 1,
GUIComCommand.PduProc        = GuiFrontPanelPduProc,
};

#endif
#ifdef __cplusplus
}
#endif

#include "TdDatabase.h"
#include "DbBusiness.h"
#include "TdDatabaseC.h"

using namespace std;
//ȫ?ֱ?��
//ͼƬbuf?ͳ???
char *cpPicBuf = NULL; int iPicLen =0;
char *cpFaceBuf = NULL; int iFaceLen =0;
char *cpPlateBuf = NULL; int iPlateLen =0;
//??????��
int iCountTmp = 0, iTimeTmp = 0;
int ifailCount[4] = {0};
long long iInsertCount[4] = {0};

int iStreamfailCount = 0;
int iStreamSucessCount = 0;
int iStreamopenCount = 0;
int iStreamwriteCount = 0;
struct timeval strTime[4];
int iTimeCount = 0;
pthread_t its_testid[4][4];

char g_cStreamPath[64];

//???ݿ?????
CTdDatabase* g_pDb = NULL;
//int iChanlNo[8] = {0, 1, 2, 3, 4, 5, 6, 7};
typedef struct 
{
    char cPath[64];
    int iChanlNo;
    int iTimeNo;
}TestStruct;
#if FEDOG
/*-----------------------------------------------------------
  * ????ԭ??: td_u8 BytesXOR(TComProtocol _stBuff)
  * ????????: _stBuff----????ͨѶЭ????һ??????
  * ????????: ????ǰ?߸??ֽڵ?????????
  * ????????: ??_stBuffǰ?߸??ֽڵ?????ֵ
  2008-12-06 ?????????ĺ???????ֵ????Ϊָ?�??
*---------------------------------------------------------*/
unsigned char BytesXOR(const TComProtocol *_stBuff)
{
    unsigned char ucTemp;

    ucTemp  = _stBuff->m_ucCmdHeand1;
    ucTemp ^= _stBuff->m_ucCmdHeand2;
    ucTemp ^= _stBuff->m_ucCmdHeand3;
    ucTemp ^= _stBuff->m_ucIdentifier;
    ucTemp ^= _stBuff->m_Code1;
    ucTemp ^= _stBuff->m_Code2;
    ucTemp ^= _stBuff->m_Code3;

    return ucTemp;
}
static void GuiFrontPanelPduProc(const TComProtocol *_pArg)
{
    return ;
}

static void ComWriteData(int _iFid, const void *_pData, int _iSize)
{
    int iCnt = 0;

    if(_iFid < 1)
        return ;
    while (g_blFpFlg && iCnt++ < 50000)
    {
        usleep(100 * 1000);
    }
    g_blFpFlg = true;
    iCnt = write(_iFid, _pData, _iSize);
    g_blFpFlg = false;
    if (iCnt != _iSize)
    {
        g_iComErrCnt++;
    }
    else
    {
        g_iComErrCnt = 0;
    }
}

void* SetDevNoToFP(void* _iDevNo)
{
    TComProtocol stComDataBuff;
    unsigned short usDevNo = *(unsigned short*)_iDevNo;
  //  TFpComEnableCmdStatMsg * pFpComEnableCmdStatMsg = g_ptGuiFpStatusMsg;
/*
    if(pFpComEnableCmdStatMsg->m_cFpComEnableCmdStat == GUI_FP_UPSTAT_FREE
    || pFpComEnableCmdStatMsg->m_cFpComEnableCmdStat == GUI_FP_UPSATA6) // ??Ƭ???ǹر?״̬
    {
        //dbgprintf("Dev to Fp heart beat..........................\n");
*/   
    while(1)
    {
        stComDataBuff.m_ucCmdHeand1 = CMDHEAD1;
        stComDataBuff.m_ucCmdHeand2 = CMDHEAD2;
        stComDataBuff.m_ucCmdHeand3 = CMDHEAD3;
        stComDataBuff.m_ucIdentifier = COM_IDEN_SET_DEV_NO;
        stComDataBuff.m_Code1       = usDevNo / 256;
        stComDataBuff.m_Code2       = usDevNo % 256;
        stComDataBuff.m_Code3       = 0x00;
        stComDataBuff.m_Checkout    = BytesXOR(&stComDataBuff);

        // pthread_mutex_lock(&g_tFpMutex);

        ComWriteData(GUIComCommand.m_iFdCom, &stComDataBuff, sizeof(stComDataBuff));
        usleep(60*2);
    }

        printf("GUIComCommand.m_iFdCom=%d usDevNo =%d\n", GUIComCommand.m_iFdCom, usDevNo);
       /*  pthread_mutex_unlock(&g_tFpMutex);
   }*/
   
return NULL;
}

static int OpenComDev(const char *_pcDev)
{
    int fd = open(_pcDev, O_RDWR);      //| O_NOCTTY | O_NDELAY

    if (fd < 0)
    {
        return -1;
    }
    else
    {
        return fd;
    }
}

#endif
int disk_AtoI(char a)
{
    if(a >= '0' && a <= '9' )
    {
        return a - '0';
    }
    else if(a >= 'a' && a <= 'z')
    {
        return a - 'a' + 10;
    }
    else if(a >= 'A' && a <= 'Z')
    {
        return a - 'A' + 10;
    }
    return 0;
}
void Free_Value()
{   
    if (cpFaceBuf != NULL)
    {
        free(cpFaceBuf);    
        cpFaceBuf = NULL;
    }
    if (cpPicBuf != NULL)
    {
        free(cpPicBuf);    
        cpPicBuf = NULL;
    }
    if (cpPlateBuf != NULL)
    {
        free(cpPlateBuf);    
        cpPlateBuf = NULL;
    }
    return ;
}


int getImage(int iclass, char *cStreamPath, TestStruct *_pTestParm, int _iCaptureTime)
{
	
    int iRet = 0;
    int iFd = 0;
    char cTmp[64] = "\0";
    TTFileParam stTTParam = {0};
    //vfs_open????
	struct timeb tbTime = {0};
    (void)ftime(&tbTime);
    stTTParam.m_eType = TD_FILE_TYPE_PICSTREAM;
    stTTParam.m_iChn = _pTestParm->iChanlNo;//stGetPathPara.m_iChn;
    stTTParam.m_iCustomType = tbTime.millitm / 10;
    stTTParam.m_iPreSize = 0;
    stTTParam.m_iTime = _iCaptureTime;
    strcpy(stTTParam.m_cExtName, "jpg");
    stTTParam.m_iParam = 1;
    memcpy(stTTParam.m_cBlockDevPath, _pTestParm->cPath, sizeof(_pTestParm->cPath));
	printf("%s (%d) before vfs_Open... \n",__FUNCTION__, __LINE__);
    iFd = vfs_Open(&stTTParam, cTmp, O_WRONLY|O_CREAT );
    if(iFd < 0)
    {
        iStreamopenCount++;
        iRet = -1;
        goto LEAVE;
    }
	printf("%s (%d) before vfs_Write... \n",__FUNCTION__, __LINE__);
	iRet = vfs_Write(iFd, cpPicBuf, iPicLen);
	if (iRet <= 0)
    {
        iStreamwriteCount++;
        iRet = -1;
        goto LEAVE;
    }
	printf("%s (%d) vfs_Write success... \n",__FUNCTION__, __LINE__);
LEAVE:
    iRet = vfs_Close( iFd);
    if(iRet != 0)
    {
        iRet = -1;
        iFd = 0;
        return iRet;
    }
    iFd = 0;
    //????·??

    if(iRet == 0 && cTmp[0] != '\0')
    {
        memcpy(cStreamPath, cTmp, sizeof(cTmp)-1);
        
        iStreamSucessCount++;
    }
    else
        iStreamfailCount++;

    return iRet;
}
int nvr_test(CTdDatabase *_pDb, DbHandle handle, TestStruct *_pTestParm)
{
	TWriteParaInsertFace paras;
	string str_for_cStreamPath;
	memset(&paras, 0, sizeof(TWriteParaInsertFace));
    struct timeval tv_time_data, testTime;
	int i = 0;
    time_t time;
    struct tm stm;
    int iPicNum = 1;
	paras.m_eWriteType=DB_WRITE_INSERT_FACE;
	paras.m_iDiskId=0;
	
	paras.m_iChannelNo=1;
	paras.m_iFileIndex=33;
	paras.m_iFileTime=1565609244;	
	
	paras.m_iBigSize=33;
	paras.m_iLitSize=1;	
	paras.m_iLitId=0;
	
	
	paras.m_iAge=33;
	paras.m_iSex=1;
	paras.m_iRace=0;
	
	paras.m_iBaseSize=33;
	paras.m_iSimilarity=0;
	paras.m_iAlarmType=0;
	
	paras.m_iGlass=1;
	paras.m_iNative=0;

	paras.m_iIDtype=0;
	
	paras.m_iMask=0;
	paras.m_llLibID=33;
	paras.m_llBaseFaceID=1;
	
	paras.m_iReserveInt1=0;
	paras.m_iReserveInt2=0;
	
	strncpy(paras.m_cBigName, "pic", sizeof("pic"));	
	strncpy(paras.m_cLitName, "pic", sizeof("pic"));	
	strncpy(paras.m_cBaseName, "pic", sizeof("pic"));

	//strncpy(paras.m_cBigName, "0", sizeof("0")-1);	
	//strncpy(paras.m_cLitName, "0", sizeof("0")-1);	
	//strncpy(paras.m_cBaseName, "0", sizeof("0")-1);
	
	strncpy(paras.m_cLibName, "0", sizeof("0")-1);
	
	strncpy(paras.m_cName, "0", sizeof("0")-1);
	
	strncpy(paras.m_cBirth, "0", sizeof("0")-1);
	
	strncpy(paras.m_cIDNo, "0", sizeof("0")-1);
	
	strncpy(paras.m_cReserveString1, "0", sizeof("0")-1);
	strncpy(paras.m_cReserveString2, "0", sizeof("0")-1);
	//----
#if 1
	
	
#endif
	time = strTime[_pTestParm->iTimeNo].tv_sec;
	localtime_r(&time, &stm);
	//strftime(para.S_CAPTURE[i], 32, "%Y-%m-%d %H:%M:%S", &stm);
	//printf("para.S_CAPTURE[i]=%s\n", para.S_CAPTURE[i]);
	getImage(1, g_cStreamPath, _pTestParm, (strTime[_pTestParm->iTimeNo].tv_sec));
	//printf("%s (%d) \n",__FUNCTION__, __LINE__);
	printf("%s (%d) testThread id=%lu \n",__FUNCTION__, __LINE__,pthread_self());
#if 0
	for (i=0; i<iPicNum; i++)
    {        
        //gettimeofday(&tv_time_data, NULL);
        time = strTime[_pTestParm->iTimeNo].tv_sec;
        localtime_r(&time, &stm);
        strftime(para.S_CAPTURE[i], 32, "%Y-%m-%d %H:%M:%S", &stm);
	    printf("para.S_CAPTURE[i]=%s\n", para.S_CAPTURE[i]);
		//------------------------------------------------------------------------
        getImage(1, str_for_cStreamPath, _pTestParm, para.m_iCapTime);
		if(str_for_cStreamPath == "")
        //if(para.S_PIC_NAME[i][0] == '\0')
        {   
            ifailCount[_pTestParm->iTimeNo]++;
            return -1;
        }
	
		printf("%s (%d) \n",__FUNCTION__, __LINE__);
        //para.m_iDiskId = disk_AtoI(para.S_PIC_NAME[i][1]);
    }
#endif

	 if(g_cStreamPath[0] == '\0')
        {   
            ifailCount[_pTestParm->iTimeNo]++;
            return -1;
        }
	if (NULL != _pDb)
    {
       //int iRet = _pDb->ExecWrite(handle, (void*)&paras);
	   int iRet = _pDb->ExecWrite((void*)&paras);
       printf("iRet=%d \n",iRet);
       if(iRet == 0)
       {
            iInsertCount[_pTestParm->iTimeNo]--;
       }
        iTimeCount++;
        if(iTimeCount >= PICESECNUM)
        {
            strTime[_pTestParm->iTimeNo].tv_sec++;
            iTimeCount = 0;
        }
		gettimeofday(&testTime, NULL);
		if(iTimeTmp != (int)testTime.tv_sec) 
		{
            //main 809 iStreamopenCount= 3216173 iStreamwriteCount= 0 iStreamSucessCount= 0 iStreamfailCount= 0 
            
			printf("%s %d iCountTmp = %d \n",__FUNCTION__, __LINE__, iCountTmp);
			iTimeTmp = (int)testTime.tv_sec;
			iCountTmp = 0;	
			printf("%s %d iStreamopenCount= %d iStreamwriteCount= %d iStreamSucessCount= %d iStreamfailCount= %d \n",
                __FUNCTION__, __LINE__, 
                iStreamopenCount, iStreamwriteCount,
                iStreamSucessCount, iStreamfailCount);
           
		}
		iCountTmp++;
    }

    return 0;
}

#if 0
int its_test(CTdDatabase *_pDb, DbHandle handle, TestStruct *_pTestParm)
{
	TWriteParaInsertCap para;
    memset(&para, 0, sizeof(TWriteParaInsertCap));
    struct timeval tv_time_data, testTime;
    int i = 0;
    time_t time;
    struct tm stm;
    int iPicNum = 1;
    
    para.m_eWriteType = DB_WRITE_INSERT_CAP;
   
    gettimeofday(&tv_time_data, NULL);
    time = 0;//tv_time_data.tv_sec + tv_time_data.tv_usec/1000000;
    localtime_r(&time, &stm);
    strftime(para.T_LAMP_BEGIN, 32, "%H:%M:%S", &stm);//???
    
    gettimeofday(&tv_time_data, NULL);
    para.m_iCapTime = strTime[_pTestParm->iTimeNo].tv_sec;

    para.BJLX = 0;
    para.F_SPEED = 0;
    para.I_ALGILLGALTYPE = 0;
    
    gettimeofday(&tv_time_data, NULL);
    for (i=0; i<iPicNum; i++)
    {
        para.I_CAPTURE_MS[i] = 0;
    }
    
    para.I_CARREGIONNUM = 0;
    para.I_COLOR_CAR_NO = 0;
    para.I_COLOR_PLATE_NO = 0;
    for (i=0; i<iPicNum; i++)
    {
        para.I_CRC_IMAGE[i] = 0;
    }
    para.I_FACE_PICTURENUM = 0;
    para.I_FLAG = 1;    //?ϴ?״̬
    para.I_DOCKING_STATE = 1;
    para.I_DOCKING_STATE2 = 1;
    para.I_HOST_CHANEL_NO = 0;
    para.I_PIC_NUM = 1;
    para.I_ROADWAY_ID = 0;
    para.I_TARGETTYPE = 0;
    para.I_UPTIME = 0;//wrong
    para.I_PLATE_NUM = 0;//add new
    para.I_BRAND = 0;//车辆品牌
    para.I_SUBBRAND = 0;//车辆子品???
    para.I_UUID = 0;

    for (i=0; i<iPicNum; i++)
    {        
        //gettimeofday(&tv_time_data, NULL);
        time = strTime[_pTestParm->iTimeNo].tv_sec;
        localtime_r(&time, &stm);
        strftime(para.S_CAPTURE[i], 32, "%Y-%m-%d %H:%M:%S", &stm);
	    printf("para.S_CAPTURE[i]=%s\n", para.S_CAPTURE[i]);
		//------------------------------------------------------------------------
        getImage(1, para.S_PIC_NAME[i], _pTestParm, para.m_iCapTime);
        if(para.S_PIC_NAME[i][0] == '\0')
        {   
            ifailCount[_pTestParm->iTimeNo]++;
            return -1;
        }
	
		printf("%s %d para.S_PIC_NAME[%d] = %s\n",__FUNCTION__, __LINE__, i,para.S_PIC_NAME[i]);
        para.m_iDiskId = disk_AtoI(para.S_PIC_NAME[i][1]);
    }
    strncpy(para.S_CARREGION, "0", sizeof("0")-1);
    strncpy(para.S_CARREGION_ECOP, "0", sizeof("0")-1);
    strncpy(para.S_COLOR_CAR, "0", sizeof("0")-1);
    strncpy(para.S_COLOR_PLATE, "0", sizeof("0")-1);
    //printf("%s %s \n", para.S_COLOR_PLATE, _stPic.m_strPlateColor.c_str());
    strncpy(para.S_COPILOTFACE_REGION, "0", sizeof("0")-1);
    strncpy(para.S_CROSSING_NO, "0", sizeof(para.S_CROSSING_NO)-1);
    strncpy(para.S_FACEREGION,"0", sizeof(para.S_FACEREGION)-1);

    strncpy(para.S_FACE_PICTURENAME[0], "0", sizeof(para.S_FACE_PICTURENAME[0])-1);
    strncpy(para.S_PIC_PATH, "0", sizeof(para.S_PIC_PATH)-1);
    strncpy(para.S_PLATE, "0", sizeof(para.S_PLATE)-1);
    strncpy(para.S_PLATELOCATION, "0", sizeof(para.S_PLATELOCATION)-1);

    strncpy(para.S_FACE_PICTURENAME[0], "0", sizeof(para.S_FACE_PICTURENAME[0])-1);
    strncpy(para.S_REC_FILE_NAME, "0", sizeof(para.S_REC_FILE_NAME)-1);
    snprintf(para.S_SYMBOL, sizeof(para.S_SYMBOL)-1, "%d", 0);
    strncpy(para.S_TYPE, "0", sizeof(para.S_TYPE)-1);
    strncpy(para.S_VEHICLEBRAND_REGION, "0", sizeof(para.S_VEHICLEBRAND_REGION)-1);
    strncpy(para.S_VIOLATION_TYPE, "0", sizeof(para.S_VIOLATION_TYPE)-1);


    gettimeofday(&tv_time_data, NULL);
    time = 0;//tv_time_data.tv_sec + tv_time_data.tv_usec/1000000;
    localtime_r(&time, &stm);
    strftime(para.T_LAMP_END, 32, "%H:%M:%S", &stm);//???ƽ???ʱ??

    if (NULL != _pDb)
    {
       int iRet = _pDb->ExecWrite(handle, (void*)&para);
       printf("iRet=%d \n",iRet);
       if(iRet == 0)
       {
            iInsertCount[_pTestParm->iTimeNo]--;
       }
        iTimeCount++;
        if(iTimeCount >= PICESECNUM)
        {
            strTime[_pTestParm->iTimeNo].tv_sec++;
            iTimeCount = 0;
        }
		gettimeofday(&testTime, NULL);
		if(iTimeTmp != (int)testTime.tv_sec) 
		{
            
			printf("%s %d iCountTmp = %d \n",__FUNCTION__, __LINE__, iCountTmp);
			iTimeTmp = (int)testTime.tv_sec;
			iCountTmp = 0;	
			printf("%s %d iStreamopenCount= %d iStreamwriteCount= %d iStreamSucessCount= %d iStreamfailCount= %d \n",
                __FUNCTION__, __LINE__, 
                iStreamopenCount, iStreamwriteCount,
                iStreamSucessCount, iStreamfailCount);
           
		}
		iCountTmp++;
    }

    return 0;
}
#endif
void* testThread(void* s)
{
	struct timeval startTime, endTime;
	int time = 0;
   // TestStruct * stpTmp = (TestStruct *)s;
    DbHandle handle = g_pDb->Register((char*)"nvr_test");
    //DbHandle handle = g_pDb->Register((char*)"its_test");
    
    while(1)
	{
       // its_test(g_pDb, handle, (TestStruct *)s);
		nvr_test(g_pDb, handle, (TestStruct *)s);
	   sleep(1);
	   
    }

    return NULL;
}

void* DatabaseDebugThread(void* _pArg)
{
	printf("%s (%d) DatabaseDebugThread id=%lu \n",__FUNCTION__, __LINE__,pthread_self());
    CTdDatabase* pDb = NULL;
    TdDbGetObject((void**)&pDb);
    FILE* fp;
    char* cBuf = NULL;
    int iBufSize = 1024*64;
    printf("%s (%d) DatabaseDebugThread id=%lu \n",__FUNCTION__, __LINE__,pthread_self());
    const char* pcFile = "/tmp/trade_rtmsg/database";
    if ((fp = fopen(pcFile, "w")) == NULL)
    {
        printf("%s open rtmsg file err!\n", __func__);
        return NULL;
    }
	//printf("%s %d\n",__FUNCTION__, __LINE__);
    while (1)
    {
        cBuf = new char[iBufSize];
        memset(cBuf, 0, iBufSize);
        g_pDb->GetDebugInfo(cBuf);
  
        fseek(fp, 0, SEEK_SET);
        fputs(cBuf, fp);
        fflush(fp);

        delete cBuf;
        sleep(1);
		printf("%s (%d) DatabaseDebugThread...ing\n",__FUNCTION__, __LINE__);
    }

    return NULL;
}
int readImgae()
{
	printf("%s (%d)...before fopen jpg\n",__FUNCTION__, __LINE__);
	int iRet = 0;
	FILE *fp = NULL;	
//pic
	fp = fopen("./pic.JPG", "rb");
	//fp = fopen("./pic.jpg", "rb");	
    if(fp == NULL)
    {
        iRet = -1;
        goto LEAVE;
    }
	printf("%s (%d)...after fopen jpg \n",__FUNCTION__, __LINE__);
    fseek(fp, 0, SEEK_END);
    iPicLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
	cpPicBuf = (char *)malloc(iPicLen);
    fread(cpPicBuf, 1, iPicLen, fp);
LEAVE:

    fclose(fp);
    fp = NULL;

	return iRet;
}
void Mount(int _iNum)
{
    char cMountPath[64] = "\0";
    for(int i = 0; i < _iNum; i++)
    {
        snprintf(cMountPath, sizeof(cMountPath), "/dev/scsi/host0%d/part1",i);
         tdfs_Mount(cMountPath);
    }
}

int main(int argc, char *argv[])
{
    int iRet = 0;
    pthread_t its_debugid;
    int iDevNo = 18;
    int iDiskNo = 1;
    int iDiskNum = 0;
    int iDiskNone[4] = {1,3,7,15};
    TestStruct stTestParm[4][4];
    char cPathTmp[64] = "\0";
    //kill???̷?ֹ?ؽ?????
    system("killall TODO;killall gui;killall dvr1;killall trade.bin");
    system("/dvr/closedog");
    //TestStruct?�????ʼ??
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            memset(stTestParm[i]+j, 0, sizeof(TestStruct));
            stTestParm[i][j].iTimeNo = i;
            snprintf(cPathTmp, sizeof(cPathTmp), "/dev/scsi/host0%d/part1",i);
            strncpy(stTestParm[i][j].cPath, cPathTmp, sizeof(cPathTmp) - 1);
            stTestParm[i][j].iChanlNo = j;
        }
    }
    iInsertCount[0] = DISKTAILCOUNT;
    iInsertCount[1] = DISKTAILCOUNT;
    iInsertCount[2] = DISKTAILCOUNT;
    iInsertCount[3] = DISKTAILCOUNT;
    //ʱ??ת??
    #if TIME
    struct tm stm;
    char cTime[64] = "\0";
    if(argc-1 < 2)
    {
        gettimeofday(&strTime[0], NULL);
        iDiskNo = 1;
        printf("get local time\n");
    }
    else if(argc-1 < 3)
    {
        iDiskNo = 1;
        snprintf(cTime, sizeof(cTime), "%s %s", argv[1], argv[2]);
        printf("cTime=%s\n", cTime);
        strptime(cTime, "%Y-%m-%d %H:%M:%S", &stm);
        int iTimeSec = mktime(&stm);
        strTime[0].tv_sec = iTimeSec;
    }
    else if(argc-1 < 4)
    {
        iDiskNum= atoi(argv[3]);
        iDiskNum = iDiskNum - 1; 
        printf("argv[3]=%s\n",argv[3]);
        iDiskNo = iDiskNone[iDiskNum];
        snprintf(cTime, sizeof(cTime), "%s %s", argv[1], argv[2]);
        printf("cTime=%s\n", cTime);
        strptime(cTime, "%Y-%m-%d %H:%M:%S", &stm);
        int iTimeSec = mktime(&stm);
        strTime[0].tv_sec = iTimeSec;
        strTime[1].tv_sec = iTimeSec + 604800;
        strTime[2].tv_sec = iTimeSec + 604800 * 2;
        strTime[3].tv_sec = iTimeSec + 604800 * 3;
    }
    else
    {
        iDiskNum= atoi(argv[3]);
        iDiskNum = iDiskNum - 1; 
        printf("argv[3]=%s\n",argv[3]);
        iDiskNo = iDiskNone[iDiskNum];
        snprintf(cTime, sizeof(cTime), "%s %s", argv[1], argv[2]);
        printf("cTime=%s\n", cTime);
        strptime(cTime, "%Y-%m-%d %H:%M:%S", &stm);
        int iTimeSec = mktime(&stm);
        int iDatime = atoi(argv[4]);
        strTime[0].tv_sec = iTimeSec;
        strTime[1].tv_sec = iTimeSec + iDatime * 86400;
        strTime[2].tv_sec = iTimeSec + iDatime * 86400 * 2;
        strTime[3].tv_sec = iTimeSec + iDatime * 86400 * 3;
        printf("iDatime=%d iDatime * 86400=%d\n", iDatime, iDatime * 86400);
    }
    printf("strTime.tv_sec=%d\n",strTime[0].tv_sec);
    #endif
    iRet = tdfs_Init();
    printf("%s %d tdfs_Init iRet = %d\n",__FUNCTION__, __LINE__,iRet);
    sleep(1);
    iRet = vfs_Init();
    printf("%s %d vfs_Init iRet = %d\n",__FUNCTION__, __LINE__,iRet);
    switch (iDiskNo)
    {
        case 1:
            Mount(1);
            iDiskNum = 1;
            break;
        case 3:
            Mount(2);
            iDiskNum = 2;
            break;
        case 7:
            Mount(3);
            iDiskNum = 3;
            break;
        case 15:
           Mount(4);
            iDiskNum = 4;
            break;
        default:
            Mount(1);
            iDiskNum = 1;
            break;
    }
    //????ι????????
    #if FEDOG
    GUIComCommand.m_iFdCom = OpenComDev(GUIComCommand.m_pu8Dev);
    #endif
    //?��???ͼƬ
    iRet = readImgae();
    if(iRet != 0)
    {
        printf("%s %d readImgae fail!!! iRet=%d\n",__FUNCTION__, __LINE__, iRet);
        Free_Value();
        return -1;
    }
    //???ݿ?????
    printf("%s (%d) idiskno =%d\n",__FUNCTION__, __LINE__, iDiskNo);

	g_pDb = new CTdDatabase(TD_DB_NVR);
    //g_pDb = new CTdDatabase(TD_DB_ITS);
    if (NULL != g_pDb)
    {
		printf("%s (%d) CTdDatabase success \n",__FUNCTION__, __LINE__);
	}
	else
	{
		printf("%s (%d) CTdDatabase failed \n",__FUNCTION__, __LINE__);
	}
    g_pDb->Init(iDiskNo, NULL);
    sleep(2);
	printf("%s (%d) g_pDb->Init \n",__FUNCTION__, __LINE__);
    //????????
    //while(1);
    for(int i = 0; i < iDiskNum; i++)
    {
        pthread_create(&its_testid[i][0], NULL, testThread, (void *)stTestParm[i]);
        pthread_create(&its_testid[i][1], NULL, testThread, (void *)(stTestParm[i] + 1));
        pthread_create(&its_testid[i][2], NULL, testThread, (void *)(stTestParm[i] + 2));
        pthread_create(&its_testid[i][3], NULL, testThread, (void *)(stTestParm[i] + 3));
    }
    //???ݿ???????Ϣд?ļ?????
    pthread_create(&its_debugid, NULL, DatabaseDebugThread, NULL);
    //????ι??????
#if FEDOG
    pthread_create(&its_debugid, NULL, SetDevNoToFP, (void *)&iDevNo);
#endif
    while(1)
    {
        for(int i = 0; i < iDiskNum; i++)
        {
            if(ifailCount[i] >= 10 ||iInsertCount[i] <= 0)
            {
                printf("%s %d iStreamopenCount= %d iStreamwriteCount= %d iStreamSucessCount= %d iStreamfailCount= %d \n",
                    __FUNCTION__, __LINE__, 
                    iStreamopenCount, iStreamwriteCount,
                    iStreamSucessCount, iStreamfailCount);
                printf("ifailCount[%d] = %d\n", i,ifailCount[i]);
                pthread_cancel(its_testid[i][0]);
                pthread_cancel(its_testid[i][1]);
                pthread_cancel(its_testid[i][2]);
                pthread_cancel(its_testid[i][3]);
                ifailCount[i] = 0;
                if(ifailCount[0] == 0 && ifailCount[1] == 0 && ifailCount[2] == 0 &&ifailCount[3] == 0)
                {
                    Free_Value();
                    exit(-1);
                }
                
            }
        }

        sleep(60);
		printf("%s (%d) main while \n",__FUNCTION__, __LINE__);
    }
    Free_Value();
	printf("%s (%d) finished\n",__FUNCTION__, __LINE__);
    return 0;


}
