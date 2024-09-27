--
function Camera(X, Y, W, H)
    local this = {}
	
	this.X = X
	this.Y = Y
	this.W = W
	this.H = H
	
	this.Num = LE.Camera:New(X, Y, W, H)
	
	local function Current()
		LE.Camera:Current(this.Num)
	end
	this.Current = Current
	
	local function Size(W, H)
		LE.Camera:Size(this.Num, W, H)
	end
	this.Size = Size
	
	local function Move(Mode, X, Y)
		LE.Camera:Move(this.Num, Mode, X, Y)
	end
	this.Move = Move
	
	local function Speed(Value)
		LE.Camera:Speed(this.Num, Value)
	end
	this.Speed = Speed
	
    return this
end