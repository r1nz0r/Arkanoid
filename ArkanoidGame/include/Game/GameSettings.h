#pragma once

namespace Arkanoid
{
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	const float PADDLE_WIDTH = 80.f;
	const float PADDLE_HEIGHT = 10.f;
	const float PADDLE_SPEED = 550.f;

	const float BALL_SIZE = 8.f;
	const float BALL_INITIAL_SPEED = 400.f;
	const float BALL_ANGLE_ACCELERATION = 200.f;
	const float BOUNCE_ANGLE_MAX = 40.f;

	const float BLOCK_WIDTH = 60.f;
	const float BLOCK_HEIGHT = 15.f;

	const float TARGET_FRAMERATE = 60.f;

	static const char* GAME_NAME = "ArkanoidGame";
}