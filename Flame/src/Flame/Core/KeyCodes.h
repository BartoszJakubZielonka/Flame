#pragma once

namespace flame
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define FL_KEY_SPACE           ::flame::Key::Space
#define FL_KEY_APOSTROPHE      ::flame::Key::Apostrophe    /* ' */
#define FL_KEY_COMMA           ::flame::Key::Comma         /* , */
#define FL_KEY_MINUS           ::flame::Key::Minus         /* - */
#define FL_KEY_PERIOD          ::flame::Key::Period        /* . */
#define FL_KEY_SLASH           ::flame::Key::Slash         /* / */
#define FL_KEY_0               ::flame::Key::D0
#define FL_KEY_1               ::flame::Key::D1
#define FL_KEY_2               ::flame::Key::D2
#define FL_KEY_3               ::flame::Key::D3
#define FL_KEY_4               ::flame::Key::D4
#define FL_KEY_5               ::flame::Key::D5
#define FL_KEY_6               ::flame::Key::D6
#define FL_KEY_7               ::flame::Key::D7
#define FL_KEY_8               ::flame::Key::D8
#define FL_KEY_9               ::flame::Key::D9
#define FL_KEY_SEMICOLON       ::flame::Key::Semicolon     /* ; */
#define FL_KEY_EQUAL           ::flame::Key::Equal         /* = */
#define FL_KEY_A               ::flame::Key::A
#define FL_KEY_B               ::flame::Key::B
#define FL_KEY_C               ::flame::Key::C
#define FL_KEY_D               ::flame::Key::D
#define FL_KEY_E               ::flame::Key::E
#define FL_KEY_F               ::flame::Key::F
#define FL_KEY_G               ::flame::Key::G
#define FL_KEY_H               ::flame::Key::H
#define FL_KEY_I               ::flame::Key::I
#define FL_KEY_J               ::flame::Key::J
#define FL_KEY_K               ::flame::Key::K
#define FL_KEY_L               ::flame::Key::L
#define FL_KEY_M               ::flame::Key::M
#define FL_KEY_N               ::flame::Key::N
#define FL_KEY_O               ::flame::Key::O
#define FL_KEY_P               ::flame::Key::P
#define FL_KEY_Q               ::flame::Key::Q
#define FL_KEY_R               ::flame::Key::R
#define FL_KEY_S               ::flame::Key::S
#define FL_KEY_T               ::flame::Key::T
#define FL_KEY_U               ::flame::Key::U
#define FL_KEY_V               ::flame::Key::V
#define FL_KEY_W               ::flame::Key::W
#define FL_KEY_X               ::flame::Key::X
#define FL_KEY_Y               ::flame::Key::Y
#define FL_KEY_Z               ::flame::Key::Z
#define FL_KEY_LEFT_BRACKET    ::flame::Key::LeftBracket   /* [ */
#define FL_KEY_BACKSLASH       ::flame::Key::Backslash     /* \ */
#define FL_KEY_RIGHT_BRACKET   ::flame::Key::RightBracket  /* ] */
#define FL_KEY_GRAVE_ACCENT    ::flame::Key::GraveAccent   /* ` */
#define FL_KEY_WORLD_1         ::flame::Key::World1        /* non-US #1 */
#define FL_KEY_WORLD_2         ::flame::Key::World2        /* non-US #2 */

