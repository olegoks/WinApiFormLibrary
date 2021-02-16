#include "FormImpl.hpp"
#include <chrono>

//Form constants
const std::wstring FormImpl::kDefaultTitle{ L"Default Form title" };
const std::size_t  FormImpl::kDefaultWidth{ 1920 };
const std::size_t  FormImpl::kDefaultHeight{ 1080 };
const std::size_t  FormImpl::kDefaultX{ 0 };
const std::size_t  FormImpl::kDefaultY{ 0 };
const std::wstring FormImpl::kClassName{ L"Main Form class name." };
const DWORD		   FormImpl::kDefaultStyle{ WS_OVERLAPPEDWINDOW };
const DWORD		   FormImpl::kDefaultExStyle{ WS_EX_TOPMOST };

const FormProc	   kDefaultFormProc{ [](Message& message)->bool { return false; } };

FormImpl::FormImpl(const HINSTANCE hInstance)noexcept(true):
	hInstance_{ hInstance },
	parent_hWnd_{ NULL },
	params_{ },
	device_context_{ NULL },
	frame_info_{ 0 },
	self_hWnd_{ NULL },
	form_proc_{ kDefaultFormProc }{

}

void FormImpl::InitFrameInfo(const size_t width, const size_t height) noexcept(true){

	frame_info_ = BITMAPINFO{ 0 };
	frame_info_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	frame_info_.bmiHeader.biWidth = width;
	frame_info_.bmiHeader.biHeight = -(static_cast<int>(height));
	frame_info_.bmiHeader.biPlanes = 1;
	frame_info_.bmiHeader.biBitCount = 32;
	frame_info_.bmiHeader.biCompression = BI_RGB;
	frame_info_.bmiHeader.biSizeImage = ((width * 24 + 31) & ~31) / 8 * height;

}

LRESULT CALLBACK FormImpl::WndProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam) {

	FormImpl* this_form = nullptr;

	if (message == WM_CREATE) {

		#ifdef _M_X64
			#define BindPointerToForm SetWindowLongPtr
			using PointerType = LONG_PTR;
			using ValueType = LONG_PTR;
		#else
			#define BindPointerToForm SetFormLong
			using PointerType = LONG;
			using ValueType = LONG;
		#endif

		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
		this_form = (FormImpl*)lpcs->lpCreateParams;
		this_form->self_hWnd_ = hWnd;
		SetLastError(NULL);
		int last_value = BindPointerToForm(hWnd, GWLP_USERDATA, reinterpret_cast<PointerType>(this_form));

		//Pointer linked to the Form
		//SetFormLongPtr return previous value or zero, if error, but if last value is 0, we should check last error

		if (last_value == 0) {

			DWORD error = GetLastError();

			if (error != 0)
				return 0;

		}

	}

	this_form = reinterpret_cast<FormImpl* const>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	if (this_form != nullptr) {
	
		KeyAction key_action{ message, wParam, lParam };

		bool mouse_message = (key_action.action_ == Action::MouseMove
			|| key_action.action_ == Action::LMouseDown
			|| key_action.action_ == Action::LMouseUp
			|| key_action.action_ == Action::RMouseDown
			|| key_action.action_ == Action::RMouseUp);

		Message message{};

		if (mouse_message)
			message = Message{ key_action, GET_X_LPARAM(lParam),  GET_Y_LPARAM(lParam) };
		else
			message = Message{ key_action };

		bool message_processed = this_form->form_proc_(message);

		if (message_processed)
			return LRESULT{ 0 };
	
	}

	switch (message) {

	case WM_COMMAND: { 

		
		break; 
	}
	case WM_CLOSE: { DestroyWindow(hWnd);break; }

	case WM_DESTROY: { PostQuitMessage(0);break; }
		
	default: return DefWindowProc(hWnd, message, wParam, lParam); 
		
	}

}
		
FormImpl::~FormImpl() {}

const HWND FormImpl::Handle() const noexcept(true){

	return self_hWnd_;

}

void FormImpl::InitFormProc(FormProc messages_processing) noexcept(true){

	form_proc_ = messages_processing;

}

void FormImpl::Caption(const std::wstring& caption)noexcept(true){

	SetWindowText(self_hWnd_, caption.c_str());
}

void FormImpl::Size(const size_t width, const size_t height) noexcept(true){

	params_.width_ = width;
	params_.height_ = height;

	SetWindowPos(self_hWnd_, NULL, params_.x_, params_.y_, width, height, SWP_NOZORDER);
	InitFrameInfo(width, height);

}

void FormImpl::Style(DWORD ex_dwStyle, DWORD dwStyle) noexcept(true){

	params_.ex_dwStyle_ = ex_dwStyle;
	params_.dwStyle_ = dwStyle;

	if (self_hWnd_ != NULL)
		SetWindowLongPtr(self_hWnd_, GWL_STYLE, static_cast<LONG_PTR>(params_.dwStyle_));

}

void FormImpl::RegisterFormClass(const std::wstring& class_name)noexcept(false) {

	params_.sz_class_name_ = class_name;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = NULL;//CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 4;
	wc.hInstance = hInstance_;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = params_.sz_class_name_.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		throw FormExcep{ u8"RegisterClass exception." };

}

void FormImpl::Create(const std::wstring& class_name, const HWND parent_hWnd)noexcept(false){
	
	FormImpl::RegisterFormClass(class_name);
	this->parent_hWnd_ = parent_hWnd;

	//Creating Form with default//installed parametrs
	self_hWnd_ = CreateWindowEx(params_.ex_dwStyle_, 
		params_.sz_class_name_.c_str(),
		params_.title_.c_str(),
		params_.dwStyle_,
		params_.x_,
		params_.y_,
		params_.width_,
		params_.height_,
		parent_hWnd,
		HMENU(NULL),
		(HINSTANCE)hInstance_,
		this);

	if (!self_hWnd_) throw FormExcep{ u8"CreateWindowEx exception." };
	else {

		SetProcessDPIAware();//Вызывая эту функцию (SetProcessDPIAware), вы сообщаете системе, что интерфейс вашего приложения умеет сам правильно масштабироваться при высоких значениях DPI (точки на дюйм). Если вы не выставите этот флаг, то интерфейс вашего приложения может выглядеть размыто при высоких значениях DPI.
		device_context_ = GetDC(self_hWnd_);

	}

}

void FormImpl::Show(int nCmdShow) noexcept(false){

	/*if (!*/ShowWindow(self_hWnd_, nCmdShow);//)
		//throw FormExcep{ u8"ShowWindow exception." };

}

WPARAM FormImpl::StartMessageLoop()const noexcept(true) {

	MSG msg{ 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;

}

void FormImpl::Destroy() noexcept(true){

	SendMessage(self_hWnd_, WM_CLOSE, NULL, NULL);

}

void FormImpl::Run()noexcept(false){
	
	StartMessageLoop();

}


void FormImpl::ShowFrame(const void* const frame_buffer, const size_t size)noexcept(false) {

	if (!SetDIBitsToDevice(
		FormImpl::device_context_,
		0,
		0,
		FormImpl::params_.width_,
		FormImpl::params_.height_,
		0,
		0,
		0,
		FormImpl::params_.height_,
		frame_buffer,
		&frame_info_,
		DIB_PAL_COLORS
	)) throw FormExcep{ u8"SetDIBitsToDevice exception." };

}
