--
function camera(x, y, w, h)
    local this = {}
	
	this.x = x
	this.y = y
	this.w = w
	this.h = h
	
	this.num = le.camera:new(x, y, w, h)
	
	local function current()
		le.camera:current(this.num)
	end
	this.current = current
	
	local function size(w, h)
		le.camera:size(this.num, w, h)
	end
	this.size = size
	
	local function move(mode, x, y)
		le.camera:move(this.num, mode, x, y)
	end
	this.move = move
	
	local function speed(value)
		le.camera:speed(this.num, value)
	end
	this.speed = speed
	
    return this
end