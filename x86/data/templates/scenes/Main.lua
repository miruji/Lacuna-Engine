-- Lacuna Engine scene file
require('Objects/Camera')

function tablelength(T)
	local count = 0
	for _ in pairs(T) do count = count + 1 end
	return count
end
function Init()
	--
	print('LE', LE)
	print('LE Length', tablelength(LE))
	
	C = Camera('256', '256', '1280', '768')
	C.Current()
	
end
function Draw()
	-- movement
	if ( LE.Key:Pressed(LE.Key:Code('W')) ) then
		C.Y = (C.Y-64)..''
		C.Move('MOVE', '0', '-64')
	elseif ( LE.Key:Pressed(LE.Key:Code('A')) ) then
		C.X = (C.X-64)..''
		C.Move('MOVE', '-64', '0')
	elseif ( LE.Key:Pressed(LE.Key:Code('S')) ) then
		C.Y = (C.Y+64)..''
		C.Move('MOVE', '0', '64')
	elseif ( LE.Key:Pressed(LE.Key:Code('D')) ) then
		C.X = (C.X+64)..''
		C.Move('MOVE', '64', '0')
	end
end
