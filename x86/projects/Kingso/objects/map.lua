-- test game obj
require("objects/object")
require("objects/mapGeneration")

-- entity
function map()
    local this = {}
	
	-- textures
	this.number        = le.texture:new("textures/number.png", "rgba_f:1,1,1,1")
		
		le.texture.tile:new(this.number, "0;0;64;64", 0)   -- 0
		le.texture.tile:new(this.number, "64;0;64;64", 0)  -- 1
		le.texture.tile:new(this.number, "128;0;64;64", 0) -- 2
		le.texture.tile:new(this.number, "196;0;64;64", 0) -- 3
		le.texture.tile:new(this.number, "256;0;64;64", 0) -- 4
		le.texture.tile:new(this.number, "320;0;64;64", 0) -- 5
		le.texture.tile:new(this.number, "384;0;64;64", 0) -- 6
		le.texture.tile:new(this.number, "448;0;64;64", 0) -- 7
		le.texture.tile:new(this.number, "512;0;64;64", 0) -- 8
		le.texture.tile:new(this.number, "576;0;64;64", 0) -- 9
		
	this.noRiver       = le.texture:new("textures/noRiver.png", "rgba_f:1,1,1,1")
	this.layer1Texture = le.texture:new("textures/map.png", "rgba_f:1,1,1,1")
	
		-- = basic =
		le.texture.tile:new(this.layer1Texture, "0;0;64;64", 0)  -- water  0
		le.texture.tile:new(this.layer1Texture, "0;64;64;64", 0) -- land   1
		 
		-- = river =
			-- more basic
			le.texture.tile:new(this.layer1Texture, "64;0;64;64", 0)  -- up-bottom & left-right  2
			le.texture.tile:new(this.layer1Texture, "128;0;64;64", 0) -- lake                    3
			le.texture.tile:new(this.layer1Texture, "448;0;64;64", 0) -- island                  4
			
			-- end
			le.texture.tile:new(this.layer1Texture, "0;128;64;64", 0)     -- top end     5  *
			le.texture.tile:new(this.layer1Texture, "256;128;64;64", 0)   -- top end     6
			
			le.texture.tile:new(this.layer1Texture, "0;128;64;64", 180)   -- bottom end  7  *
			le.texture.tile:new(this.layer1Texture, "256;128;64;64", 180) -- bottom end  8
			
			le.texture.tile:new(this.layer1Texture, "0;128;64;64", -90)   -- right end   9  *
			le.texture.tile:new(this.layer1Texture, "256;128;64;64", -90) -- right end   10
			
			le.texture.tile:new(this.layer1Texture, "0;128;64;64", 90)    -- left end    11 *
			le.texture.tile:new(this.layer1Texture, "256;128;64;64", 90)  -- left end    12
			
			-- basic up-bottom & left-right
			le.texture.tile:new(this.layer1Texture, "0;192;64;64", 0)    -- up-bottom  13 *
			le.texture.tile:new(this.layer1Texture, "64;192;64;64", 0)   -- up-bottom  14
			le.texture.tile:new(this.layer1Texture, "64;192;64;64", 180) -- up-bottom  15
						 
			le.texture.tile:new(this.layer1Texture, "0;192;64;64", 90)   -- left-right  16 *
			le.texture.tile:new(this.layer1Texture, "64;192;64;64", 90)  -- left-right  17
			le.texture.tile:new(this.layer1Texture, "64;192;64;64", -90) -- left-right  18
			
			-- angles
			le.texture.tile:new(this.layer1Texture, "0;256;64;64", 0)   -- bottom-right  19 *
			le.texture.tile:new(this.layer1Texture, "64;256;64;64", 0)  -- bottom-right  20
			le.texture.tile:new(this.layer1Texture, "128;256;64;64", 0) -- bottom-right  21
			le.texture.tile:new(this.layer1Texture, "192;256;64;64", 0) -- bottom-right  22
			le.texture.tile:new(this.layer1Texture, "256;256;64;64", 0) -- bottom-right  23
			
			le.texture.tile:new(this.layer1Texture, "0;256;64;64", 90)   -- bottom-left  24 *
			le.texture.tile:new(this.layer1Texture, "128;256;64;64", 90) -- bottom-left  25
			le.texture.tile:new(this.layer1Texture, "64;256;64;64", 90)  -- bottom-left  26
			le.texture.tile:new(this.layer1Texture, "256;256;64;64", 90) -- bottom-left  27
			le.texture.tile:new(this.layer1Texture, "192;256;64;64", 90) -- bottom-left  28
			
			le.texture.tile:new(this.layer1Texture, "0;256;64;64", -90)   -- top-right  29 *
			le.texture.tile:new(this.layer1Texture, "64;256;64;64", -90)  -- top-right  30
			le.texture.tile:new(this.layer1Texture, "128;256;64;64", -90) -- top-right  31
			le.texture.tile:new(this.layer1Texture, "192;256;64;64", -90) -- top-right  32
			le.texture.tile:new(this.layer1Texture, "256;256;64;64", -90) -- top-right  33
			
			le.texture.tile:new(this.layer1Texture, "0;256;64;64", 180)   -- top-left  34 *
			le.texture.tile:new(this.layer1Texture, "128;256;64;64", 180) -- top-left  35
			le.texture.tile:new(this.layer1Texture, "64;256;64;64", 180)  -- top-left  36
			le.texture.tile:new(this.layer1Texture, "256;256;64;64", 180) -- top-left  37
			le.texture.tile:new(this.layer1Texture, "192;256;64;64", 180) -- top-left  38
			
			-- third up-bottom & left-right
			le.texture.tile:new(this.layer1Texture, "0;320;64;64", 0)   -- left-right bottom   39 *
			le.texture.tile:new(this.layer1Texture, "64;320;64;64", 0)  -- left-right bottom   40
			le.texture.tile:new(this.layer1Texture, "128;320;64;64", 0) -- left-right bottom   41
			le.texture.tile:new(this.layer1Texture, "192;320;64;64", 0) -- left-right bottom   42
			le.texture.tile:new(this.layer1Texture, "256;320;64;64", 0) -- left-right bottom   43
			
			le.texture.tile:new(this.layer1Texture, "0;320;64;64", 180)   -- left-right up       44 *
			le.texture.tile:new(this.layer1Texture, "128;320;64;64", 180) -- left-right up       45
			le.texture.tile:new(this.layer1Texture, "64;320;64;64", 180)  -- left-right up       46
			le.texture.tile:new(this.layer1Texture, "256;320;64;64", 180) -- left-right bottom   47
			le.texture.tile:new(this.layer1Texture, "192;320;64;64", 180) -- left-right bottom   48
			
			le.texture.tile:new(this.layer1Texture, "0;320;64;64", -90)   -- up-bottom right     49 *
			le.texture.tile:new(this.layer1Texture, "128;320;64;64", -90) -- up-bottom right     50
			le.texture.tile:new(this.layer1Texture, "64;320;64;64", -90)  -- up-bottom right     51
			le.texture.tile:new(this.layer1Texture, "192;320;64;64", -90) -- left-right bottom   52
			le.texture.tile:new(this.layer1Texture, "256;320;64;64", -90) -- left-right bottom   53
			
			le.texture.tile:new(this.layer1Texture, "0;320;64;64", 90)   -- up-bottom left     54 *
			le.texture.tile:new(this.layer1Texture, "64;320;64;64", 90)  -- up-bottom left     55
			le.texture.tile:new(this.layer1Texture, "128;320;64;64", 90) -- up-bottom left     56
			le.texture.tile:new(this.layer1Texture, "256;320;64;64", 90) -- left-right bottom  57
			le.texture.tile:new(this.layer1Texture, "192;320;64;64", 90) -- left-right bottom  58
			
		-- = land =
		-- basic borders
			le.texture.tile:new   (this.layer1Texture, "0;384;64;64", 0)   -- bottom  59 *
			le.texture.tile:new   (this.layer1Texture, "0;384;64;64", 180) -- up      60
			le.texture.tile:new   (this.layer1Texture, "0;384;64;64", -90) -- right   61
			le.texture.tile:new   (this.layer1Texture, "0;384;64;64", 90)  -- left    62
			
		-- joints-diagonals
			le.texture.tile:new(this.layer1Texture, "64;64;64;64", 0)    -- 4 diagonal  63 *
			le.texture.tile:new(this.layer1Texture, "128;64;64;64", 0)   -- 2 diagonal  64 *
			le.texture.tile:new(this.layer1Texture, "128;64;64;64", 90)  -- 2 diagonal  65
			
			le.texture.tile:new(this.layer1Texture, "256;64;64;64", 0)   -- 1 diagonal  66 *
			le.texture.tile:new(this.layer1Texture, "256;64;64;64", 90)  -- 1 diagonal  67
			le.texture.tile:new(this.layer1Texture, "256;64;64;64", -90) -- 1 diagonal  68
			le.texture.tile:new(this.layer1Texture, "256;64;64;64", 180) -- 1 diagonal  69
			
			le.texture.tile:new(this.layer1Texture, "512;64;64;64", 0)   -- 2 diagonal  70 *
			le.texture.tile:new(this.layer1Texture, "512;64;64;64", 180) -- 2 diagonal  71
			le.texture.tile:new(this.layer1Texture, "512;64;64;64", -90) -- 2 diagonal  72
			le.texture.tile:new(this.layer1Texture, "512;64;64;64", 90)  -- 2 diagonal  73
			
			le.texture.tile:new(this.layer1Texture, "768;64;64;64", 0)   -- 3 diagonal  74 *
			le.texture.tile:new(this.layer1Texture, "768;64;64;64", 90)  -- 3 diagonal  75
			le.texture.tile:new(this.layer1Texture, "768;64;64;64", -90) -- 3 diagonal  76
			le.texture.tile:new(this.layer1Texture, "768;64;64;64", 180) -- 3 diagonal  77
			
		-- more borders
			le.texture.tile:new(this.layer1Texture, "256;384;64;64", 0)   -- bottom  78 *
			le.texture.tile:new(this.layer1Texture, "320;384;64;64", 0)   -- bottom  79
			le.texture.tile:new(this.layer1Texture, "384;384;64;64", 0)   -- bottom  80
			
			le.texture.tile:new(this.layer1Texture, "320;384;64;64", 180) -- up  81 *
			le.texture.tile:new(this.layer1Texture, "256;384;64;64", 180) -- up  82
			le.texture.tile:new(this.layer1Texture, "384;384;64;64", 180) -- up  83
			
			le.texture.tile:new(this.layer1Texture, "256;384;64;64", 90)  -- right  84 *
			le.texture.tile:new(this.layer1Texture, "320;384;64;64", 90)  -- right  85
			le.texture.tile:new(this.layer1Texture, "384;384;64;64", 90)  -- right  86
			
			le.texture.tile:new(this.layer1Texture, "320;384;64;64", -90) -- left  87 *
			le.texture.tile:new(this.layer1Texture, "256;384;64;64", -90) -- left  88
			le.texture.tile:new(this.layer1Texture, "384;384;64;64", -90) -- left  89
			
		-- angles
			le.texture.tile:new(this.layer1Texture, "0;448;64;64", 0)    -- right-bottom  90 *
			le.texture.tile:new(this.layer1Texture, "64;448;64;64", 0)   -- right-bottom  91
			
			le.texture.tile:new(this.layer1Texture, "0;448;64;64", 90)   -- left-bottom   92 *
			le.texture.tile:new(this.layer1Texture, "64;448;64;64", 90)  -- left-bottom   93
			
			le.texture.tile:new(this.layer1Texture, "0;448;64;64", -90)  -- right-top     94 *
			le.texture.tile:new(this.layer1Texture, "64;448;64;64", -90) -- right-top     95
			
			le.texture.tile:new(this.layer1Texture, "0;448;64;64", 180)  -- left-top      96 *
			le.texture.tile:new(this.layer1Texture, "64;448;64;64", 180) -- left-top      97
			
		-- ends
			le.texture.tile:new(this.layer1Texture, "0;512;64;64", 0)     -- left-right    98 *
			le.texture.tile:new(this.layer1Texture, "64;512;64;64", 0)    -- left-right    99
			
			le.texture.tile:new(this.layer1Texture, "0;512;64;64", 90)    -- top-bottom  100 *
			le.texture.tile:new(this.layer1Texture, "64;512;64;64", 90)   -- top-bottom  101
			
			le.texture.tile:new(this.layer1Texture, "256;512;64;64", 0)   -- bottom      102 *
			le.texture.tile:new(this.layer1Texture, "256;512;64;64", 180) -- top         103
			le.texture.tile:new(this.layer1Texture, "256;512;64;64", -90) -- right       104
			le.texture.tile:new(this.layer1Texture, "256;512;64;64", 90)  -- left        105
			
		-- = river =
		-- angles more (fix)
			le.texture.tile:new(this.layer1Texture, "1280;256;64;64", 0)   -- right-bottom  106
			le.texture.tile:new(this.layer1Texture, "1280;256;64;64", 90)  -- left-bottom   107
			le.texture.tile:new(this.layer1Texture, "1280;256;64;64", -90) -- top-right     108
			le.texture.tile:new(this.layer1Texture, "1280;256;64;64", 180) -- top-left      109
		
		-- ends more (fix)
			le.texture.tile:new(this.layer1Texture, "512;512;64;64", 0)   -- bottom  110 *
			le.texture.tile:new(this.layer1Texture, "512;512;64;64", 180) -- top     111
			le.texture.tile:new(this.layer1Texture, "512;512;64;64", -90) -- right   112
			le.texture.tile:new(this.layer1Texture, "512;512;64;64", 90)  -- left    113
			
			le.texture.tile:new(this.layer1Texture, "768;512;64;64", 0)   -- bottom  114 *
			le.texture.tile:new(this.layer1Texture, "768;512;64;64", 180) -- top     115
			le.texture.tile:new(this.layer1Texture, "768;512;64;64", -90) -- right   116
			le.texture.tile:new(this.layer1Texture, "768;512;64;64", 90)  -- left    117
			
		-- lined angles (fix)
			le.texture.tile:new(this.layer1Texture, "386;192;64;64", 0)   -- bottom  118 *
			le.texture.tile:new(this.layer1Texture, "448;192;64;64", 0)   -- bottom  119
			
			le.texture.tile:new(this.layer1Texture, "448;192;64;64", 180) -- top     120 *
			le.texture.tile:new(this.layer1Texture, "386;192;64;64", 180) -- top     121
			
			le.texture.tile:new(this.layer1Texture, "448;192;64;64", -90) -- right   122 *
			le.texture.tile:new(this.layer1Texture, "386;192;64;64", 90)  -- left    123
			
			le.texture.tile:new(this.layer1Texture, "386;192;64;64", -90) -- right   124 *
			le.texture.tile:new(this.layer1Texture, "448;192;64;64", 90)  -- left    125
			
		-- = water & land =
		-- water & land rotate
			le.texture.tile:new(this.layer1Texture, "0;0;64;64", 90)   -- water  126
			le.texture.tile:new(this.layer1Texture, "0;0;64;64", 180)  -- water  127
			le.texture.tile:new(this.layer1Texture, "0;0;64;64", -90)  -- water  128
			
			le.texture.tile:new(this.layer1Texture, "0;64;64;64", 90)  -- land   129
			le.texture.tile:new(this.layer1Texture, "0;64;64;64", 180) -- land   130
			le.texture.tile:new(this.layer1Texture, "0;64;64;64", -90) -- land   131
			
		-- river
			le.texture.tile:new(this.layer1Texture, "512;128;64;64", 0)   --  132
			le.texture.tile:new(this.layer1Texture, "512;128;64;64", 90)  --  133
			le.texture.tile:new(this.layer1Texture, "512;128;64;64", 180) --  134
			le.texture.tile:new(this.layer1Texture, "512;128;64;64", -90) --  135
			
			le.texture.tile:new(this.layer1Texture, "768;128;64;64", 0)   --  136
			le.texture.tile:new(this.layer1Texture, "768;128;64;64", 90)  --  137
			le.texture.tile:new(this.layer1Texture, "768;128;64;64", 180) --  138
			le.texture.tile:new(this.layer1Texture, "768;128;64;64", -90) --  139
			
		-- island rotate
			le.texture.tile:new(this.layer1Texture, "448;0;64;64", 90)  -- island  140
			le.texture.tile:new(this.layer1Texture, "448;0;64;64", 180) -- island  141
			le.texture.tile:new(this.layer1Texture, "448;0;64;64", -90) -- island  142
			
		-- river
			le.texture.tile:new(this.layer1Texture, "64;128;64;64", 0)    -- top end  143 *
			le.texture.tile:new(this.layer1Texture, "64;128;64;64", 90)   -- top end  144
			le.texture.tile:new(this.layer1Texture, "64;128;64;64", 180)  -- top end  145
			le.texture.tile:new(this.layer1Texture, "64;128;64;64", -90)  -- top end  146
			le.texture.tile:new(this.layer1Texture, "128;128;64;64", 0)   -- top end  147 *
			le.texture.tile:new(this.layer1Texture, "128;128;64;64", 90)  -- top end  148
			le.texture.tile:new(this.layer1Texture, "128;128;64;64", 180) -- top end  149
			le.texture.tile:new(this.layer1Texture, "128;128;64;64", -90) -- top end  150
			le.texture.tile:new(this.layer1Texture, "192;128;64;64", 0)   -- top end  151 *
			le.texture.tile:new(this.layer1Texture, "192;128;64;64", 90)  -- top end  152
			le.texture.tile:new(this.layer1Texture, "192;128;64;64", 180) -- top end  153
			le.texture.tile:new(this.layer1Texture, "192;128;64;64", -90) -- top end  154
			
			le.texture.tile:new(this.layer1Texture, "320;128;64;64", 0)   -- top end  155 *
			le.texture.tile:new(this.layer1Texture, "320;128;64;64", 90)  -- top end  156
			le.texture.tile:new(this.layer1Texture, "320;128;64;64", 180) -- top end  157
			le.texture.tile:new(this.layer1Texture, "320;128;64;64", -90) -- top end  158
			le.texture.tile:new(this.layer1Texture, "380;128;64;64", 0)   -- top end  159 *
			le.texture.tile:new(this.layer1Texture, "380;128;64;64", 90)  -- top end  160
			le.texture.tile:new(this.layer1Texture, "380;128;64;64", 180) -- top end  161
			le.texture.tile:new(this.layer1Texture, "380;128;64;64", -90) -- top end  162
			le.texture.tile:new(this.layer1Texture, "448;128;64;64", 0)   -- top end  163 *
			le.texture.tile:new(this.layer1Texture, "448;128;64;64", 90)  -- top end  164
			le.texture.tile:new(this.layer1Texture, "448;128;64;64", 180) -- top end  165
			le.texture.tile:new(this.layer1Texture, "448;128;64;64", -90) -- top end  166
			
		-- river
			le.texture.tile:new(this.layer1Texture, "576;128;64;64", 0)   --  167 *
			le.texture.tile:new(this.layer1Texture, "576;128;64;64", 90)  --  168
			le.texture.tile:new(this.layer1Texture, "576;128;64;64", 180) --  169
			le.texture.tile:new(this.layer1Texture, "576;128;64;64", -90) --  170
			le.texture.tile:new(this.layer1Texture, "640;128;64;64", 0)   --  171 *
			le.texture.tile:new(this.layer1Texture, "640;128;64;64", 90)  --  172
			le.texture.tile:new(this.layer1Texture, "640;128;64;64", 180) --  173
			le.texture.tile:new(this.layer1Texture, "640;128;64;64", -90) --  174
			le.texture.tile:new(this.layer1Texture, "704;128;64;64", 0)   --  175 *
			le.texture.tile:new(this.layer1Texture, "704;128;64;64", 90)  --  176
			le.texture.tile:new(this.layer1Texture, "704;128;64;64", 180) --  177
			le.texture.tile:new(this.layer1Texture, "704;128;64;64", -90) --  178
			
			le.texture.tile:new(this.layer1Texture, "832;128;64;64", 0)   --  179 *
			le.texture.tile:new(this.layer1Texture, "832;128;64;64", 90)  --  180
			le.texture.tile:new(this.layer1Texture, "832;128;64;64", 180) --  181
			le.texture.tile:new(this.layer1Texture, "832;128;64;64", -90) --  182
			le.texture.tile:new(this.layer1Texture, "896;128;64;64", 0)   --  183 *
			le.texture.tile:new(this.layer1Texture, "896;128;64;64", 90)  --  184
			le.texture.tile:new(this.layer1Texture, "896;128;64;64", 180) --  185
			le.texture.tile:new(this.layer1Texture, "896;128;64;64", -90) --  186
			le.texture.tile:new(this.layer1Texture, "960;128;64;64", 0)   --  187 *
			le.texture.tile:new(this.layer1Texture, "960;128;64;64", 90)  --  188
			le.texture.tile:new(this.layer1Texture, "960;128;64;64", 180) --  189
			le.texture.tile:new(this.layer1Texture, "960;128;64;64", -90) --  190
			
	-- block distance (draw)
	this.blockSize = 64
	this.blockDistanceX = 0
	this.blockDistanceY = 0
	this.blockDistanceW = 0
	this.blockDistanceH = 0
	local function updateBlockDistance(cx, cy, cw, ch)
		if cx > 0 then this.blockDistanceX = cx/this.blockSize end
		if cy > 0 then this.blockDistanceY = cy/this.blockSize end
		this.blockDistanceW = this.blockDistanceX+ cw/this.blockSize +1
		this.blockDistanceH = this.blockDistanceY+ ch/this.blockSize +1
	end
	this.updateBlockDistance = updateBlockDistance
	
	this.debugMap = "normal"
	
	-- -- -- generate -- -- --
	this.size = 10
	-- grid
	this.layer2 = {{}}
		this.layer2Texture = -1
		this.drawingGrid = true
		local function generateGrid(size)
			--
			this.layer2Texture = le.texture:new("textures/grid.png", "rgba_f:1,1,1,0.77")
			for i=0, 7 do
			for j=0, 7 do
				for q=0, 1 do
					
					degree = 0
					if (q == 1) then
						degree = 180
					end
					
					le.texture.tile:new(this.layer2Texture, (i*64)..";"..(j*64)..";64;64", degree)
				end
			end end
			
			for i=1, size do
				this.layer2[i] = {}
			for j=1, size do
				this.layer2[i][j] = object("grid_"..i.."_"..j, (i-1)*this.blockSize, (j-1)*this.blockSize, this.blockSize, this.blockSize)
					
					this.layer2[i][j].addTexture(this.layer2Texture)
					this.layer2[i][j].tileNum = le.random:int(0, this.layer2[i][j].textureTileSize(0)-1)
			end
			end
			--
		end
		this.generateGrid = generateGrid
	
	-- pixelate
	this.layer3 = {{}}
		this.layer3Texture = -1
		local function generatePixelate(size)
			--
			this.layer3Texture = le.texture:new("textures/pixelate.png", "rgba_f:1,1,1,0.2")
			for i=0, 7 do
			for j=0, 7 do
				for q=0, 3 do
					
					degree = 0
					if (q == 1) then
						degree = 90
					elseif (q == 2) then
						degree = 180
					elseif (q == 3) then
						degree = -90
					end
					
					le.texture.tile:new(this.layer3Texture, (i*64)..";"..(j*64)..";64;64", degree)
				end
			end end
			
			for i=1, size do
				this.layer3[i] = {}
			for j=1, size do
				this.layer3[i][j] = object("pixelate_"..i.."_"..j, (i-1)*this.blockSize, (j-1)*this.blockSize, this.blockSize, this.blockSize)
					
					this.layer3[i][j].addTexture(this.layer3Texture)
					this.layer3[i][j].tileNum = le.random:int(0, this.layer3[i][j].textureTileSize(0)-1)
			end
			end
			--
		end
		this.generatePixelate = generatePixelate
	
	-- generate (land)
	this.layer1 = {{}}
	
	local function blockTest(i, j, data)
		--
		d1 = data:sub(1,1)
		d1w = false
		d1r = false
			if (d1 == 'n') then d1 = -1
		elseif (d1 == 'w') then 
				d1w = true
				d1 = true
		elseif (d1 == 'r') then 
				d1r = true
				d1 = true
		elseif (d1 == '0') then d1 = true else
								d1 = false end
		d2 = data:sub(2,2)
		d2w = false
		d2r = false
			if (d2 == 'n') then d2 = -1
		elseif (d2 == 'w') then 
				d2w = true
				d2 = true
		elseif (d2 == 'r') then 
				d2r = true
				d2 = true
		elseif (d2 == '0') then d2 = true else
								d2 = false end
		d3 = data:sub(3,3)
		d3w = false
		d3r = false
			if (d3 == 'n') then d3 = -1
		elseif (d3 == 'w') then 
				d3w = true
				d3 = true
		elseif (d3 == 'r') then 
				d3r = true
				d3 = true
		elseif (d3 == '0') then d3 = true else
								d3 = false end
		d4 = data:sub(4,4)
		d4w = false
		d4r = false
			if (d4 == 'n') then d4 = -1
		elseif (d4 == 'w') then 
				d4w = true
				d4 = true
		elseif (d4 == 'r') then 
				d4r = true
				d4 = true
		elseif (d4 == '0') then d4 = true else
								d4 = false end
		d5 = data:sub(5,5)
		d5w = false
		d5r = false
			if (d5 == 'n') then d5 = -1
		elseif (d5 == 'w') then 
				d5w = true
				d5 = true
		elseif (d5 == 'r') then 
				d5r = true
				d5 = true
		elseif (d5 == '0') then d5 = true else
								d5 = false end
		d6 = data:sub(6,6)
		d6w = false
		d6r = false
			if (d6 == 'n') then d6 = -1
		elseif (d6 == 'w') then 
				d6w = true
				d6 = true
		elseif (d6 == 'r') then 
				d6r = true
				d6 = true
		elseif (d6 == '0') then d6 = true else
								d6 = false end
		d7 = data:sub(7,7)
		d7w = false
		d7r = false
			if (d7 == 'n') then d7 = -1
		elseif (d7 == 'w') then 
				d7w = true
				d7 = true
		elseif (d7 == 'r') then 
				d7r = true
				d7 = true
		elseif (d7 == '0') then d7 = true else
								d7 = false end
		d8 = data:sub(8,8)
		d8w = false
		d8r = false
			if (d8 == 'n') then d8 = -1
		elseif (d8 == 'w') then 
				d8w = true
				d8 = true
		elseif (d8 == 'r') then 
				d8r = true
				d8 = true
		elseif (d8 == '0') then d8 = true else
								d8 = false end
		-- -1 -1 
		if (i >= 2 and j >= 2 and d1 ~= -1) then
			if d1w and (this.layer1[j-1][i-1].land == d1 or (this.layer1[j-1][i-1].river and this.layer1[j-1][i-1].river ~= nil)) then 
				return false
			elseif not d1w and (this.layer1[j-1][i-1].land ~= d1 and this.layer1[j-1][i-1].river ~= d1r) then
				return false
			end
		end
		-- 0 -1
		if (i >= 2 and d2 ~= -1) then
			if d2w and (this.layer1[j][i-1].land == d2 or (this.layer1[j][i-1].river and this.layer1[j][i-1].river ~= nil)) then
				return false
			elseif not d2w and (this.layer1[j][i-1].land ~= d2 and this.layer1[j][i-1].river ~= d2r) then
				return false
			end
		end
		-- +1 -1
		if (i >= 2 and j <= this.size-1 and d3 ~= -1) then
			if d3w and (this.layer1[j+1][i-1].land == d3 or (this.layer1[j+1][i-1].river and this.layer1[j+1][i-1].river ~= nil)) then
				return false
			elseif not d3w and (this.layer1[j+1][i-1].land ~= d3 and this.layer1[j+1][i-1].river ~= d3r) then
				return false
			end
		end
		-- -1 0
		if (j >= 2 and d4 ~= -1) then
			if d4w and (this.layer1[j-1][i].land == d4 or (this.layer1[j-1][i].river and this.layer1[j-1][i].river ~= nil)) then
				return false
			elseif not d4w and (this.layer1[j-1][i].land ~= d4 and this.layer1[j-1][i].river ~= d4r) then
				return false
			end
		end
		-- +1 0
		if (j <= this.size-1 and d5 ~= -1) then
			if d5w and (this.layer1[j+1][i].land == d5 or (this.layer1[j+1][i].river and this.layer1[j+1][i].river ~= nil)) then
				return false
			elseif not d5w and (this.layer1[j+1][i].land ~= d5 and this.layer1[j+1][i].river ~= d5r) then
				return false
			end
		end
		-- -1 +1
		if (i <= this.size-1 and j >= 2 and d6 ~= -1) then
			if d6w and (this.layer1[j-1][i+1].land == d6 or (this.layer1[j-1][i+1].river and this.layer1[j-1][i+1].river ~= nil)) then
				return false
			elseif not d6w and (this.layer1[j-1][i+1].land ~= d6 and this.layer1[j-1][i+1].river ~= d6r) then
				return false
			end
		end
		-- 0 +1
		if (i <= this.size-1 and d7 ~= -1) then
			if d7w and (this.layer1[j][i+1].land == d7 or (this.layer1[j][i+1].river and this.layer1[j][i+1].river ~= nil)) then
				return false
			elseif not d7w and (this.layer1[j][i+1].land ~= d7 and this.layer1[j][i+1].river ~= d7r) then
				return false
			end
		end
		-- +1 +1
		if (i <= this.size-1 and j <= this.size-1 and d8 ~= -1) then
			if d8w and (this.layer1[j+1][i+1].land == d8 or (this.layer1[j+1][i+1].river and this.layer1[j+1][i+1].river ~= nil)) then
				return false
			elseif not d8w and (this.layer1[j+1][i+1].land ~= d8 and this.layer1[j+1][i+1].river ~= d8r) then
				return false
			end
		end
		
		return true
	end
	this.blockTest = blockTest
	
	local function setLayer1Block(i, j, value, river)
		local layer = this.layer1[j][i]
		layer.block = value
		if river then
			layer.river = true
		end
		print(value)
	end
	this.setLayer1Block = setLayer1Block
	
	local function generate(size)
		--
		this.size = size
		mg = mapGeneration(size)
		
		biomes = 1
		-- basic land/water
		for i=1, size do
			this.layer1[i] = {}
		for j=1, size do
			this.layer1[i][j] = object("block_"..i.."_"..j, (i-1)*this.blockSize, (j-1)*this.blockSize, this.blockSize, this.blockSize)
				
				this.layer1[i][j].block = mg[j]:sub(i,i)
				if (this.layer1[i][j].block == '0') then
					this.layer1[i][j].land = true
				else
					this.layer1[i][j].land = false
				end
				this.layer1[i][j].biome = le.random:int(0, 9)
				
				this.layer1[i][j].addTexture(this.layer1Texture)
				this.layer1[i][j].addTexture(this.noRiver)
				this.layer1[i][j].addTexture(this.number)
		end
		end
		-- grid / pixelate
		this.generateGrid(size)
		this.generatePixelate(size)
		------------------------------------------------------------------
		-- 1 gen
		print(">> generation [1]")
		for i=1, size do for j=1, size do
		this.blockTest(i, j, "n0n00n0n")
		if (this.layer1[j][i].block == '-') then
			-- rivers
			-- = lake =
					if (this.blockTest(i, j, "n0n00n0n")) then
						this.setLayer1Block(i, j, '3', true)
					
			-- = end =
				-- top end
				elseif (this.blockTest(i, j, "n0n00n-n")) then
						this.setLayer1Block(i, j, '5', true)
				-- bottom end
				elseif (this.blockTest(i, j, "n-n00n0n")) then
						this.setLayer1Block(i, j, '7', true)
				-- right end
				elseif (this.blockTest(i, j, "n0n0-n0n")) then
						this.setLayer1Block(i, j, '9', true)
				-- left end
				elseif (this.blockTest(i, j, "n0n-0n0n")) then
						this.setLayer1Block(i, j, '11', true)
					
			-- = angles =
				-- bottom-right
				elseif (this.blockTest(i, j, "n0n0rn-0") or this.blockTest(i, j, "n0n0-nr0")) then
						this.setLayer1Block(i, j, '19', true)
				-- bottom-left
				elseif (this.blockTest(i, j, "n0nr00-n") or this.blockTest(i, j, "n0n-00rn")) then
						this.setLayer1Block(i, j, '24', true)
				-- top-right
				elseif (this.blockTest(i, j, "nr00-n0n") or this.blockTest(i, j, "n-00rn0n")) then
						this.setLayer1Block(i, j, '29', true)
				-- top-left
				elseif (this.blockTest(i, j, "0rn-0n0n") or this.blockTest(i, j, "0-nr0n0n")) then
						this.setLayer1Block(i, j, '34', true)
					
			-- = up-bottom & left-right =
				-- up-bottom || left-right
				elseif (this.blockTest(i, j, "n-n00n-n")) then
						this.setLayer1Block(i, j, '13', true)
				elseif (this.blockTest(i, j, "n0n--n0n")) then
						this.setLayer1Block(i, j, '16', true)
				-- up-bottom & left-right
				elseif (this.blockTest(i, j, "0-0--0-0")) then
						this.setLayer1Block(i, j, '2', true)
			-- = third up-bottom & left-right =
				-- up-bottom right
				elseif (this.blockTest(i, j, "n-00-n-0")) then
						this.setLayer1Block(i, j, '49', true)
				-- up-bottom left
				elseif (this.blockTest(i, j, "0-n-00-n")) then
						this.setLayer1Block(i, j, '54', true)
				-- left-right up 
				elseif (this.blockTest(i, j, "0-0--n0n")) then
						this.setLayer1Block(i, j, '44', true)
				-- left-right bottom
				elseif (this.blockTest(i, j, "n0n--0-0")) then
						this.setLayer1Block(i, j, '39', true)
				end
			--
		end
		end end
		-- 2 gen
		print(">> generation [2]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '-') then
			-- rivers repeat
			-- = angles =
				-- bottom-right
					if (this.blockTest(i, j, "n0n0rn-0") or this.blockTest(i, j, "n0n0-nr0") or this.blockTest(i, j, "n0n0wnw0")) then
						this.setLayer1Block(i, j, '19', true)
				-- bottom-left
				elseif (this.blockTest(i, j, "n0nr00-n") or this.blockTest(i, j, "n0n-00rn") or this.blockTest(i, j, "n0nw00wn")) then
						this.setLayer1Block(i, j, '24', true)
				-- top-right
				elseif (this.blockTest(i, j, "nr00-n0n") or this.blockTest(i, j, "n-00rn0n") or this.blockTest(i, j, "nw00wn0n")) then
						this.setLayer1Block(i, j, '29', true)
				-- top-left
				elseif (this.blockTest(i, j, "0rn-0n0n") or this.blockTest(i, j, "0-nr0n0n") or this.blockTest(i, j, "0wnw0n0n")) then
						this.setLayer1Block(i, j, '34', true)
				end
		end
		end end
		-- 3 gen
		print(">> generation [3]")
		for i=1, size do for j=1, size do
			-- rivers rebuild
			-- = up-bottom =
				if (this.layer1[j][i].block == '13') then
						if (this.blockTest(i, j, "nwn00nrn")) then
						this.setLayer1Block(i, j, '14', true)
					elseif (this.blockTest(i, j, "nrn00nwn")) then
						this.setLayer1Block(i, j, '15', true)
					end
			-- = left-right =
			elseif (this.layer1[j][i].block == '16') then
						if (this.blockTest(i, j, "n0nrwn0n")) then
						this.setLayer1Block(i, j, '17', true)
					elseif (this.blockTest(i, j, "n0nwrn0n")) then
						this.setLayer1Block(i, j, '18', true)
					end
			end
		end end
		-- 4 gen
		print(">> generation [4]")
		for i=1, size do for j=1, size do
			-- rivers rebuild
			-- = end =
				-- top end
					if (this.layer1[j][i].block == '5' and this.blockTest(i, j, "n0n00nwn")) then
						this.setLayer1Block(i, j, '6', true)
				-- bottom end
				elseif (this.layer1[j][i].block == '7' and this.blockTest(i, j, "nwn00n0n")) then
						this.setLayer1Block(i, j, '8', true)
				-- right end
				elseif (this.layer1[j][i].block == '9' and this.blockTest(i, j, "n0n0wn0n")) then
						this.setLayer1Block(i, j, '10', true)
				-- left end
				elseif (this.layer1[j][i].block == '11' and this.blockTest(i, j, "n0nw0n0n")) then
						this.setLayer1Block(i, j, '12', true)
				end
		end end
		-- 5 gen
		print(">> generation [5]")
		for i=1, size do for j=1, size do
			-- rivers fix
			-- = angles =
				-- bottom-right
					if (this.layer1[j][i].block == '19') then
						-- fix 1
							if (this.blockTest(i, j, "n0n0rnw0")) then
								this.setLayer1Block(i, j, '21', true)
						elseif (this.blockTest(i, j, "n0n0wnr0")) then
								this.setLayer1Block(i, j, '20', true)
						-- fix 2
						elseif (this.blockTest(i, j, "n0w0rnrn")) then
								this.setLayer1Block(i, j, '22', true)
						elseif (this.blockTest(i, j, "n0n0rwrn")) then
								this.setLayer1Block(i, j, '23', true)
						end
				-- bottom-left
				elseif (this.layer1[j][i].block == '24') then
						-- fix 1
							if (this.blockTest(i, j, "n0nr00wn")) then
								this.setLayer1Block(i, j, '26', true)
						elseif (this.blockTest(i, j, "n0nw00rn")) then
								this.setLayer1Block(i, j, '25', true)
						-- fix 2
						elseif (this.blockTest(i, j, "w0nr0nrn")) then
								this.setLayer1Block(i, j, '27', true)
						elseif (this.blockTest(i, j, "n0nr0nrw")) then
								this.setLayer1Block(i, j, '28', true)
						end
				-- top-right
				elseif (this.layer1[j][i].block == '29') then
						-- fix 1
							if (this.blockTest(i, j, "nr00wn0n")) then
								this.setLayer1Block(i, j, '31', true)
						elseif (this.blockTest(i, j, "nw00rn0n")) then
								this.setLayer1Block(i, j, '30', true)
						-- fix 2
						elseif (this.blockTest(i, j, "wrn0rn0n")) then
								this.setLayer1Block(i, j, '32', true)
						elseif (this.blockTest(i, j, "nrn0rn0w")) then
								this.setLayer1Block(i, j, '33', true)
						end
				-- top-left
				elseif (this.layer1[j][i].block == '34') then
						-- fix 1
							if (this.blockTest(i, j, "0rnw0n0n")) then
								this.setLayer1Block(i, j, '36', true)
						elseif (this.blockTest(i, j, "0wnr0n0n")) then
								this.setLayer1Block(i, j, '35', true)
						-- fix 2
						elseif (this.blockTest(i, j, "nrwr0n0n")) then
								this.setLayer1Block(i, j, '37', true)
						elseif (this.blockTest(i, j, "nrnr0w0n")) then
								this.setLayer1Block(i, j, '38', true)
						end
				end
		end end
		-- 6 gen
		print(">> generation [6]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = island =
				if ( this.blockTest(i, j, "nwnwwnwn") ) then
					this.setLayer1Block(i, j, '4', false)
				end
		end
		end end
		-- 7 gen
		print(">> generation [7]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = basic borders 1 gen =
				-- bottom
					if ( (this.blockTest(i, j, "n0n00nwn") or this.blockTest(i, j, "n0nr0nwn") or this.blockTest(i, j, "n0n0rnwn")) or
						 (this.blockTest(i, j, "nrw00nwn") or this.blockTest(i, j, "nrnr0nwn") or this.blockTest(i, j, "nrn0rnwn")) ) then
						this.setLayer1Block(i, j, '59', false)
				-- up
				elseif ( (this.blockTest(i, j, "nwn00n0n") or this.blockTest(i, j, "nwnr0n0n") or this.blockTest(i, j, "nwn0rn0n")) or
						 (this.blockTest(i, j, "nwn00nrn") or this.blockTest(i, j, "nwnr0nrn") or this.blockTest(i, j, "nwn0rnrn")) ) then
						this.setLayer1Block(i, j, '60', false)
				-- right
				elseif ( (this.blockTest(i, j, "n0n0wn0n") or this.blockTest(i, j, "nrn0wn0n") or this.blockTest(i, j, "n0n0wnrn")) or
						 (this.blockTest(i, j, "n0nrwn0n") or this.blockTest(i, j, "nrnrwn0n") or this.blockTest(i, j, "n0nrwnrn")) ) then
						this.setLayer1Block(i, j, '61', false)
				-- left
				elseif ( (this.blockTest(i, j, "n0nw0n0n") or this.blockTest(i, j, "nrnw0n0n") or this.blockTest(i, j, "n0nw0nrn")) or
						 (this.blockTest(i, j, "n0nwrn0n") or this.blockTest(i, j, "nrnwrn0n") or this.blockTest(i, j, "n0nwrnrn")) ) then
						this.setLayer1Block(i, j, '62', false)
				end
		end
		end end
		-- 8 gen
		print(">> generation [8]")
		for i=1, size do for j=1, size do
			-- river
			-- = third up-bottom & left-right fix =
				-- left-right bottom
					if (this.layer1[j][i].block == '39') then
						-- fix 1
							if (this.blockTest(i, j, "n0wrwn-0")) then
								this.setLayer1Block(i, j, '40', true)
						elseif (this.blockTest(i, j, "w0nwr0-n")) then
								this.setLayer1Block(i, j, '41', true)
						-- fix 2
						elseif (this.blockTest(i, j, "n0wrrnrn")) then
								this.setLayer1Block(i, j, '42', true)
						elseif (this.blockTest(i, j, "w0nrrnrn")) then
								this.setLayer1Block(i, j, '43', true)
						end
				-- left-right up
				elseif (this.layer1[j][i].block == '44') then
						-- fix 1
							if (this.blockTest(i, j, "n-0rwn0w")) then
								this.setLayer1Block(i, j, '45', true)
						elseif (this.blockTest(i, j, "0-nwrw0n")) then
								this.setLayer1Block(i, j, '46', true)
						-- fix 2
						elseif (this.blockTest(i, j, "nrnrrn0w")) then
								this.setLayer1Block(i, j, '47', true)
						elseif (this.blockTest(i, j, "nrnrrw0n")) then
								this.setLayer1Block(i, j, '48', true)
						end
				-- up-bottom right
				elseif (this.layer1[j][i].block == '49') then
						-- fix 1
							if (this.blockTest(i, j, "nrn0-ww0")) then
								this.setLayer1Block(i, j, '50', true)
						elseif (this.blockTest(i, j, "ww00-nrn")) then
								this.setLayer1Block(i, j, '51', true)
						-- fix 2
						elseif (this.blockTest(i, j, "wrn0rnrn")) then
								this.setLayer1Block(i, j, '52', true)
						elseif (this.blockTest(i, j, "nrn0rwrn")) then
								this.setLayer1Block(i, j, '53', true)
						end
				-- up-bottom left
				elseif (this.layer1[j][i].block == '54') then
						-- fix 1
							if (this.blockTest(i, j, "nrn-00ww")) then
								this.setLayer1Block(i, j, '55', true)
						elseif (this.blockTest(i, j, "0ww-0nrn")) then
								this.setLayer1Block(i, j, '56', true)
						-- fix 2
						elseif (this.blockTest(i, j, "nrwr0nrn")) then
								this.setLayer1Block(i, j, '57', true)
						elseif (this.blockTest(i, j, "nrnr0nrw")) then
								this.setLayer1Block(i, j, '58', true)
						end
				end
		end end
		-- 9 gen
		print(">> generation [9]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = joints 1 gen =
				-- 4 & 2 diagonal
					if (this.blockTest(i, j, "-0-00-0-")) then
					this.setLayer1Block(i, j, '63', false)
				elseif (this.blockTest(i, j, "00w00w00")) then
						this.setLayer1Block(i, j, '64', false)
				elseif (this.blockTest(i, j, "w000000w")) then
						this.setLayer1Block(i, j, '65', false)
				end
		end
		end end
		-- 10 gen
		print(">> generation [10]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = joints-diagonals 1 gen =
				-- 4 & 2 diagonal
					if (this.blockTest(i, j, "-0-00-0-")) then
						this.setLayer1Block(i, j, '63', false)
				elseif (this.blockTest(i, j, "00w00w00")) then
						this.setLayer1Block(i, j, '64', false)
				elseif (this.blockTest(i, j, "w000000w")) then
						this.setLayer1Block(i, j, '65', false)
				end
		end
		end end
		-- 11 gen
		print(">> generation [11]")
		for i=1, size do for j=1, size do
			-- land
			-- = basic borders =
				-- bottom
					if (this.layer1[j][i].block == '59') then
							if ( this.blockTest(i, j, "w0w00www") ) then
								this.setLayer1Block(i, j, '80', false)
						elseif ( this.blockTest(i, j, "00w00www") or this.blockTest(i, j, "r0w0rwww") or this.blockTest(i, j, "00w0rwww") or this.blockTest(i, j, "r0w00www") ) then
								this.setLayer1Block(i, j, '78', false)
						elseif ( this.blockTest(i, j, "w0000www") or this.blockTest(i, j, "w0rr0www") or this.blockTest(i, j, "w00r0www") or this.blockTest(i, j, "w0r00www") ) then
								this.setLayer1Block(i, j, '79', false)
						end
				-- up
				elseif (this.layer1[j][i].block == '60') then
							if ( this.blockTest(i, j, "www00w0w") ) then
								this.setLayer1Block(i, j, '83', false)
						elseif ( this.blockTest(i, j, "www0000w") or this.blockTest(i, j, "www0rr0w") or this.blockTest(i, j, "www0r00w") or this.blockTest(i, j, "www00r0w") ) then
								this.setLayer1Block(i, j, '81', false)
						elseif ( this.blockTest(i, j, "www00w00") or this.blockTest(i, j, "wwwr0w0r") or this.blockTest(i, j, "w00r0w00") or this.blockTest(i, j, "www00w0r") ) then
								this.setLayer1Block(i, j, '82', false)
						end
				-- right
				elseif (this.layer1[j][i].block == '61') then
							if ( this.blockTest(i, j, "w0w0ww0w") ) then
								this.setLayer1Block(i, j, '89', false)
						elseif ( this.blockTest(i, j, "w0w0w00w") or this.blockTest(i, j, "wrw0wr0w") or this.blockTest(i, j, "wrw0w00w") or this.blockTest(i, j, "w0w0wr0w") ) then
								this.setLayer1Block(i, j, '88', false)
						elseif ( this.blockTest(i, j, "00w0ww0w") or this.blockTest(i, j, "r0w0wwrw") or this.blockTest(i, j, "00w0wwrw") or this.blockTest(i, j, "r0w0ww0w") ) then
								this.setLayer1Block(i, j, '87', false)
						end
				-- left
				elseif (this.layer1[j][i].block == '62') then
							if ( this.blockTest(i, j, "w0ww0w0w") ) then
								this.setLayer1Block(i, j, '86', false)
						elseif ( this.blockTest(i, j, "w0ww0w00") or this.blockTest(i, j, "wrww0w0r") or this.blockTest(i, j, "wrww0w00") or this.blockTest(i, j, "w0ww0w0r") ) then
								this.setLayer1Block(i, j, '85', false)
						elseif ( this.blockTest(i, j, "w00w0w0w") or this.blockTest(i, j, "w0rw0wrw") or this.blockTest(i, j, "w00w0wrw") or this.blockTest(i, j, "w0rw0w0w") ) then
								this.setLayer1Block(i, j, '84', false)
						end
				end
		end end
		-- 12 gen
		print(">> generation [12]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = ends 1 =
				-- left-right
					if ( this.blockTest(i, j, "nwn00nwn") or this.blockTest(i, j, "nwnrrnwn") or this.blockTest(i, j, "nwnr0nwn") or this.blockTest(i, j, "nwn0rnwn") ) then
						this.setLayer1Block(i, j, '98', false)
				-- top-bottom
				elseif ( this.blockTest(i, j, "n0nwwn0n") or this.blockTest(i, j, "nrnwwnrn") or this.blockTest(i, j, "nrnwwn0n") or this.blockTest(i, j, "n0nwwnrn") ) then
						this.setLayer1Block(i, j, '100', false)
				-- top
				elseif ( this.blockTest(i, j, "nwnwwn0n") or this.blockTest(i, j, "nwnwwnrn") ) then
						this.setLayer1Block(i, j, '103', false)
				-- bottom
				elseif ( this.blockTest(i, j, "n0nwwnwn") or this.blockTest(i, j, "nrnwwnwn") ) then
						this.setLayer1Block(i, j, '102', false)
				-- right
				elseif ( this.blockTest(i, j, "nwn0wnwn") or this.blockTest(i, j, "nwnrwnwn") ) then
						this.setLayer1Block(i, j, '104', false)
				-- left
				elseif ( this.blockTest(i, j, "nwnw0nwn") or this.blockTest(i, j, "nwnwrnwn") ) then
						this.setLayer1Block(i, j, '105', false)
				end
		end
		end end
		-- 13 gen
		print(">> generation [13]")
		for i=1, size do for j=1, size do
			-- land
			-- = ends 2 =
					if ( this.layer1[j][i].block == '13' and (this.blockTest(i, j, "nwn00nwn") or this.blockTest(i, j, "nwnrrnwn") or this.blockTest(i, j, "nwnr0nwn") or this.blockTest(i, j, "nwn0rnwn")) ) then
						this.setLayer1Block(i, j, '99', false)
				elseif ( this.layer1[j][i].block == '16' and (this.blockTest(i, j, "n0nwwn0n") or this.blockTest(i, j, "nrnwwnrn") or this.blockTest(i, j, "nrnwwn0n") or this.blockTest(i, j, "n0nwwnrn")) ) then
						this.setLayer1Block(i, j, '101', false)
				end
		end end
		-- 14 gen
		print(">> generation [14]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = angles =
				-- right-bottom
					if ( this.blockTest(i, j, "w0w0wwwn") ) then
						this.setLayer1Block(i, j, '91', false)
				elseif ( this.blockTest(i, j, "nnnnwnwn") ) then
						this.setLayer1Block(i, j, '90', false)
				-- left-bottom
				elseif ( this.blockTest(i, j, "w0ww0nww") ) then
						this.setLayer1Block(i, j, '93', false)
				elseif ( this.blockTest(i, j, "nnnwnnwn") ) then
						this.setLayer1Block(i, j, '92', false)
				-- right-top
				elseif ( this.blockTest(i, j, "wwn0ww0w") ) then
						this.setLayer1Block(i, j, '95', false)
				elseif ( this.blockTest(i, j, "nwnnwnnn") ) then
						this.setLayer1Block(i, j, '94', false)
				-- left-top
				elseif ( this.blockTest(i, j, "nwww0w0w") ) then
						this.setLayer1Block(i, j, '97', false)
				elseif ( this.blockTest(i, j, "nwnwnnnn") ) then
						this.setLayer1Block(i, j, '96', false)
				end
		end
		end end
		-- 15 gen
		print(">> generation [15]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = basic borders 1 gen =
				-- bottom
					if ( this.blockTest(i, j, "nnnrrnwn") ) then
						this.setLayer1Block(i, j, '59', false)
				-- up
				elseif ( this.blockTest(i, j, "nwnrrnnn") ) then
						this.setLayer1Block(i, j, '60', false)
				-- right
				elseif ( this.blockTest(i, j, "nrnnwnrn")) then
						this.setLayer1Block(i, j, '61', false)
				-- left
				elseif ( this.blockTest(i, j, "nrnwnnrn") ) then
						this.setLayer1Block(i, j, '62', false)
				end
		end
		end end
		-- 16 gen
		print(">> generation [16]")
		for i=1, size do for j=1, size do
		if (this.layer1[j][i].block == '0') then
			-- land
			-- = diagonals =
				-- 3 diagonal
					if ( this.blockTest(i, j, "nnwn0w0w") ) then
						this.setLayer1Block(i, j, '74', false)
				elseif ( this.blockTest(i, j, "wnn0nw0w") ) then
						this.setLayer1Block(i, j, '75', false)
				elseif ( this.blockTest(i, j, "w0wn0nnw") ) then
						this.setLayer1Block(i, j, '76', false)
				elseif ( this.blockTest(i, j, "w0w0nwnn") ) then
						this.setLayer1Block(i, j, '77', false)
				-- 2 diagonal
				--elseif ( this.blockTest(i, j, "0n0nnw0w") or this.blockTest(i, j, "rnrnnw0w") or this.blockTest(i, j, "rn0nnw0w")  or this.blockTest(i, j, "0nrnnw0w") ) then
				elseif ( this.blockTest(i, j, "nnnnnw0w") or this.blockTest(i, j, "nnnnnwrw") ) then
						this.setLayer1Block(i, j, '70', false)
				--elseif ( this.blockTest(i, j, "w0wnn0n0") or this.blockTest(i, j, "w0wnnrnr") or this.blockTest(i, j, "w0wnn0nr")  or this.blockTest(i, j, "w0wnnrn0") ) then
				elseif ( this.blockTest(i, j, "w0wnnnnn") or this.blockTest(i, j, "wrwnnnnn") ) then
						this.setLayer1Block(i, j, '71', false)
				--elseif ( this.blockTest(i, j, "0nwn00nw") or this.blockTest(i, j, "rnwn0rnw") or this.blockTest(i, j, "rnwn00nw")  or this.blockTest(i, j, "0nwn0rnw") ) then
				elseif ( this.blockTest(i, j, "nnwn0nnw") or this.blockTest(i, j, "nnwnrnnw") ) then
						this.setLayer1Block(i, j, '72', false)
				--elseif ( this.blockTest(i, j, "wn00nwn0") or this.blockTest(i, j, "wnr0nwnr") or this.blockTest(i, j, "wnr0nwn0")  or this.blockTest(i, j, "wn00nwnr") ) then
				elseif ( this.blockTest(i, j, "wnn0nwnn") or this.blockTest(i, j, "wnnrnwnn") ) then
						this.setLayer1Block(i, j, '73', false) -- 73
				-- 1 diagonal
				elseif ( this.blockTest(i, j, "0nnnnnnw") or this.blockTest(i, j, "rnnnnnnw") ) then
						this.setLayer1Block(i, j, '66', false)
				elseif ( this.blockTest(i, j, "nn0nnwnn") or this.blockTest(i, j, "nnrnnwnn") ) then
						this.setLayer1Block(i, j, '67', false)
				elseif ( this.blockTest(i, j, "nnwnn0nn") or this.blockTest(i, j, "nnwnnrnn") ) then
						this.setLayer1Block(i, j, '68', false)
				elseif ( this.blockTest(i, j, "wnnnnnn0") or this.blockTest(i, j, "wnnnnnnr") ) then
						this.setLayer1Block(i, j, '69', false)
				end
		end
		end end
		-- 17 gen
		print(">> generation [17]")
		for i=1, size do for j=1, size do
			-- river
			-- = angles more (fix) =
				-- right-bottom
					if ( this.layer1[j][i].block == '19' and this.blockTest(i, j, "nnnnwnw0") ) then
						this.setLayer1Block(i, j, '106', true)
				-- left-bottom
				elseif ( this.layer1[j][i].block == '24' and this.blockTest(i, j, "nnnwn0wn") ) then
						this.setLayer1Block(i, j, '107', true)
				-- top-right
				elseif ( this.layer1[j][i].block == '29' and this.blockTest(i, j, "nw0nwnnn") ) then
						this.setLayer1Block(i, j, '108', true)
				-- top-left
				elseif ( this.layer1[j][i].block == '34' and this.blockTest(i, j, "0wnwnnnn") ) then
						this.setLayer1Block(i, j, '109', true)
				end
		end end
		-- 18 gen
		print(">> generation [18]")
		for i=1, size do for j=1, size do
			-- river
			-- = ends more (fix 1) =
				if ( this.layer1[j][i].block == '16' ) then
						if ( this.blockTest(i, j, "n0nrrw0w") ) then
							this.setLayer1Block(i, j, '110', true)
					elseif ( this.blockTest(i, j, "w0wrrn0n") ) then
							this.setLayer1Block(i, j, '111', true)
					elseif ( this.blockTest(i, j, "nrnrrw0w") ) then
							this.setLayer1Block(i, j, '114', true)
					elseif ( this.blockTest(i, j, "w0wrrnrn") ) then
							this.setLayer1Block(i, j, '115', true)
					end
			elseif ( this.layer1[j][i].block == '13' ) then
						if ( this.blockTest(i, j, "nrw00nrw") ) then
							this.setLayer1Block(i, j, '112', true)
					elseif ( this.blockTest(i, j, "wrn00wrn") ) then
							this.setLayer1Block(i, j, '113', true)
					elseif ( this.blockTest(i, j, "nrwr0nrw") ) then
							this.setLayer1Block(i, j, '116', true)
					elseif ( this.blockTest(i, j, "wrn0rwrn") ) then
							this.setLayer1Block(i, j, '117', true)
					end
			end
		end end
		-- 19 gen
		print(">> generation [19]")
		for i=1, size do for j=1, size do
			-- river
			-- = ends more (fix 2) =
					if ( (this.layer1[j][i].block == '47' or this.layer1[j][i].block == '48') and this.blockTest(i, j, "nrnrrw0w") ) then
						this.setLayer1Block(i, j, '114', true)
				elseif ( (this.layer1[j][i].block == '42' or this.layer1[j][i].block == '43') and this.blockTest(i, j, "w0wrrnrn") ) then
						this.setLayer1Block(i, j, '115', true)
				elseif ( (this.layer1[j][i].block == '57' or this.layer1[j][i].block == '58') and this.blockTest(i, j, "nrwr0nrw") ) then
						this.setLayer1Block(i, j, '116', true)
				elseif ( (this.layer1[j][i].block == '52' or this.layer1[j][i].block == '53') and this.blockTest(i, j, "wrn0rwrn") ) then
						this.setLayer1Block(i, j, '117', true)
				end
		end end
		-- 20 gen
		print(">> generation [20]")
		for i=1, size do for j=1, size do
			-- river
			-- = lined angles =
				if ( this.layer1[j][i].block == '16' ) then
						if ( this.blockTest(i, j, "nnnrrnnw") ) then
							this.setLayer1Block(i, j, '122', true)
					elseif ( this.blockTest(i, j, "nnnrrwnn") ) then
							this.setLayer1Block(i, j, '123', true)
					elseif ( this.blockTest(i, j, "nnwrrnnn") ) then
							this.setLayer1Block(i, j, '124', true)
					elseif ( this.blockTest(i, j, "wnnrrnnn") ) then
							this.setLayer1Block(i, j, '125', true)
					end
			elseif ( this.layer1[j][i].block == '13' ) then
						if ( this.blockTest(i, j, "nrnnnnrw") ) then
							this.setLayer1Block(i, j, '118', true)
					elseif ( this.blockTest(i, j, "nrnrnwnn") ) then
							this.setLayer1Block(i, j, '119', true)
					elseif ( this.blockTest(i, j, "nrwnnnrn") ) then
							this.setLayer1Block(i, j, '120', true)
					elseif ( this.blockTest(i, j, "wrnnnnrn") ) then
							this.setLayer1Block(i, j, '121', true)
					end
			end
		end end
		-- 21 gen
		print(">> generation [21]")
		for i=1, size do for j=1, size do
			-- river
			-- = ends fix =
				if ( this.layer1[j][i].block == '5' ) then
						if ( this.blockTest(i, j, "n0n000rw") ) then
							this.setLayer1Block(i, j, '132', true)
					elseif ( this.blockTest(i, j, "n0n00wr0") ) then
							this.setLayer1Block(i, j, '136', true)
					end
			elseif ( this.layer1[j][i].block == '7' ) then
						if ( this.blockTest(i, j, "wr000n0n") ) then
							this.setLayer1Block(i, j, '134', true)
					elseif ( this.blockTest(i, j, "0rw00n0n") ) then
							this.setLayer1Block(i, j, '138', true)
					end
			elseif ( this.layer1[j][i].block == '9' ) then
						if ( this.blockTest(i, j, "n0w0rn00") ) then
							this.setLayer1Block(i, j, '135', true)
					elseif ( this.blockTest(i, j, "n000rn0w") ) then
							this.setLayer1Block(i, j, '139', true)
					end
			elseif ( this.layer1[j][i].block == '11' ) then
						if ( this.blockTest(i, j, "00nr0w0n") ) then
							this.setLayer1Block(i, j, '133', true)
					elseif ( this.blockTest(i, j, "w0nr000n") ) then
							this.setLayer1Block(i, j, '137', true)
					end
			end
		end end
		-- 22 gen
		print(">> generation [21]")
		for i=1, size do for j=1, size do
			-- river
			-- = ends fix =
				-- up
					if ( this.layer1[j][i].block == '136' ) then
							if ( this.blockTest(i, j, "wnwnnwrn") ) then
								this.setLayer1Block(i, j, '187', true)
						elseif ( this.blockTest(i, j, "nnwnnwrn") ) then
								this.setLayer1Block(i, j, '179', true)
						elseif ( this.blockTest(i, j, "wnnnnwrn") ) then
								this.setLayer1Block(i, j, '183', true)
						end
				elseif ( this.layer1[j][i].block == '132' ) then
							if ( this.blockTest(i, j, "wnwnnnrw") ) then
								this.setLayer1Block(i, j, '175', true)
						elseif ( this.blockTest(i, j, "nnwnnnrw") ) then
								this.setLayer1Block(i, j, '167', true)
						elseif ( this.blockTest(i, j, "wnnnnnrw") ) then
								this.setLayer1Block(i, j, '171', true)
						end
				-- right
				elseif ( this.layer1[j][i].block == '133' ) then
							if ( this.blockTest(i, j, "nnwrnwnw") ) then
								this.setLayer1Block(i, j, '176', true)
						elseif ( this.blockTest(i, j, "nnnrnwnw") ) then
								this.setLayer1Block(i, j, '168', true)
						elseif ( this.blockTest(i, j, "nnwrnwnn") ) then
								this.setLayer1Block(i, j, '172', true)
						end
				elseif ( this.layer1[j][i].block == '137' ) then
							if ( this.blockTest(i, j, "wnwrnnnw") ) then
								this.setLayer1Block(i, j, '188', true)
						elseif ( this.blockTest(i, j, "wnnrnnnw") ) then
								this.setLayer1Block(i, j, '180', true)
						elseif ( this.blockTest(i, j, "wnwrnnnn") ) then
								this.setLayer1Block(i, j, '184', true)
						end
				-- bottom
				elseif ( this.layer1[j][i].block == '138' ) then
							if ( this.blockTest(i, j, "nrwnnwnw") ) then
								this.setLayer1Block(i, j, '189', true)
						elseif ( this.blockTest(i, j, "nrwnnwnn") ) then
								this.setLayer1Block(i, j, '181', true)
						elseif ( this.blockTest(i, j, "nrwnnnnw") ) then
								this.setLayer1Block(i, j, '185', true)
						end
				elseif ( this.layer1[j][i].block == '134' ) then
							if ( this.blockTest(i, j, "wrnnnwnw") ) then
								this.setLayer1Block(i, j, '177', true)
						elseif ( this.blockTest(i, j, "wrnnnwnn") ) then
								this.setLayer1Block(i, j, '169', true)
						elseif ( this.blockTest(i, j, "wrnnnnnw") ) then
								this.setLayer1Block(i, j, '173', true)
						end
				-- left
				elseif ( this.layer1[j][i].block == '139' ) then
							if ( this.blockTest(i, j, "wnnnrwnw") ) then
								this.setLayer1Block(i, j, '190', true)
						elseif ( this.blockTest(i, j, "wnnnrnnw") ) then
								this.setLayer1Block(i, j, '182', true)
						elseif ( this.blockTest(i, j, "nnnnrwnw") ) then
								this.setLayer1Block(i, j, '186', true)
						end
				elseif ( this.layer1[j][i].block == '135' ) then
							if ( this.blockTest(i, j, "wnwnrwnn") ) then
								this.setLayer1Block(i, j, '178', true)
						elseif ( this.blockTest(i, j, "wnwnrnnn") ) then
								this.setLayer1Block(i, j, '170', true)
						elseif ( this.blockTest(i, j, "nnwnrwnn") ) then
								this.setLayer1Block(i, j, '174', true)
						end
				end
		end end
		-- 23 gen
		print(">> generation [23]")
		for i=1, size do for j=1, size do
			-- river
			-- = ends fix =
				if ( this.layer1[j][i].block == '6' ) then
						if ( this.blockTest(i, j, "w0w00nwn") ) then
							this.setLayer1Block(i, j, '163', true)
					elseif ( this.blockTest(i, j, "00w00nwn") or this.blockTest(i, j, "r0w00nwn") ) then
							this.setLayer1Block(i, j, '155', true)
					elseif ( this.blockTest(i, j, "w0000nwn") or this.blockTest(i, j, "w0r00nwn") ) then
							this.setLayer1Block(i, j, '159', true)
					end
			elseif ( this.layer1[j][i].block == '8' ) then
						if ( this.blockTest(i, j, "nwn00w0w") ) then
							this.setLayer1Block(i, j, '165', true)
					elseif ( this.blockTest(i, j, "nwn0000w") or this.blockTest(i, j, "nwn00r0w") ) then
							this.setLayer1Block(i, j, '161', true)
					elseif ( this.blockTest(i, j, "nwn00w00") or this.blockTest(i, j, "nwn00w0r") ) then
							this.setLayer1Block(i, j, '157', true)
					end
			elseif ( this.layer1[j][i].block == '10' ) then
						if ( this.blockTest(i, j, "w0n0ww0n") ) then
							this.setLayer1Block(i, j, '166', true)
					elseif ( this.blockTest(i, j, "w0n0wr0n") or this.blockTest(i, j, "w0n0w00n") ) then
							this.setLayer1Block(i, j, '158', true)
					elseif ( this.blockTest(i, j, "r0n0ww0n") or this.blockTest(i, j, "00n0ww0n") ) then
							this.setLayer1Block(i, j, '162', true)
					end
			elseif ( this.layer1[j][i].block == '12' ) then
						if ( this.blockTest(i, j, "n0ww0n0w") ) then
							this.setLayer1Block(i, j, '164', true)
					elseif ( this.blockTest(i, j, "n0ww0n0r") or this.blockTest(i, j, "n0ww0n00") ) then
							this.setLayer1Block(i, j, '160', true)
					elseif ( this.blockTest(i, j, "n0rw0n0w") or this.blockTest(i, j, "n00w0n0w") ) then
							this.setLayer1Block(i, j, '156', true)
					end
			end
		end end
		-- ? gen (more gen)
		
		-- end gen
		print(">> generation [end]")
		for i=1, size do for j=1, size do
			if (this.layer1[j][i].block == '-') then
				-- water
				if (le.random:int("0","1") == "1") then
					this.setLayer1Block(i, j, '126', false)
				else
						if (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '127', false)
					elseif (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '128', false)
					end
				end
		elseif (this.layer1[j][i].block == '0') then
				-- land
				if (le.random:int("0","1") == "1") then
					this.setLayer1Block(i, j, '129', false)
				else
						if (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '130', false)
					elseif (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '131', false)
					end
				end
		elseif (this.layer1[j][i].block == '4') then
				-- land
				if (le.random:int("0","1") == "1") then
					this.setLayer1Block(i, j, '140', false)
				else
						if (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '141', false)
					elseif (le.random:int("0","1") == "1") then 
							this.setLayer1Block(i, j, '142', false)
					end
				end
		end
		end end
		------------------------------------------------------------------
	end
	this.generate = generate
	
	-- -- -- load map -- -- --
	local function load(loadmap)
		this.layer1 = loadmap
		size = #this.layer1
		-- grid
		this.generateGrid(size)
		-- pixelate
		this.generatePixelate(size)
	end
	this.load = load
	
	-- -- -- draw map -- -- --
	firstDraw = true
	hForMax = 0
	wForMax = 0
	local function draw(cx, cy, cw, ch, distanceUpdate)
		-- pre math
		if distanceUpdate or firstDraw then
			this.updateBlockDistance(cx, cy, cw, ch)
			
			hForMax = math.min(this.size, this.blockDistanceH - 1)
			wForMax = math.min(this.size, this.blockDistanceW - 1)
		end
		--print(this.blockDistanceX.." : "..wForMax, this.blockDistanceY.." : "..hForMax)
		-- 
		for i = this.blockDistanceY, hForMax do
		for j = this.blockDistanceX, wForMax do
			-- basic
			local b = this.layer1[j][i]
			local block = b.block
			if block == '-' then
				b.drawTile(0, 0)
			elseif block == '0' then
				b.drawTile(0, 1)
			else
				b.drawTile(0, block)
			end
			-- biomes
			if this.debugMap == 'biome' and b.biome then
				b.drawTile(2, b.biome)
			elseif this.debugMap == 'river' and b.river then
				b.drawTexture(1)
			end
			-- grid / pixelate
			if this.drawingGrid then
				this.layer2[j][i].drawTile(0, this.layer2[j][i].tileNum) -- g
			end
			this.layer3[j][i].drawTile(0, this.layer3[j][i].tileNum) -- p
		end
		end
		--
		if (firstDraw == true) then
			firstDraw = false
		end
	end
	this.draw = draw
	
    return this
end