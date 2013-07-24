#ifndef _CACHE_HASHSEARCH_H
#define _CACHE_HASHSEARCH_H

#pragma once

#include <cstdio>  
#include <cctype>    

#define HASHTABLESIZE_K 1361
#define HASHTABLESIZE_W 10949
#define HASHTABLESIZE_10W 175447   
#define HASHTABLESIZE_100W 1403641

int getNextHashTableSize(int curSize);
  
//���µĺ�������һ������Ϊ0x500����10��������1280����cryptTable[0x500]  
void prepareCryptTable();
  
//���º�������lpszFileName �ַ�����hashֵ������dwHashType Ϊhash�����ͣ�  
//������GetHashTablePos����������ñ������������ȡ��ֵΪ0��1��2���ú���  
//����lpszFileName �ַ�����hashֵ��  
unsigned long HashString( char *pStr, unsigned long dwHashType );


class HashTableIniter{
public:
    static HashTableIniter m_instance;
private:
    HashTableIniter(){prepareCryptTable();};
};

#endif