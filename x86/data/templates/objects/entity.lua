-- Entity
Entity = {}
function Entity : New(Name)
    local this = {}
    this.Name = Name
    
    setmetatable(this, self)
    Entity.__index = Entity
    return this
end
