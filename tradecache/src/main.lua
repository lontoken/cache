package.cpath = ".\\?.dll"

require "cache"

local bs = string.byte("B");

local countUnit = 100;
local countStock = 100;
local stock = "";
local bg = os.clock();
local idx = 0;
for idx = 1, countUnit do
	for ii = 1000, countStock + 1000 do
		stock = "600" .. ii .. "SS";
		local res = cache.addUnitStock(20130714, idx, stock, bs, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);        
		 if res ~= 0 then
			print("add stock faild: " .. idx);
		 end
	end
end
local be = os.clock();
local count = countUnit * countStock;
print(string.format('stock add--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be - bg, (be - bg) * 1000000/count, bg, be));


local bg = os.clock();
local idx = 0;
for idx = 1, countUnit do
	for ii = 1000, countStock + 1000 do
		stock = "600" .. ii .. "SS";
		local res = cache.getUnitStock(idx, stock, bs);        
		if res ~= 0 then
			print("get stock faild: " .. idx);
		end
	end
end
local be = os.clock();
local count = countUnit * countStock;
print(string.format('stock get--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be - bg, (be - bg) * 1000000/count, bg, be));




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
print(string.format('add--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be -   bg,  (be - bg) * 1000000/count, bg, be));


local bg = os.clock();
for idx = 1, count do
     local res, ua = cache.getUnitAsset(idx, "CNY");    
     if res ~= 0 then
        print("get faild: " .. idx);
     end
end
local be = os.clock();
print(string.format('get--> : %d  cost:%0.4f, per: %d, be=%0.4f, bg=%.04f', count, be -   bg, (be - bg) * 1000000/count, bg, be));



print(cache.add(1.0,2.0))
print(cache.sub(20.1,19))
