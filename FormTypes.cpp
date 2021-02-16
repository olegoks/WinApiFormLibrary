#include "Library/FormTypes.hpp"

#define VK_A 65
#define VK_B 66
#define VK_D 68
#define VK_W 87
#define VK_S 83

Key ConvertWParamToKey(UINT wParam)noexcept(true) {

	switch (wParam) {

	case VK_UP: return Key::ArrowUp;
	case VK_DOWN: return Key::ArrowDown;
	case VK_LEFT: return Key::ArrowLeft;
	case VK_RIGHT: return Key::ArrowRight;
	case VK_A: return Key::A;
	case VK_D: return Key::D;
	case VK_S: return  Key::S;
	case VK_W: return Key::W;
	default: return Key::Nothing;

	}

}

Action ConvertMessageToAction(UINT message)noexcept(true) {

	switch (message) {

	case WM_MOUSEMOVE: return Action::MouseMove;
	case WM_KEYUP: return Action::KeyUp;
	case WM_KEYDOWN: return Action::KeyDown;
	case WM_LBUTTONDOWN: return Action::LMouseDown;
	case WM_LBUTTONUP: return Action::LMouseUp;
	case WM_RBUTTONDOWN: return Action::RMouseDown;
	case WM_RBUTTONUP: return Action::RMouseUp;
	
	default:return Action::Nothing;

	}

}

KeyAction::KeyAction(UINT Message, WPARAM wParam, LPARAM lParam)noexcept(true) :
	key_{ ConvertWParamToKey(wParam) },
	action_{ ConvertMessageToAction(Message) },
	message_{ Message },
	wParam_{ wParam },
	lParam_{ lParam } {}

KeyAction::KeyAction()noexcept(true) :
	key_{ Key::Nothing },
	action_{ Action::Nothing }{}

KeyAction::KeyAction(Key key, Action action)noexcept(true) :
	key_{ key },
	action_{ action }{}

bool KeyAction::operator !=(const KeyAction& key_action)noexcept(true) {

	return this->key_ != key_action.key_ || this->action_ != key_action.action_;

}


Message::Message()noexcept(true) :
	key_type{ KeyAction{} }{}

Message::Message(KeyAction key, const int x, const int y)noexcept(true) :
	key_type{ key },
	x_{ x },
	y_{ y }{}
