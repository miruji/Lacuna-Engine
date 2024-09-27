--
function printTable(table, indent)
    indent = indent or 0
    local spacing = ""
	if indent >= 1 then
		for i = 1, indent do
			spacing = spacing .. "  "
		end
	end
    
    for key, value in pairs(table) do
        if type(value) == "table" then
            print(spacing .. key .. ":")
            printTable(value, indent + 1)
        elseif type(value) ~= "function" then
            print(spacing .. key .. ": " .. tostring(value))
        end
    end
end