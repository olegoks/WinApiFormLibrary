#include "FormImplementation.hpp"

#include <chrono>
#include <Button.hpp>

FormImplementation::FormImplementation()noexcept(true):
	AbstractComponent::AbstractComponent{} {

	AbstractComponent::ChangeStyle(NULL, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);
	
}

FormImplementation::~FormImplementation() noexcept(true){



}

HWND FormImplementation::GetHandle() const noexcept{

	return AbstractComponent::GetHandle();
}

void FormImplementation::ChangeCaption(const std::wstring& caption){
	
	try {
	
		AbstractComponent::ChangeText(caption);
	
	} catch (const ComponentException&) {

		throw ComponentException{ u8"Form changing size error." };

	}

}

void FormImplementation::Create(const HWND parent_hWnd){
	
	try {

		AbstractComponent::RegisterComponentClass(L"Form");

		if (WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };

		//AbstractComponent::ChangeStyle(ex_dwStyle_, dwStyle_/*WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN*/);
		AbstractComponent::CreateComponent(parent_hWnd);

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Creating form error," };

	}

}

void FormImplementation::Show(int nCmdShow){

	AbstractComponent::ShowComponent(nCmdShow);

}

void FormImplementation::Destroy(){

	AbstractComponent::DestroyComponent();

}


WPARAM FormImplementation::StartMessageLoop()const {

	MSG message{ 0 };

	BOOL no_error = 0;

	while ((no_error = GetMessage(&message, NULL, NULL, NULL)) != 0) {

		TranslateMessage(&message);

		//Call WinProc function and get MSG msg message
		DispatchMessage(&message);

	}

	return message.wParam;

}

void FormImplementation::Run(){
	
	StartMessageLoop();

}


