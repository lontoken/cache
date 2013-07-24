#include <iostream>
#include "hashsearch.h"
#include "base.h"

HashTableIniter HashTableIniter::m_instance;

//crytTable[]���汣�����HashString�������潫���õ���һЩ���ݣ���prepareCryptTable  
//���������ʼ��  
unsigned long cryptTable[0x500];  

int getNextHashTableSize(int curSize)
{
    if(curSize < HASHTABLESIZE_K){
        return HASHTABLESIZE_K; 
    }else if(curSize < HASHTABLESIZE_W){
        return HASHTABLESIZE_W;
    }else if(curSize < HASHTABLESIZE_10W){
        return HASHTABLESIZE_10W;
    }else if(curSize < HASHTABLESIZE_100W){
        return HASHTABLESIZE_100W;
    }

    ASSERT(false);

    return 0;
}

//���µĺ�������һ������Ϊ0x500����10��������1280����cryptTable[0x500]  
void prepareCryptTable()  
{   
    std::cout << "==prepareCryptTable== call == " << std::endl;
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;  
  
    for( index1 = 0; index1 < 0x100; index1++ )  
    {   
        for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )  
        {   
            unsigned long temp1, temp2;  
  
            seed = (seed * 125 + 3) % 0x2AAAAB;  
            temp1 = (seed & 0xFFFF) << 0x10;  
  
            seed = (seed * 125 + 3) % 0x2AAAAB;  
            temp2 = (seed & 0xFFFF);  
  
            cryptTable[index2] = ( temp1 | temp2 );   
       }   
   }   
}  


//���º�������pStr �ַ�����hashֵ������dwHashType Ϊhash�����ͣ�  
//������GetHashTablePos����������ñ������������ȡ��ֵΪ0��1��2���ú���  
//����pStr�ַ�����hashֵ��  
unsigned long HashString( char *pStr, unsigned long dwHashType )  
{   
    unsigned char *key  = (unsigned char *)pStr;  
    unsigned long seed1 = 0x7FED7FED;  
    unsigned long seed2 = 0xEEEEEEEE;  
    int ch;  
  
    while( *key != 0 )  
    {   
        ch = toupper(*key++);  
  
        seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);  
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;   
    }  
    return seed1;   
}  