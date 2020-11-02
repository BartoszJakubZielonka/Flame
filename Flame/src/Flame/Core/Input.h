#pragma once

#include "Flame/Core/Base.h"
#include "Flame/Core/KeyCodes.h"
#include "Flame/Core/MouseCodes.h"

namespace flame
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};
}
