--
function Object(Name)
    local this = {}
	
	this.Name = Name
	this.X = 0
	this.Y = 0
	this.W = 0
	this.H = 0
	this.Textures = {}
	
	local function Init()
		LE.Object:New(this.Name, this.X, this.Y, this.W, this.H)
	end
	this.Init = Init
	
	local function AddTexture(TextureNum)
		table.insert(this.Textures, TextureNum)
		LE.Object.Texture:Set(this.Name, TextureNum)
	end
	this.AddTexture = AddTexture
	
	local function AddTile(TextureNum, Values)
		LE.Texture.Tile:New(this.Textures[TextureNum+1], Values)
	end
	this.AddTile = AddTile
	
	local function TextureTileSize(TextureNum)
		return LE.Texture.Tile:Size(this.Textures[TextureNum+1])
	end
	this.TextureTileSize = TextureTileSize
	
	local function DrawTexture(TextureNum)
		LE.Object.Texture:Draw(this.Name, this.Textures[TextureNum+1])
	end
	this.DrawTexture = DrawTexture
	
	local function DrawTile(TextureNum, TileNum)
		LE.Object.Tile:Draw(this.Name, this.Textures[TextureNum+1], TileNum)
	end
	this.DrawTile = DrawTile
	
    return this
end