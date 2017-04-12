require("bi")
--[[socket = require("socket")
require("bi")
print("****&*&*&*&*&*&*")
print(string.pack(">i", 54))
print(string.format("%06X",6))
value2 = ''
key = 'cmpg'
value1 = '\x00\x00\x00\x00\x00\x00\x00\x01'
print(string.pack(">i", #value1), #value1)
value2 = string.format("%s%s%s", key, string.pack(">i", #value1), value1)
print(value2)
local http = require("socket.http")
local url = "http://www.baidu.com"
local body, headers, code = http.request(url)
print(code)
print(headers)
-- print(body)
]]--

--[[
local Colors = require("Colors")
local dm = DMText:new("中文And English Σ(*ﾟдﾟﾉ)")
local dm1 = DMText:new("English with diffrent color English with diffrent color English with diffrent color English with diffrent color English with diffrent color English with diffrent color English with diffrent color English with diffrent color")
dm1:setColor(unpack(Colors.Gold))
dm1:setAlpha(150)
local w = 800
dm1:setPosition(w, 400)
dm:setPosition(w, 300)
dm:setColor(unpack(Colors.Pink))
dm:setAlpha(150)

local dm_w = dm:width()
local dm1_w = dm1:width()
print(DMText)
print (dm)
local delay = 10;
dm.speed = (w + dm_w) / delay;
dm1.speed = (w + dm1_w) / delay;
print(dm.speed)
print(dm1.speed)
]]--

--[[
local text = '{"info":[[0,1,25,16777215,1481644422,2114849008,0,"5d6ed2f6",0],"110",[19858282,"晓风残月泣",0,0,0,10000,1],[10,"坂粉","坂本叔",1000,11433699],[20,0,6215679,">50000"],["title-75-1","title-75-1"],0,0],"cmd":"DANMU_MSG"}'
local v = cjson.decode(text)
function pp(t)
    if (type(t) == "table") then
        for k, v in pairs(t) do
            print(k.." ---> " .. tostring(v))
            if type(v) == "table" then
                pp(v)
            end
        end
    else
        print("-->" .. t)
    end
end
pp(v)
]]--

local LiveDanmaku = require('live_danmaku')

local liveDanmakuInstance = nil

function QBGetLiveAdress(url, index)
    liveDanmakuInstance = LiveDanmaku(url)
    return liveDanmakuInstance:get_live_address(url, index)
    -- local l = LiveDanmaku(url)
    -- return l:get_live_address(url, index)
end

function DMText:update(dt)
    local x, y = self:getPosition()
    x = x - self.speed * dt
    self:setPosition(x, y);
end
function QBDraw(painter)
    -- dm:draw(painter)
    -- dm1:draw(painter)
    -- print("called by parent")
    if (liveDanmakuInstance ~= nil) then
        liveDanmakuInstance:draw(painter)
    end
end

function QBUpdate(dt)
    -- print(dt)
    -- dm:update(dt)
    -- dm1:update(dt)
    -- dd()
    if (liveDanmakuInstance ~= nil) then
        liveDanmakuInstance:update(dt)
    end
end
