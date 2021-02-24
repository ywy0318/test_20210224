#include <stdio.h>
#include <string.h>
//C语言字符串切片
//https://zhidao.baidu.com/question/186822021.html

int findSubstringIndexSplitByComma(const char *pSrc, const char *pDst); 
int getSubstringByIndexSplitByComma(const char *pSrcString,const int index,char *pSubString,const int pSubStringSize);

void main(void)
{
    char *p_src_string = "S1,S2,S3,S4,S5,S6,S7";
    char *p_need_find_string = "S6";
    char sub_string[10] = {};
    int index = 0;
    
    index = findSubstringIndexSplitByComma(p_src_string,p_need_find_string);
    if(-1 != index)
    {
        printf("The index of SubString[%s] in SrcString[%s] is [%d]\n",p_need_find_string,p_src_string,index);
    }
    
    if(-1 != getSubstringByIndexSplitByComma(p_src_string,index,sub_string,sizeof(sub_string)))
    {
        printf("Get sub string from SrcString[%s] by index[%d]:SubString--[%s]\n",p_src_string,index,sub_string);        
    }
    else
    {
        printf("Can not find SubString in [%s] by index[%d]\n",p_src_string,index);
    }

}
//if can not find substring in srcString,return -1
//if can find,return the num of comma before the substring
//for example:
//srcstring S1,S2,S3  subString:S2,return 1
//srcstring S1,S2,S3  subString:S4,return -1
int findSubstringIndexSplitByComma(const char *pSrc, const char *pDst)  
{  
    int i = 0;
    int j = 0; 
    int comma_cnt = 0;
    
    for (i=0; pSrc[i]!='\0'; i++)  
    {
        if(',' == pSrc[i])
        {
            comma_cnt++;
        }
        
        if(pSrc[i]!=pDst[0])  
            continue;         
        
        j = 0;  
        while(pDst[j]!='\0' && pSrc[i+j]!='\0')  
        {  
            j++;  
            if(pDst[j]!=pSrc[i+j]) 
            {
                break;    
            }  
        }  
        if(pDst[j]=='\0')  
            return comma_cnt;  
    }  
    return -1;  
}

//if can not find substring by index in srcstring,return -1
//if can find,return 0,and cpy this subString to pSubString,so you need ensure the pSubString has enough space to save the substring
//srcString ",,,",if index = 1,substring is empty,if the substring space is not enough,cut short the subString in srcString
//pay attention to the index = 0,if the index is 0,find_index = 0
int getSubstringByIndexSplitByComma(const char *pSrcString,const int index,char *pSubString,const int pSubStringSize)
{
    int comma_cnt = 0;
    int i = 0;
    int j = 0;
    int find_index = 0;

    //get srcString comma cnt,if equal the index,start copy to the pSubString
    for(i = 0;pSrcString[i] != '\0';i++)
    {
        if(comma_cnt == index)
        {
            break;
        }
        if(',' == pSrcString[i])
        {
            comma_cnt++;
        }
    }
    //can not find the index of comma_cnt,just return 
    if('\0' == pSrcString[i])
    {
        return -1;
    }
    //find 
    find_index = i;
    for(j = 0;('\0' != pSrcString[j + find_index]);j++)
    {
        if(j < pSubStringSize)
        {
            if(',' == pSrcString[j + find_index])
            {
                break;
            }
            else
            {
                pSubString[j] = pSrcString[j + find_index];
            }            
        }
        else
        {
            printf("The subString space is not enough\n");
            break;
        }
    }
    pSubString[j] = '\0';
    
    return 0;
}
