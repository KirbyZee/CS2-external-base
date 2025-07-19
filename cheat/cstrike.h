#pragma once
#include "entity.h"
#include "cfg.h"
#include "drawing.h"
#include "math.h"
#include "sdk.h"

namespace cstrike {
	view_matrix_t matrix;
	view_matrix_t updateMatrix();

	void drawBox(entities::PLAYER actor, ImColor col);
	void drawBones(entities::PLAYER actor, ImColor col);
	void drawSnapline(entities::PLAYER actor, ImColor col);

	Drawing* draw = new Drawing();
}

view_matrix_t cstrike::updateMatrix() {
	return memory->read<view_matrix_t>(client + Offsets::dwViewMatrix);
}

void cstrike::drawBox(entities::PLAYER actor, ImColor col) {
	if (actor.actorBase == localplayer::pawn)
		return;

	if (&actor == nullptr || actor.PlayerPos.IsZero())
		return;
	if (actor.health <= 0)
		return;

	Vec3 head_t = { actor.PlayerPos.x, actor.PlayerPos.y, actor.PlayerPos.z + 70.f };
	Vec3 screenPos, screenHead;

	if (!W2S(actor.PlayerPos, screenPos, cstrike::matrix) || !W2S(head_t, screenHead, matrix))
		return;

	float height = std::abs(screenPos.y - screenHead.y);
	float width = height / 2.0f;

	ImVec2 topLeft(screenHead.x - width / 2, screenHead.y);
	ImVec2 bottomRight(topLeft.x + width, topLeft.y + height);

	// Draw box
	draw->drawBox(topLeft, bottomRight, ImColor(0, 0, 0, 255), 2.0f, 0.f);
	draw->drawBox(topLeft, bottomRight, col, 1, 0.f);

	// Draw filled box
	if (cfg::nameEsp) {
		ImVec2 namePos(topLeft.x + width / 2, topLeft.y - 18); // 18 pixels above box
		ImGui::GetBackgroundDrawList()->AddText(
			ImVec2(namePos.x - ImGui::CalcTextSize(actor.name).x / 2, namePos.y),
			IM_COL32(255, 255, 255, 255), // White color
			actor.name
		);
	}

	// Health bar
	const float healthBarWidth = 3.f;
	const float healthBarOffset = 2.f;
	ImVec2 healthBarPos(topLeft.x - healthBarWidth - healthBarOffset, topLeft.y);
	ImVec2 healthBarSize(healthBarWidth, height);
	draw->drawHealthBar(healthBarPos, healthBarSize, actor.health);



}
void cstrike::drawBones(entities::PLAYER actor, ImColor col) {
	if (actor.health <= 0)
		return;

	Vec3 screenBones[13];
	bool allVisible = true;

	for (int i = 0; i < 13; ++i) {
		if (!W2S(actor.bones[i], screenBones[i], matrix)) {
			allVisible = false;
			break;
		}
	}

	if (!allVisible) return;

	ImVec2 boneScreen[13];
	for (int i = 0; i < 13; ++i) {
		boneScreen[i] = ImVec2(screenBones[i].x, screenBones[i].y);
	}

	auto drawBoneLine = [&](int a, int b) {
		if (a < 13 && b < 13) {
			float dx = boneScreen[b].x - boneScreen[a].x;
			float dy = boneScreen[b].y - boneScreen[a].y;
			float length = std::sqrt(dx * dx + dy * dy);

			if (length <= 75.0f) {
				// Draw black outline first (behind)
				draw->drawLine(boneScreen[a], boneScreen[b], ImColor(0, 0, 0), 2.f);  // Black outline with thickness 2
				// Then draw the colored bone line
				draw->drawLine(boneScreen[a], boneScreen[b], col, 1.f);  // Colored line with thickness 1
			}
		}
		};

	// Bone connections
	drawBoneLine(0, 1);
	drawBoneLine(1, 2);
	drawBoneLine(1, 3);
	drawBoneLine(2, 4);
	drawBoneLine(3, 5);
	drawBoneLine(4, 6);
	drawBoneLine(5, 7);
	drawBoneLine(1, 8);
	drawBoneLine(8, 9);
	drawBoneLine(8, 10);
	drawBoneLine(9, 11);
	drawBoneLine(10, 12);
}



void cstrike::drawSnapline(entities::PLAYER actor, ImColor col) {
	if (actor.actorBase == localplayer::pawn)
		return;

	if (&actor == nullptr || actor.PlayerPos.IsZero())
		return;
	if (actor.health <= 0)
		return;

	Vec3 screenPos;
	if (!W2S(actor.PlayerPos, screenPos, matrix))
		return;

	// Mitte des Bildschirms annehmen
	ImVec2 screenCenter(ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y);

	// Zuerst eine dickere schwarze Outline (Hintergrundlinie)
	draw->drawLine(screenCenter, ImVec2(screenPos.x, screenPos.y), ImColor(0, 0, 0), 3.0f);  // Schwarze Linie für Outline

	// Dann die farbige Linie (Snapline)
	draw->drawLine(screenCenter, ImVec2(screenPos.x, screenPos.y), col, 1.0f);  // Normale farbige Linie
}



 



  