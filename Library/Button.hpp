#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <any>
#include <FormTypes.hpp>

EXPIMP class Button {
private:

	std::any impl_;

public:

	EXPIMP explicit Button();
	EXPIMP ~Button()noexcept;

public:

	EXPIMP void SetProcessFunction(ProcessMessage messages_processing)noexcept;
	EXPIMP void ChangeSize(const size_t width, const size_t height);
	EXPIMP void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle);
	EXPIMP void ChangePosition(const int x, const int y);
	EXPIMP bool WasCreated()const noexcept;

	EXPIMP int GetHeight()const noexcept;
	EXPIMP int GetWidth()const noexcept;
	EXPIMP int GetX()const noexcept;
	EXPIMP int GetY()const noexcept;

	EXPIMP void Image(const std::wstring& bitmap_path);
	EXPIMP void ChangeText(const std::wstring& text);
	EXPIMP void Create(const HWND parent_hWnd = NULL);
	EXPIMP void Show(int nCmdShow = SW_SHOWNORMAL);
	EXPIMP void Destroy();

};

#endif //BUTTON_HPP