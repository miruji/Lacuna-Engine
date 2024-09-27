-- Lacuna Engine scene script file
require('objects/camera')
require('objects/object')

require('objects/functions/tableLength')
require('objects/functions/printTable')

objects = {}
function init()
	print( '! init func' )
	print( tableLength(le) )
	print( 'scene  : ', le.scene.name )
	
	c = camera(0, 0, 1280, 768)
	c.current()
	--print( "objects: ", le.scene.objects )
	--print( "size   : ", tableLength(le.scene.objects) )
	--printTable(le.scene.objects)
	
	le.texture:new('textures/bottomPanel.png', 'rgba_f:1,1,1,1');
	
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
function update()
	-- ui
	le.ui:windowBegin('ui1', 'noTitleBar, noMove, noDocking, noResize, noBackground, noBringToFrontOnFocus, noScroll')
		if firstUpdate == true then
			le.ui:setWindowPos(0, 588)
			le.ui:setWindowSize(1280, 163)
		end
		le.ui:findImage('bottomPanel')
		
		le.ui:setCursorPos(32, 38)
		le.ui:text('Hello world!')
	le.ui:windowEnd()
	--
	if firstUpdate == true then
		firstUpdate = false
	end
	-- movement
	if le.key:pressed(le.key:code('W')) then
		c.y = tostring(c.y - 64)
		c.move('move', 0, -64)
	elseif le.key:pressed(le.key:code('A')) then
		c.x = tostring(c.x - 64)
		c.move('move', -64, 0)
	elseif le.key:pressed(le.key:code('S')) then
		c.y = tostring(c.y + 64)
		c.move('move', 0, 64)
	elseif le.key:pressed(le.key:code('D')) then
		c.x = tostring(c.x + 64)
		c.move('move', 64, 0)
	end
end

function draw()
	-- objects
	for i = 1, #objects do
		objects[i].drawTextures()
	end
end