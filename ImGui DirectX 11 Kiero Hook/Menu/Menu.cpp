#include<Menu/Menu.h>




ImFont* arialFont;

void SetupImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
    ImVec4 tabColor = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_Tab] = tabColor;
    style.Colors[ImGuiCol_TabHovered] = ImVec4(
        tabColor.x, tabColor.y, tabColor.z, 0.30f
    );
    style.Colors[ImGuiCol_TabActive] = ImVec4(
        tabColor.x, tabColor.y, tabColor.z, 0.90f
    );
    style.Colors[ImGuiCol_TabUnfocused] = tabColor;
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(
        tabColor.x, tabColor.y, tabColor.z, 0.50f
    );
}
void SeparatorText(const char* label)
{
    ImGui::Spacing();
    ImGui::Text(label);
    ImGui::Separator();
    ImGui::Spacing();
}
bool waitingForKey = false;
std::string GetKeyName(int vk)
{
    if (vk == 0)
        return "None";

    switch (vk)
    {
    case VK_LBUTTON: return "Mouse1";
    case VK_RBUTTON: return "Mouse2";
    case VK_MBUTTON: return "Mouse3";
    case VK_XBUTTON1: return "Mouse4";
    case VK_XBUTTON2: return "Mouse5";
    }

    if (vk >= 'A' && vk <= 'Z')
        return std::string(1, char(vk));

    if (vk >= VK_F1 && vk <= VK_F24)
        return "F" + std::to_string(vk - VK_F1 + 1);

    if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9)
        return "Num" + std::to_string(vk - VK_NUMPAD0);

    if (vk == VK_SHIFT || vk == VK_LSHIFT) return "LShift";
    if (vk == VK_RSHIFT) return "RShift";

    if (vk == VK_CONTROL || vk == VK_LCONTROL) return "LCtrl";
    if (vk == VK_RCONTROL) return "RCtrl";

    if (vk == VK_MENU || vk == VK_LMENU) return "LAlt";
    if (vk == VK_RMENU) return "RAlt";

    if (vk == VK_SPACE) return "Space";
    if (vk == VK_TAB) return "Tab";
    if (vk == VK_ESCAPE) return "Escape";
    if (vk == VK_RETURN) return "Enter";
    if (vk == VK_BACK) return "Backspace";
    if (vk == VK_CAPITAL) return "CapsLock";

    char name[64] = {};
    UINT scan = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);

    if (scan)
    {
        if (GetKeyNameTextA(scan << 16, name, sizeof(name)))
            return name;
    }

    return "VK_" + std::to_string(vk);
}




