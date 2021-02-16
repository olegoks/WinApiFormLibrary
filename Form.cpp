#include "Library/Form.hpp"
#include "FormImpl.hpp"

Form::Form(const HINSTANCE hInstance) noexcept(true):
	impl_{ nullptr } {

	try {

		impl_ = new FormImpl{ hInstance };

	} catch (const std::bad_alloc& exception) { }

}

Form::~Form()noexcept(true){

	if (std::any_cast<FormImpl*>(impl_) != nullptr)
		delete std::any_cast<FormImpl*>(impl_);
	
}
void Form::Create(const std::wstring& class_name, const HWND parent_hWnd) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Create(class_name, parent_hWnd);

}

void Form::Show(int nCmdShow) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Show(nCmdShow);

}

void Form::Run() noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Run();

}

void Form::Destroy() noexcept(false){

	std::any_cast<FormImpl*>(impl_)->Destroy();

}

void Form::ShowFrame(const void* const frame_buffer, const size_t size) noexcept(false){

	std::any_cast<FormImpl*>(impl_)->ShowFrame(frame_buffer, size);

}

void Form::Caption(const std::wstring& caption) noexcept(true){

	std::any_cast<FormImpl*>(impl_)->Caption(caption);

}

const HWND Form::Handle() const noexcept(true){
	
	return std::any_cast<FormImpl*>(impl_)->Handle();

}

void Form::InitFormProc(FormProc messages_processing) noexcept(true){

	std::any_cast<FormImpl*>(impl_)->InitFormProc(messages_processing);

}

void Form::Size(const size_t width, const size_t height) noexcept(true){

	std::any_cast<FormImpl*>(impl_)->Size(width, height);

}

void Form::Style(DWORD ex_dwStyle, DWORD dwStyle) noexcept(true){

	std::any_cast<FormImpl*>(impl_)->Style(ex_dwStyle, dwStyle);

}

