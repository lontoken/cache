/**********************************************************************
* 成交信息信息 business
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_BUSINESS_H
#define _CACHE_BUSINESS_H

#pragma once

#include <sstream>
#include <ctime>
#include "config.h"

#pragma pack(STRUCT_PACK_LEN)

typedef struct TBusiness{
    int busin_date;
    int batchop_id;
    int business_id;
    int businclass_code;
    int fund_id;
    int unit_id;
    COMBICODE_TYPE combi_code;
    STOCKCODE_TYPE stock_code;
    CURRENCY_TYPE balance;
    CURRENCY_TYPE current_cash;
    AMOUNT_TYPE business_amount;
    AMOUNT_TYPE current_amount;
    PRICE_TYPE business_price;
    int business_time;
    int entrust_id;
    ENTDIR_CODE_TYPE entrustdirection_code;
    CURRENCY_TYPE jy_fee;
    CURRENCY_TYPE js_fee;
    CURRENCY_TYPE yh_fee;
    CURRENCY_TYPE gh_fee;
    CURRENCY_TYPE qt_fee;
    CURRENCY_TYPE yj_fee;
    CURRENCY_TYPE jg_fee;
    CURRENCY_TYPE zg_fee;
    CURRENCY_TYPE js2_fee;
    int operator_id;
    struct timeval busi_timestamp;
    SUMMARY_TYPE summary;

    OperateType opType;
} Business;

#pragma pack()

#endif