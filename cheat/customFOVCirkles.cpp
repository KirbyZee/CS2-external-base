#define _USE_MATH_DEFINES
#include <cmath> // M_PI verfügbar machen
#include "../ext/imgui/imgui.h"
#include <numbers>
#include <vector>
#include "../ext/imgui/imgui_internal.h"









void DrawCustomFOVCircle(const ImVec2& center, float radius, ImU32 color, float time) {
    const int numPoints = 200;  // Anzahl der Punkte, die den Kreis bilden
    const float pi = 3.14159265358979323846f;  // Definition von Pi, falls nicht verfügbar
    float angleStep = 2 * pi / numPoints;  // Winkel zwischen den Punkten


    for (int i = 0; i < numPoints; ++i) {
        // Berechne den Punkt auf dem Rand des Kreises
        float angle = angleStep * i;

        // Animiert den Radius, um einen pulsierenden Effekt zu erzielen
        float dynamicRadius = radius + sin(time + (i * 0.1f)) * 5.0f;  // Pulsierende Änderung des Radius

        // Berechne die Position des aktuellen Punktes
        ImVec2 point = ImVec2(center.x + cos(angle) * dynamicRadius, center.y + sin(angle) * dynamicRadius);

        // Zeichne den Punkt
        ImGui::GetBackgroundDrawList()->AddCircleFilled(point, 2.0f, color);
    }
}

void DrawGlowFOVCircle(const ImVec2& center, float radius, ImColor color, float time) {
    const int segments = 64; // Anzahl der Segmente für den Kreis

    // Dynamischer Glüheffekt basierend auf der Zeit
    const float glowEffect = sin(time * 2.0f) * 0.5f + 0.5f; // Dynamische Stärke des Glühen

    // Erstelle den äußeren Ring mit Glühen
    ImColor outerGlowColor(color.Value.x, color.Value.y, color.Value.z, glowEffect); // Glow-Effekt
    ImGui::GetBackgroundDrawList()->AddCircle(center, radius + 3.0f, outerGlowColor, segments, 3.0f); // Äußeren Rand mit Glühen

    // Erstelle den inneren Kreis ohne Glühen
    ImColor innerColor = color; // Die originale Farbe für den inneren Kreis
    ImGui::GetBackgroundDrawList()->AddCircle(center, radius, innerColor, segments, 2.0f); // Innerer Rand ohne Glühen
}

void DrawPulsingWaveFOVCircle(const ImVec2& center, float radius, ImColor color, float time) {
    const int segments = 64; // Anzahl der Segmente für den Kreis

    // Berechne die pulsierende Wellenstärke basierend auf der Zeit
    const float waveEffect = sin(time * 1.5f) * 0.5f + 0.5f; // Pulsierende Welle, Stärke variiert mit der Zeit

    // Berechne die Wellenbreite (dynamisch vergrößern/verkleinern)
    const float waveRadius = radius + waveEffect * 10.0f; // Radius der Wellenbasis

    // Erstelle den pulsierenden äußeren Kreis (Welle)
    ImColor waveColor(color.Value.x, color.Value.y, color.Value.z, 0.4f + waveEffect * 0.6f); // Wellenfarbe mit Transparenz
    ImGui::GetBackgroundDrawList()->AddCircle(center, waveRadius, waveColor, segments, 3.0f); // Wellenkreis

    // Optional: Füge einen inneren Kreis hinzu (normaler Kreis, der nicht pulsiert)
    ImColor innerColor = color; // Ursprüngliche Farbe für den inneren Kreis
    ImGui::GetBackgroundDrawList()->AddCircle(center, radius, innerColor, segments, 2.0f); // Innerer Kreis
}


void DrawAnimatedFOVCircle(const ImVec2& center, float radius, ImColor userColor, float time) {
    // Schwarz als Startfarbe
    ImColor black = ImColor(0, 0, 0);

    // Sinusfunktion für sanfte Übergänge
    float t = (sin(time * 2.0f) + 1.0f) / 2.0f; // ergibt Werte zwischen 0.0 und 1.0

    // Interpolation zwischen Schwarz und Benutzerfarbe
    ImColor animatedColor;
    animatedColor.Value.x = black.Value.x + (userColor.Value.x - black.Value.x) * t;
    animatedColor.Value.y = black.Value.y + (userColor.Value.y - black.Value.y) * t;
    animatedColor.Value.z = black.Value.z + (userColor.Value.z - black.Value.z) * t;
    animatedColor.Value.w = black.Value.w + (userColor.Value.w - black.Value.w) * t;

    // Kreis zeichnen
    ImGui::GetBackgroundDrawList()->AddCircle(center, radius, animatedColor, 100, 2.0f);
}

void DrawDoubleColorFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time)
{
    auto draw = ImGui::GetBackgroundDrawList();

    const int segments = 100;
    const float speed = 2.0f; // Geschwindigkeit der Animation

    for (int i = 0; i < segments; ++i)
    {
        float startAngle = (i / (float)segments) * 2.0f * IM_PI;
        float endAngle = ((i + 1) / (float)segments) * 2.0f * IM_PI;

        float t = (sin(time * speed + startAngle * 4.0f) + 1.0f) / 2.0f;
        ImColor blendedColor = ImColor(
            (int)(color1.Value.x * 255 * (1.0f - t) + color2.Value.x * 255 * t),
            (int)(color1.Value.y * 255 * (1.0f - t) + color2.Value.y * 255 * t),
            (int)(color1.Value.z * 255 * (1.0f - t) + color2.Value.z * 255 * t),
            255
        );

        draw->PathArcTo(center, radius, startAngle, endAngle, 2);
        draw->PathStroke(blendedColor, false, 2.0f);
    }
}


void DrawDashedFOVCircle(const ImVec2& center, float radius, ImColor color, float time) {
    const int segments = 100;
    const float dashLength = 5.0f;
    const float spaceLength = 5.0f;
    const float rotationSpeed = 1.0f; // Umdrehungsgeschwindigkeit

    float angleStep = (2.0f * IM_PI) / segments;
    float rotationOffset = time * rotationSpeed;

    for (int i = 0; i < segments; ++i) {
        float startAngle = i * angleStep + rotationOffset;
        float endAngle = startAngle + dashLength / radius;

        // Nur jede zweite Linie zeichnen
        if (i % 2 == 0) {
            ImVec2 start = ImVec2(center.x + cosf(startAngle) * radius, center.y + sinf(startAngle) * radius);
            ImVec2 end = ImVec2(center.x + cosf(endAngle) * radius, center.y + sinf(endAngle) * radius);
            ImGui::GetBackgroundDrawList()->AddLine(start, end, color, 2.0f);
        }
    }
}

void DrawBreathingGradientFOVCircle(const ImVec2& center, float baseRadius, ImColor colorStart, ImColor colorEnd, float time)
{
    const int segments = 128;
    const float breathingSpeed = 2.0f; // wie schnell er "atmet"
    const float breathingAmount = 10.0f; // wie viel größer/kleiner

    // Radius animieren
    float animatedRadius = baseRadius + sinf(time * breathingSpeed) * breathingAmount;

    auto drawList = ImGui::GetBackgroundDrawList();

    // Kreis zeichnen mit Gradient
    for (int i = 0; i < segments; ++i)
    {
        float startAngle = (i / (float)segments) * 2.0f * IM_PI;
        float endAngle = ((i + 1) / (float)segments) * 2.0f * IM_PI;

        ImVec2 startPoint = ImVec2(center.x + cosf(startAngle) * animatedRadius, center.y + sinf(startAngle) * animatedRadius);
        ImVec2 endPoint = ImVec2(center.x + cosf(endAngle) * animatedRadius, center.y + sinf(endAngle) * animatedRadius);

        // Lerp zwischen Start- und Endfarbe je nach Position
        float t = (i / (float)segments);
        ImColor currentColor;
        currentColor.Value.x = colorStart.Value.x + t * (colorEnd.Value.x - colorStart.Value.x);
        currentColor.Value.y = colorStart.Value.y + t * (colorEnd.Value.y - colorStart.Value.y);
        currentColor.Value.z = colorStart.Value.z + t * (colorEnd.Value.z - colorStart.Value.z);
        currentColor.Value.w = 1.0f;

        drawList->AddLine(startPoint, endPoint, currentColor, 2.5f);
    }
}


