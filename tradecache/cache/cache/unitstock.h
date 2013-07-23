/**********************************************************************
* 子账户股份信息 unitstock
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_UNITSTOCK_H
#define _CACHE_UNITSTOCK_H

#pragma once

#include <sstream>
#include "config.h"

#pragma pack(STRUCT_PACK_LEN)

typedef struct TUnitStock{
    int busin_date;
    int unit_id;
    STOCKCODE_TYPE stock_code;
    BS_TYPE bs;
    AMOUNT_TYPE begin_amount;
    CURRENCY_TYPE begin_cost;
    CURRENCY_TYPE begin_total_profit;
    CURRENCY_TYPE begin_total_buyfee;
    CURRENCY_TYPE begin_total_salefee;
    AMOUNT_TYPE current_amount;
    AMOUNT_TYPE prebuy_amount;
    AMOUNT_TYPE presale_amount;
    CURRENCY_TYPE prebuy_balance;
    CURRENCY_TYPE presale_balance;
    AMOUNT_TYPE buy_amount;
    AMOUNT_TYPE sale_amount;
    CURRENCY_TYPE buy_balance;
    CURRENCY_TYPE sale_balance;
    CURRENCY_TYPE buy_fee;
    CURRENCY_TYPE sale_fee;

    OperateType opType;
}UnitStock;  

#pragma pack()

#endif