-- Lacuna Engine scene script file
require('objects/camera')
require('objects/object')

require('objects/map')
require('objects/loadMap')

require('objects/functions/tableLength')
require('objects/functions/printTable')

objects = {}
function init()
	print( '! init func' )
	print( tableLength(le) )
	print( 'scene  : ', le.scene.name )
	
	c = camera(256, 256, 1280, 768)
	c.current()
	
	--print( "objects: ", le.scene.objects )
	--print( "size   : ", tableLength(le.scene.objects) )
	--printTable(le.scene.objects)
	
	-- map
	m = map()
	--m.load(loadMap_land0)
	m.generate(50)
	
	-- map output
	for i, value in ipairs(mg) do
		buffer = ""
		for j=1, value:len() do
			buffer = buffer.. value[j].." "
		end
		print(buffer)
		buffer = ""
	end
	
	-- code object
	c1 = object('castle1', 612, 452, 24, 24)
		c1t = le.texture:new('textures/castle.png', 'rgba_f:1,1,1,1')
		--print("castle1 texture num: ", c1t)
		--le.texture:rotate(c1t, "90")
		c1.addTexture(c1t)
		c1.addTexture(le.texture:new('textures/bracket.png', 'rgba_f:1,1,0.5,1'))
	table.insert(objects, c1)
	
	-- to object list to draw
	for i = 1, #le.scene.objects do
		local item = le.scene.objects[i]
		
		o = object(item.name, item.position[1], item.position[2], item.size[1], item.size[2])
		for j = 1, #item.textures do
			o.addTexture(le.texture:new(item.textures[j][1], item.textures[j][2]))
		end
		
		table.insert(objects, o)
	end
end

firstUpdate = true
mapDistanceUpdate = false
function update()
	-- ui
		-- top panel 1
		le.ui:windowBegin('ui1', 'noTitleBar, noMove, noDocking, noResize, noBackground, noBringToFrontOnFocus, noScroll')
			if firstUpdate == true then
				le.ui:setWindowPos(0, 0)
				le.ui:setWindowSize(212, 108)
			end
			le.ui:image(le.texture:new('textures/topPanel1.png', 'rgba_f:1,1,1,1'), 212, 108)
			
			le.ui:setCursorPos(17, 2)
			le.ui:findImage('player')
			
			le.ui:setCursorPos(59, 2)
			if le.ui:button('', 136, 28) then
				print('log button')
			end
			le.ui:setCursorPos(59, 2)
			le.ui:centerText('log', 90, 2, 105, 28)
		le.ui:windowEnd()
		-- top panel 2
		le.ui:windowBegin('ui2', 'noTitleBar, noMove, noDocking, noResize, noBackground, noBringToFrontOnFocus, noScroll')
			if firstUpdate == true then
				le.ui:setWindowPos(1188, 0)
				le.ui:setWindowSize(92, 168)
			end
			le.ui:image(le.texture:new('textures/topPanel2.png', 'rgba_f:1,1,1,1'), 92, 168)
			
			le.ui:setCursorPos(26, 2)
			if le.ui:button('time', 64, 28) then
				print('time button')
			end
			le.ui:setCursorPos(55, 46)
			le.ui:button('', 32, 17)
			le.ui:setCursorPos(55, 78)
			le.ui:button('', 32, 17)
			le.ui:setCursorPos(55, 110)
			le.ui:button('', 32, 17)
			le.ui:setCursorPos(55, 142)
			le.ui:button('', 32, 17)
		le.ui:windowEnd()
	--
	if firstUpdate == true then
		firstUpdate = false
	end
	-- movement
	if le.key:pressed(le.key:code('W')) then
		c.y = c.y-64
		c.move('move', 0, -64)
		mapDistanceUpdate = true
	elseif le.key:pressed(le.key:code('A')) then
		c.x = c.x-64
		c.move('move', -64, 0)
		mapDistanceUpdate = true
	elseif le.key:pressed(le.key:code('S')) then
		c.y = c.y+64
		c.move('move', 0, 64)
		mapDistanceUpdate = true
	elseif le.key:pressed(le.key:code('D')) then
		c.x = c.x+64
		c.move('move', 64, 0)
		mapDistanceUpdate = true
	-- grid
	elseif le.key:pressed(le.key:code('G')) then
		m.drawingGrid = not m.drawingGrid
	-- debug map
	elseif le.key:pressed(le.key:code('N')) then
		m.debugMap = 'normal'
	elseif le.key:pressed(le.key:code('R')) then
		m.debugMap = 'river'
	elseif le.key:pressed(le.key:code('B')) then
		m.debugMap = 'biome'
	end
end

function draw()
	-- map
	m.draw(c.x, c.y, c.w, c.h, mapDistanceUpdate)
	
	-- objects
	for i = 1, #objects do
		objects[i].drawTextures()
	end
	
	-- ! в объекте должна быть функция которая принимает аргумент несколько номеров для отрисоки drawTexture
	
	-- отрисовывает все объекты каждый кадр
	-- ссылки на отрисовки добавляются сюда после scene build func (а точнее после работы init)
	-- эта функция тоже добавляется сюда и не может иметь дубликат как сделано сейчас
	-- она ссылкается на объекты из le.scene и поэтому должна реагировать на изменения в update
end