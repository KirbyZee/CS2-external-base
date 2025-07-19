#ifndef DRAWING_H
#define DRAWING_H
#include "overlay.h"
#include "math.h"



template <typename T>
T customClamp(T value, T min, T max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    return value;
}

class Drawing {
public:
    // Draw a box (rectangle)
    void drawBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float thickness = 1.0f, float rounding = 0.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddRect(
            topLeft,                              // Top-left corner
            bottomRight,                          // Bottom-right corner
            color,                                // Color (ImColor automatically converts to ImU32)
            rounding,                             // Rounding radius
            0,                                    // Flags (e.g., ImDrawFlags_RoundCornersAll)
            thickness                             // Line thickness
        );
    }

    void drawFilledBox(const ImVec2& topLeft, const ImVec2& bottomRight, const ImColor& color, float thickness = 1.0f, float rounding = 0.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddRectFilled(
            topLeft,                              // Top-left corner
            bottomRight,                          // Bottom-right corner
            color,                                // Color (ImColor automatically converts to ImU32)
            rounding,                             // Rounding radius
            0
        );
    }

    // Draw a line
    void drawLine(const ImVec2& start, const ImVec2& end, const ImColor& color, float thickness = 1.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddLine(
            start,                                // Start point
            end,                                  // End point
            color,                                // Color (ImColor automatically converts to ImU32)
            thickness                             // Line thickness
        );
    }

    // Draw a circle outline
    void drawCircle(const ImVec2& center, float radius, const ImColor& color, float thickness = 1.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddCircle(
            center,                               // Center of the circle
            radius,                               // Radius of the circle
            color,                                // Color (ImColor automatically converts to ImU32)
            0,                                    // Number of segments (0 lets ImGui auto-calculate)
            thickness                             // Line thickness
        );
    }

    // Draw a filled circle
    void drawFilledCircle(const ImVec2& center, float radius, const ImColor& color) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddCircleFilled(
            center,                               // Center of the circle
            radius,                               // Radius of the circle
            color                                 // Color (ImColor automatically converts to ImU32)
        );
    }

    // Draw a snapline from the screen center to the player's position
    void drawSnapline(const ImVec2& screenCenter, const ImVec2& playerPos, const ImColor& color, float thickness = 1.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddLine(
            screenCenter,                         // Start at screen center
            playerPos,                            // End at player position
            color,                                // Color of the line
            thickness                             // Line thickness
        );
    }

    ImColor GetColorHealth(int health)
    {
        if (health > 98)
            return ImColor(0.0f, 1.0f, 0.0f, 0.8f);
        if (health > 95)
            return ImColor(0.1f, 1.0f, 0.1f, 0.8f);
        if (health > 90)
            return ImColor(0.2f, 1.0f, 0.2f, 0.8f);
        if (health > 80)
            return ImColor(0.4f, 1.0f, 0.0f, 0.8f);
        if (health > 70)
            return ImColor(0.6f, 1.0f, 0.0f, 0.8f);
        if (health > 60)
            return ImColor(0.8f, 1.0f, 0.0f, 0.8f);
        if (health > 50)
            return ImColor(1.0f, 1.0f, 0.0f, 0.8f);
        if (health > 40)
            return ImColor(1.0f, 0.8f, 0.0f, 0.8f);
        if (health > 30)
            return ImColor(1.0f, 0.6f, 0.0f, 0.8f);
        if (health > 25)
            return ImColor(1.0f, 0.4f, 0.0f, 0.8f);
        if (health > 15)
            return ImColor(1.0f, 0.2f, 0.0f, 0.8f);
        if (health > 5)
            return ImColor(1.0f, 0.0f, 0.0f, 0.8f);
        return ImColor(0.5f, 0.0f, 0.0f, 0.8f);
    }
    // Add these new functions to your Drawing class
    void drawHealthBar(const ImVec2& pos, const ImVec2& size, float health, float maxHealth = 100.f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        // Calculate health percentage
        float healthPercent = health / maxHealth;
        healthPercent = customClamp(healthPercent, 0.f, 1.f);

        // Colors
        ImColor bgColor(40, 40, 40, 255);
        ImColor healthColor = GetColorHealth(health); // Use your existing health color function

        // Background
        drawList->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), bgColor);

        // Health fill
        float fillHeight = size.y * healthPercent;
        drawList->AddRectFilled(
            ImVec2(pos.x, pos.y + size.y - fillHeight),
            ImVec2(pos.x + size.x, pos.y + size.y),
            healthColor
        );

        // Border
        drawList->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(0, 0, 0, 255), 0.f, 0, 1.f);
    }

    // Draw text
    void drawText(const ImVec2& position, const char* text, const ImColor& color, float size = 16.0f) {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();

        // Scale font size (ImGui uses PushFont for different font sizes; this is a simple workaround)
        ImGuiIO& io = ImGui::GetIO();
        float originalFontSize = io.FontGlobalScale;
        io.FontGlobalScale = size / 16.0f; // Adjust font scaling relative to default size

        // Add text to the drawing list
        drawList->AddText(
            position,
            color,
            text
        );

        // Restore original font size
        io.FontGlobalScale = originalFontSize;
    }
};

#endif
