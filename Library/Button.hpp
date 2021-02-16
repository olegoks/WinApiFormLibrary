#pragma once

#include "FormTypes.hpp"

EXPIMP class Button final {
private:
	
	static const std::wstring kDefaultText;

	const HINSTANCE hInstance_;
	HWND self_hWnd_;
	HWND parent_hWnd_;
	std::wstring text_;
	int pos_x_;
	int pos_y_;
	int width_;
	int height_;
	FormProc proc_;

public:

	EXPIMP explicit Button(const HINSTANCE hInstance)noexcept(true):
		hInstance_{ hInstance },
		self_hWnd_{ NULL },
		parent_hWnd_{ NULL },
		pos_x_{ 0 },
		pos_y_{ 0 },
		width_{ 100 },
		height_{ 30 },
		proc_{ [](Message& message)noexcept->bool { return false; } }{

	}

	EXPIMP void Create(const HWND parent_hWnd, const std::wstring text = kDefaultText)noexcept(false) {

		self_hWnd_ = CreateWindow(L"Button", text.c_str(), BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_BORDER,
			pos_x_, pos_y_, width_, height_,
			parent_hWnd, NULL, hInstance_, NULL);

		if (self_hWnd_ == NULL)
			throw FormExcep{ u8"Creating button exception." };
		
		#ifdef _M_X64
			#define BindPointerToForm SetWindowLongPtr
			using PointerType = LONG_PTR;
			using ValueType = LONG_PTR;	
		#else
			#define BindPointerToForm SetFormLong
			using PointerType = LONG;
			using ValueType = LONG;
		#endif

		BindPointerToForm(self_hWnd_, GWLP_USERDATA, reinterpret_cast<PointerType>(this));

	}

	EXPIMP void Show()noexcept(false) {

		ShowWindow(self_hWnd_, SW_SHOWNORMAL);

	}

	EXPIMP void InitButtonProc(FormProc process_messages)noexcept(true) {

		proc_ = process_messages;

	}

};