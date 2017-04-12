local blue = require('blue')
local class = require('middleclass')
local md5 = require("md5")
local http = require('socket.http')
local SLAXML = require 'slaxml'

math.randomseed(os.time())
math.random()
math.random()
math.random()

local LiveDanmaku = class('LiveDanmaku')

function getJsonString(s)
    local count = 1
    local start = 1
    local can_start = false

    for i = 1, #s do
        local c = s:sub(i, i)
        if c == "{" then
            start = i + 1
            can_start = true;
            break
        end
    end
    if not can_start then
        return nil, nil
    end

    local out = "{"
    local _end = nil
    s = s:sub(start)
    for i = 1, #s do
        local c = s:sub(i, i)
        if c == "}" then
            count = count - 1
        else
            if c == "{" then
                count = count + 1
            end
        end
        out = out .. c
        if count == 0 then
            _end = i
            break
        end
    end
    if count ~= 0 then
        return nil, nil
    end
    return out, _end
end

function DMText:update(dt)
    local x, y = self:getPosition()
    x = x - self.speed * dt
    self:setPosition(x, y);
end

function LiveDanmaku:resetChannels()
    local w, h = getWindowSize()
    self.channels = {}
    self.c_keys = {}
    local j = 1;
    for i = 30, h, 30 do
        self.channels[tostring(i)] = true
        self.c_keys[j] = tostring(i)
        j = j + 1
    end
end

function LiveDanmaku:getYPosition()
    for k, v in ipairs(self.c_keys) do
        if (self.channels[v]) == true then
            self.channels[v] = false
            return v
        end
    end
    return self.c_keys[1]
end

function LiveDanmaku:init(url)
    self:resetChannels()
    self.danmaku = {}
    self.url = url
    self.client = blue.tcpClient()
    self.roomID = nil
    self.urls = {}
    self.current_url = self:get_live_address(url, 1)
    if (self.roomID ~= nil) then
        print(self.new_damaku_received)
        self.client:setCallback(self.new_damaku_received, self)
        local serverURL = self:get_cmt_server()
        print(serverURL)
        local success, err = self.client:connect(serverURL, 788, false)
        if not success then
            print("*******************************")
            print(err)
        end
        local b = tostring(math.floor(100000000000000 + 200000000000000 * math.random()))
        b = b:gsub("%.", "")
        b = b:gsub("e%+.*", tostring(math.random(1, 9)))
        -- s = '{"uid":148386509433407,"roomid":1016}'
        local s = '{"uid":'.. b .. ',"roomid":' .. self.roomID .. '}'
        print(s)
        s = self:make_data(s, 7)
        print(s)
        self.client:send(s)
        local s1 = self:make_data("", 2)
        self.client:send(s1)
        self.client:send(s1)
        self.client:send(s1)
        self.client:send(s1)
        self.client:send(s1)
        self.client:send(s1)
        self.client:setPing(true, 20, s1)
    end
end

function LiveDanmaku:update(dt)
    -- print("LiveDanmaku:update")
    local windowWidth, _ = getWindowSize()
    self:resetChannels()
    local need_delete = {}
    for k, v in pairs(self.danmaku) do
        v:update(dt)
        local x, y = v:getPosition()
        local w = v:width()
        if x + w < -10 then
            print("=====this will be delete====: \n====: "..v:getText())
            print("====position:  "..tostring(x).. " , "..tostring(y))
            print("====width: "..tostring(w))
            print("===========================")
            -- print("about to delete damaku")
            table.insert(need_delete, k)
        end
        if x + w > windowWidth then
            self.channels[tostring(y)] = false
        end
    end

    for i = #need_delete, 1, -1 do
        local dmt = self.danmaku[need_delete[i]]
        print("==**===confirm delete==**==: \n====: "..dmt:getText())
        local x, y = dmt:getPosition()
        local w = dmt:width()
        print("====position:  "..tostring(x).. " , "..tostring(y))
        print("====width: "..tostring(w))
        print("===========================")
        table.remove(self.danmaku, need_delete[i])
    end

    self.client:update(dt)

end

-- _type normal is 7
-- hand shack is 2
function LiveDanmaku:make_data(data, _type)
    data = string.pack(">i", #data + 16) .. '\x00\x10\x00\x01' .. string.pack('>i', _type)..string.pack('>i', 1)..data
    return data
end

function LiveDanmaku:get_live_roomID(url)
    local body, headers, code = http.request(url)
    local roomID = 0;
    _,_,_,roomID = string.find(body, "(var ROOMID = )(%d+)(;)")
    print(roomID)
    return roomID
end

function LiveDanmaku:get_live_address(url, index)
    if #self.urls > index then
        return self.urls[index]
    end
    self.roomID = self:get_live_roomID(url)
    url = "platform=android&cid="..self.roomID.."&quality=1&otype=xml&appkey=&type=mp4&rnd="..tostring(math.random(1, 9999))
    print(url)
    local tmp = url
    local sign = md5.sumhexa(tmp)
    url = "http://live.bilibili.com/api/playurl?"..url.."&sign="..sign
    print(url)
    body, _, _ = http.request(url)
    print(body)
    url = self:get_address(body, index)
    print("finaly i got: "..url)
    return url
end

function LiveDanmaku:get_address(xml, index)
    self.urls = {}
    local parser = SLAXML:parser{
        text = function(text)
            if #text > 15 then
                print(text)
                table.insert(self.urls, text)
            end
        end
    }
    parser:parse(xml, {stripWhitespace=true})
    return self.urls[index]
end

function LiveDanmaku:get_cmt_server()
    local r = http.request('http://live.bilibili.com/api/player?id=cid:' .. self.roomID)
    print(r)
    local a,b,serverURL,c = string.find(r, "<server>(.*)</server>")
    print(a)
    print(b)
    print(serverURL)
    print(c)
    return serverURL
end

function LiveDanmaku:intToRGB(rgbint)
    local r = math.floor(rgbint / 256 / 256 % 256)
    local g = math.floor(rgbint / 256 % 256)
    local b = math.floor(rgbint % 256)
    return r, g, b
end

function LiveDanmaku:new_damaku_received(data)
    print("data::::"..data)
    local w, h = getWindowSize()
    print(w)
    local out, _end = getJsonString(data)
    while out do
        if out:find("DANMU_MSG") == nil then
            break
        end
        print("get json string:---->"..out)
        local func = function()
            local obj = cjson.decode(out)
            local cmd = obj.cmd
            if (cmd and cmd == "DANMU_MSG") then
                local info = obj.info
                if (info) then
                    if (#info >= 3) then
                        local danmaku_info = info[1]
                        local fontSize = danmaku_info[3]
                        local color = danmaku_info[4]
                        local content = info[2]
                        local u_info = info[3]
                        local u_name = ""
                        if (u_info and #u_info >= 2) then
                            u_name = u_info[2]
                        end
                        local dm = DMText:new(content)
                        local y = self:getYPosition()
                        dm:setPosition(w, y)
                        dm:setColor(self:intToRGB(color))
                        dm:setAlpha(200)
                        local dm_w = dm:width()
                        local delay = 10;
                        dm.speed = (w + dm_w) / delay;
                        table.insert(self.danmaku, dm)
                    end
                end
            end
        end
        local ret, err = pcall(func)
        if not ret then
            print(err)
        end
    if _end then
        data = data:sub(_end)
        out, _end = getJsonString(data)
    else
        data = nil
    end

    end
end

function LiveDanmaku:draw(painter)
    for k, v in pairs(self.danmaku) do
        v:draw(painter)
    end
end

return LiveDanmaku
