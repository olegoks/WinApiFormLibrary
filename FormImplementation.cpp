#include "FormImplementation.hpp"

#include <chrono>
#include <Button.hpp>

FormImplementation::FormImplementation()noexcept(true):
	AbstractComponent::AbstractComponent{} {

	AbstractComponent::ChangeStyle(NULL, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);
	
}

FormImplementation::~FormImplementation() noexcept(true){



}

//LRESULT CALLBACK FormImplementation::WndProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam)noexcept(false) {
//
//	if (message == WM_CREATE) {
//
//		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
//		FormImplementation* this_form = (FormImplementation*)lpcs->lpCreateParams;
//		this_form->self_hWnd_ = hWnd;
//		SetLastError(NULL);
//		int last_value = BindPointerToForm(hWnd, GWLP_USERDATA, reinterpret_cast<PointerType>(this_form));
//
//		if (last_value == 0) {
//
//			DWORD error = GetLastError();
//
//			if (error != 0)
//				throw FormExcep{ u8"BindPointerToWindow error." };
//		}
//		else
//			throw FormExcep{ u8"BindPointerToWindow error." };
//
//	}
//
//	bool message_processed = false;
//	Message mes{ message, wParam, lParam };
//
//	if (message == WM_COMMAND) {
//		
//		LONG_PTR ptr = GetWindowLongPtr(HWND(lParam), GWLP_USERDATA);
//		Button* this_button = reinterpret_cast<Button* const>(ptr);
//		
//		if (ptr != NULL)
//			message_processed = this_button->proc_(mes);
//	
//	} else {
//
//		LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
//		FormImplementation* this_form = reinterpret_cast<FormImplementation* const>(ptr);
//
//		if (ptr != NULL)
//			message_processed = this_form->form_proc_(mes);
//		
//	}
//
//	if (message_processed)
//		return LRESULT{ 0 };
//
//	switch (message) {
//
//	case WM_CLOSE: { DestroyWindow(hWnd);break; }
//	case WM_DESTROY: { PostQuitMessage(0);break; }
//	default: return DefWindowProc(hWnd, message, wParam, lParam); 
//		
//	}
//
//}
		
//FormImplementation::~FormImplementation()noexcept(true) {
//
//
//}
//
//const HWND FormImplementation::Handle() const noexcept(true){
//
//	return self_hWnd_;
//
//}
//
//void FormImplementation::InitFormProc(FormProc messages_processing) noexcept(true){
//
//	form_proc_ = messages_processing;
//
//}
//
//#include <string>
//#include <iostream>
//
//void FormImplementation::Position(const int x, const int y) noexcept(false){
//
//	if (WasCreated()) {
//	
//		BOOL success = SetWindowPos(self_hWnd_, NULL, x, y, params_.width_, params_.height_, NULL);
//		
//		if (!success) 
//			throw FormExcep{ u8"SetWindowPos error." };
//
//	}
//	
//	params_.x_ = x;
//	params_.y_ = y;
//
//}
//
//void FormImplementation::Caption(const std::wstring& caption)noexcept(false){
//
//	if (WasCreated()) {
//	
//		BOOL success = SetWindowText(self_hWnd_, caption.c_str());
//		
//		if (!success) 
//			throw FormExcep{ u8"SetWindowText error." };
//
//	}
//
//	params_.title_ = caption;
//
//}
//
//void FormImplementation::Size(const size_t width, const size_t height) noexcept(false){
//
//	if (WasCreated()) {
//
//		BOOL success = SetWindowPos(self_hWnd_, NULL, params_.x_, params_.y_, width, height, SWP_NOZORDER);
//		
//		if (!success) 
//			throw FormExcep{ u8"SetWindowPos error." };
//
//	}
//	
//	params_.width_ = width;
//	params_.height_ = height;
//
//	InitFrameInfo(width, height);
//
//}
//
//int FormImplementation::Width() const noexcept(true){
//
//	return params_.width_;
//}
//
//int FormImplementation::Height() const noexcept(true){
//
//	return params_.height_;
//}
//
//int FormImplementation::X() const noexcept(true){
//
//	return params_.x_;
//}
//
//int FormImplementation::Y() const noexcept(true){
//
//	return params_.y_;
//}
//
//void FormImplementation::Style(DWORD ex_dwStyle, DWORD dwStyle) noexcept(false){
//
//	if (WasCreated()) {
//	
//		BOOL success = SetWindowLongPtr(self_hWnd_, GWL_STYLE, static_cast<LONG_PTR>(params_.dwStyle_));
//		
//		if (!success) 
//			throw FormExcep{ u8"Changing form style error." };
//	
//	}
//
//	params_.ex_dwStyle_ = ex_dwStyle;
//	params_.dwStyle_ = dwStyle;
//
//}
//
//bool FormImplementation::WasCreated() const noexcept(true){
//
//	return self_hWnd_ != NULL;
//}
//
//void FormImplementation::RegisterFormClass(const std::wstring& class_name)noexcept(false) {
//
//	params_.sz_class_name_ = class_name;
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(wc);
//	wc.style = NULL;//CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = this->WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 4;
//	wc.hInstance = hInstance_;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = params_.sz_class_name_.c_str();
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	if (!RegisterClassEx(&wc))
//		throw FormExcep{ u8"RegisterClass error." };
//
//}

HWND FormImplementation::GetHandle() const noexcept{

	return AbstractComponent::GetHandle();
}

void FormImplementation::ChangeCaption(const std::wstring& caption){
	
	try {
	
		AbstractComponent::ChangeText(caption);
	
	} catch (const ComponentException& exception) {

		throw;

	}

}

void FormImplementation::Create(const HWND parent_hWnd){
	
	try {

		AbstractComponent::RegisterComponentClass(L"Form");

		if (WasCreated()) throw ComponentException{ u8"CreateWindowEx error." };

		//AbstractComponent::ChangeStyle(ex_dwStyle_, dwStyle_/*WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN*/);
		AbstractComponent::CreateComponent(parent_hWnd);

	} catch (const ComponentException& exception) {

		throw;

	}

}

void FormImplementation::Show(int nCmdShow){

	AbstractComponent::ShowComponent(nCmdShow);

}

void FormImplementation::Destroy(){

	AbstractComponent::DestroyComponent();

}


WPARAM FormImplementation::StartMessageLoop()const {

	MSG msg{ 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;

}

void FormImplementation::Run(){
	
	StartMessageLoop();

}


