/**********************************************************************
* 子账户股份信息 unitstock
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_UNITSTOCK_H
#define _CACHE_UNITSTOCK_H

#pragma once

#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>  
#include "config.h"
#include "luaunit.h"
#include "base.h"

using namespace std;

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

typedef struct TBSNote{
    BS_TYPE bs;
    UnitStock* pUnitStock;
}BSNote;

typedef struct TUnitStockStockCode{
    STOCKCODE_TYPE stock_code;
    unsigned long nHashA;
    unsigned long nHashB;
    char bExists;
    BSNote* pBs;
}UnitStockStockCode;

typedef struct TUnitStockNote{
    int unit_id;
    int noteSize;
    int noteCapacity;
    UnitStockStockCode* pStockNote;
}UnitStockNote;

#pragma pack()

class UnitStockStore{
public:
    UnitStockStore(){};
    virtual ~UnitStockStore(){};

    static UnitStockStore& getInstance(){return m_instance;};

    UnitStock* addUnitStock(UnitStock* pUnitStock);
    UnitStock* getUnitStock(int unitId, STOCKCODE_TYPE stock, BS_TYPE bs);
    UnitStock* updateUnitStockByTrade(UnitStock* pAsset);
private:
    UnitStockStore(UnitStockStore const&){};              // copy ctor is hidden
    UnitStockStore& operator=(UnitStockStore const&){};           // assign op is hidden

    std::vector<UnitStockNote*> vUnitList;
    static UnitStockStore m_instance;
};

CACHE_LIB_API getUnitStock(lua_State* L);

CACHE_LIB_API addUnitStock(lua_State* L);

CACHE_LIB_API updateUnitStockByTrade(lua_State* L);

int BinarySearchVector_US(std::vector<UnitStockNote*>::iterator it, int low, int high, int target, int *pos);
int AddHashTable_US(char *pStr, UnitStockStockCode *lpTable, int nTableSize);
int GetHashTablePos_US(char *pStr, UnitStockStockCode *lpTable, int nTableSize);

#endif