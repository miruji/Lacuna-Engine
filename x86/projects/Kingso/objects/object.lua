--
function object(name, x, y, w, h)
    local this = {}
	
	this.name = name
	this.x = x
	this.y = y
	this.w = w
	this.h = h
	this.textures = {}
	
	le.object:new(this.name, this.x, this.y, this.w, this.h)
	
	local function addTexture(textureNum)
		table.insert(this.textures, textureNum)
		le.object.texture:set(this.name, textureNum)
	end
	this.addTexture = addTexture
	
	local function addTile(textureNum, values)
		le.texture.tile:new(this.textures[textureNum+1], values)
	end
	this.addTile = addTile
	
	local function textureTileSize(textureNum)
		return le.texture.tile:size(this.textures[textureNum+1])
	end
	this.textureTileSize = textureTileSize
	
	local function drawTexture(textureNum)
		le.object.texture:draw(this.name, this.textures[textureNum+1])
	end
	this.drawTexture = drawTexture
	
	local function drawTextures()
		for i = 1, #this.textures do
			this.drawTexture(tostring(i-1))
		end
	end
	this.drawTextures = drawTextures
	
	local function drawTile(textureNum, tileNum)
		le.object.tile:draw(this.name, this.textures[textureNum+1], tileNum)
	end
	this.drawTile = drawTile
	
    return this
end