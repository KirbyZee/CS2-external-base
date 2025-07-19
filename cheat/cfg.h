#pragma once

namespace cfg {
	bool teamCheck = true;
	bool espOn = false;
	bool bones = false;

	bool aimbot = false;
	bool drawFov = false;
	inline bool nameEsp = false;
	float smoothing = 50.f;
	float fovSize = 25.f;
	int aimKey = 0x06;
	int aimBone = 0;

	float boxColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float boneColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float fovColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
}