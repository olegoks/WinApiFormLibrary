#include "Library/Form.hpp"
#include "FormImplementation.hpp"

EXPIMP Form::Form() noexcept(true):
	impl_{ nullptr } {

	try {

		impl_ = new FormImplementation{};

	} catch (const std::bad_alloc& exception) { }

}

EXPIMP Form::~Form()noexcept(true){

	if (std::any_cast<FormImplementation*>(impl_) != nullptr)
		delete std::any_cast<FormImplementation*>(impl_);
	
}
EXPIMP void Form::Create(const HWND parent_hWnd){

	std::any_cast<FormImplementation*>(impl_)->Create(parent_hWnd);

}

EXPIMP void Form::Show(int nCmdShow){

	std::any_cast<FormImplementation*>(impl_)->Show(nCmdShow);

}

EXPIMP void Form::Run() noexcept(false){

	std::any_cast<FormImplementation*>(impl_)->Run();

}

EXPIMP void Form::Destroy() noexcept(false){

	std::any_cast<FormImplementation*>(impl_)->Destroy();

}

EXPIMP void Form::ChangeCaption(const std::wstring& caption){

	std::any_cast<FormImplementation*>(impl_)->ChangeCaption(caption);

}

EXPIMP const HWND Form::GetHandle() const noexcept{
	
	return std::any_cast<FormImplementation*>(impl_)->GetHandle();

}


EXPIMP void Form::SetProcessFunction(ProcessMessage messages_processing) noexcept{

	std::any_cast<FormImplementation*>(impl_)->SetProcessFunction(messages_processing);

}

EXPIMP void Form::ChangeSize(const size_t width, const size_t height){

	std::any_cast<FormImplementation*>(impl_)->ChangeSize(width, height);

}

EXPIMP int Form::GetWidth() const noexcept{

	return std::any_cast<FormImplementation*>(impl_)->GetWidth();
}

EXPIMP int Form::GetHeight() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetHeight();
}

EXPIMP int Form::GetX() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetX();
}

EXPIMP int Form::GetY() const noexcept
{
	return std::any_cast<FormImplementation*>(impl_)->GetY();
}

void Form::ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle){

	std::any_cast<FormImplementation*>(impl_)->ChangeStyle(ex_dwStyle, dwStyle);

}

EXPIMP void Form::ChangePosition(int x, int y) {

	std::any_cast<FormImplementation*>(impl_)->ChangePosition(x, y);

}