/* Function keys */
#define FL_KEY_ESCAPE          ::flame::Key::Escape
#define FL_KEY_ENTER           ::flame::Key::Enter
#define FL_KEY_TAB             ::flame::Key::Tab
#define FL_KEY_BACKSPACE       ::flame::Key::Backspace
#define FL_KEY_INSERT          ::flame::Key::Insert
#define FL_KEY_DELETE          ::flame::Key::Delete
#define FL_KEY_RIGHT           ::flame::Key::Right
#define FL_KEY_LEFT            ::flame::Key::Left
#define FL_KEY_DOWN            ::flame::Key::Down
#define FL_KEY_UP              ::flame::Key::Up
#define FL_KEY_PAGE_UP         ::flame::Key::PageUp
#define FL_KEY_PAGE_DOWN       ::flame::Key::PageDown
#define FL_KEY_HOME            ::flame::Key::Home
#define FL_KEY_END             ::flame::Key::End
#define FL_KEY_CAPS_LOCK       ::flame::Key::CapsLock
#define FL_KEY_SCROLL_LOCK     ::flame::Key::ScrollLock
#define FL_KEY_NUM_LOCK        ::flame::Key::NumLock
#define FL_KEY_PRINT_SCREEN    ::flame::Key::PrintScreen
#define FL_KEY_PAUSE           ::flame::Key::Pause
#define FL_KEY_F1              ::flame::Key::F1
#define FL_KEY_F2              ::flame::Key::F2
#define FL_KEY_F3              ::flame::Key::F3
#define FL_KEY_F4              ::flame::Key::F4
#define FL_KEY_F5              ::flame::Key::F5
#define FL_KEY_F6              ::flame::Key::F6
#define FL_KEY_F7              ::flame::Key::F7
#define FL_KEY_F8              ::flame::Key::F8
#define FL_KEY_F9              ::flame::Key::F9
#define FL_KEY_F10             ::flame::Key::F10
#define FL_KEY_F11             ::flame::Key::F11
#define FL_KEY_F12             ::flame::Key::F12
#define FL_KEY_F13             ::flame::Key::F13
#define FL_KEY_F14             ::flame::Key::F14
#define FL_KEY_F15             ::flame::Key::F15
#define FL_KEY_F16             ::flame::Key::F16
#define FL_KEY_F17             ::flame::Key::F17
#define FL_KEY_F18             ::flame::Key::F18
#define FL_KEY_F19             ::flame::Key::F19
#define FL_KEY_F20             ::flame::Key::F20
#define FL_KEY_F21             ::flame::Key::F21
#define FL_KEY_F22             ::flame::Key::F22
#define FL_KEY_F23             ::flame::Key::F23
#define FL_KEY_F24             ::flame::Key::F24
#define FL_KEY_F25             ::flame::Key::F25

/* Keypad */
#define FL_KEY_KP_0            ::flame::Key::KP0
#define FL_KEY_KP_1            ::flame::Key::KP1
#define FL_KEY_KP_2            ::flame::Key::KP2
#define FL_KEY_KP_3            ::flame::Key::KP3
#define FL_KEY_KP_4            ::flame::Key::KP4
#define FL_KEY_KP_5            ::flame::Key::KP5
#define FL_KEY_KP_6            ::flame::Key::KP6
#define FL_KEY_KP_7            ::flame::Key::KP7
#define FL_KEY_KP_8            ::flame::Key::KP8
#define FL_KEY_KP_9            ::flame::Key::KP9
#define FL_KEY_KP_DECIMAL      ::flame::Key::KPDecimal
#define FL_KEY_KP_DIVIDE       ::flame::Key::KPDivide
#define FL_KEY_KP_MULTIPLY     ::flame::Key::KPMultiply
#define FL_KEY_KP_SUBTRACT     ::flame::Key::KPSubtract
#define FL_KEY_KP_ADD          ::flame::Key::KPAdd
#define FL_KEY_KP_ENTER        ::flame::Key::KPEnter
#define FL_KEY_KP_EQUAL        ::flame::Key::KPEqual

#define FL_KEY_LEFT_SHIFT      ::flame::Key::LeftShift
#define FL_KEY_LEFT_CONTROL    ::flame::Key::LeftControl
#define FL_KEY_LEFT_ALT        ::flame::Key::LeftAlt
#define FL_KEY_LEFT_SUPER      ::flame::Key::LeftSuper
#define FL_KEY_RIGHT_SHIFT     ::flame::Key::RightShift
#define FL_KEY_RIGHT_CONTROL   ::flame::Key::RightControl
#define FL_KEY_RIGHT_ALT       ::flame::Key::RightAlt
#define FL_KEY_RIGHT_SUPER     ::flame::Key::RightSuper
#define FL_KEY_MENU            ::flame::Key::Menu