void DrawElectricFlickerFOVCircle(const ImVec2& center, float radius, ImColor color, float time) {
    const int segments = 100;
    const float flickerSpeed = 5.0f; // Geschwindigkeit des Flackerns
    const float flickerIntensity = 0.2f; // Intensität des Flackerns

    float angleStep = (2.0f * IM_PI) / segments;
    float flickerOffset = sinf(time * flickerSpeed) * flickerIntensity;

    for (int i = 0; i < segments; ++i) {
        float startAngle = i * angleStep;
        float endAngle = startAngle + angleStep;

        // Berechnung der Start- und Endpunkte der Linie
        ImVec2 start = ImVec2(center.x + cosf(startAngle) * radius, center.y + sinf(startAngle) * radius);
        ImVec2 end = ImVec2(center.x + cosf(endAngle) * radius, center.y + sinf(endAngle) * radius);

        // Flackern hinzufügen, indem die Linienfarbe variiert wird
        ImColor flickerColor = color;
        flickerColor.Value.w += flickerOffset; // Flacker-Effekt durch Transparenz-Änderung

        // Zeichne die Linie mit der flickernden Farbe
        ImGui::GetBackgroundDrawList()->AddLine(start, end, flickerColor, 2.0f);
    }
}


void DrawRainbowFlowFOVCircle(const ImVec2& center, float radius, float time) {
    const int segments = 100; // Anzahl der Segmente für den Kreis
    const float speed = 0.2f; // Geschwindigkeit der Farbdynamik
    const float angleStep = (2.0f * IM_PI) / segments; // Schrittweite für den Winkel

    for (int i = 0; i < segments; ++i) {
        // Berechnung des Start- und Endwinkels für jedes Segment
        float startAngle = i * angleStep;
        float endAngle = startAngle + angleStep;

        // Berechnung der Start- und Endpunkte des Segments
        ImVec2 start = ImVec2(center.x + cosf(startAngle) * radius, center.y + sinf(startAngle) * radius);
        ImVec2 end = ImVec2(center.x + cosf(endAngle) * radius, center.y + sinf(endAngle) * radius);

        // Berechne die Farbe, die mit der Zeit verändert wird, um einen Regenbogen-Effekt zu erzielen
        float colorFactor = (i + time * speed) / segments; // Farbänderung abhängig vom Index und der Zeit
        ImColor rainbowColor = ImColor::HSV(colorFactor, 1.0f, 1.0f); // Erstelle den Regenbogen-Effekt

        // Zeichne das Segment mit der berechneten Farbe
        ImGui::GetBackgroundDrawList()->AddLine(start, end, rainbowColor, 2.0f);
    }
}

void DrawPixelatedRetroFOVCircle(const ImVec2& center, float radius, ImColor color, float time) {
    const int pixelCount = 100; // Anzahl der Pixel (Pixelgröße und Auflösung des Kreises)
    const float angleStep = (2.0f * IM_PI) / pixelCount; // Berechnung des Winkels pro Pixel

    for (int i = 0; i < pixelCount; ++i) {
        // Berechnung des Winkels und der Position für jedes "Pixel"
        float angle = i * angleStep;
        float x = center.x + cosf(angle) * radius;
        float y = center.y + sinf(angle) * radius;

        // Zeichne ein Quadrat (Pixel) an der berechneten Position
        ImVec2 pixelPos = ImVec2(x, y);
        ImVec2 pixelSize = ImVec2(3.0f, 3.0f); // Pixelgröße

        // Zeichne das "Pixel" (kleines Quadrat)
        ImGui::GetBackgroundDrawList()->AddRectFilled(
            pixelPos - pixelSize / 2.0f,  // Startpunkt des Rechtecks
            pixelPos + pixelSize / 2.0f,  // Endpunkt des Rechtecks
            color);  // Die Farbe des Pixels
    }
}

void DrawTesterFOVCIRKLE(const ImVec2& center, float radius, ImColor fovCol, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    const int segments = 128; // Schöner runder Kreis

    // Rotation auf Basis der Zeit
    float rotation = time * 0.5f; // 0.5f = Rotationsgeschwindigkeit

    // Farben
    ImColor innerColor(0, 0, 0, 255); // Schwarzer Rand (volle Deckkraft)

    // Punkte berechnen und zeichnen
    for (int i = 0; i < segments; i++)
    {
        float startAngle = (i / (float)segments) * 2.0f * IM_PI + rotation;
        float endAngle = ((i + 1) / (float)segments) * 2.0f * IM_PI + rotation;

        ImVec2 start = ImVec2(center.x + cosf(startAngle) * radius, center.y + sinf(startAngle) * radius);
        ImVec2 end = ImVec2(center.x + cosf(endAngle) * radius, center.y + sinf(endAngle) * radius);

        // 1. Schwarze Linie (hintergrund)
        drawList->AddLine(start, end, innerColor, 1.5f);

        // 2. Farbige Linie (vordergrund)
        drawList->AddLine(start, end, fovCol, 1.0f);
    }
}







