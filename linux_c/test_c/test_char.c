#include<stdio.h>
#include<string.h>

typedef struct
{
    int m_iChn;                                     //通道号
    char m_cChnName[63 + 2];         //通道名
    unsigned int m_uiTime;                          //警情时间
    int m_iAlarmType;                               //警情类型 见枚举EPreTargetAlarnTypeEnum
    char m_strBigFileName[63 + 1];     //大图文件名 -- 非人脸用大图
    char m_strSmlFileName[63 + 1];     //小图文件名
    char m_strBaseFileName[63 + 1];    //底图文件名
    int m_iSimilar;                                 //相似度
    char m_strBaseLibName[63 + 1];   //人脸库的名字
    char m_strName[63 + 1];          //对应的人名
    char m_cMsgType;                                //目标侦测信息的数据类型：见枚举 ETargetSenseMsgTypeEnum
    char m_cReverse[3];
    /* m_cReverse修改记录：
     * (4->3) 2020-07-27 XM20200213-1_2盘智能人脸NVR换代项目 增加m_cMsgType */        
    int m_iReverse[1];      //预留
    /* m_iReverse修改记录：
     * (2->1) 2020-07-27 XM20200213-1_2盘智能人脸NVR换代项目 增加m_iReverse[4] */    
} TTargetAlarmMsg;

int main()
{
	TTargetAlarmMsg T ;
	memset(&T,0,sizeof(TTargetAlarmMsg)); 
	T.m_cMsgType = 10;
	printf("%d\n",T.m_cMsgType);
	return 0;
}
