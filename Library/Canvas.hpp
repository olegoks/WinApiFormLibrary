#pragma once

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <any>
#include <FormTypes.hpp>

EXPIMP class Canvas {
private:

	std::any impl_;

public:

	EXPIMP explicit Canvas();

	EXPIMP Color GetDefaultBackgroundColor()const noexcept;
	EXPIMP void Line(int x, int y, int _x, int _y, const Color& color)noexcept;
	EXPIMP void Create(const HWND parent_hWnd);
	EXPIMP void SetCanvasProc(ProcessMessage process_canvas)noexcept;
	EXPIMP void SetPixel(int x, int y, const Pixel& pixel)noexcept;
	EXPIMP void ChangeSize(const int width, const int height);
	EXPIMP void ChangePosition(const int x, const int y);
	EXPIMP void Fill(const Color& color)noexcept(true);
	EXPIMP void Show(int nCmdShow);
	EXPIMP void Destroy();
	EXPIMP void Flush();

};

#endif //CANVAS_HPP