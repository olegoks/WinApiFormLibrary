#pragma once



#ifndef EDITIMPLEMENTATION_HPP
#define EDITIMPLEMENTATION_HPP

#include <string>
#include <AbstractComponent.hpp>

class EditImplementation : public AbstractComponent {
public:
	
	explicit EditImplementation(){

		try {
		
			AbstractComponent::ChangeStyle(NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | ES_LEFT);
		
		} catch (const ComponentException& exception) {

			throw;

		}

	}

	void Create(const HWND parent_hWnd = NULL)override {

		try {

			AbstractComponent::CreateComponent(parent_hWnd, L"edit");
		
		} catch (const ComponentException& exception) {

			throw;

		}

	}

	void Show(int nCmdShow = SW_SHOW)override {
		
		try {
		
			AbstractComponent::ShowComponent(SW_SHOW);
		
		} catch (const ComponentException& exception) {

			throw;

		}

	}

	std::wstring GetText()const {

		wchar_t text[256];

		int success = GetWindowTextW(AbstractComponent::GetHandle(), text, 256);

		if (!success)
			throw ComponentException{ u8"GetWindowText error." };

		return std::wstring{ text };

	}

	void Destroy()override {

		try {
			
			AbstractComponent::DestroyComponent();

		} catch (const ComponentException& exception) {

			throw;

		}

	}

};

#endif //EDITIMPLEMENTATION_HPP