void DrawCircleWithTransparentCenter(const ImVec2& center, float outerRadius, float innerRadius, ImColor outerColor) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Zeichne den äußeren Kreis
    drawList->AddCircle(center, outerRadius, outerColor, 64, 2.0f); // 64 Segmente für einen glatten Kreis

    // Zeichne den inneren transparenten Kreis mit halbtransparenter Farbe
    ImColor semiTransparentColor(outerColor.Value.x, outerColor.Value.y, outerColor.Value.z, 0.5f); // Die Alpha-Komponente auf 0.2 setzen
    drawList->AddCircleFilled(center, innerRadius, semiTransparentColor); // Innerer Kreis mit halbtransparenter Farbe
}

void DrawTransparentFOVCircle(const ImVec2& center, float radius, ImColor circleColor) {
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Setze den Alpha-Wert intern auf 0.2 für Transparenz
    ImColor transparentColor(circleColor.Value.x, circleColor.Value.y, circleColor.Value.z, 0.2f);
    drawList->AddCircleFilled(center, radius, transparentColor); // Vollständig gefüllter, transparenter Kreis
}



void DrawWaterWaveFOVCircle(const ImVec2& center, float baseRadius) {
    static float time = 0.0f;
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    // Berechne die Verzerrung des Kreises wie Wellen
    float waveOffset = sin(time * 2.0f) * 5.0f;  // Verzerrung der Kreisform durch Sinuswelle

    // Zeichne den Kreis mit dieser Verzerrung
    drawList->AddCircleFilled(center, baseRadius + waveOffset, ImColor(0, 255, 255, 150));

    time += ImGui::GetIO().DeltaTime;
}



// Call this inside your ImGui render loop!
void DrawWavyFOVCircle(const ImVec2& center, float radius, ImColor color, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    int numPoints = 128; // Glattheit
    float waveAmplitude = 5.0f; // Wellenhöhe
    float waveFrequency = 10.0f; // Wie viele Wellen auf dem Kreis
    float step = 2.0f * IM_PI / numPoints;

    ImVec2 previousPoint;

    for (int i = 0; i <= numPoints; ++i)
    {
        float angle = i * step;
        float wavyRadius = radius + std::sin(angle * waveFrequency + time * 2.0f) * waveAmplitude;

        ImVec2 point = {
            center.x + wavyRadius * std::cos(angle),
            center.y + wavyRadius * std::sin(angle)
        };

        if (i > 0)
            drawList->AddLine(previousPoint, point, color, 1.5f);

        previousPoint = point;
    }
}

void DrawWavyFOVCircleDots(const ImVec2& center, float radius, ImColor color, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    int numPoints = 128; // Anzahl Punkte
    float waveAmplitude = 5.0f; // Ausschlag der Welle
    float waveFrequency = 10.0f; // Wellenfrequenz
    float step = 2.0f * IM_PI / numPoints;
    float pointSize = 2.0f; // Größe der Punkte

    for (int i = 0; i <= numPoints; ++i)
    {
        float angle = i * step;
        float wavyRadius = radius + std::sin(angle * waveFrequency + time * 2.0f) * waveAmplitude;

        ImVec2 point = {
            center.x + wavyRadius * std::cos(angle),
            center.y + wavyRadius * std::sin(angle)
        };

        drawList->AddCircleFilled(point, pointSize, color);
    }
}

void DrawSmoothGlowFOVCircle(const ImVec2& center, float radius, ImColor color, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    int numPoints = 150; // Viele Punkte für schön smooth
    float waveAmplitude = 2.0f; // Leichtes "Atmen", optional
    float step = 2.0f * IM_PI / numPoints;
    float basePointSize = 2.0f; // Basisgröße der Punkte

    // Optional: Atmende Punktgröße (fühlt sich lebendiger an)
    float breathing = 0.5f + 0.5f * std::sin(time * 2.0f);

    for (int i = 0; i <= numPoints; ++i)
    {
        float angle = i * step;
        float dynamicRadius = radius + std::sin(angle * 4.0f + time * 2.0f) * waveAmplitude;

        ImVec2 point = {
            center.x + dynamicRadius * std::cos(angle),
            center.y + dynamicRadius * std::sin(angle)
        };

        ImColor glowColor = ImColor(
            color.Value.x,
            color.Value.y,
            color.Value.z,
            0.2f // Glow Alpha (weniger Deckkraft)
        );

        // Erst einen leichten Glow
        drawList->AddCircleFilled(point, basePointSize * 2.5f * breathing, glowColor);

        // Dann den eigentlichen Punkt
        drawList->AddCircleFilled(point, basePointSize * breathing, color);
    }
}

