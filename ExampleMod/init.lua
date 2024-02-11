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
local imgui = load_imgui({version="1.11.0", mod="NoitaDearImGuiExampleMod"})

-- Global values, we don't want these to reset on every iteration.
local fx, fy
local clear_progress = 0
local clearing = false
local itemix = 1
local r, g, b, a = 1, 1, 1, 1

function GetEntityCount(tag, name)
    local entities = EntityGetWithTag(tag) or {}
    local cnt = 0
    for _, e in ipairs(entities) do
        if EntityGetName(e) == name then
            cnt = cnt + 1
        end
    end
    return cnt
end

local discarded = 0

local hamis_count = 0
local hamis_history = {}

local zombie_count = 0
local zombie_history = {}

local miner_count = 0
local miner_history = {}

local shotgunner_count = 0
local shotgunner_history = {}

local font_text = "The quick brown fox jumps over the lazy dog"


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

    if imgui.Begin("Player position.") then
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

    -- Collect data to show in graph
    if GameGetFrameNum() % 30 == 0 then
        hamis_count = GetEntityCount("enemy", "$animal_longleg")
        zombie_count = GetEntityCount("enemy", "$animal_zombie")
        miner_count = GetEntityCount("enemy", "$animal_miner")
        shotgunner_count = GetEntityCount("enemy", "$animal_shotgunner")

        table.insert(hamis_history, hamis_count)
        table.insert(zombie_history, zombie_count)
        table.insert(miner_history, miner_count)
        table.insert(shotgunner_history, shotgunner_count)

        while #hamis_history > 200 do
            table.remove(hamis_history, 1)
            table.remove(zombie_history, 1)
            table.remove(miner_history, 1)
            table.remove(shotgunner_history, 1)
            discarded = discarded + 1
        end
    end

    local implot = imgui.implot
    imgui.SetNextWindowSize(800, 400, imgui.Cond.Once)
    if imgui.Begin("Enemy Tracker") then
        if implot.BeginPlot("Enemies") then

            implot.SetupAxes("time", "enemy count", implot.PlotAxisFlags.AutoFit);
            implot.SetupAxisLimits(implot.Axis.Y1, 0, 20)

            implot.PlotLine("Hämis", hamis_history, 1, discarded)
            implot.PlotLine("Zombie", zombie_history, 1, discarded)
            implot.PlotLine("Miner", miner_history, 1, discarded)
            implot.PlotLine("Shotgunner", shotgunner_history, 1, discarded)
            implot.EndPlot()
        end
        imgui.End()
    end

    if imgui.Begin("Fonts") then
        fonts = {
            {"Noita Pixel", imgui.GetNoitaFont()},
            {"Noita Pixel x1.4", imgui.GetNoitaFont1_4x()},
            {"Noita Pixel x1.8", imgui.GetNoitaFont1_8x()},
            {"ImGui", imgui.GetImGuiFont()},
            {"Monospace", imgui.GetMonospaceFont()},
            {"Glyph", imgui.GetGlyphFont()},
        }

        local _
        _, font_text = imgui.InputText("Text", font_text)

        for _, f in ipairs(fonts) do
            imgui.Separator()
            imgui.Text(f[1] .. ":")

            imgui.PushFont(f[2])
            imgui.Text(font_text)
            imgui.PopFont()
        end

        imgui.End()
    end
end
