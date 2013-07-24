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
  
//以下的函数生成一个长度为0x500（合10进制数：1280）的cryptTable[0x500]  
void prepareCryptTable();
  
//以下函数计算lpszFileName 字符串的hash值，其中dwHashType 为hash的类型，  
//在下面GetHashTablePos函数里面调用本函数，其可以取的值为0、1、2；该函数  
//返回lpszFileName 字符串的hash值；  
unsigned long HashString( char *pStr, unsigned long dwHashType );

void printTable();

#endif