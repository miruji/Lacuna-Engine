require("objects/functions/tableLength")
require("objects/functions/splitStr")

-- for s[0]
string_meta = getmetatable('')
function string_meta:__index(key)
    local val = string[key]
    if (val) then
        return val
    elseif ( tonumber(key) ) then
        return self:sub(key, key)
    else
        error( "attempt to index a string value with bad key ('"..tostring(key).."' is not part of the string library)", 2 )
    end
end
-- replace char in str
function replaceChar(pos, str, r)
    return str:sub(1, pos-1) ..r.. str:sub(pos+1)
end
--
function mapGeneration(size) -- ! size > ~4 
	local this = {}
	result = {}
	
	-- fill map 50/50
	for i=1, size do
		buffer = ""
		for j=1, size do
			
			if (le.random:int("0","1") == '0') then buffer = buffer..'0'
			else                                    buffer = buffer..'-' end
			
		end
		result[i] = buffer
	end
	
	-- block test (basic)
	local function blockTest(i, j, data)
		-- 1
		if (data[1] ~= 'N') then
		if (i>1 and j>1) then
			if (data[1] ~= result[i-1][j-1]) then
				return false
			end
		else return false end
		end
		-- 2
		if (data[2] ~= 'N') then
		if (i>1) then
			if (data[2] ~= result[i-1][j]) then
				return false
			end
		else return false end
		end
		-- 3
		if (data[3] ~= 'N') then
		if (i>1 and j<size-1) then
			if (data[3] ~= result[i-1][j+1]) then
				return false
			end
		else return false end
		end
		-- 4
		if (data[4] ~= 'N') then
		if (j>1) then
			if (data[4] ~= result[i][j-1]) then
				return false
			end
		else return false end
		end
		-- 5
		if (data[5] ~= 'N') then
		if (j<size-1) then
			if (data[5] ~= result[i][j+1]) then
				return false
			end
		else return false end
		end
		-- 6
		if (data[6] ~= 'N') then
		if (i<size-1 and j>1) then
			if (data[6] ~= result[i+1][j-1]) then
				return false
			end
		else return false end
		end
		-- 7
		if (data[7] ~= 'N') then
		if (i<size-1) then
			if (data[7] ~= result[i+1][j]) then
				return false
			end
		else return false end
		end
		-- 8
		if (data[8] ~= 'N') then
		if (i<size-1 and j<size-1) then
			if (data[8] ~= result[i+1][j+1]) then
				return false
			end
		else return false end
		end
		
		return true
	end
	this.blockTest = blockTest
	-- block test (count)
	local function blockTest2(i, j, count, type)
		searchCount = 0
		
		c1 = false
		c2 = false
		c3 = false
		c4 = false
		c5 = false
		c6 = false
		c7 = false
		c8 = false
		
		s  = splitStr(count,';')
		sl = tableLength( s )
		for i=1, sl do
				if (s[i] == '1') then c1 = true
			elseif (s[i] == '2') then c2 = true
			elseif (s[i] == '3') then c3 = true
			elseif (s[i] == '4') then c4 = true
			elseif (s[i] == '5') then c5 = true
			elseif (s[i] == '6') then c6 = true
			elseif (s[i] == '7') then c7 = true
			elseif (s[i] == '8') then c8 = true
			end
		end
		
		-- 1
		if (i>1 and j>1) then
		if (result[i-1][j-1] == type) then
			searchCount = searchCount+1
		end end
		-- 2
		if (i>1) then
		if (result[i-1][j] == type) then
			searchCount = searchCount+1
		end end
		-- 3
		if (i>1 and j<size-1) then
		if (result[i-1][j+1] == type) then
			searchCount = searchCount+1
		end end
		-- 4
		if (j>1) then
		if (result[i][j-1] == type) then
			searchCount = searchCount+1
		end end
		-- 5
		if (j<size-1) then
		if (result[i][j+1] == type) then
			searchCount = searchCount+1
		end end
		-- 6
		if (i<size-1 and j>1) then
		if (result[i+1][j-1] == type) then
			searchCount = searchCount+1
		end end
		-- 7
		if (i<size-1) then
		if (result[i+1][j] == type) then
			searchCount = searchCount+1
		end end
		-- 8
		if (i<size-1 and j<size-1) then
		if (result[i+1][j+1] == type) then
			searchCount = searchCount+1
		end end
		
			if (searchCount == 8 and c8 == true) then
				return true
		elseif (searchCount == 7 and c7 == true) then
				return true
		elseif (searchCount == 6 and c6 == true) then
				return true
		elseif (searchCount == 5 and c5 == true) then
				return true
		elseif (searchCount == 4 and c4 == true) then
				return true
		elseif (searchCount == 3 and c3 == true) then
				return true
		elseif (searchCount == 2 and c2 == true) then
				return true
		elseif (searchCount == 1 and c1 == true) then
				return true
		else
				return false
		end
	end
	this.blockTest2 = blockTest2
	
	-- gen 1 (land 1)
	for q=0, 2 do
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' and blockTest2(i, j, "3;6;8", '0') ) then
			result[i] = replaceChar(j, result[i], '-')
		end
		if ( result[i][j] == '-' and blockTest2(i, j, "3;6;8", '-') ) then
			if ( tonumber(le.random:int("0","10")) >= 8 ) then
				result[i] = replaceChar(j, result[i], '0')
			end
		end
	end end
	end
	-- gen 2 (land 2)
	for q=0, 50 do
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' and blockTest2(i, j, "3;6;7;8", '0') ) then
			result[i] = replaceChar(j, result[i], '-')
		end
		if ( result[i][j] == '-' and blockTest2(i, j, "3;6;7;8", '-') ) then
			result[i] = replaceChar(j, result[i], '0')
		end
	end end
	end
	-- gen 3 (fix land)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' and 
			 (blockTest(i, j, "-0----0-") or blockTest(i, j, "---00---") or 
			  blockTest(i, j, "-0------") or blockTest(i, j, "------0-") or
			  blockTest(i, j, "---0----") or blockTest(i, j, "----0---")
			 ) and le.random:int("0","1") == "1" 
		   ) then
			result[i] = replaceChar(j, result[i], '-')
		end
	end end
	-- gen 4 (fix land & lakes 1)
	for i=1, size do
	for j=1, size do
			if ( result[i][j] == '0' and blockTest(i, j, "0-0000-0") or blockTest(i, j, "000--000") ) then
				result[i] = replaceChar(j, result[i], '-')
		elseif ( result[i][j] == '-' and blockTest(i, j, "N0N00N0N") ) then
				if ( tonumber(le.random:int("0","10")) >= 4 ) then
					result[i] = replaceChar(j, result[i], '0')
				end
		end
	end end
	-- gen 5 (fix borders)
	for i=1, size do
	for j=1, size do
		Border1 = tonumber(le.random:int("0",(size/8)..""))
		if (le.random:int("0","3") == "3") then
			Border1 = Border1*2
		end
		Border2 = tonumber(le.random:int("2","4"))
		if (le.random:int("0","5") == "5") then
			Border2 = Border2*2
		end
		
			if ( result[i][j] == '0' and (i <= Border1 or i >= size-(Border1-1) or j <= Border1 or j >= size-(Border1-1)) ) then
				result[i] = replaceChar(j, result[i], '-')
		elseif ( result[i][j] == '0' and (i <= Border2 or i >= size-(Border2-1) or j <= Border2 or j >= size-(Border2-1)) ) then
				result[i] = replaceChar(j, result[i], '-')
		end
	end end
	-- gen 6 (fix rivers 1)
	for i=1, size do
	for j=1, size do
			if ( le.random:int("0","4") == "1" and result[i][j] == '-' and blockTest(i, j, "N0NNNNNN") and result[i-2][j] == '-') then
				result[i-1] = replaceChar(j, result[i-1], '-')
		elseif ( le.random:int("0","4") == "1" and result[i][j] == '-' and blockTest(i, j, "NNN0NNNN") and result[i][j-2] == '-') then
				result[i] = replaceChar(j-1, result[i], '-')
		end
	end end
	-- gen 7 (more land)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '-' and le.random:int("0","3") == "3" ) then
			result[i] = replaceChar(j, result[i], '0')
		end
	end end
	-- gen 8 (fix borders)
	for i=1, size do
	for j=1, size do
		Border1 = tonumber(le.random:int("0",(size/8)..""))
		if (le.random:int("0","3") == "3") then
			Border1 = Border1*2
		end
		Border2 = tonumber(le.random:int("2","4"))
		if (le.random:int("0","5") == "5") then
			Border2 = Border2*2
		end
		
			if ( result[i][j] == '0' and (i <= Border1 or i >= size-(Border1-1) or j <= Border1 or j >= size-(Border1-1)) ) then
				result[i] = replaceChar(j, result[i], '-')
		elseif ( result[i][j] == '0' and (i <= Border2 or i >= size-(Border2-1) or j <= Border2 or j >= size-(Border2-1)) ) then
				result[i] = replaceChar(j, result[i], '-')
		end
	end end
	-- gen 9 (fix rivers 2)
	for i=1, size do
	for j=1, size do
			if ( le.random:int("0","5") == "1" and result[i][j] == '-' and blockTest(i, j, "N0NNNNNN") and result[i-2][j] == '-') then
				result[i-1] = replaceChar(j, result[i-1], '-')
		elseif ( le.random:int("0","5") == "1" and result[i][j] == '-' and blockTest(i, j, "NNN0NNNN") and result[i][j-2] == '-') then
				result[i] = replaceChar(j-1, result[i], '-')
		end
	end end
	-- gen 10 (fix land & lakes 2)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '-' and blockTest(i, j, "N0N00N0N") and le.random:int("0","1") == "1" ) then
			result[i] = replaceChar(j, result[i], '0')
		end
	end end
	-- gen 11 (angles)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' and 
		     (blockTest(i, j, "-00---0-") or blockTest(i, j, "00----0-") or blockTest(i, j, "-0---00-") or blockTest(i, j, "-0----00") or
			  blockTest(i, j, "---00--0") or blockTest(i, j, "--000---") or blockTest(i, j, "---000--") or blockTest(i, j, "0--00---") or
			  blockTest(i, j, "-00-----") or blockTest(i, j, "00------") or blockTest(i, j, "-----00-") or blockTest(i, j, "------00") or
			  blockTest(i, j, "----0--0") or blockTest(i, j, "--0-0---") or blockTest(i, j, "---0-0--") or blockTest(i, j, "0--0----")) 
		   ) then
			result[i] = replaceChar(j, result[i], '-')
		end
	end end
	-- gen 12 (islands fix 1)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' ) then 
				if ( blockTest(i, j, "--0--0--") or blockTest(i, j, "0------0") ) then
					result[i] = replaceChar(j, result[i], '-')
			elseif ( le.random:int("0","4") == "1" and 
			         (blockTest(i, j, "--0-----") or blockTest(i, j, "0-------") or
					  blockTest(i, j, "-------0") or blockTest(i, j, "-----0--")) 
				   ) then
					result[i] = replaceChar(j, result[i], '-')
			end
		end
	end end
	-- gen 12 (islands fix 2)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '-' ) then 
				if ( blockTest(i, j, "-0----0-") and blockTest2(i-1, j, "1;2;3;4;5;6;7;8", '0') ) then
					result[i-1] = replaceChar(j, result[i-1], '-')
			elseif ( blockTest(i, j, "---00---") and blockTest2(i, j-1, "1;2;3;4;5;6;7;8", '0') ) then
					result[i] = replaceChar(j-1, result[i], '-')
			end
		end
	end end
	-- gen 13 (islands fix 3)
	for i=1, size do
	for j=1, size do
		if ( result[i][j] == '0' and blockTest2(i, j, "1;2;3;4;5;6;7;8", '0') == false) then 
			result[i] = replaceChar(j, result[i], '-')
		end
	end end
	
	return result
end