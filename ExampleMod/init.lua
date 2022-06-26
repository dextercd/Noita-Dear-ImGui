local imgui = load_imgui({version="0.0.0"})

local fx, fy
local clear_progress = 0
local clearing = false
local itemix = 1

local r, g, b, a = 1, 1, 1, 1

function OnWorldPostUpdate()
    local player = EntityGetWithTag("player_unit")[1]
    local x, y = -1, -1
    if player then
        x, y = EntityGetTransform(player)
        if fx == nil then
            fx, fy = x, y
        end
    end

    imgui.Begin("Player position")
        imgui.Text(string.format("Position: %.2f %.2f", x, y))
        if imgui.Button("Reset") then
            EntitySetTransform(player, fx, fy)
        end

        if not clearing then
            if imgui.Button("Clear") then
                clearing = true
                v = v + 100
            end
        else
            imgui.ProgressBar(clear_progress, -1, 0, "Clearing..")
            clear_progress = clear_progress + 1/60/3
            if clear_progress > 1.2 then
                EntityKill(player)
            end
        end

        -- In many cases the first result returned indicates whether the input changed.
        -- If you don't care about it you can just write it to a random variable, in this case we use _.
        _, itemix = imgui.Combo("Test", itemix, {"Hey", "Hello", "Bye", "Bananana"})

        -- If you do care about it, but want to keep the variable local to the current scope,
        -- you can split if over multiple lines like this:
        local col_changed
        col_changed, r, g, b, a = imgui.ColorEdit4("Colour", r, g, b, a)
    imgui.End()
end
