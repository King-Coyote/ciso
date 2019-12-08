local staticStyle = {
    enabled = {
        bgColor = {50,50,50,255},
        fgColor = {255,255,255,255}
    }
}

local dynamicStyle = {
    enabled = {
        bgColor = {50,50,50,255},
        fgColor = {255,255,255,255}
    },
    hover = {
        bgColor = {75,85,100,255},
        fgColor = {255,255,255,255}
    },
    clicked = {
        bgColor = {95, 115, 120,255},
        fgColor = {255,255,255,255}
    },
}
-- package.path = package.path .. ";./ButtonBasic.lua"
-- print(package.path)
-- local scriptPath = arg[0]
-- local dir = string.match(scriptPath, '^.*/')
-- local startSize = {100, 50}
-- local pos = {Gui:screenWidth() - 100, 0}
-- package.path = package.path .. ';' .. dir .. '?.lua'
-- local ButtonBasic = require "ButtonBasic"
-- ButtonBasic(startSize, pos, 'Fuck', 'buttonBasic')

-- local startSize = {100, 50}
-- local pos = {Gui:screenWidth() - 100, 0}

-- local objectSelectorDropdown = {
--     type = "button",
--     id = "objSelectorDropdown",
--     style = staticStyle,
--     properties = {
--         position = {pos[1], pos[2] + startSize[2]},
--         size = {75,100},
--         hidden = true,
--         handleOnNotClick = function(self, x, y, mouseButton)
--             self.call:setProperties{
--                 hidden = true
--             }
--         end,
--     },
-- }

-- local objectSelectorOther = {
--     type = "button",
--     style = dynamicStyle,
--     id = 'objectSelectorOther',
--     properties = {
--         position = {pos[1], pos[2]},
--         size = startSize,
--         handleOnClick = function(self, x, y, mouseButton)
--             objectSelectorDropdown.call:setProperties{
--                 hidden = false,
--             }
--         end
--     },
-- }

-- Gui:render{
--     objectSelectorOther,
--     objectSelectorDropdown
-- }

-- print(objectSelectorDropdown.call)
-- print(objectSelectorOther.call)