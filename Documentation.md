#### bool BeginTabBar(string str_id)

#### bool BeginTabBar(string, ImGuiTabBarFlags)

#### void EndTabBar()

#### [bool, bool] BeginTabItem(string label, bool, ImGuiTabItemFlags)

#### void EndTabItem()

#### bool TabItemButton(string label)

#### bool TabItemButton(string, ImGuiTabItemFlags)

#### void SetTabItemClosed(string)

#### void Separator()

#### void SameLine()

#### void SameLine(float offset_from_start_x)

#### void SameLine(float, float)

#### void NewLine()

#### void Spacing()

#### void Dummy(float size_x, float size_y)

#### void Indent()

#### void Indent(float)

#### void Unindent()

#### void Unindent(float)

#### void BeginGroup()

#### void EndGroup()

#### [float, float] GetCursorPos()

#### float GetCursorPosX()

#### float GetCursorPosY()

#### void SetCursorPos(float local_pos_x, float local_pos_y)

#### void SetCursorPosX(float)

#### void SetCursorPosY(float)

#### [float, float] GetCursorStartPos()

#### [float, float] GetCursorScreenPos()

#### void SetCursorScreenPos(float size_x, float size_y)

#### void AlignTextToFramePadding()

#### float GetTextLineHeight()

#### float GetTextLineHeightWithSpacing()

#### float GetFrameHeight()

#### float GetFrameHeightWithSpacing()

#### void PushID(string)

#### void PushID(int)

#### void PopID()

#### unsigned int GetID(string)

#### bool BeginPopup(string str_id)

#### bool BeginPopup(string, ImGuiWindowFlags)

#### bool BeginPopupModal(string str_id)

#### bool BeginPopupModal(string str_id, bool open)

#### bool BeginPopupModal(string str_id, bool open, ImGuiWindowFlags flags)

#### void EndPopup()

#### void OpenPopup(string str_id)

#### void OpenPopup(string, ImGuiPopupFlags)

#### void OpenPopup(ImGuiID id)

#### void OpenPopup(ImGuiID, ImGuiPopupFlags)

#### void OpenPopupOnItemClick()

#### void OpenPopupOnItemClick(string str_id)

#### void OpenPopupOnItemClick(string, ImGuiPopupFlags)

#### void CloseCurrentPopup()

#### bool BeginPopupContextItem()

#### bool BeginPopupContextItem(string str_id)

#### bool BeginPopupContextItem(string, ImGuiPopupFlags)

#### bool BeginPopupContextWindow()

#### bool BeginPopupContextWindow(string str_id)

#### bool BeginPopupContextWindow(string, ImGuiPopupFlags)

#### bool BeginPopupContextVoid()

#### bool BeginPopupContextVoid(string str_id)

#### bool BeginPopupContextVoid(string, ImGuiPopupFlags)

#### bool IsPopupOpen(string str_id)

#### bool IsPopupOpen(string, ImGuiPopupFlags)

#### ImGuiIO GetIO()

#### bool BeginTable(string str_id, int column)

#### bool BeginTable(string str_id, int column, ImGuiTableFlags flags)

#### bool BeginTable(string str_id, int column, ImGuiTableFlags flags, float outer_size_x, float outer_size_y)

#### bool BeginTable(string str_id, int column, ImGuiTableFlags flags, float outer_size_x, float outer_size_y, float inner_size)

#### void EndTable()

#### void TableNextRow()

#### void TableNextRow(ImGuiTableRowFlags row_flags)

#### void TableNextRow(ImGuiTableRowFlags, float)

#### bool TableNextColumn()

#### bool TableSetColumnIndex(int)

#### void TableSetupColumn(string label)

#### void TableSetupColumn(string label, ImGuiTableColumnFlags flags)

#### void TableSetupColumn(string label, ImGuiTableColumnFlags flags, float init_width_or_weight)

#### void TableSetupColumn(string, ImGuiTableColumnFlags, float, ImGuiID)

#### void TableSetupScrollFreeze(int, int)

#### void TableHeadersRow()

#### void TableHeader(string label)

#### int TableGetColumnCount()

#### int TableGetColumnIndex()

#### int TableGetRowIndex()

#### string TableGetColumnName()

#### string TableGetColumnName(int)

#### ImGuiTableColumnFlags TableGetColumnFlags()

#### ImGuiTableColumnFlags TableGetColumnFlags(int)

#### void TableSetColumnEnabled(int, bool)

