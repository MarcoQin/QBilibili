local class = require('middleclass')
local socket = require('socket')

local client = class('client')

function client:init()
    self.host = nil
    self.port = nil
    self.connected = false
    self.socket = nil
    self.callbacks = {
        recv = nil
    }
    self.handshake = nil
    self.ping = nil
end

function client:setPing(enabled, time, msg)
    -- If ping is enabled, create a self.ping
    -- and set the time(second) and the message in it,
    -- but most importantly, keep the time.
    -- If disabled, set self.ping to nil.
    if enabled then
        self.ping = {
            time = time,
            msg = msg,
            timer = time
        }
    else
        self.ping = nil
    end
end

function client:connect(host, port, dns)
    -- Verify our inputs.
    if not host or not port then
        return false, "Invalid arguments"
    end
    -- Resolve dns if needed (dns is true by default).
    if dns ~= false then
        local ip = socket.dns.toip(host)
        if not ip then
            return false, "DNS lookup failed for" .. host
        end
        host = ip
    end
    -- set up
    self:createSocket()
    self.host = host
    self.port = port
    local success, err = self:_connect()
    if not success then
        self.host = nil
        self.port = nil
        print(err)
        return false, err
    end
    self.connected = true
    -- if self.handshake then
        -- self:send(self.handshake .. "+\n")
    -- end
    return true
end

function client:disconnect()
    if self.connected then
        -- self:send(self.handshake .. "-\n")
        self:_disconnect()
        self.host = nil
        self.port = nil
    end
end

function client:send(data)
    if not self.connected then
        return false, "Not connected"
    end
    return self:_send(data)
end

function client:receive()
    if not self.connected then
        return false, "Not connected"
    end
    return self:_receive()
end

function client:update(dt)
    -- print("client:update")
    if not self.connected then print("connect lost");return end
    -- print("client:update")
    assert(dt, "Update needs a dt!")
    if self.ping then
        self.ping.timer = self.ping.timer + dt
        if self.ping.timer > self.ping.time then
            print("send ping")
            self:_send(self.ping.msg)
            self.ping.timer = 0
        end
    end
    if self.callbacks.recv then
        -- print("callbacks.recv is not nil")
        local data, err = self:_receive()
        -- if (data) then
            -- print("llbacks.recv then:::::"..data)
        -- end
        local i = 5
        while data and i > 0 do
            self.callbacks.recv(self.out_instance, data)
            data, err = self:_receive()
            i = i - 1;
        end
    end
    -- print("no callbacks")
end

function client:setCallback(cbk, out_instance)
    self.out_instance = out_instance
    self.callbacks.recv = cbk
end

local tcpClient = class('tcpClient', client)

function tcpClient:createSocket()
    -- self.socket = socket.tcp()
    -- self.socket:settimeout(0)
end

function tcpClient:_connect()
    -- self.socket:settimeout(5)
    -- local success, err = self.socket:connect(self.host, self.port)
    self.socket, err = socket.connect(self.host, self.port)
    self.socket:settimeout(0)
    return self.socket ~= nil, err
end

function tcpClient:_disconnect()
    self.socket:shutdown()
end

function tcpClient:_send(data)
    return self.socket:send(data)
end

function tcpClient:_receive()
    local packet = ""
    local i = 5
    while  i > 0 do
        -- print("prepare for receive")
        -- local skt, e, p = c:receive(1024)
        local skt, e, p = self.socket:receive(8192)
        -- print(skt)
        -- print(e)
        -- if (skt) then
            -- print("SKT*******"..skt)
        -- end
        if (#p > 10) then
            packet = packet .. p
            -- print("#p    ::::"..p)
        end
        if (not skt) then break; end
        if (e) then break; end
        i = i - 1
    end -- /while-do
    if packet ~= "" then
        return packet
    end
    return nil, "No message"
end

function tcpClient:setoption(option, value)
    if option == "broadcast" then
        self.socket:setoption("broadcast", not not value)
    end
end

blue = {}
blue.tcpClient = tcpClient
