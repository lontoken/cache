#include <iostream>
#include "unitasset.h"
#include "unitstock.h"
#include "hashsearch.h"

using namespace std;

void unitAssetTest()
{
    UnitAssetStore& ua = UnitAssetStore::getInstance();
    UnitAsset* pRes = NULL;
    UnitAsset* asset = new UnitAsset();

    asset->unit_id = 1;
    snprintf(asset->currency_code, sizeof(asset->currency_code), "%s", "CNY");
    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "size: " << ua.getUnitListSize() << endl;        
    }

    asset = new UnitAsset();
    asset->unit_id = 3;
    snprintf(asset->currency_code, sizeof(asset->currency_code), "%s", "CNY");
    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "size: " << ua.getUnitListSize() << endl;        
    }

    asset = new UnitAsset();
    asset->unit_id = 2;
    snprintf(asset->currency_code, sizeof(asset->currency_code), "%s", "CNY");
    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "size: " << ua.getUnitListSize() << endl;        
    }

    asset = new UnitAsset();
    asset->unit_id = 10;
    snprintf(asset->currency_code, sizeof(asset->currency_code), "%s", "CNY");
    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "size: " << ua.getUnitListSize() << endl;        
    }

    asset = new UnitAsset();
    asset->unit_id = 8;
    snprintf(asset->currency_code, sizeof(asset->currency_code), "%s", "CNY");
    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "size: " << ua.getUnitListSize() << endl;        
    }

    pRes = ua.addUnitAsset(asset);
    if(pRes){
        cout << "--size: " << ua.getUnitListSize() << endl;        
    }

    asset = ua.getUnitAsset(1, "CNY");
    if(asset){
        cout << "get: 1: " << asset->unit_id << endl;
    }

    asset = ua.getUnitAsset(8, "CNY");
    if(asset){
        cout << "get: 8: " << asset->unit_id << endl;
    }

    asset->current_cash = 100;
    pRes = ua.updateUnitAssetByTrade(asset);
    if(pRes){
        cout << "update: 8: " << asset->current_cash << endl;
    }
}

void testUnitStock()
{
    UnitStockStore& us = UnitStockStore::getInstance();
    UnitStock* pRes = NULL;

    UnitStock* asset = new UnitStock();
    memset(asset, 0, sizeof(UnitStock));
    asset->unit_id = 1;
    snprintf(asset->stock_code, sizeof(asset->stock_code), "%s", "600570SS");
    asset->bs = 'B';
    pRes = us.addUnitStock(asset);
    if(pRes){
        cout << "size: " << us.getUnitListSize() << endl;        
    }

    asset = new UnitStock();
    memset(asset, 0, sizeof(UnitStock));
    asset->unit_id = 2;
    snprintf(asset->stock_code, sizeof(asset->stock_code), "%s", "600570SS");
    asset->bs = 'B';
    pRes = us.addUnitStock(asset);
    if(pRes){
        cout << "size: " << us.getUnitListSize() << endl;        
    }

    asset = us.getUnitStock(2, "600570SS", 'B');
    if(asset){
        cout <<"get: "<< asset->unit_id << ", " << asset->stock_code << endl;
    }
}

int main()
{

    //unitAssetTest();
    testUnitStock();

    int i;
    cin >> i;

    return 0;
}