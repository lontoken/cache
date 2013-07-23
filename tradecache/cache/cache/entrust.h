/**********************************************************************
* 委托信息信息 entrust
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_ENTRUST_H
#define _CACHE_ENTRUST_H

#pragma once

#include <sstream>
#include <ctime>
#include "config.h"

#pragma pack(STRUCT_PACK_LEN)

typedef struct TEntrust{
    int busin_date;
    int entrust_id;
    int unit_id;
    int batchop_id;
    int report_id;
    COMBICODE_TYPE combi_code;
    STOCKCODE_TYPE stock_code;
    ENTDIR_CODE_TYPE entrustdirection_code;
    PRICETYPE_TYPE price_type;
    CURRENCY_TYPE price;
    AMOUNT_TYPE amount;
    CURRENCY_TYPE balance;
    CURRENCY_TYPE prebuy_balance;
    CURRENCY_TYPE presale_balance;
    CURRENCY_TYPE prebuy_fee;
    CURRENCY_TYPE presale_fee;
    CURRENCY_TYPE prebuy_frozen_balance;
    ENTSTATUS_TYPE entrust_status;
    int entrust_time;
    char cancel_flag;
    int cancel_id;
    AMOUNT_TYPE cancel_amount;
    AMOUNT_TYPE business_amount;
    CURRENCY_TYPE business_balance;
    string remarks;
    int operator_id;
    struct timeval ent_timestamp;
    IP_TYPE ip;
    MAC_TYPE mac;

    OperateType opType;
}Entrust;

#endif