#### void TableSetBgColor(ImGuiTableBgTarget target, float r, float g, float b, float a)

#### void TableSetBgColor(ImGuiTableBgTarget target, float r, float g, float b, float a, int column_n)

#### void TextUnformatted(ref string_view text)

#### void Text(ref string_view text)

#### void TextColored(float colr, float colg, float colb, float cola, ref string_view text)

#### void TextDisabled(ref string_view text)

#### void TextWrapped(ref string_view text)

#### void LabelText(ref string_view label, ref string_view text)

#### void BulletText(ref string_view text)

#### [bool, float, float, float] ColorEdit3(string label, float r, float g, float b)

#### [bool, float, float, float] ColorEdit3(string label, float r, float g, float b, ImGuiColorEditFlags flags)

#### [bool, float, float, float, float] ColorEdit4(string label, float r, float g, float b, float a)

#### [bool, float, float, float, float] ColorEdit4(string label, float r, float g, float b, float a, ImGuiColorEditFlags flags)

#### [bool, float, float, float] ColorPicker3(string label, float r, float g, float b)

#### [bool, float, float, float] ColorPicker3(string label, float r, float g, float b, ImGuiColorEditFlags flags)

#### [bool, float, float, float, float] ColorPicker4(string label, float r, float g, float b, float a)

#### [bool, float, float, float, float] ColorPicker4(string label, float r, float g, float b, float a, ImGuiColorEditFlags flags)

#### bool ColorButton(string desc_id, float r, float g, float b, float a)

#### bool ColorButton(string desc_id, float r, float g, float b, float a, ImGuiColorEditFlags flags)

#### bool ColorButton(string desc_id, float r, float g, float b, float a, ImGuiColorEditFlags flags, float size_x, float size_y)

#### [bool, float] DragFloat(string label, float v)

#### [bool, float] DragFloat(string label, float v, float v_speed)

#### [bool, float] DragFloat(string label, float v, float v_speed, float v_min)

#### [bool, float] DragFloat(string label, float v, float v_speed, float v_min, float v_max)

#### [bool, float] DragFloat(string label, float v, float v_speed, float v_min, float v_max, string format)

#### [bool, float] DragFloat(string label, float v, float v_speed, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float] DragFloat2(string label, float v1, float v2)

#### [bool, float, float] DragFloat2(string label, float v1, float v2, float v_speed)

#### [bool, float, float] DragFloat2(string label, float v1, float v2, float v_speed, float v_min)

#### [bool, float, float] DragFloat2(string label, float v1, float v2, float v_speed, float v_min, float v_max)

#### [bool, float, float] DragFloat2(string label, float v1, float v2, float v_speed, float v_min, float v_max, string format)

#### [bool, float, float] DragFloat2(string label, float v1, float v2, float v_speed, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3, float v_speed)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3, float v_speed, float v_min)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3, float v_speed, float v_min, float v_max)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3, float v_speed, float v_min, float v_max, string format)

#### [bool, float, float, float] DragFloat3(string label, float v1, float v2, float v3, float v_speed, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4, float v_speed)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4, float v_speed, float v_min)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max, string format)

#### [bool, float, float, float, float] DragFloat4(string label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed, float v_min)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, string format)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, string format, string format_max)

#### [bool, float, float] DragFloatRange2(string label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, string format, string format_max, ImGuiSliderFlags flags)

#### [bool, int] DragInt(string label, int v)

#### [bool, int] DragInt(string label, int v, float v_speed)

#### [bool, int] DragInt(string label, int v, float v_speed, int v_min)

#### [bool, int] DragInt(string label, int v, float v_speed, int v_min, int v_max)

#### [bool, int] DragInt(string label, int v, float v_speed, int v_min, int v_max, string format)

#### [bool, int] DragInt(string label, int v, float v_speed, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int] DragInt2(string label, int v1, int v2)

#### [bool, int, int] DragInt2(string label, int v1, int v2, float v_speed)

#### [bool, int, int] DragInt2(string label, int v1, int v2, float v_speed, int v_min)

#### [bool, int, int] DragInt2(string label, int v1, int v2, float v_speed, int v_min, int v_max)

#### [bool, int, int] DragInt2(string label, int v1, int v2, float v_speed, int v_min, int v_max, string format)

#### [bool, int, int] DragInt2(string label, int v1, int v2, float v_speed, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3, float v_speed)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3, float v_speed, int v_min)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3, float v_speed, int v_min, int v_max)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3, float v_speed, int v_min, int v_max, string format)

