#include <iostream>
#include "unitasset.h"

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

int main()
{
    UnitAsset* pRes;
    STOCKCODE_TYPE pCode;
    cout << sizeof(pRes) << "  " << sizeof(UnitAsset) << "  " << sizeof(*pRes) << endl;
    cout << sizeof(pCode) << "  " << sizeof(STOCKCODE_TYPE) << "  " << sizeof(*pCode) << endl;

    unitAssetTest();

    int i;
    cin >> i;

    return 0;
}