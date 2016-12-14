-- class = require('middleclass')
-- require('LUBE')
local http = require('socket.http')
local md5 = require("md5")
local SLAXML = require 'slaxml'
math.randomseed(os.time())
math.random()
math.random()
math.random()

function get_live_address(url, index)
    local body, headers, code = http.request(url)
    local roomID = 0;
    _,_,_,roomID = string.find(body, "(var ROOMID = )(%d+)(;)")
    print(roomID)
    url = "platform=android&cid="..roomID.."&quality=1&otype=xml&appkey=&type=mp4&rnd="..tostring(math.random(1, 9999))
    print(url)
    local tmp = url
    local sign = md5.sumhexa(tmp)
    url = "http://live.bilibili.com/api/playurl?"..url.."&sign="..sign
    print(url)
    body, _, _ = http.request(url)
    print(body)
    url = get_address(body, index)
    print("finaly i got: "..url)
    return url
end

function get_address(xml, index)
    local urls = {}
    local parser = SLAXML:parser{
        text = function(text)
            if #text > 15 then
                print(text)
                table.insert(urls, text)
            end
        end
    }
    parser:parse(xml, {stripWhitespace=true})
    return urls[index]
end


-- local url = "http://live.bilibili.com/1000"
-- get_live_address(url)

-- _type normal is 7
-- hand shack is 2
function make_data(data, _type)
    data = string.pack(">i", #data + 16) .. '\x00\x10\x00\x01' .. string.pack('>i', _type)..string.pack('>i', 1)..data
    return data
end

local socket = require('socket')
c, error_message = socket.connect("livecmt-2.bilibili.com", 788)
if (c == nil)  then
    print("connect failed  "..error_message)
end
c:settimeout(0)
-- s = '{"uid":148386509433407,"roomid":1016}'
s = '{"uid":148386509433407,"roomid":39936}'
s = '{"uid":263172571157652,"roomid":39936}'
-- s = '{"uid":148386509433407,"roomid":5067}'
s = make_data(s, 7)
print(s)
c:send(s)
-- s = '\x00\x00\x006\x00\x10\x00\x01\x00\x00\x00\x07\x00\x00\x00\x01{"uid":148386509433407,"roomid":12265}'
-- s = '\x00\x00\x005\x00\x10\x00\x01\x00\x00\x00\x07\x00\x00\x00\x01{"uid":243998525188999,"roomid":1016}'
-- c:send(s)
-- s = '\x00\x00\x00\x10\x00\x10\x00\x01\x00\x00\x00\x02\x00\x00\x00\x01'
-- c:send(s)
-- c:send(s)
-- c:send(s)
-- c:send(s)
s1 = make_data("", 2)
c:send(s1)
c:send(s1)
c:send(s1)
c:send(s1)
c:send(s1)
c:send(s1)
-- c:send(s1)
function dd()
while  true  do
    -- print("prepare for receive")
    -- local skt, e, p = c:receive(1024)
    local skt, e, p = c:receive(8192)
    -- print(skt)
    -- print(e)
    if (skt) then  print("SKT*******"..skt)  end
    if (#p > 10) then  print(p)  end
    if (not skt) then print("not skt");break; end
    if (e) then print(e);break; end
end -- /while-do
end
-- co = coroutine.create(dd)
-- coroutine.resume(co)
