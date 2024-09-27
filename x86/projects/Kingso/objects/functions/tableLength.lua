--
function tableLength(T)
	local Count = 0
	for _ in pairs(T) do Count = Count + 1 end
	return Count
end