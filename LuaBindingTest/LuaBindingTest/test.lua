-- test.lua

-- local this = GetComponent("test.lua");

function start()
    Print("Hello I am a Lua Script");

    Print("Something: " .. this:GetOwner():GetSomething());

    this.hm = "Hello World";

    Print(this:PrintHm());


end

function update(deltaTime)
end