void RenderMenu()
{
    ImGui::SetNextWindowSize(ImVec2(200, 350));
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize);

    if (ImGui::BeginTabBar("MainTabs", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton))
    {
        
        if (ImGui::BeginTabItem("ESP"))
        {

            ImGui::Spacing();
            SeparatorText("ESP Settings");
          
            ImGui::Checkbox("Box", &Setting::ESP::BOX);
            ImGui::Checkbox("TeamCheck", &Setting::ESP::TeamCheck);
            ImGui::Checkbox("Health Bar", &Setting::ESP::HealthBar);
            ImGui::Checkbox("Skeleton", &Setting::ESP::Skeleton);
            ImGui::Checkbox("Distance", &Setting::ESP::Distance);
            ImGui::Checkbox("SnapLine", &Setting::ESP::SnapLine);
          
      

            ImGui::SameLine();
            ImGui::ColorEdit4("##SnapColor", (float*)&Setting::ESP::SnapLineColor,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_DisplayRGB);

            ImGui::Checkbox("Visible Check", &Setting::ESP::VisibleCheck);

            ImGui::SameLine();
            ImGui::ColorEdit4("##VisibleColor", (float*)&Setting::ESP::VisibleColor,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_DisplayRGB);
            ImGui::Separator();

            ImGui::Text("Skeleton Thickness");
            ImGui::SliderFloat("##SkThick", &Setting::ESP::SkeletonThickness, 0.1f, 5.0f);

            ImGui::Text("Skeleton Color:");
            ImGui::SameLine();
            ImGui::ColorEdit4("##SkColor", (float*)&Setting::ESP::SkeletonColor,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_DisplayRGB);

            ImGui::Separator();

            ImGui::Text("Box Thickness");
            ImGui::SliderFloat("##BoxThick", &Setting::ESP::BoxThickness, 0.1f, 5.0f);

            ImGui::Text("Box Color:");
            ImGui::SameLine();
            ImGui::ColorEdit4("##BoxColor", (float*)&Setting::ESP::BoxColor,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_DisplayRGB);


            ImGui::EndTabItem();
        }

        // ------------------ AIMBOT TAB ------------------
        if (ImGui::BeginTabItem("Aimbot"))
        {
           
            ImGui::Spacing();
            SeparatorText("Aimbot Settings");

            ImGui::Checkbox("Aimbot", &Setting::Aimbot::Aimbot);

            if (Setting::Aimbot::Aimbot)
            {
                const char* boneNames[] = { "Head", "Neck", "Pelvis" };
                int boneValues[] = { 6,     5,      0 };

                int currentIndex = 6;
                for (int i = 0; i < 3; i++)
                {
                    if (Setting::Aimbot::AimbotIn == boneValues[i])
                    {
                        currentIndex = i;
                        break;
                    }
                }

                ImGui::Text("Aim Bone:");
                if (ImGui::Combo("##AimBone", &currentIndex, boneNames, 3))
                    Setting::Aimbot::AimbotIn = boneValues[currentIndex];

                ImGui::Text("Aimbot FOV");
                ImGui::SliderFloat("##FOV", &Setting::Aimbot::FOV, 0.1f, 180.0f);
                ImGui::Spacing();

                // -------- Keybind ----------
                ImGui::Text("Aimbot Key:");
                ImGui::SameLine();

                std::string btn = "[" + (waitingForKey ? std::string("Press key...") : GetKeyName(Setting::Aimbot::VKKey)) + "]";
                if (ImGui::Button(btn.c_str(), ImVec2(120, 25)))
                {
                    waitingForKey = true;
                }

                if (waitingForKey)
                {
                    for (int vk = 1; vk <= 255; vk++)
                    {
                        if (GetAsyncKeyState(vk) & 0x8000)
                        {
                            Setting::Aimbot::VKKey = vk;
                            waitingForKey = false;
                            break;
                        }
                    }
                }
            }
            ImGui::Checkbox("Triggerbot", &Setting::Aimbot::TriggerBot);
            if (Setting::Aimbot::TriggerBot)
            {
                ImGui::Text("Trigger FOV");
                ImGui::SameLine();
                ImGui::SliderFloat("##FOVTriger", &Setting::Aimbot::TriggerFov, 5.0f, 10.0f);
            }
            ImGui::EndTabItem();
        }

       
        if (ImGui::BeginTabItem("Memory"))
        {
            ImGui::Spacing();
            SeparatorText("Memory Settings");

            ImGui::Checkbox("Bunny Hop [SPACE]", &Setting::Memory::JumpEvent);

                const char* modes[] = { "Disable Glow", "Glow Color", "Glow Rainbow"};
                ImGui::Combo("##GlowOption", &Setting::ESP::GlowMode, modes, IM_ARRAYSIZE(modes));

                if (Setting::ESP::GlowMode == 0)
                {
                    Setting::Memory::Glow = false;
                    Setting::ESP::RainbowGlow = false;
                }
                else if(Setting::ESP::GlowMode == 1)
                {
                    Setting::Memory::Glow = true;
                    Setting::ESP::RainbowGlow = false;
                    ImGui::SameLine();
                    ImGui::ColorEdit4("Glow Color", Setting::ESP::GlowColor,
                        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB);
                }
                else
                {
                    Setting::Memory::Glow = true;
                    Setting::ESP::RainbowGlow = true;
                }
            





            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

