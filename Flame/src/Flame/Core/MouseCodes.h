#pragma once

namespace flame
{
	typedef enum class MouseCode: uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define FL_MOUSE_BUTTON_0      ::flame::Mouse::Button0
#define FL_MOUSE_BUTTON_1      ::flame::Mouse::Button1
#define FL_MOUSE_BUTTON_2      ::flame::Mouse::Button2
#define FL_MOUSE_BUTTON_3      ::flame::Mouse::Button3
#define FL_MOUSE_BUTTON_4      ::flame::Mouse::Button4
#define FL_MOUSE_BUTTON_5      ::flame::Mouse::Button5
#define FL_MOUSE_BUTTON_6      ::flame::Mouse::Button6
#define FL_MOUSE_BUTTON_7      ::flame::Mouse::Button7
#define FL_MOUSE_BUTTON_LAST   ::flame::Mouse::ButtonLast
#define FL_MOUSE_BUTTON_LEFT   ::flame::Mouse::ButtonLeft
#define FL_MOUSE_BUTTON_RIGHT  ::flame::Mouse::ButtonRight
#define FL_MOUSE_BUTTON_MIDDLE ::flame::Mouse::ButtonMiddle