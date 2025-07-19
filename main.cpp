#include <iostream>
#include "cheat/cstrike.h"
#include "cheat/aimbot.h"
#include "cheat/customFovCirkles.h"


bool showMenu = true;











void aimbotThread() {
    while (true) {
        if (cfg::aimbot)
            aimbot::doAimbot();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

HWND WaitForCSWindow()
{
    HWND hwnd = nullptr;
    std::wcout << L"Waiting for Counter-Strike..." << std::endl;
    while ((hwnd = FindWindowW(nullptr, L"Counter-Strike 2")) == nullptr)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::wcout << L"Counter-Strike found" << std::endl;
    return hwnd;
}


void setStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.WindowRounding = 11.5f;
    style.WindowBorderSize = 0.0f;
    style.WindowMinSize = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(20.0f, 3.4f);
    style.FrameRounding = 7.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
    style.IndentSpacing = 21.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 4.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.85f, 0.80f, 1.00f, 1.00f);          // Light purple
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.50f, 0.80f, 1.00f);   // Muted purple
    colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.09f, 0.28f, 1.00f);       // Deep purple
    colors[ImGuiCol_ChildBg] = ImVec4(0.22f, 0.10f, 0.32f, 1.00f);        // Slightly lighter purple
    colors[ImGuiCol_PopupBg] = ImVec4(0.22f, 0.10f, 0.32f, 1.00f);        // Popup background
    colors[ImGuiCol_Border] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);         // Purple border
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);        // Frame background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f); // Hovered
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);  // Active
    colors[ImGuiCol_TitleBg] = ImVec4(0.22f, 0.10f, 0.32f, 1.00f);        // Title background
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);  // Active title
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.18f, 0.09f, 0.28f, 0.75f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.22f, 0.10f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.10f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.60f, 0.30f, 0.90f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);      // Bright purple
    colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.30f, 0.90f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.60f, 0.30f, 0.90f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.60f, 0.30f, 0.90f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.30f, 0.90f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.20f, 0.60f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.09f, 0.28f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.30f, 0.15f, 0.45f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.50f, 0.25f, 0.75f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.18f, 0.09f, 0.28f, 0.70f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.18f, 0.09f, 0.28f, 0.70f);
}

inline std::string GetKeyName(int vk)
{
    UINT scanCode = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);
    char keyName[128] = { 0 };
    if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName)))
        return std::string(keyName);
    switch (vk) {
    case VK_LBUTTON: return "LMB";
    case VK_RBUTTON: return "RMB";
    case VK_MBUTTON: return "MMB";
    case VK_XBUTTON1: return "X1";
    case VK_XBUTTON2: return "X2";
    default: return "Unknown";
    }
}





std::string banner = R"(github.com/KirbyZee)";

