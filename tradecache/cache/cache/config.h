/**********************************************************************
* ≈‰÷√–≈œ¢
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/

#ifndef _CACHE_CONFIG_H
#define _CACHE_CONFIG_H

#pragma once

#include <sstream>

#define STRUCT_PACK_LEN 4

typedef double CURRENCY_TYPE;
typedef double PRICE_TYPE;
typedef long AMOUNT_TYPE;
typedef int ENTDIR_CODE_TYPE;
typedef char PRICETYPE_TYPE;
typedef char ENTSTATUS_TYPE;
typedef char COMBICODE_TYPE[129];
typedef char STOCKCODE_TYPE[65];
typedef char SUMMARY_TYPE[4001];
typedef char IP_TYPE[33];
typedef char MAC_TYPE[33];
typedef char BS_TYPE;
typedef char CURRENCY_CODE_TYPE[4];

typedef enum TOperateType{
    Get = 0,
    Update = 1,
    Insert = 2
}OperateType;

#endif