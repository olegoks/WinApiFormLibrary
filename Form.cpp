#include "Library/Form.hpp"
#include "FormImplementation.hpp"

Form::Form():
	impl_{ } {

	try {

		impl_ = new FormImplementation{};

	} catch (const std::bad_alloc&) { 
	
		throw ComponentException{ u8"Form allocation memory error." };

	}

}

Form::~Form()noexcept(true){

	if (impl_.has_value())
		delete std::any_cast<FormImplementation*>(impl_);
	
}
Form::Form(Form&& move_form) noexcept:
	impl_{ } {

	std::swap(impl_, move_form.impl_);

}

Form& Form::operator=(Form&& move_form) noexcept{

	if (&move_form == this) return *this;

	std::swap(impl_, move_form.impl_);

	return *this;

}
void Form::Create(const HWND parent_hWnd){

	std::any_cast<FormImplementation*>(impl_)->Create(parent_hWnd);

}

void Form::Show(int nCmdShow){

	std::any_cast<FormImplementation*>(impl_)->Show(nCmdShow);

}

void Form::Run() noexcept(false){

	std::any_cast<FormImplementation*>(impl_)->Run();

}

void Form::Destroy() noexcept(false){

	std::any_cast<FormImplementation*>(impl_)->Destroy();

}

void Form::ChangeCaption(const std::wstring& caption){

	std::any_cast<FormImplementation*>(impl_)->ChangeCaption(caption);

}

const HWND Form::GetHandle() const noexcept{
	
	return std::any_cast<FormImplementation*>(impl_)->GetHandle();

}


void Form::SetProcessFunction(ProcessMessage messages_processing) noexcept{

	std::any_cast<FormImplementation*>(impl_)->SetProcessFunction(messages_processing);

}

void Form::ChangeSize(const int width, const int height){

	std::any_cast<FormImplementation*>(impl_)->ChangeSize(width, height);

}

int Form::GetWidth() const noexcept{

	return std::any_cast<FormImplementation*>(impl_)->GetWidth();
}

int Form::GetHeight() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetHeight();
}

int Form::GetX() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetX();
}

int Form::GetY() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetY();
}

void Form::ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle){

	std::any_cast<FormImplementation*>(impl_)->ChangeStyle(ex_dwStyle, dwStyle);

}

void Form::ChangePosition(int x, int y) {

	std::any_cast<FormImplementation*>(impl_)->ChangePosition(x, y);

}

