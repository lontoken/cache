/**********************************************************************
* 子账户资金信息 unitasset
* Auth: ganlong
* Build: 2013.07.23
**********************************************************************/
#ifndef _CACHE_UNITASSET_H
#define _CACHE_UNITASSET_H

#pragma once

#include <sstream>
#include <vector>
#include "config.h"
#include "luaunit.h"
#include "base.h"

#define DATA_LEN_UNITASSET 14 

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
    CURRENCY_TYPE presale_fee;
    CURRENCY_TYPE input_balance;
    CURRENCY_TYPE output_balance;
    CURRENCY_TYPE input_total;
    CURRENCY_TYPE output_total;

    OperateType opType;
}UnitAsset;

typedef struct TCurrencyNote{
    CURRENCY_CODE_TYPE currency_code;
    UnitAsset* pUnitAsset;
}CurrencyNote;

typedef struct TUnitAssetNote{
    int unit_id;
    int noteSize;
    CurrencyNote* pCurNote;
}UnitAssetNote;

#pragma pack()

#define LUAPACK_UNITASSET_TABLE(L, p) lua_newtable(L); \
    lua_pushinteger(L, 1); lua_pushinteger(L, (p)->busin_date); lua_settable(L, -3); \
    lua_pushinteger(L, 2); lua_pushinteger(L, (p)->unit_id); lua_settable(L, -3); \
    lua_pushinteger(L, 3); lua_pushlstring(L, (p)->currency_code, sizeof(CURRENCY_CODE_TYPE)); lua_settable(L, -3); \
    lua_pushinteger(L, 4); lua_pushnumber(L, (p)->begin_cash); lua_settable(L, -3); \
    lua_pushinteger(L, 5); lua_pushnumber(L, (p)->current_cash); lua_settable(L, -3); \
    lua_pushinteger(L, 6); lua_pushnumber(L, (p)->prebuy_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 7); lua_pushnumber(L, (p)->prebuy_fee); lua_settable(L, -3); \
    lua_pushinteger(L, 8); lua_pushnumber(L, (p)->presale_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 9); lua_pushnumber(L, (p)->presale_fee); lua_settable(L, -3); \
    lua_pushinteger(L, 10); lua_pushnumber(L, (p)->input_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 11); lua_pushnumber(L, (p)->output_balance); lua_settable(L, -3); \
    lua_pushinteger(L, 12); lua_pushnumber(L, (p)->input_total); lua_settable(L, -3); \
    lua_pushinteger(L, 13); lua_pushnumber(L, (p)->output_total); lua_settable(L, -3); \
    lua_pushinteger(L, 14); lua_pushnumber(L, (p)->opType); lua_settable(L, -3)

#define LUAPACK_UNITASSET(L, p) \
    lua_pushinteger(L, (p)->busin_date); \
    lua_pushinteger(L, (p)->unit_id); \
    lua_pushlstring(L, (p)->currency_code, sizeof(CURRENCY_CODE_TYPE));\
    lua_pushnumber(L, (p)->begin_cash); \
    lua_pushnumber(L, (p)->current_cash); \
    lua_pushnumber(L, (p)->prebuy_balance); \
    lua_pushnumber(L, (p)->prebuy_fee); \
    lua_pushnumber(L, (p)->presale_balance); \
    lua_pushnumber(L, (p)->presale_fee); \
    lua_pushnumber(L, (p)->input_balance); \
    lua_pushnumber(L, (p)->output_balance); \
    lua_pushnumber(L, (p)->input_total); \
    lua_pushnumber(L, (p)->output_total); \
    lua_pushnumber(L, (p)->opType) 

#define LUAUNPACK_UNITASSET(L, p) \
    (p)->busin_date = PAI(L, 1); \
    (p)->unit_id = PAI(L, 2); \
    CS((p)->currency_code, L, 3); \
    (p)->begin_cash = PAI(L, 4); \
    (p)->current_cash = PAI(L, 5); \
    (p)->prebuy_balance = PAI(L, 6); \
    (p)->prebuy_fee = PAI(L, 7); \
    (p)->presale_balance = PAI(L, 8); \
    (p)->presale_fee = PAI(L, 9); \
    (p)->input_balance = PAI(L, 10); \
    (p)->output_balance = PAI(L, 11); \
    (p)->input_total = PAI(L, 12); \
    (p)->output_total = PAI(L, 13)

class UnitAssetStore{
public:
    UnitAssetStore(){};
    virtual ~UnitAssetStore(){};

    static UnitAssetStore& getInstance(){return m_instance;};

    UnitAsset* getUnitAsset(int unitId, CURRENCY_CODE_TYPE curCode);
    UnitAsset* addUnitAsset(UnitAsset* asset);
    UnitAsset* updateUnitAssetByTrade(UnitAsset* pAsset);

    int getUnitListSize(){return vUnitList.size();};
private:
    UnitAssetStore(UnitAssetStore const&){};              // copy ctor is hidden
    UnitAssetStore& operator=(UnitAssetStore const&){};           // assign op is hidden

    std::vector<UnitAssetNote*> vUnitList;
    static UnitAssetStore m_instance;
};


CACHE_LIB_API getUnitAsset(lua_State* L);

CACHE_LIB_API addUnitAsset(lua_State* L);

CACHE_LIB_API updateUnitAssetByTrade(lua_State* L);

int BinarySearchVector_UA(std::vector<UnitAssetNote*>::iterator it, int low, int high, int target, int *pos);

#endif