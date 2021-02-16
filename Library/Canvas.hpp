#pragma once

#include <algorithm>
#include "Form.hpp"

using Color = Pixel;

EXPIMP class Canvas final : protected Form{

private:

	Pixel* buffer_;
	int width_;
	int height_;
	int pixels_number_;

public:

	EXPIMP explicit Canvas(const HINSTANCE hInstance, const int width, const int height, const Color& color = Color{ 255, 255, 255 })noexcept(true) :
		Form::Form{ hInstance },
		buffer_{ nullptr },
		width_{ width },
		height_{ height },
		pixels_number_{ width_ * height_ }{

		Form::Size(width, height);

		try {
		
			buffer_ = new Pixel[pixels_number_];

			std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

				pixel = color;

				});
		
		} catch (const std::bad_alloc&) {  }

	}

	EXPIMP void Line(int x, int y, int _x, int _y, const Color& color)noexcept(true) {

		const int deltaX = abs(_x - x);
		const int deltaY = abs(_y - y);
		const int signX = x < _x ? 1 : -1;
		const int signY = y < _y ? 1 : -1;

		int error = deltaX - deltaY;

		buffer_[width_ * _y + _x] = color;

		while (x != _x || y != _y){

			const int error2 = error * 2;

			SetPixel(x, y, color);

			if (error2 > - deltaY){

				error -= deltaY;
				x += signX;

			}

			if (error2 < deltaX){

				error += deltaX;
				y += signY;

			}

		}

		Canvas::Flush();

	}


	EXPIMP void SetPixel(int x, int y, const Pixel& pixel)noexcept(false) {

		if (buffer_ == nullptr) throw FormExcep{ u8"Bad allocation exception." };

		int index = y * width_ + x;

		if (index > 0 && index < pixels_number_)
			buffer_[index] = pixel;
		
	}

	EXPIMP void Flush()noexcept(true) {

		ShowFrame(buffer_, pixels_number_);

	}

	EXPIMP void Create(const HWND parent_hWnd)noexcept(false) {

		Form::Style(WS_EX_DLGMODALFRAME, WS_CHILD | WS_BORDER);
		Form::Create(L"Canvas", parent_hWnd);

	}

	EXPIMP void Show(int nCmdShow)noexcept(false) {

		Form::Show(SW_SHOW);
			
	}

	EXPIMP void InitCanvasProc(FormProc process_canvas)noexcept(true) {

		Form::InitFormProc(process_canvas);

	}

};