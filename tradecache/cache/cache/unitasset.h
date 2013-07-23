/**********************************************************************
* 子账户资金信息 unitasset
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_UNITASSET_H
#define _CACHE_UNITASSET_H

#pragma once

#include <sstream>
#include "config.h"
#include "luaunit.h"

#pragma pack(STRUCT_PACK_LEN)

typedef struct TUnitAsset{
    int busin_date;
    int unit_id;
    CURRENCY_CODE_TYPE currency_code;
    CURRENCY_TYPE begin_cash;
    CURRENCY_TYPE current_cash;
    CURRENCY_TYPE prebuy_balance;
    CURRENCY_TYPE prebuy_fee;
    CURRENCY_TYPE presale_balance;
    CURRENCY_TYPE input_balance;
    CURRENCY_TYPE output_balance;
    CURRENCY_TYPE input_total;
    CURRENCY_TYPE output_total;

    OperateType opType;
}UnitAsset;

#pragma pack()

CACHE_LIB_API GetUnitAsset(lua_State* L)
{
    int unitId = 0;
    char curCode[4] = {0};

    unitId = PAI(L, 1);
    CS(curCode, L, 2);
}

#endif