void DrawClassicFOVCircle(ImVec2 center, float radius, ImColor color)
{
    auto drawList = ImGui::GetBackgroundDrawList();
    drawList->AddCircle(
        center,
        radius,
        color,
        128,      // Segments: schön rund
        2.0f      // Thickness: 2px dick
    );
}

void DrawStarWaveGradientFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    int numPoints = 150; // Auflösung der Sternform
    float spikeAmplitude = 15.0f; // Wie stark die Sternzacken rausgehen
    float waveAmplitude = 5.0f;   // Kleine Wellenbewegung
    float spikeFrequency = 5.0f;  // Wie viele Zacken entstehen

    float step = 2.0f * IM_PI / numPoints;

    for (int i = 0; i <= numPoints; ++i)
    {
        float t = (float)i / (float)numPoints; // Für Gradient
        float angle = i * step;

        // Sternform: Grundradius + Zacken + Wellen
        float dynamicRadius = radius
            + std::sin(angle * spikeFrequency + time * 2.0f) * spikeAmplitude // Zacken
            + std::sin(angle * 2.0f + time * 3.0f) * waveAmplitude;            // leichte Wellen

        ImVec2 point = {
            center.x + dynamicRadius * std::cos(angle),
            center.y + dynamicRadius * std::sin(angle)
        };

        // Farbverlauf berechnen
        ImColor currentColor = ImColor(
            color1.Value.x + (color2.Value.x - color1.Value.x) * t,
            color1.Value.y + (color2.Value.y - color1.Value.y) * t,
            color1.Value.z + (color2.Value.z - color1.Value.z) * t,
            1.0f
        );

        drawList->AddCircleFilled(point, 2.0f, currentColor);
    }
}

void DrawAnimatedDualColorFOVCircle(const ImVec2& center, float radius, ImColor color1, ImColor color2, float time)
{
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    int numLines = 60; // Wie viele Linien (dichter oder lockerer)
    float lineLength = 8.0f; // Länge der Linien
    float rotationSpeed = 2.0f; // Geschwindigkeit der Animation

    float step = 2.0f * IM_PI / numLines;
    float rotation = time * rotationSpeed;

    for (int i = 0; i < numLines; ++i)
    {
        float angle = i * step + rotation;

        ImVec2 start = {
            center.x + radius * cosf(angle),
            center.y + radius * sinf(angle)
        };

        ImVec2 end = {
            center.x + (radius + lineLength) * cosf(angle),
            center.y + (radius + lineLength) * sinf(angle)
        };

        // Farben abwechselnd: Hälfte eine Farbe, Hälfte die andere
        ImColor currentColor = (i % 2 == 0) ? color1 : color2;

        drawList->AddLine(start, end, currentColor, 2.0f); // 2.0f = Linienstärke
    }
}



float animationOffset = 0.0f; // Offset für Farbbewegung
float ThicknessFOV = 3.0f;
float animationSpeed = 0.05f;
ImVec4 color1 = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Schwarz
ImVec4 color2 = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Blau


void DrawMovingFOVCircle(ImDrawList* drawList, ImVec2 center, float radius) {
    int numSegments = 100;
    float angleStep = 2 * IM_PI / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        // Farben interpolieren und Offset animieren
        float t = (float)i / (float)numSegments;
        float mixFactor = sin(animationOffset - t * 2 * IM_PI) * 0.5f + 0.5f;
        ImVec4 color = ImLerp(color1, color2, mixFactor);

        // Winkel für die Linie berechnen (im Uhrzeigersinn)
        float angle1 = -i * angleStep; // Negativer Winkel für Uhrzeigersinn
        float angle2 = -(i + 1) * angleStep;

        // Start- und Endpunkt der Linie berechnen
        ImVec2 p1 = ImVec2(center.x + cos(angle1) * radius, center.y + sin(angle1) * radius);
        ImVec2 p2 = ImVec2(center.x + cos(angle2) * radius, center.y + sin(angle2) * radius);

        drawList->AddLine(p1, p2, ImGui::GetColorU32(color), ThicknessFOV);
    }

    // Offset aktualisieren, um den Effekt der Bewegung im Uhrzeigersinn zu erzeugen
    animationOffset -= animationSpeed; // Offset verringern für Uhrzeigersinn-Rotation
    if (animationOffset < 0.0f) {
        animationOffset += 2 * IM_PI;
    }
}