#### [bool, int, int, int] DragInt3(string label, int v1, int v2, int v3, float v_speed, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4, float v_speed)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4, float v_speed, int v_min)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max, string format)

#### [bool, int, int, int, int] DragInt4(string label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed, int v_min)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, string format)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, string format, string format_max)

#### [bool, int, int] DragIntRange2(string label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, string format, string format_max, ImGuiSliderFlags flags)

#### [bool, bool] Begin(string name, bool, ImGuiWindowFlags)

Unlike standard ImGui, you must only call [End](#void-end) if the window is visible (indicated by the first return value).

So this is wrong:

```lua
if imgui.Begin("Chat") then
    -- ...
end
imgui.End() -- BAD BAD shouldn't run `End` if the window isn't visible.
```

This is correct:

```lua
if imgui.Begin("Chat") then
    -- ...
    imgui.End()
end
```

#### void End()

Indicates the End of a window started by [Begin](#bool-bool-beginstring-name-bool-imguiwindowflags).

#### bool BeginChild(string str_id)

#### bool BeginChild(string str_id, float size_x, float size_y)

#### bool BeginChild(string str_id, float size_x, float size_y, bool border)

#### bool BeginChild(string str_id, float size_x, float size_y, bool border, ImGuiWindowFlags flags)

#### void EndChild()

#### bool IsWindowAppearing()

#### bool IsWindowCollapsed()

#### bool IsWindowFocused()

#### bool IsWindowFocused(ImGuiFocusedFlags)

#### bool IsWindowHovered()

#### bool IsWindowHovered(ImGuiHoveredFlags)

#### [float, float] GetWindowPos()

#### [float, float] GetWindowSize()

#### float GetWindowWidth()

#### float GetWindowHeight()

#### void SetNextWindowPos(float pos_x, float pos_y)

#### void SetNextWindowPos(float pos_x, float pos_y, ImGuiCond cond)

#### void SetNextWindowPos(float pos_x, float pos_y, ImGuiCond cond, float pivot_x, float pivot_y)

#### void SetNextWindowSize(float size_x, float size_y)

#### void SetNextWindowSize(float size_x, float size_y, ImGuiCond cond)

#### void SetNextWindowSizeConstraints(float min_x, float min_y, float max_x, float max_y)

#### void SetNextWindowContentSize(float size_x, float size_y)

#### void SetNextWindowCollapsed(bool collapsed)

#### void SetNextWindowCollapsed(bool, ImGuiCond)

#### void SetNextWindowFocus()

#### void SetNextWindowBgAlpha(float)

#### void SetNextWindowViewport(ImGuiID)

#### void SetWindowPos(float pos_x, float pos_y)

#### void SetWindowPos(float pos_x, float pos_y, ImGuiCond cond)

#### void SetWindowPos(string name, float pos_x, float pos_y)

#### void SetWindowPos(string name, float pos_x, float pos_y, ImGuiCond cond)

#### void SetWindowSize(float pos_x, float pos_y)

#### void SetWindowSize(float pos_x, float pos_y, ImGuiCond cond)

#### void SetWindowSize(string name, float pos_x, float pos_y)

#### void SetWindowSize(string name, float pos_x, float pos_y, ImGuiCond cond)

#### void SetWindowCollapsed(bool collapsed)

#### void SetWindowCollapsed(bool collapsed, ImGuiCond cond)

#### void SetWindowCollapsed(string name, bool collapsed)

#### void SetWindowCollapsed(string name, bool collapsed, ImGuiCond cond)

#### void SetWindowFocus(string)

#### void SetWindowFocus(std::nullptr_t)

#### [float, float] GetContentRegionAvail()

#### [float, float] GetContentRegionMax()

#### [float, float] GetWindowContentRegionMin()

#### [float, float] GetWindowContentRegionMax()

#### float GetScrollX()

#### float GetScrollY()

#### void SetScrollX(float)

#### void SetScrollY(float)

#### float GetScrollMaxX()

#### float GetScrollMaxY()

#### void SetScrollHereX(float)

#### void SetScrollHereY(float)

#### void SetScrollFromPosX(float local_x)

#### void SetScrollFromPosX(float, float)

#### void SetScrollFromPosY(float local_y)

#### void SetScrollFromPosY(float, float)

#### void SetNextWindowScroll(float x, float y)

#### bool Button(string label)

#### bool Button(string label, float width, float height)

#### bool SmallButton(string)

#### bool InvisibleButton(string str_id, float size_x, float size_y)

#### bool InvisibleButton(string str_id, float size_x, float size_y, ImGuiButtonFlags flags)

#### bool ArrowButton(string, ImGuiDir)

#### [bool, bool] Checkbox(string label, bool value)

#### [bool, unsigned] CheckboxFlags(string label, unsigned flags, unsigned flags_value)

#### bool RadioButton(string, bool)

#### void ProgressBar(float fraction)

#### void ProgressBar(float fraction, float size_x)

#### void ProgressBar(float fraction, float size_x, float size_y)

#### void ProgressBar(float fraction, float size_x, float size_y, string overlay)

#### void Bullet()

#### bool IsItemHovered()

#### bool IsItemHovered(ImGuiHoveredFlags)

#### bool IsItemActive()

#### bool IsItemFocused()

#### bool IsItemClicked()

#### bool IsItemClicked(ImGuiMouseButton)

#### bool IsItemVisible()

#### bool IsItemEdited()

#### bool IsItemActivated()

#### bool IsItemDeactivated()

#### bool IsItemDeactivatedAfterEdit()

#### bool IsItemToggledOpen()

#### bool IsAnyItemHovered()

#### bool IsAnyItemActive()

#### bool IsAnyItemFocused()

#### ImGuiID GetItemID()

#### [float, float] GetItemRectMin()

#### [float, float] GetItemRectMax()

#### [float, float] GetItemRectSize()

#### void SetItemAllowOverlap()

#### bool IsKeyDown(ImGuiKey)

#### bool IsKeyPressed(ImGuiKey key)

#### bool IsKeyPressed(ImGuiKey, bool)

#### bool IsKeyReleased(ImGuiKey)

#### int GetKeyPressedAmount(ImGuiKey, float, float)

#### string GetKeyName(ImGuiKey)

#### void SetNextFrameWantCaptureKeyboard(bool)

#### void PushAllowKeyboardFocus(bool)

#### void PopAllowKeyboardFocus()

#### void SetKeyboardFocusHere()

#### void SetKeyboardFocusHere(int)

#### void BeginTooltip()

#### void EndTooltip()

#### void SetTooltip(string text)

#### void BeginDisabled()

#### void BeginDisabled(bool)

#### void EndDisabled()

#### bool BeginDragDropSource()

#### bool BeginDragDropSource(ImGuiDragDropFlags)

#### bool SetDragDropPayload(string type, object payload)

Set the drag and drop payload which can be retrieved using one of the Accept/Get -DragAndDropPayload functions.

Booleans, strings, and doubles can be dragged and dropped between Lua contexts
(e.g. to a different LuaComponent or whole different mod.)
Other values such as tables or userdata can only be retrieved by the same mod.

#### bool SetDragDropPayload(string, object, ImGuiCond)

#### void EndDragDropSource()

#### object AcceptDragDropPayload(string type)

#### object AcceptDragDropPayload(string type, ImGuiDragDropFlags)

#### bool BeginDragDropTarget()

#### void EndDragDropTarget()

#### object GetDragDropPayload()

#### void PushStyleColor(ImGuiCol idx, float r, float g, float b)

#### void PushStyleColor(ImGuiCol idx, float r, float g, float b, float a)

#### void PopStyleColor()

#### void PopStyleColor(int)

#### void PushStyleVar(ImGuiStyleVar, float)

#### void PushStyleVar(ImGuiStyleVar idx, float valx, float valy)

#### void PopStyleVar()

#### void PopStyleVar(int)

#### void PushAllowKeyboardFocus(bool)

#### void PopAllowKeyboardFocus()

#### void PushButtonRepeat(bool)

#### void PopButtonRepeat()

#### void PushItemWidth(float)

#### void PopItemWidth()

#### void SetNextItemWidth(float)

#### float CalcItemWidth()

#### void PushTextWrapPos()

#### void PushTextWrapPos(float)

#### void PopTextWrapPos()

#### [bool, ref string] InputText(string label, ref string str)

#### [bool, ref string] InputText(string label, ref string str, ImGuiInputTextFlags flags)

#### [bool, ref string] InputTextMultiline(string label, ref string str)

#### [bool, ref string] InputTextMultiline(string label, ref string str, float size_x, float size_y)

#### [bool, ref string] InputTextMultiline(string label, ref string str, float size_x, float size_y, ImGuiInputTextFlags flags)

#### [bool, ref string] InputTextWithHint(string label, string hint, ref string str)

#### [bool, ref string] InputTextWithHint(string label, string hint, ref string str, ImGuiInputTextFlags flags)

#### [bool, float] InputFloat(string label, float v)

#### [bool, float] InputFloat(string label, float v, float step)

#### [bool, float] InputFloat(string label, float v, float step, float step_fast)

#### [bool, float] InputFloat(string label, float v, float step, float step_fast, string format)

#### [bool, float] InputFloat(string label, float v, float step, float step_fast, string format, ImGuiInputTextFlags flags)

#### [bool, float, float] InputFloat2(string label, float v1, float v2)

#### [bool, float, float] InputFloat2(string label, float v1, float v2, string format)

#### [bool, float, float] InputFloat2(string label, float v1, float v2, string format, ImGuiInputTextFlags flags)

#### [bool, float, float, float] InputFloat3(string label, float v1, float v2, float v3)

#### [bool, float, float, float] InputFloat3(string label, float v1, float v2, float v3, string format)

#### [bool, float, float, float] InputFloat3(string label, float v1, float v2, float v3, string format, ImGuiInputTextFlags flags)

#### [bool, float, float, float, float] InputFloat4(string label, float v1, float v2, float v3, float v4)

#### [bool, float, float, float, float] InputFloat4(string label, float v1, float v2, float v3, float v4, string format)

#### [bool, float, float, float, float] InputFloat4(string label, float v1, float v2, float v3, float v4, string format, ImGuiInputTextFlags flags)

#### [bool, int] InputInt(string label, int v)

#### [bool, int] InputInt(string label, int v, int step)

#### [bool, int] InputInt(string label, int v, int step, int step_fast)

#### [bool, int] InputInt(string label, int v, int step, int step_fast, ImGuiInputTextFlags flags)

#### [bool, int, int] InputInt2(string label, int v1, int v2)

#### [bool, int, int] InputInt2(string label, int v1, int v2, ImGuiInputTextFlags flags)

#### [bool, int, int, int] InputInt3(string label, int v1, int v2, int v3)

#### [bool, int, int, int] InputInt3(string label, int v1, int v2, int v3, ImGuiInputTextFlags flags)

#### [bool, int, int, int, int] InputInt4(string label, int v1, int v2, int v3, int v4)

#### [bool, int, int, int, int] InputInt4(string label, int v1, int v2, int v3, int v4, ImGuiInputTextFlags flags)

#### [bool, double] InputDouble(string label, double v)

#### [bool, double] InputDouble(string label, double v, double step)

#### [bool, double] InputDouble(string label, double v, double step, double step_fast)

#### [bool, double] InputDouble(string label, double v, double step, double step_fast, string format)

#### [bool, double] InputDouble(string label, double v, double step, double step_fast, string format, ImGuiInputTextFlags flags)

#### bool BeginCombo(string label, string preview_value)

#### bool BeginCombo(string, string, ImGuiComboFlags)

#### void EndCombo()

#### [bool, int] Combo(string label, int current_item, table items)

#### [bool, int] Combo(string label, int current_item, table items, int popup_max_height_in_items)

#### bool Selectable(string label)

#### bool Selectable(string label, bool selected)

#### bool Selectable(string label, bool selected, ImGuiSelectableFlags flags)

#### bool Selectable(string label, bool selected, ImGuiSelectableFlags flags, float size_x, float size_y)

#### ImGuiID GetMainViewportID()

#### [float, float] GetMainViewportWorkPos()

#### [float, float] GetMainViewportPos()

#### [float, float] GetMainViewportSize()

#### [float, float] GetMainViewportWorkSize()

#### string GetClipboardText()

#### void SetClipboardText(string)

#### bool BeginMenuBar()

#### void EndMenuBar()

#### bool BeginMainMenuBar()

#### void EndMainMenuBar()

#### bool BeginMenu(string label)

#### bool BeginMenu(string, bool)

#### void EndMenu()

#### bool MenuItem(string label)

#### bool MenuItem(string label, string shortcut)

#### [bool, bool] MenuItem(string label, string shortcut, bool selected)

#### [bool, bool] MenuItem(string label, string shortcut, bool selected, bool enabled)

#### ImGuiStyle GetStyle()

#### [bool, float] SliderFloat(string label, float v, float v_min, float v_max)

#### [bool, float] SliderFloat(string label, float v, float v_min, float v_max, string format)

#### [bool, float] SliderFloat(string label, float v, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float] SliderFloat2(string label, float v1, float v2, float v_min, float v_max)

#### [bool, float, float] SliderFloat2(string label, float v1, float v2, float v_min, float v_max, string format)

#### [bool, float, float] SliderFloat2(string label, float v1, float v2, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float, float] SliderFloat3(string label, float v1, float v2, float v3, float v_min, float v_max)

#### [bool, float, float, float] SliderFloat3(string label, float v1, float v2, float v3, float v_min, float v_max, string format)

#### [bool, float, float, float] SliderFloat3(string label, float v1, float v2, float v3, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, float, float, float, float] SliderFloat4(string label, float v1, float v2, float v3, float v4, float v_min, float v_max)

#### [bool, float, float, float, float] SliderFloat4(string label, float v1, float v2, float v3, float v4, float v_min, float v_max, string format)

#### [bool, float, float, float, float] SliderFloat4(string label, float v1, float v2, float v3, float v4, float v_min, float v_max, string format, ImGuiSliderFlags flags)

#### [bool, int] SliderInt(string label, int v, int v_min, int v_max)

#### [bool, int] SliderInt(string label, int v, int v_min, int v_max, string format)

#### [bool, int] SliderInt(string label, int v, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int] SliderInt2(string label, int v1, int v2, int v_min, int v_max)

#### [bool, int, int] SliderInt2(string label, int v1, int v2, int v_min, int v_max, string format)

#### [bool, int, int] SliderInt2(string label, int v1, int v2, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int, int] SliderInt3(string label, int v1, int v2, int v3, int v_min, int v_max)

#### [bool, int, int, int] SliderInt3(string label, int v1, int v2, int v3, int v_min, int v_max, string format)

#### [bool, int, int, int] SliderInt3(string label, int v1, int v2, int v3, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### [bool, int, int, int, int] SliderInt4(string label, int v1, int v2, int v3, int v4, int v_min, int v_max)

#### [bool, int, int, int, int] SliderInt4(string label, int v1, int v2, int v3, int v4, int v_min, int v_max, string format)

#### [bool, int, int, int, int] SliderInt4(string label, int v1, int v2, int v3, int v4, int v_min, int v_max, string format, ImGuiSliderFlags flags)

#### bool TreeNode(string label)

#### bool TreeNodeEx(string, ImGuiTreeNodeFlags)

#### bool TreeNode(string label, ImGuiTreeNodeFlags flags, string text)

#### void TreePush(string)

#### void TreePop()

#### float GetTreeNodeToLabelSpacing()

#### bool CollapsingHeader(string label)

#### bool CollapsingHeader(string label, ImGuiTreeNodeFlags flags)

#### bool CollapsingHeader(string label, bool visible)

#### bool CollapsingHeader(string label, bool visible, ImGuiTreeNodeFlags flags)

#### void SetNextItemOpen(bool is_open)

#### void SetNextItemOpen(bool, ImGuiCond)

#### ImFont GetFontIndex(std::size_t font_index)

#### ImFont GetNoitaFont()

#### ImFont GetNoitaFont1_4x()

#### ImFont GetNoitaFont1_8x()

#### ImFont GetImGuiFont()

#### void PushFont(ImFont)

#### void PopFont()

#### float GetFontSize()

#### bool IsMouseDown(ImGuiMouseButton)

#### bool IsMouseClicked(ImGuiMouseButton button)

#### bool IsMouseClicked(ImGuiMouseButton, bool)

#### bool IsMouseReleased(ImGuiMouseButton)

#### bool IsMouseDoubleClicked(ImGuiMouseButton)

#### int GetMouseClickedCount(ImGuiMouseButton)

#### bool IsMousePosValid()

#### bool IsMousePosValid(float posx, float posy)

#### [float, float] GetMousePos()

#### [float, float] GetMousePosOnOpeningCurrentPopup()

#### bool IsMouseDragging(ImGuiMouseButton button)

#### bool IsMouseDragging(ImGuiMouseButton, float)

#### [float, float] GetMouseDragDelta()

#### [float, float] GetMouseDragDelta(ImGuiMouseButton button)

#### [float, float] GetMouseDragDelta(ImGuiMouseButton button, float lock_threshold)

#### void ResetMouseDragDelta()

#### void ResetMouseDragDelta(ImGuiMouseButton)

#### ImGuiMouseCursor GetMouseCursor()

#### void SetMouseCursor(ImGuiMouseCursor)

#### void SetNextFrameWantCaptureMouse(bool)
