# Native Example

This is a small project that shows how you can use the NoitaDearImGui mod from
another mod's native C++ code. This works by linking against the `.lib` file of
the mod.

Assuming you have the mod installed in your local Noita mods directory, you can
add it to your search path and configure the build like this:

```
cmake '<path containing CMakeLists.txt>' -DCMAKE_PREFIX_PATH="C:\Program Files (x86)\Steam\steamapps\common\Noita\mods"
```

## Disclaimer

This works by dynamically linking to a DLL that exposes all Dear ImGui functions.
You should be aware of the fact that this is discouraged by Dear ImGui.. For
details see the [comment on the `IMGUI_API` macro](https://github.com/ocornut/imgui/blob/9aae45eb4a05a5a1f96be1ef37eb503a12ceb889/imgui.h#L72-L80).
