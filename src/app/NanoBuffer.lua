NanoBuffer = NanoBuffer or {}

--local bit = require "bit"
local bytes = {}

function NanoBuffer.put(value)
	for i=1,2 do
		local byte = string.byte(value, i)
		local s = bit.tohex(byte)
		print(type(s))
		print(s)
		for i=1,#s do
			--print(bit.tobit(s[i]))
		end

		table.insert(bytes, byte)
	end
end

function NanoBuffer.getBytes()
	return bytes
end

return NanoBuffer