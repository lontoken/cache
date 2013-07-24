#include <iostream>
#include "base.h"
#include "unitstock.h"
#include "hashsearch.h"

UnitStockStore UnitStockStore::m_instance;

int BinarySearchVector_US(std::vector<UnitStockNote*>::iterator it, int low, int high, int target, int *pos)
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

int AddHashTable_US(char *pStr, UnitStockStockCode *lpTable, int nTableSize)
{
    const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;

    unsigned long nHash = HashString(pStr, HASH_OFFSET);
    unsigned long nHashA = HashString(pStr, HASH_A);
    unsigned long nHashB = HashString(pStr, HASH_B);
    int nHashStart = nHash % nTableSize;
    int nHashPos = nHashStart;

    while( lpTable[nHashPos].bExists ){
        nHashPos = (nHashPos + 1) % nTableSize;

        if(nHashPos == nHashStart){
            return -1;
        }
    }

    lpTable->bExists = '1';
    lpTable->nHashA = nHashA;
    lpTable->nHashB = nHashB;

    return nHashPos;
}

int GetHashTablePos_US(char *pStr, UnitStockStockCode *lpTable, int nTableSize)
{
    const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;

    unsigned long nHash = HashString(pStr, HASH_OFFSET);
    unsigned long nHashA = HashString(pStr, HASH_A);
    unsigned long nHashB = HashString(pStr, HASH_B);
    int nHashStart = nHash % nTableSize;
    int nHashPos = nHashStart;

    while( lpTable[nHashPos].bExists ){
        if(lpTable[nHashPos].nHashA == nHashA &&  lpTable[nHashPos].nHashB == nHashB){
            return nHashPos;
        }else{
            nHashPos = (nHashPos + 1) % nTableSize;
        }

        if(nHashPos == nHashStart) break;
    }
    return -1;
}


CACHE_LIB_API getUnitStock(lua_State* L)
{
    return 1;
}

CACHE_LIB_API addUnitStock(lua_State* L)
{
    return 1;
}

CACHE_LIB_API updateUnitStockByTrade(lua_State* L)
{
    return 1;
}


UnitStock* UnitStockStore::addUnitStock(UnitStock* pUnitStock)
{
    int idx = 0;
    int pos = 0;
    UnitStockStore& pUs = UnitStockStore::getInstance();
    int unitId = pUnitStock->unit_id;

    idx = BinarySearchVector_US(pUs.vUnitList.begin(), 0, pUs.vUnitList.size() - 1, unitId, &pos);

    //没有此子账户的股份数据
    if(idx < 0){
        UnitStockNote* pNote = new UnitStockNote();
        memset(pNote, 0, sizeof(UnitStockNote));
        pNote->unit_id = unitId;
        pNote->noteCapacity = HASHTABLESIZE_W;
        pNote->pStockNote = new UnitStockStockCode[pNote->noteCapacity];
        memset(pNote->pStockNote, 0, sizeof(UnitStockStockCode) * pNote->noteCapacity);

        BSNote* pBs = NULL;
        int hashPos = AddHashTable_US(pUnitStock->stock_code, pNote->pStockNote, pNote->noteCapacity);
        if(hashPos >= 0){
            UnitStockStockCode* pStock = pNote->pStockNote + hashPos;
            pBs = new BSNote();
            memset(pBs, 0, sizeof(BSNote));
            pStock->pBs = pBs;

            pBs->bs = pUnitStock->bs;
            pBs->pUnitStock = pUnitStock;
        }else{
            ASSERT(false);
        } 

        pUs.vUnitList.insert(pUs.vUnitList.begin() + pos, pNote);
        return pUnitStock;
    }else{
        UnitStockNote* pNote = (pUs.vUnitList)[idx];

        BSNote* pBs = NULL;
        int hashPos = GetHashTablePos_US(pUnitStock->stock_code, pNote->pStockNote, pNote->noteCapacity);

        //没有对应的证券的持仓信息
        if(hashPos < 0){
            hashPos = AddHashTable_US(pUnitStock->stock_code, pNote->pStockNote, pNote->noteCapacity);
            if(hashPos < 0){
                int hashSize = getNextHashTableSize(pNote->noteCapacity);
                UnitStockStockCode* pNewStock = new UnitStockStockCode[hashSize];
                memset(pNewStock, 0, sizeof(UnitStockStockCode) * hashSize);
                memcpy(pNewStock, pNote->pStockNote, sizeof(UnitStockStockCode) * pNote->noteCapacity);
                delete [] pNote->pStockNote;
                pNote->pStockNote = pNewStock;
                pNote->noteCapacity = hashSize;
                //..todo 之前的HASH会失效

                hashPos = AddHashTable_US(pUnitStock->stock_code, pNote->pStockNote, pNote->noteCapacity);
            }

            UnitStockStockCode* pStock = pNote->pStockNote + hashPos;
            pBs = new BSNote();
            memset(pBs, 0, sizeof(BSNote));
            pStock->pBs = pBs;

            pBs->bs = pUnitStock->bs;
            pBs->pUnitStock = pUnitStock;

            return pUnitStock;
        }else{
            UnitStockStockCode* pStock = pNote->pStockNote + hashPos;
            if(pStock->pBs->bs != pUnitStock->bs){
                ASSERT(false);
            }else{
                return NULL;
            }
        }
    }

    return NULL;
}


UnitStock* UnitStockStore::getUnitStock(int unitId, STOCKCODE_TYPE stock, BS_TYPE bs)
{
    int idx = 0;
    int pos = 0;
    UnitStockStore& pUs = UnitStockStore::getInstance();

    idx = BinarySearchVector_US(pUs.vUnitList.begin(), 0, pUs.vUnitList.size() - 1, unitId, &pos);
    if(idx >= 0){
        UnitStockNote* pNote = (pUs.vUnitList)[idx];
        int hashPos = GetHashTablePos_US(stock, pNote->pStockNote, pNote->noteCapacity);
        if(hashPos >= 0){
            UnitStockStockCode* pStock = pNote->pStockNote + hashPos;
            if(pStock->pBs->bs == bs){
                return pStock->pBs->pUnitStock;
            }
        }
    }

    return NULL;
}

UnitStock* UnitStockStore::updateUnitStockByTrade(UnitStock* pAsset)
{
    UnitStock* pData = this->getUnitStock(pAsset->unit_id, pAsset->stock_code, pAsset->bs);   
    if(pData){
        pData->current_amount = pAsset->current_amount;
        pData->prebuy_amount = pAsset->prebuy_amount;
        pData->presale_amount = pAsset->presale_amount;
        pData->prebuy_balance = pAsset->prebuy_balance;
        pData->presale_balance = pAsset->presale_balance;
        pData->sale_amount = pAsset->sale_amount;
        pData->buy_balance = pAsset->buy_balance;
        pData->sale_balance = pAsset->sale_balance;
        pData->buy_fee = pAsset->buy_fee;
        pData->sale_fee = pAsset->sale_fee;

        if(OperateTypeGet == pData->opType){
            pData->opType = OperateTypeUpdate;
        }

        return pData;
    }else{
        return NULL;
    }
}