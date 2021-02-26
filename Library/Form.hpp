#pragma once
#ifndef WINDOW_INTERFACE_HPP
#define WINDOW_INTERFACE_HPP

#include <windows.h>
#include <any>

#include "FormTypes.hpp"

EXPIMP class Form{
private:

	std::any impl_;

public:

	EXPIMP explicit Form()noexcept(true);
	EXPIMP ~Form()noexcept(true);

protected:

	EXPIMP void Create(const HWND parent_hWnd = NULL);
	EXPIMP void Show(int nCmdShow);
	EXPIMP void Run();
	EXPIMP void Destroy();

public:

	EXPIMP void ChangeCaption(const std::wstring& caption)noexcept(false);
	EXPIMP const HWND GetHandle()const noexcept(true);
	EXPIMP void SetProcessFunction(ProcessMessage messages_processing)noexcept(true);
	EXPIMP void ChangeSize(const size_t width, const size_t height)noexcept(false);
	EXPIMP int GetWidth()const noexcept(true);
	EXPIMP int GetHeight()const noexcept(true);
	EXPIMP int GetX()const noexcept(true);
	EXPIMP int GetY()const noexcept(true);

	EXPIMP void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle)noexcept(false);
	EXPIMP void ChangePosition(int x, int y)noexcept(false);

};

#endif //WINDOW_INTERFACE_HPP