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

function DMText:update(dt)
    local x, y = self:getPosition()
    x = x - self.speed * dt
    self:setPosition(x, y);
end
function QBDraw(painter)
    -- dm:draw(painter)
    -- dm1:draw(painter)
    -- print("called by parent")
end

function QBUpdate(dt)
    -- print(dt)
    -- dm:update(dt)
    -- dm1:update(dt)
    dd()
end
