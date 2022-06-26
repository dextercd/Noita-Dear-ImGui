-- Any mod that wants to use NoitaDearImGui should be below it in the mod load
-- order. Any such mod will gain a new function named 'load_imgui'.
--
-- You should pass it the version you want and the name of your mod. This will
-- be used to try to keep your mod compatible with newer versions of the
-- NoitaDearImGui mod.
-- If your mod requests a newer version than the one the user has installed they
-- will receive a warning about this.
--
-- load_imgui returns a table with functions and enumeration values. This is
-- used to create GUIs.
local imgui = load_imgui({version="0.0.1", mod="NoitaDearImGuiExampleMod"})

-- Global values, we don't want these to reset on every iteration.
local fx, fy
local clear_progress = 0
local clearing = false
local itemix = 1
local r, g, b, a = 1, 1, 1, 1

-- You must call the Widgets functions on every frame that you want your UI to
-- be shown. Here we use OnWorldPostUpdate.
function OnWorldPostUpdate()
    local player = EntityGetWithTag("player_unit")[1]
    local x, y = -1, -1
    if player then
        x, y = EntityGetTransform(player)
        if fx == nil then
            fx, fy = x, y
        end
    end

    imgui.Begin("Player position.")
        imgui.Text(string.format("Position: %.2f %.2f", x, y))
        if imgui.Button("Reset") then
            EntitySetTransform(player, fx, fy)
        end

        if not clearing then
            imgui.SameLine()
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
        -- you can create the variable on a separate line:
        local col_changed
        col_changed, r, g, b, a = imgui.ColorEdit4("Colour", r, g, b, a)
    imgui.End()
end