int main() {
    SetConsoleTitleA("KirbyZee external base");
    std::cout << banner << std::endl;

    WaitForCSWindow();
    Sleep(2000);

    localplayer::init();
    entities::init();
    std::thread(aimbotThread).detach();
    overlay::SetupWindow();

    if (!(overlay::CreateDeviceD3D(overlay::Window)))
        return 1;

    setStyle();

    while (!overlay::ShouldQuit)
    {
        overlay::Render();

        cstrike::matrix = memory->read<view_matrix_t>(client + Offsets::dwViewMatrix);

        // Menu open/close bind (Insert)
        if (GetAsyncKeyState(VK_INSERT) & 1)
            showMenu = !showMenu;

        if (showMenu)
        {
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);
            ImGui::Begin("KirbyZee", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            if (ImGui::BeginTabBar("CheatTabs"))
            {
                if (ImGui::BeginTabItem("Visuals"))
                {
                    ImGui::Text("ESP Options");
                    ImGui::Separator();
                    ImGui::Checkbox("Box ESP", &cfg::espOn);
                    ImGui::Checkbox("Bone ESP", &cfg::bones);
                    ImGui::Checkbox("Name ESP", &cfg::nameEsp); 
                    ImGui::Spacing();
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Aimbot"))
                {
                    ImGui::Text("Aimbot Settings");
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Aimbot", &cfg::aimbot);

                    ImGui::SameLine();
                    static bool waitingForKey = false;
                    std::string buttonLabel = "[ ";
                    buttonLabel += waitingForKey ? "Press key..." : GetKeyName(cfg::aimKey);
                    buttonLabel += " ]";
                    if (ImGui::Button(buttonLabel.c_str()))
                        waitingForKey = true;
                    if (waitingForKey)
                    {
                        for (int vk = 1; vk < 256; ++vk)
                        {
                            if (GetAsyncKeyState(vk) & 0x8000)
                            {
                                cfg::aimKey = vk;
                                waitingForKey = false;
                                break;
                            }
                        }
                    }

                    ImGui::Checkbox("Draw FOV", &cfg::drawFov);
                    ImGui::SliderFloat("FOV Size", &cfg::fovSize, 1.f, 1000.f);
                    ImGui::SliderFloat("Aim Smooth", &cfg::smoothing, 0.f, 100.f);

                    ImGui::Spacing();
                    ImGui::Text("FOV Circle Type");
                    if (ImGui::BeginCombo("##FOVType",
                        currentFOVCircleType == SIMPLE ? "Simple" :
                        currentFOVCircleType == DYNAMIC ? "Glowing" :
                        currentFOVCircleType == PULSING ? "Pulsing Wave" :
                        currentFOVCircleType == ANIMATED ? "Animated" :
                        currentFOVCircleType == DOUBLE_COLOR ? "Double Color" :
                        currentFOVCircleType == DASHED ? "Dashed" :
                        currentFOVCircleType == BREATHING_GRADIENT ? "Breathing Gradient" :
                        currentFOVCircleType == ELECTRIC_FLICKER ? "Electric Flicker" :
                        currentFOVCircleType == RAINBOW_FLOW ? "Rainbow Flow" :
                        currentFOVCircleType == PIXELATED_RETRO ? "Pixelated Retro" :
                        currentFOVCircleType == TEST ? "Test" :
                        currentFOVCircleType == DynamicFOV ? "DynamicCIRKLE" :
                        currentFOVCircleType == FilledFov ? "FilledFOV" :
                        currentFOVCircleType == WaterFov ? "WaterFov" :
                        currentFOVCircleType == wavy ? "WavyFov" :
                        currentFOVCircleType == dots ? "DotsFov" :
                        currentFOVCircleType == glowing ? "glow2Fov" :
                        currentFOVCircleType == classy ? "ClassyFov" :
                        currentFOVCircleType == star ? "StarFov" :
                        currentFOVCircleType == dual ? "DualFov" :
                        currentFOVCircleType == klar ? "Klar Fov" :
                        "Unknown"))
                    {
                        if (ImGui::Selectable("Simple", currentFOVCircleType == SIMPLE)) currentFOVCircleType = SIMPLE;
                        if (ImGui::Selectable("Glowing", currentFOVCircleType == DYNAMIC)) currentFOVCircleType = DYNAMIC;
                        if (ImGui::Selectable("Pulsing Wave", currentFOVCircleType == PULSING)) currentFOVCircleType = PULSING;
                        if (ImGui::Selectable("Animated", currentFOVCircleType == ANIMATED)) currentFOVCircleType = ANIMATED;
                        if (ImGui::Selectable("Double Color", currentFOVCircleType == DOUBLE_COLOR)) currentFOVCircleType = DOUBLE_COLOR;
                        if (ImGui::Selectable("Dashed", currentFOVCircleType == DASHED)) currentFOVCircleType = DASHED;
                        if (ImGui::Selectable("Breathing Gradient", currentFOVCircleType == BREATHING_GRADIENT)) currentFOVCircleType = BREATHING_GRADIENT;
                        if (ImGui::Selectable("Electric Flicker", currentFOVCircleType == ELECTRIC_FLICKER)) currentFOVCircleType = ELECTRIC_FLICKER;
                        if (ImGui::Selectable("Rainbow Flow", currentFOVCircleType == RAINBOW_FLOW)) currentFOVCircleType = RAINBOW_FLOW;
                        if (ImGui::Selectable("Pixelated Retro", currentFOVCircleType == PIXELATED_RETRO)) currentFOVCircleType = PIXELATED_RETRO;
                        if (ImGui::Selectable("Test", currentFOVCircleType == TEST)) currentFOVCircleType = TEST;
                        if (ImGui::Selectable("DynamicCIRKLE", currentFOVCircleType == DynamicFOV)) currentFOVCircleType = DynamicFOV;
                        if (ImGui::Selectable("Filled FOV", currentFOVCircleType == FilledFov)) currentFOVCircleType = FilledFov;
                        if (ImGui::Selectable("Water FOV", currentFOVCircleType == WaterFov)) currentFOVCircleType = WaterFov;
                        if (ImGui::Selectable("Wavy FOV", currentFOVCircleType == wavy)) currentFOVCircleType = wavy;
                        if (ImGui::Selectable("dots FOV", currentFOVCircleType == dots)) currentFOVCircleType = dots;
                        if (ImGui::Selectable("glow2 FOV", currentFOVCircleType == glowing)) currentFOVCircleType = glowing;
                        if (ImGui::Selectable("classy FOV", currentFOVCircleType == classy)) currentFOVCircleType = classy;
                        if (ImGui::Selectable("Star FOV", currentFOVCircleType == star)) currentFOVCircleType = star;
                        if (ImGui::Selectable("dual FOV", currentFOVCircleType == dual)) currentFOVCircleType = dual;
                        if (ImGui::Selectable("Klar FOV", currentFOVCircleType == klar)) currentFOVCircleType = klar;
                        ImGui::EndCombo();
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Colors & Misc"))
                {
                    ImGui::Text("Colors");
                    ImGui::Separator();
                    ImGui::ColorEdit4("Box Color", cfg::boxColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::ColorEdit4("Bone Color", cfg::boneColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                    ImGui::ColorEdit4("Fov Color", cfg::fovColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

                    ImGui::Spacing();
                    ImGui::Text("Misc");
                    ImGui::Separator();
                    ImGui::Checkbox("Team Check", &cfg::teamCheck);

                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }

        ImColor fovCol(cfg::fovColor[0], cfg::fovColor[1], cfg::fovColor[2], cfg::fovColor[3]);
        ImColor boxCol(cfg::boxColor[0], cfg::boxColor[1], cfg::boxColor[2], cfg::boxColor[3]);
        ImColor boneCol(cfg::boneColor[0], cfg::boneColor[1], cfg::boneColor[2], cfg::boneColor[3]);

        if (cfg::drawFov) {
            switch (currentFOVCircleType) {
            case SIMPLE: DrawCustomFOVCircle(SDK::screenCenter, cfg::fovSize, fovCol, 0.0f); break;
            case DYNAMIC: DrawGlowFOVCircle(SDK::screenCenter, cfg::fovSize, fovCol, ImGui::GetTime()); break;
            case PULSING: DrawPulsingWaveFOVCircle(SDK::screenCenter, cfg::fovSize, fovCol, ImGui::GetTime()); break;
            case ANIMATED: DrawAnimatedFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case DOUBLE_COLOR: DrawDoubleColorFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(0, 0, 139), ImColor(fovCol), ImGui::GetTime()); break;
            case DASHED: DrawDashedFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case ELECTRIC_FLICKER: DrawElectricFlickerFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case RAINBOW_FLOW: DrawRainbowFlowFOVCircle(SDK::screenCenter, cfg::fovSize, ImGui::GetTime()); break;
            case BREATHING_GRADIENT: DrawBreathingGradientFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(0.0f, 0.0f, 1.0f), ImColor(1.0f, 0.0f, 0.0f), ImGui::GetTime()); break;
            case PIXELATED_RETRO: DrawPixelatedRetroFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime());
            case TEST: DrawTesterFOVCIRKLE(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case DynamicFOV: DrawCircleWithTransparentCenter(SDK::screenCenter, cfg::fovSize, cfg::fovSize * 0.2f, ImColor(fovCol)); break;
            case FilledFov: DrawTransparentFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol)); break;
            case WaterFov: DrawWaterWaveFOVCircle(SDK::screenCenter, cfg::fovSize); break;
            case wavy: DrawWavyFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case dots: DrawWavyFOVCircleDots(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case glowing: DrawSmoothGlowFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(fovCol), ImGui::GetTime()); break;
            case classy: DrawClassicFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(0, 255, 255, 255)); break;
            case star: DrawStarWaveGradientFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(1.0f, 0.0f, 0.5f), ImColor(0.0f, 0.5f, 1.0f), ImGui::GetTime()); break;
            case dual: DrawAnimatedDualColorFOVCircle(SDK::screenCenter, cfg::fovSize, ImColor(1.0f, 0.2f, 0.2f), ImColor(0.2f, 0.2f, 1.0f), ImGui::GetTime()); break;
            case klar: DrawMovingFOVCircle(ImGui::GetBackgroundDrawList(), SDK::screenCenter, cfg::fovSize); break;
            }
        }

        for (entities::PLAYER& actor : entities::entities) {
            if (cfg::espOn)
                cstrike::drawBox(actor, boxCol);
            if (cfg::bones)
                cstrike::drawBones(actor, boneCol);
            cstrike::drawSnapline(actor, ImColor(255, 255, 255));
        }

        overlay::EndRender();
    }

    overlay::CloseOverlay();
}
