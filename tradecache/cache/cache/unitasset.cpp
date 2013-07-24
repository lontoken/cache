#include <iostream>
#include "base.h"
#include "unitasset.h"

using namespace std;

UnitAssetStore UnitAssetStore::m_instance;

int BinarySearchVector_UA(std::vector<UnitAssetNote*>::iterator it, int low, int high, int target, int *pos)
{
    int mid = 0;
    int curVal = 0;
    int posTmp = low;
    while(low <= high)
    {
        mid = (low + high) / 2;
        curVal = (*(it + mid))->unit_id;

        if (target < curVal){
            high = mid - 1;
            posTmp = mid; 
        }else if(curVal < target){
            low = mid + 1;
            posTmp = mid + 1;
        }else{
            return mid;
        }   
    }

    *pos = posTmp;

    return -1;
}

//获取子账户的指定币种的资金信息
//@param 1 int 子账户ID
//@param 2 str 币种
//@return 1 0:找到数据  非0:没找到
//@return 2 table{busin_date, unit_id, currency_code, begin_cash, current_cash, 
//          prebuy_balance, prebuy_fee, presale_balance, input_balance, output_balance, 
//          input_total, output_total, opType}
CACHE_LIB_API getUnitAsset(lua_State* L)
{
    int unitId = 0;
    CURRENCY_CODE_TYPE curCode = {0};

    unitId = PAI(L, 1);
    CS(curCode, L, 2);

    UnitAsset* pAsset = UnitAssetStore::getInstance().getUnitAsset(unitId, curCode);
    //UnitAsset* pAsset = new UnitAsset();
    //pAsset->busin_date = 2;
    //pAsset->unit_id = 21;
    //snprintf(pAsset->currency_code, sizeof(pAsset->currency_code), "CNY");

    if(pAsset){
        PN(L, 0);
        LUAPACK_UNITASSET_TABLE(L, pAsset);
        return 2;
    }else{
        PN(L, 1);
        return 1;
    }
}


//添加子账户资金信息
//@param {busin_date, unit_id, currency_code, begin_cash, current_cash, 
//          prebuy_balance, prebuy_fee, presale_balance, presale_fee, input_balance, 
//          output_balance, input_total, output_total}
//@return 0:成功  非0:失败
CACHE_LIB_API addUnitAsset(lua_State* L)
{
    UnitAsset* pAsset = new UnitAsset();
    memset(pAsset, 0, sizeof(UnitAsset));

    LUAUNPACK_UNITASSET(L, pAsset);

    //cout << "unitid=" << pAsset->unit_id << ", code=" << pAsset->currency_code << endl;

    UnitAsset* pRes = UnitAssetStore::getInstance().addUnitAsset(pAsset);
    if(pRes){
        PN(L, 0);
    }else{
        PN(L, 1);
    }

    return 1;
}


//更新子账户资金信息
//@param {unit_id, currency_code, current_cash, prebuy_balance, prebuy_fee, 
//          presale_balance, presale_fee}
//@return 0:成功  非0:失败
CACHE_LIB_API updateUnitAssetByTrade(lua_State* L)
{
    UnitAsset asset;
    memset(&asset, 0, sizeof(UnitAsset));
    asset.unit_id = PAI(L, 1); 
    CS(asset.currency_code, L, 2); 
    asset.current_cash = PAI(L, 3); 
    asset.prebuy_balance = PAI(L, 4); 
    asset.prebuy_fee = PAI(L, 5); 
    asset.presale_balance = PAI(L, 6); 
    asset.presale_fee = PAI(L, 7);


    //cout << "update unitid=" << asset.unit_id << ", code=" << asset.currency_code << endl;

    UnitAsset* pRes = UnitAssetStore::getInstance().updateUnitAssetByTrade(&asset);
    if(pRes){
        PN(L, 0);
    }else{
        PN(L, 1);
    }

    return 1;
}


