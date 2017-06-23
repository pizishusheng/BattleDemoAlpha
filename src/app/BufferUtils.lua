BufferUtils = BufferUtils or {}

local nanoBuffer = require("app/Nanobuffer")

function BufferUtils.toBytes(value)
	local id = value["id"]

	if id == 1 then
		nanoBuffer.put(1).put(value["x"]).put(value["y"])
	end
	return nanoBuffer.getBytes()
end

function BufferUtils.fromBytes(bytes)
	local values = {}
	
end

return BufferUtils

