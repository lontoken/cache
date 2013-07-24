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

#define DATA_LEN_UNITSTOCK 21

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

#define LUAPACK_UNITSTOCK_TABLE(L, p) lua_newtable(L); \
    lua_pushinteger(L, 1); lua_pushinteger(L, (p)->busin_date); lua_settable(L, -3); \
    lua_pushinteger(L, 2); lua_pushinteger(L, (p)->unit_id); lua_settable(L, -3); \
    lua_pushinteger(L, 3); lua_pushlstring(L, (p)->stock_code, sizeof(STOCKCODE_TYPE)); lua_settable(L, -3); \
    lua_pushinteger(L, 4); lua_pushinteger(L, (int)((p)->bs)); lua_settable(L, -3); \
    lua_pushinteger(L, 5); lua_pushnumber(L, (p)->begin_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 6); lua_pushnumber(L, (p)->begin_cost); lua_settable(L, -3); \
    lua_pushinteger(L, 7); lua_pushnumber(L, (p)->begin_total_profit); lua_settable(L, -3); \
    lua_pushinteger(L, 8); lua_pushnumber(L, (p)->begin_total_buyfee); lua_settable(L, -3); \
    lua_pushinteger(L, 9); lua_pushnumber(L, (p)->begin_total_salefee); lua_settable(L, -3); \
    lua_pushinteger(L, 10); lua_pushnumber(L, (p)->current_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 11); lua_pushnumber(L, (p)->prebuy_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 12); lua_pushnumber(L, (p)->presale_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 13); lua_pushnumber(L, (p)->prebuy_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 14); lua_pushnumber(L, (p)->presale_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 15); lua_pushnumber(L, (p)->buy_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 16); lua_pushnumber(L, (p)->sale_amount); lua_settable(L, -3); \
    lua_pushinteger(L, 17); lua_pushnumber(L, (p)->buy_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 18); lua_pushnumber(L, (p)->sale_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 19); lua_pushnumber(L, (p)->buy_fee); lua_settable(L, -3); \
    lua_pushinteger(L, 20); lua_pushnumber(L, (p)->sale_fee); lua_settable(L, -3); \
    lua_pushinteger(L, 21); lua_pushnumber(L, (p)->opType); lua_settable(L, -3)

#define LUAUNPACK_UNITSTOCK(L, p) \
    (p)->busin_date = PAI(L, 1); \
    (p)->unit_id = PAI(L, 2); \
    CS((p)->stock_code, L, 3); \
    (p)->bs = PAC(L, 4); \
    (p)->begin_amount = PAI(L, 5); \
    (p)->begin_cost = PAI(L, 6); \
    (p)->begin_total_profit = PAI(L, 7); \
    (p)->begin_total_buyfee = PAI(L, 8); \
    (p)->begin_total_salefee = PAI(L, 9); \
    (p)->current_amount = PAI(L, 10); \
    (p)->prebuy_amount = PAI(L, 11); \
    (p)->presale_amount = PAI(L, 12); \
    (p)->prebuy_balance = PAI(L, 13); \
    (p)->presale_balance = PAI(L, 14); \
    (p)->buy_amount = PAI(L, 15); \
    (p)->sale_amount = PAI(L, 16); \
    (p)->buy_balance = PAI(L, 17); \
    (p)->sale_balance = PAI(L, 18); \
    (p)->buy_fee = PAI(L, 19); \
    (p)->sale_fee = PAI(L, 20)


class UnitStockStore{
public:
    UnitStockStore(){};
    virtual ~UnitStockStore(){};

    static UnitStockStore& getInstance(){return m_instance;};

    UnitStock* addUnitStock(UnitStock* pUnitStock);
    UnitStock* getUnitStock(int unitId, STOCKCODE_TYPE stock, BS_TYPE bs);
    UnitStock* updateUnitStockByTrade(UnitStock* pAsset);

    int getUnitListSize(){return vUnitList.size();};
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