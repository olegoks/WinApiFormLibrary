#include "AbstractComponent.hpp"

#define __STD ::std::

bool AbstractComponent::CallProcessMessage(Message& message) {

	return process_messages_(message);
}

void AbstractComponent::RegisterComponentClass(const std::wstring& class_name){

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ComponentProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(__STD uint64_t);
	wc.hInstance = hInstance_;
	wc.hIcon = NULL;//LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = /*(HBRUSH)RGB(kDefaultBackgroundColor.rgba_.r, kDefaultBackgroundColor.rgba_.g, kDefaultBackgroundColor.rgba_.b);*/(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = class_name.c_str();
	wc.hIconSm = NULL;//LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		throw ComponentException{ u8"RegisterClass error." };

	class_name_ = class_name;

}

void AbstractComponent::ShowComponent(int nCmdShow){

	ShowWindow(self_hWnd_, nCmdShow);

}

bool AbstractComponent::WasCreated() const noexcept{

	return self_hWnd_ != NULL;
}

DWORD AbstractComponent::GetStyle() const{

	BOOL result = GetWindowLongPtr(GetHandle(), GWL_STYLE);

	if (!result) {

		throw ComponentException{ u8"GetWindowLong error." };

	}

	return result;

}

DWORD AbstractComponent::GetExtendedStyle() const {

	BOOL result = GetWindowLongPtr(GetHandle(), GWL_EXSTYLE);

	if (!result) {

		throw ComponentException{ u8"GetWindowLong error." };

	}

	return result;
}

const HWND AbstractComponent::GetHandle() const noexcept {

	return self_hWnd_;
}

void AbstractComponent::DestroyComponent(){

	SendMessage(self_hWnd_, WM_CLOSE, NULL, NULL);

}

AbstractComponent::AbstractComponent(){

	hInstance_ = GetModuleHandle(NULL);

}

AbstractComponent::~AbstractComponent(){


}

void AbstractComponent::SetProcessFunction(ProcessMessage messages_processing) noexcept {

	process_messages_ = [this, messages_processing](Message& message)noexcept->bool {

		return messages_processing(message);

	};

}

void AbstractComponent::ChangePosition(const uint64_t x, const uint64_t y) noexcept(false) {

	if (WasCreated()) {

		BOOL success = SetWindowPos(self_hWnd_, NULL, x, y, GetWidth(), GetHeight(), NULL);

		if (!success)
			throw ComponentException{ u8"SetWindowPos error." };

	}

}

void AbstractComponent::ChangeSize(const uint64_t width, const uint64_t height) {

	if (WasCreated()) {

		BOOL success = SetWindowPos(self_hWnd_, NULL, GetX(), GetY(), width, height, SWP_NOZORDER);

		if (!success)
			throw ComponentException{ u8"SetWindowPos error." };

	}

}

void AbstractComponent::ChangeText(const std::wstring& text) {

	if (WasCreated()) {

		BOOL success = SetWindowText(self_hWnd_, text.c_str());

		if (!success)
			throw ComponentException{ u8"SetWindowText error." };

	}

}

int AbstractComponent::GetWidth() const {

	RECT rectangle{ 0 };

	BOOL result = GetWindowRect(self_hWnd_, &rectangle);

	if (!result)
		throw ComponentException{ u8"GetWindowRect error." };

	return rectangle.right - rectangle.left;
}

const std::uint64_t AbstractComponent::GetClientHeight() const {

	RECT client_rect{ 0 };
	BOOL result = GetClientRect(self_hWnd_, &client_rect);

	if (!result)
		throw ComponentException{ u8"GetClientRect error." };

	return client_rect.bottom;
}

const std::uint64_t AbstractComponent::GetClientWidth() const{

	RECT client_rect{ 0 };
	BOOL result = GetClientRect(self_hWnd_, &client_rect);

	if (!result)
		throw ComponentException{ u8"GetClientRect error." };

	return client_rect.right;
}

int AbstractComponent::GetHeight() const {

	RECT rectangle{ 0 };

	BOOL result = GetWindowRect(self_hWnd_, &rectangle);

	if (!result)
		throw ComponentException{ u8"GetWindowRect error." };

	return rectangle.bottom - rectangle.top;
}

int AbstractComponent::GetX() const {

	RECT rectangle{ 0 };

	BOOL result = GetWindowRect(self_hWnd_, &rectangle);

	if (!result)
		throw ComponentException{ u8"GetWindowRect error." };

	return rectangle.left;
}

int AbstractComponent::GetY() const {


	RECT rectangle{ 0 };

	BOOL result = GetWindowRect(self_hWnd_, &rectangle);

	if (!result)
		throw ComponentException{ u8"GetWindowRect error." };

	return rectangle.right;
}

#ifdef _M_X64
	using PointerType = LONG_PTR;
	using ValueType = LONG_PTR;
#else
#define BindPointerToForm SetFormLong
	using PointerType = LONG;
	using ValueType = LONG;
#endif

void AbstractComponent::CreateComponent(const HWND parent_hWnd, const std::wstring& class_name){

	if (WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };
	
	if (class_name != kDefaultClassName)
		class_name_ = class_name;

	self_hWnd_ = CreateWindowEx(kDefaultExStyle,
		class_name_.c_str(),
		text_.c_str(),
		kDefaultStyle,
		kDefaultX,
		kDefaultY,
		kDefaultWidth,
		kDefaultHeight,
		parent_hWnd,
		HMENU(NULL),
		(HINSTANCE)hInstance_,
		this);


	if (!WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };

	parent_hWnd_ = parent_hWnd;

	SetLastError(NULL);
	LONG_PTR last_value = SetWindowLongPtr(GetHandle(), GWLP_USERDATA, (PointerType)this);

	if (last_value == 0) {

		DWORD error = GetLastError();

		if (error != 0)
			throw ComponentException{ u8"BindPointerToWindow error." };

	} else
		throw ComponentException{ u8"BindPointerToWindow error." };

	SetProcessDPIAware();

}

void AbstractComponent::ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle) {

	if (WasCreated()) {

		SetWindowLongPtr(GetHandle(), GWL_STYLE, dwStyle );
		SetWindowLongPtr(GetHandle(), GWL_EXSTYLE, ex_dwStyle);
	
	}

}

LRESULT CALLBACK AbstractComponent::ComponentProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam) {

	bool message_processed = false;
	AbstractComponent* component = nullptr;
	
	Message new_message{ message, wParam, lParam };

	if(new_message.GetActionType() == ActionType::Control)
		component = (AbstractComponent*)GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
	else	
		component = (AbstractComponent*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (component != nullptr)
		message_processed = component->CallProcessMessage(new_message);

	if (message_processed)
		return LRESULT{ 0 };

	switch (message) {

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}
