#pragma once

#include <algorithm>
#include "Form.hpp"

using Color = Pixel;

EXPIMP class Canvas final : protected Form{

private:

	static inline const Color kDefaultColor = Color{ 255, 255, 255 };
	static inline const int kDefaultWidth = 600;
	static inline const int kDefaultHeight = 300;

	Pixel* buffer_;
	int width_;
	int height_;
	int pixels_number_;

public:

	EXPIMP explicit Canvas(const HINSTANCE hInstance, const int x, const int y, const int width, const int height)noexcept(false) :
		Form::Form{ hInstance },
		buffer_{ nullptr },
		width_{ width },
		height_{ height },
		pixels_number_{ width_ * height_ }{

		Form::Size(width_, height_);

		try {

			buffer_ = new Pixel[pixels_number_];

		} catch (std::bad_alloc& new_exception) {

			throw FormExcep{ std::string{ u8"Bad allocation memory: " }
				+ std::string{ new_exception.what() } };

		}


	}

	EXPIMP void Position(const int x, const int y)noexcept(true) {

		Form::Position(x, y);

	}

	EXPIMP void Fill(const Color& color)noexcept(true) {

		std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

			pixel = color;

			});

	}

	EXPIMP void Line(int x, int y, int _x, int _y, const Color& color)noexcept(true) {

		const int deltaX = abs(_x - x);
		const int deltaY = abs(_y - y);
		const int signX = x < _x ? 1 : -1;
		const int signY = y < _y ? 1 : -1;

		int error = deltaX - deltaY;

		SetPixel(x, y, color);

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

	}

	EXPIMP void SetPixel(int x, int y, const Pixel& pixel)noexcept(false) {

		int index = y * width_ + x;

		if(0 < index && index <= this->pixels_number_)
			buffer_[index] = pixel;

	}

	EXPIMP void Flush()noexcept(false) {

		ShowFrame(buffer_);

	}

	EXPIMP void Create(const HWND parent_hWnd)noexcept(false) {

		Form::Style(WS_EX_DLGMODALFRAME, WS_CHILD | WS_BORDER);
		Form::Create(L"Canvas", parent_hWnd);		
		Canvas::Fill(kDefaultColor);

	}

	EXPIMP void Show(int nCmdShow)noexcept(false) {

		Form::Show(SW_SHOW);
			
	}

	EXPIMP void InitCanvasProc(FormProc process_canvas)noexcept(true) {

		Form::InitFormProc(process_canvas);

	}

};