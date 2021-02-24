/*********************************************************************** 版权所朿(C)2015, Zhou Zhaoxiong〿** 文件名称：GetConfig.c* 文件标识：无* 内容摘要：演示Linux下配置文件的读取方法* 其它说明：无* 当前版本：V1.0* 使   者：Zhou Zhaoxiong* 完成日期＿0150507***********************************************************************/#include <stdio.h>#include <stdlib.h>#include <string.h>// 数据类型重定乿typedef unsigned char   UINT8;typedef signed   int    INT32;typedef unsigned int    UINT32;// 员工信息结构体定乿typedef struct{    UINT8  szEmployeeName[128];    // 员工姓名    INT32  iEmployeeAge;           // 员工年龄} T_EmployeeInfo;// 雇主信息结构体定乿typedef struct{    UINT8  szEmployerName[128];    // 雇主姓名    INT32  iEmployerAge;           // 雇主年龄} T_EmployerInfo;// 函数声明void GetCompletePath(UINT8 *pszConfigFileName, UINT8 *pszWholePath);void GetStringContentValue(FILE *fp, UINT8 *pszSectionName, UINT8 *pszKeyName, UINT8 *pszOutput, UINT32 iOutputLen);void GetConfigFileStringValue(UINT8 *pszSectionName, UINT8 *pszKeyName, UINT8 *pDefaultVal, UINT8 *pszOutput, UINT32 iOutputLen, UINT8 *pszConfigFileName);INT32 GetConfigFileIntValue(UINT8 *pszSectionName, UINT8 *pszKeyName, UINT32 iDefaultVal, UINT8 *pszConfigFileName);INT32 main();/*********************************************************************** 功能描述：主函数* 输入参数：无* 输出参数：无* 迿囿值：旿* 其它说明：无* 修改日期         版本叿        修改亿           修改内容* ---------------------------------------------------------------* 20150507        V1.0     Zhou Zhaoxiong          创建***********************************************************************/INT32 main(){    T_EmployeeInfo tEmployeeInfo = {0};    T_EmployerInfo tEmployerInfo = {0};    // 获取并打印员工信恿    // 获取员工姓名    //GetConfigFileStringValue("EMPLOYEEINFO", "EmployeeName", "", tEmployeeInfo.szEmployeeName, sizeof(tEmployeeInfo.szEmployeeName), "Config.ini");	//GetConfigFileStringValue("EMPLOYEEINFO", "EmployeeName", "", tEmployeeInfo.szEmployeeName, sizeof(tEmployeeInfo.szEmployeeName), "./Config.ini");    // 获取员工年龄    //tEmployeeInfo.iEmployeeAge = GetConfigFileIntValue("EMPLOYEEINFO", "EmployeeAge", 20, "Config.ini");  //  if (tEmployeeInfo.iEmployeeAge == -1)  // 判断获取到的年龄是否正确   // {  //      printf("Get EmployeeAge failed!\n");  //      return -1;  //  }  	int bigname_en=-1;	int litname_en=-1;	int basename_en=-1;	int sata_disk_number_s=-1;	int interval_s=-1;	char date_1[128]; 	//char* date_1=NULL;			//GetConfigFileStringValue("CONFIG", "bigname", "", bigname_en, sizeof(bigname_en), "./Config.ini");	//GetConfigFileStringValue("CONFIG", "litname", "", litname_en, sizeof(litname_en), "./Config.ini");	//GetConfigFileStringValue("CONFIG", "basename", "", basename_en, sizeof(basename_en), "./Config.ini");	//GetConfigFileStringValue("CONFIG", "sata_disk_number", "", sata_disk_number_s, sizeof(sata_disk_number_s), "./Config.ini");	//GetConfigFileStringValue("CONFIG", "interval", "", interval_s, sizeof(interval_s), "./Config.ini");	bigname_en=GetConfigFileIntValue("CONFIG", "bigname", -1, "./Config.ini");	litname_en=GetConfigFileIntValue("CONFIG", "litname", -1, "./Config.ini");	basename_en=GetConfigFileIntValue("CONFIG", "basename", -1, "./Config.ini");	sata_disk_number_s=GetConfigFileIntValue("CONFIG", "sata_disk_number", -7, "./Config.ini");	interval_s=GetConfigFileIntValue("CONFIG", "interval", -7, "./Config.ini");	GetConfigFileStringValue("CONFIG", "date", "2019-08-15 00:00:00", date_1, sizeof(date_1), "./Config.ini");	 if(date_1!=NULL)	 {		//strncpy(m_stDockMQParam.S_SERVER_IP, server1, strlen(server1));				printf("(%d) date_1 = %s\n", __LINE__,date_1);      	       	 }  		//date = TD_IniParser_Get_ItemValue(iID, "CONFIG", "date", "2019-08-15 00:00:00");		printf("bigname_en=%d\n",bigname_en);	printf("litname_en=%d\n",litname_en);	printf("basename_en=%d\n",basename_en);	printf("sata_disk_number_s=%d\n",sata_disk_number_s);	printf("interval_s=%d\n",interval_s);	/*   tEmployeeInfo.iEmployeeAge = GetConfigFileIntValue("EMPLOYEEINFO", "EmployeeAge", 20, "Config.ini");	if (tEmployeeInfo.iEmployeeAge == -1)  // 判断获取到的年龄是否正确	{		printf("Get EmployeeAge failed!\n");		return -1;	}	*/    // 打印读取到的员工姓名和年龿   // printf("EmployeeName is %s, EmployeeAge is %d\n", tEmployeeInfo.szEmployeeName, tEmployeeInfo.iEmployeeAge);    // 获取并打印雇主信恿    // 获取雇主姓名    GetConfigFileStringValue("EMPLOYERINFO", "EmployerName", "", tEmployerInfo.szEmployerName, sizeof(tEmployerInfo.szEmployerName), "./Config.ini");    // 获取员工年龄    tEmployerInfo.iEmployerAge = GetConfigFileIntValue("EMPLOYERINFO", "EmployerAge", 30, "./Config.ini");    if (tEmployerInfo.iEmployerAge == -1)  // 判断获取到的年龄是否正确    {        printf("Get EmployerAge failed!\n");        return -1;    }    // 打印读取到的员工姓名和年龿    //printf("EmployerName is %s, EmployerAge is %d\n", tEmployerInfo.szEmployerName, tEmployerInfo.iEmployerAge);    return 0;              }/*********************************************************************** 功能描述＿获取配置文件完整路径(包含文件吿* 输入参数＿pszConfigFileName-配置文件吿             pszWholePath-配置文件完整路径(包含文件吿* 输出参数＿旿* 迿囿值： 旿* 其它说明＿旿* 修改日期        版本叿        修改亿      修改内容* ------------------------------------------------------------------* 20150507       V1.0     Zhou Zhaoxiong     创建********************************************************************/  void GetCompletePath(UINT8 *pszConfigFileName, UINT8 *pszWholePath){    UINT8 *pszHomePath      = NULL;    UINT8  szWholePath[256] = {0};    // 先对输入参数进行异常判断    if (pszConfigFileName == NULL || pszWholePath == NULL)    {        printf("GetCompletePath: input parameter(s) is NULL!\n");        return;    }    pszHomePath = (UINT8 *)getenv("HOME");     // 获取当前用户所在的路径    if (pszHomePath == NULL)    {        printf("GetCompletePath: Can't find home path!\n");        return;    }    // 拼装配置文件路径    snprintf(szWholePath, sizeof(szWholePath)-1, "%s/zhouzx/GetConfig/%s", pszHomePath, pszConfigFileName);    strncpy(pszWholePath, szWholePath, strlen(szWholePath));}/*********************************************************************** 功能描述＿获取具体的字符串倿* 输入参数＿fp-配置文件指针             pszSectionName-段名, 妿 GENERAL             pszKeyName-配置项名, 妿 EmployeeName             iOutputLen-输出缓存长度* 输出参数＿pszOutput-输出缓存* 迿囿值： 旿* 其它说明＿旿* 修改日期         版本叿       修改亿      修改内容* ------------------------------------------------------------------* 20150507       V1.0     Zhou Zhaoxiong     创建********************************************************************/void GetStringContentValue(FILE *fp, UINT8 *pszSectionName, UINT8 *pszKeyName, UINT8 *pszOutput, UINT32 iOutputLen){    UINT8  szSectionName[100]    = {0};    UINT8  szKeyName[100]        = {0};    UINT8  szContentLine[256]    = {0};    UINT8  szContentLineBak[256] = {0};    UINT32 iContentLineLen       = 0;    UINT32 iPositionFlag         = 0;    // 先对输入参数进行异常判断    if (fp == NULL || pszSectionName == NULL || pszKeyName == NULL || pszOutput == NULL)    {        printf("%s:GetStringContentValue: input parameter(s) is NULL!\n",__FUNCTION__);        return;    }    sprintf(szSectionName, "[%s]", pszSectionName);    strcpy(szKeyName, pszKeyName);    while (feof(fp) == 0)    {        memset(szContentLine, 0x00, sizeof(szContentLine));        fgets(szContentLine, sizeof(szContentLine), fp);      // 获取段名        // 判断是否是注释行(仿开头的行就是注释行)或以其他特殊字符开头的衿        	if (szContentLine[0] == ';' || szContentLine[0] == '\r' || szContentLine[0] == '\n' || szContentLine[0] == '\0')        {            continue;        }        // 匹配段名        if (strncasecmp(szSectionName, szContentLine, strlen(szSectionName)) == 0)             {            while (feof(fp) == 0)            {                memset(szContentLine,    0x00, sizeof(szContentLine));                memset(szContentLineBak, 0x00, sizeof(szContentLineBak));                fgets(szContentLine, sizeof(szContentLine), fp);     // 获取字段倿                // 判断是否是注释行(仿开头的行就是注释行)                if (szContentLine[0] == ';')                {                    continue;                }                memcpy(szContentLineBak, szContentLine, strlen(szContentLine));                // 匹配配置项名                if (strncasecmp(szKeyName, szContentLineBak, strlen(szKeyName)) == 0)                     {                    iContentLineLen = strlen(szContentLine);                    for (iPositionFlag = strlen(szKeyName); iPositionFlag <= iContentLineLen; iPositionFlag ++)                    {                        if (szContentLine[iPositionFlag] == ' ')                        {                            continue;                        }                        if (szContentLine[iPositionFlag] == '=')                        {                            break;                        }                        iPositionFlag = iContentLineLen + 1;                        break;                    }                    iPositionFlag = iPositionFlag + 1;    // 跳过=的位罿                    if (iPositionFlag > iContentLineLen)                    {                        continue;                    }                    memset(szContentLine, 0x00, sizeof(szContentLine));                    strcpy(szContentLine, szContentLineBak + iPositionFlag);                    // 去掉内容中的无关字符                    for (iPositionFlag = 0; iPositionFlag < strlen(szContentLine); iPositionFlag ++)                    {                        if (szContentLine[iPositionFlag] == '\r' || szContentLine[iPositionFlag] == '\n' || szContentLine[iPositionFlag] == '\0')                        {                            szContentLine[iPositionFlag] = '\0';                            break;                        }                    }                    // 将配置项内容拷贝到输出缓存中                    strncpy(pszOutput, szContentLine, iOutputLen-1);                    break;                }                else if (szContentLine[0] == '[')                {                    break;                }            }            break;        }    }}/*********************************************************************** 功能描述＿从配置文件中获取字符丿* 输入参数＿pszSectionName-段名, 妿 GENERAL             pszKeyName-配置项名, 妿 EmployeeName             pDefaultVal-默认倿             iOutputLen-输出缓存长度             pszConfigFileName-配置文件吿* 输出参数＿pszOutput-输出缓存* 迿囿值： 旿* 其它说明＿旿* 修改日期        版本叿        修改亿      修改内容* ------------------------------------------------------------------* 20150507       V1.0     Zhou Zhaoxiong     创建********************************************************************/  void GetConfigFileStringValue(UINT8 *pszSectionName, UINT8 *pszKeyName, UINT8 *pDefaultVal, UINT8 *pszOutput, UINT32 iOutputLen, UINT8 *pszConfigFileName){    FILE  *fp                    = NULL;    UINT8  szWholePath[256]      = {0};	if(pszSectionName == NULL )	{		printf("pszSectionName == NULL ");	}	if(pszKeyName == NULL )	{		printf("pszKeyName == NULL ");	}	if(pszOutput == NULL )	{		printf("pszOutput == NULL ");	}	if(pszConfigFileName == NULL )	{		printf("pszConfigFileName == NULL ");	}    // 先对输入参数进行异常判断    if (pszSectionName == NULL || pszKeyName == NULL || pszOutput == NULL || pszConfigFileName == NULL)    {        printf("GetConfigFileStringValue: input parameter(s) is NULL!\n");        return;    }    // 获取默认倿        if (pDefaultVal == NULL)    {        strcpy(pszOutput, "");    }    else    {        strcpy(pszOutput, pDefaultVal);    }    // 打开配置文件    //GetCompletePath(pszConfigFileName, szWholePath);    //fp = fopen(szWholePath, "r");    fp = fopen(pszConfigFileName, "r");    if (fp == NULL)    {        printf("GetConfigFileStringValue: open %s failed!\n", pszConfigFileName);        return;    }    // 调用函数用于获取具体配置项的倿        GetStringContentValue(fp, pszSectionName, pszKeyName, pszOutput, iOutputLen);    // 关闭文件    fclose(fp);    fp = NULL;}/*********************************************************************** 功能描述＿从配置文件中获取整型变量* 输入参数＿pszSectionName-段名, 妿 GENERAL             pszKeyName-配置项名, 妿 EmployeeName             iDefaultVal-默认倿             pszConfigFileName-配置文件吿* 输出参数＿旿* 迿囿值： iGetValue-获取到的整数倿  -1-获取失败* 其它说明＿旿* 修改日期         版本叿      修改亿       修改内容* ------------------------------------------------------------------* 20150507       V1.0     Zhou Zhaoxiong     创建********************************************************************/  INT32 GetConfigFileIntValue(UINT8 *pszSectionName, UINT8 *pszKeyName, UINT32 iDefaultVal, UINT8 *pszConfigFileName){    UINT8  szGetValue[512] = {0};    INT32  iGetValue       = 0;    // 先对输入参数进行异常判断    if (pszSectionName == NULL || pszKeyName == NULL || pszConfigFileName == NULL)    {        printf("GetConfigFileIntValue: input parameter(s) is NULL!\n");        return -1;    }    GetConfigFileStringValue(pszSectionName, pszKeyName, NULL, szGetValue, 512-1, pszConfigFileName);    // 先将获取的值存放在字符型缓存中    if (szGetValue[0] == '\0' || szGetValue[0] == ';')    // 如果是结束符或分叿 则使用默认倿       {        iGetValue = iDefaultVal;    }    else    {        iGetValue = atoi(szGetValue);    }    return iGetValue;}