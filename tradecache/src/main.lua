package.cpath = ".\\?.dll"

require "cache"

--local p1, p2, p3, p4 = cache.getUnitAsset(1, "CNY");
--print(p1, p2, p3, p4);

local res, ua = cache.getUnitAsset(1, "CNY");
print(res);
if res == 0 then
    print(ua[1]);
    print(ua[2]);
end

local count = 10000;

local bg = os.clock();

local idx = 0;
for idx = 1, count do
     local res = cache.addUnitAsset(20130724, idx, "CNY", 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);        
     if res ~= 0 then
        print("add faild: " .. idx);
     end
end

local be = os.clock();
print(string.format('add--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be -   bg,  (be - bg) * 1000000/count, be, bg));


local bg = os.clock();
for idx = 1, count do
     local res, ua = cache.getUnitAsset(idx, "CNY");    
     if res ~= 0 then
        print("get faild: " .. idx);
     end
end
local be = os.clock();
print(string.format('get--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be -   bg, (be - bg) * 1000000/count, be, bg));


local r = cache.addUnitAsset(1, 2, "CNY", 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
print("r = " .. r);
if r == 0 then
    
    r, ua = cache.getUnitAsset(2, "CNY");
    if r == 0 then
        print(ua[1]);
        print(ua[2]);
        print(ua[3]);
        print(ua[4]);
    end
end

res = cache.updateUnitAssetByTrade(2, "CNY", 10, 20, 12, 13, 14);
print("update: res = ".. res);
if res == 0 then
    r, ua = cache.getUnitAsset(2, "CNY");
    if r == 0 then
        print(ua[1]);
        print(ua[2]);
        print(ua[3]);
        print(ua[4]);
        print(ua[5]);
        print(ua[6]);
        print(ua[7]);
        print(ua[8]);
    end
end

print(cache.add(1.0,2.0))
print(cache.sub(20.1,19))
