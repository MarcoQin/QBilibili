s = '{"cmd":"WELCOME","data":{"uid":14980106,"uname":"中文名","isadmin":0,"vip":1}}'
s = '{"cmd":"WELCOME","data":{"uid":14980106,"uname":"中文名","isadmin":0,"vip":1}}{"cmd":"WELCOME","data":{"uid":14980106,"uname":"中文名","isadmin":0,"vip":1}}'

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
    return out, _end
end

local s0, _end = getJsonString(s)
print(s0)
while s0 do
    s = s:sub(_end)
    s0, _end = getJsonString(s)
    print(s0)
end

