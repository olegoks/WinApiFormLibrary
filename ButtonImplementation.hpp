#pragma once

#include <filesystem>
#include <AbstractComponent.hpp>

class ButtonImplementation : public AbstractComponent {
private:

	HBITMAP hBitmap_;

public:

	ButtonImplementation():
		AbstractComponent::AbstractComponent{},
		hBitmap_{ NULL }{

		try {

			AbstractComponent::ChangeStyle(NULL, BS_DEFPUSHBUTTON | WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER /*| BS_BITMAP*/);
		
		}
		catch  (const ComponentException&) {

			throw ComponentException{ u8"Set button style exception." };

		}

	}

	void Image(const std::wstring& bitmap_path) {

		hBitmap_ = (HBITMAP)LoadImage(NULL, bitmap_path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

		if (hBitmap_ == NULL)
			throw ComponentException{ u8"LoadImage error." };

		if (WasCreated()) {
		
			DWORD current_style = AbstractComponent::GetStyle();
			DWORD current_ex_style = AbstractComponent::GetExtendedStyle();
			
			try {
			
				AbstractComponent::ChangeStyle(current_ex_style, current_ex_style | BS_BITMAP);
			
			} catch (const ComponentException&) {

				throw ComponentException{ u8"Changing button style for loading image error." };

			}

			SendMessage(GetHandle(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);
		
		}

	}

	void ChangeText(const std::wstring& text) {

		try {
		
			AbstractComponent::ChangeText(text);
		
		} catch (const ComponentException& exception) {

			throw exception;

		}

	}

	void Create(const HWND parent_hWnd = NULL)override {
		
		try {
		
			AbstractComponent::CreateComponent(parent_hWnd, L"Button");
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Creating button error." };

		}

		if (hBitmap_ != NULL)
			SendMessage(AbstractComponent::GetHandle(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap_);

	}

	HWND GetHandle()const noexcept {

		return AbstractComponent::GetHandle();

	}

	void Show(int nCmdShow = SW_SHOWNORMAL)override {

		ShowWindow(AbstractComponent::GetHandle(), nCmdShow);

	}

	void Destroy()override {

		try {
		
			AbstractComponent::DestroyComponent();
		
		} catch (const ComponentException&) {

			throw ComponentException{ u8"Destroying button error." };

		}

	}

};