//-----------UnitAssetStore 类的实现---------------
UnitAsset* UnitAssetStore::addUnitAsset(UnitAsset* asset)
{
    int idx = 0;
    int pos = 0;
    UnitAssetStore& pUa = UnitAssetStore::getInstance();
    int unitId = asset->unit_id;

    idx = BinarySearchVector_UA(pUa.vUnitList.begin(), 0, pUa.vUnitList.size() - 1, unitId, &pos);
    if(idx < 0){
        //cout << "UnitAssetStore::addUnitAsset:idx = " << idx << ", pos= " << pos << endl;

        UnitAssetNote* pNote = new UnitAssetNote();
        memset(pNote, 0, sizeof(UnitAssetNote));
        pNote->unit_id = unitId;
        
        CurrencyNote* pCurNote = new CurrencyNote();
        memset(pCurNote, 0, sizeof(CurrencyNote));
        snprintf(pCurNote->currency_code, sizeof(pCurNote->currency_code), "%s", asset->currency_code);
        pCurNote->pUnitAsset = asset;
        asset->opType = OperateTypeGet;

        pNote->pCurNote = pCurNote;
        pNote->noteSize++;

        pUa.vUnitList.insert(pUa.vUnitList.begin() + pos, pNote);
        return asset;
    }else{
        //cout << "UnitAssetStore::addUnitAsset:==idx=" << idx << endl;
        UnitAssetNote* pNote = (pUa.vUnitList)[idx];

        for(idx = 0; idx < pNote->noteSize; ++idx){
            if(strcmp(asset->currency_code, pNote->pCurNote[idx].currency_code) == 0){
                break;
            }
        }

        //没有找到对应币种的资金信息
        if(idx == pNote->noteSize){
            CurrencyNote* pCurNote = new CurrencyNote[pNote->noteSize + 1];
            if(idx == 1){
                delete pNote->pCurNote;
            }else{
                memcpy(pCurNote, pNote->pCurNote, pNote->noteSize * sizeof(CurrencyNote));
                delete [] pNote->pCurNote;
                pNote->pCurNote = pCurNote;
                pCurNote = pNote->pCurNote + pNote->noteSize;
                pNote->noteSize++;

                pCurNote->pUnitAsset = asset;
                asset->opType = OperateTypeGet;
                snprintf(pCurNote->currency_code, sizeof(pCurNote->currency_code), "%s", asset->currency_code);
            }
        }

        return NULL;
    }
}


UnitAsset* UnitAssetStore::getUnitAsset(int unitId, CURRENCY_CODE_TYPE curCode)
{
    int idx = 0;
    int pos = 0;
    UnitAssetStore& pUa = UnitAssetStore::getInstance(); 

    idx = BinarySearchVector_UA(pUa.vUnitList.begin(), 0, pUa.vUnitList.size() - 1, unitId, &pos);
    if(idx >= 0){
        UnitAssetNote* pNote = (pUa.vUnitList)[idx];

        for(idx = 0; idx < pNote->noteSize; ++idx){
            if(strcmp(curCode, pNote->pCurNote[idx].currency_code) == 0){
                return pNote->pCurNote[idx].pUnitAsset;
            }
        }
    }

    return NULL;
}

UnitAsset* UnitAssetStore::updateUnitAssetByTrade(UnitAsset* pAsset)
{
    UnitAsset* pData = this->getUnitAsset(pAsset->unit_id, pAsset->currency_code);   
    if(pData){
        pData->current_cash = pAsset->current_cash;
        pData->prebuy_balance = pAsset->prebuy_balance;
        pData->presale_balance = pAsset->presale_balance;
        pData->prebuy_fee = pAsset->prebuy_fee;
        pData->presale_fee = pAsset->presale_fee;
        
        if(OperateTypeGet == pData->opType){
            pData->opType = OperateTypeUpdate;
        }

        return pData;
    }else{
        return NULL;
    }
}
//-----------UnitAssetStore 类的实现---------------