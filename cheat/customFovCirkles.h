#pragma once
#include "../ext/imgui/imgui.h"
// customFOVCircle.h
#pragma once
enum FOVCircleType {
    SIMPLE,
    DYNAMIC,
    PULSING,
    ANIMATED,
    DOUBLE_COLOR,
    DASHED,
    BREATHING_GRADIENT,
    ELECTRIC_FLICKER,
    RAINBOW_FLOW,
    PIXELATED_RETRO, // Neue Option hinzugefügt!
    TEST,
    DynamicFOV,
    FilledFov,
 WaterFov,
 wavy,
 dots,
 glowing,
 classy,
 star,
 dual,
 klar,
};







FOVCircleType currentFOVCircleType = DASHED;  // Standardwert


void DrawGlowFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawCustomFOVCircle(const ImVec2& center, float radius, ImU32 color, float time);
void DrawPulsingWaveFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawAnimatedFOVCircle(const ImVec2& center, float radius, ImColor userColor, float time);
void DrawDoubleColorFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time);
void DrawDashedFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawBreathingGradientFOVCircle(const ImVec2& center, float baseRadius, ImColor colorStart, ImColor colorEnd, float time);
void DrawElectricFlickerFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawRainbowFlowFOVCircle(const ImVec2& center, float radius, float time);
void DrawPixelatedRetroFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawTesterFOVCIRKLE(const ImVec2& center, float radius, ImColor fovCol, float time);
void DrawCircleWithTransparentCenter(const ImVec2& center, float outerRadius, float innerRadius, ImColor outerColor);
void DrawTransparentFOVCircle(const ImVec2& center, float radius, ImColor circleColor);
void DrawWaterWaveFOVCircle(const ImVec2& center, float baseRadius);
void DrawWavyFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawWavyFOVCircleDots(const ImVec2& center, float radius, ImColor color, float time);
void DrawSmoothGlowFOVCircle(const ImVec2& center, float radius, ImColor color, float time);
void DrawClassicFOVCircle(ImVec2 center, float radius, ImColor color);
void DrawStarWaveGradientFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time);
void DrawAnimatedDualColorFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time);
void DrawMovingFOVCircle(ImDrawList* drawList, ImVec2 center, float radius);