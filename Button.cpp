#include "Button.hpp"
#include "ButtonImplementation.hpp"

Button::Button() : impl_{ nullptr } {

	try {

		impl_ = new ButtonImplementation{};

	} catch (const std::bad_alloc&) {
	
		throw ComponentException{ u8"Button allocation memory error." };

	}

}

Button::~Button()noexcept {

	if (std::any_cast<ButtonImplementation*>(impl_) != nullptr)
		delete std::any_cast<ButtonImplementation*>(impl_);

}

void Button::SetProcessFunction(ProcessMessage messages_processing) noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->SetProcessFunction(messages_processing);
}

void Button::ChangeSize(const int width, const int height)
{
	return std::any_cast<ButtonImplementation*>(impl_)->ChangeSize(width, height);
}

void Button::ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle){

	return std::any_cast<ButtonImplementation*>(impl_)->ChangeStyle(ex_dwStyle, dwStyle);
}

void Button::ChangePosition(const int x, const int y){

	return std::any_cast<ButtonImplementation*>(impl_)->ChangePosition(x, y);
}

void Button::Image(const std::wstring& bitmap_path){

	std::any_cast<ButtonImplementation*>(impl_)->Image(bitmap_path);
}

void Button::ChangeText(const std::wstring& text){

	std::any_cast<ButtonImplementation*>(impl_)->ChangeText(text);
}

bool Button::WasCreated() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->WasCreated();
}


HWND Button::GetHandle() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->GetHandle();
}

int Button::GetHeight() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->GetHeight();
}

int Button::GetWidth() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->GetWidth();
}

int Button::GetX() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->GetX();
}

int Button::GetY() const noexcept{

	return std::any_cast<ButtonImplementation*>(impl_)->GetY();
}

void Button::Create(const HWND parent_hWnd){

	std::any_cast<ButtonImplementation*>(impl_)->Create(parent_hWnd);
}

void Button::Show(int nCmdShow){

	std::any_cast<ButtonImplementation*>(impl_)->Show(nCmdShow);
}

void Button::Destroy() {

	std::any_cast<ButtonImplementation*>(impl_)->Destroy();

}
