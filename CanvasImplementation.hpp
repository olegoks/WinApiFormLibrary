#pragma once

#include <algorithm>
#include <Message.hpp>
#include <Pixel.hpp>
#include <AbstractComponent.hpp>

using CANVASINFO = BITMAPINFO;

class CanvasImplementation : private AbstractComponent{
private:

	CANVASINFO canvas_info_;
	HDC device_context_;
	std::uint64_t buffer_width_;
	std::uint64_t buffer_height_;
	std::uint64_t pixels_number_;
	Pixel* buffer_;

private:

	void ChangeCanvasInfo(const int width, const int height)noexcept;
	void ShowFrame(const void* const frame);
	void ChangeBufferSize(const uint64_t new_width, const uint64_t new_height);

public:

	static inline const Color kDefaultBackgroundColor = Color{ 255, 255, 255 };
	const uint64_t GetWidth()const noexcept;
	const uint64_t GetHeight()const noexcept;
	const uint64_t GetX()const noexcept;
	const uint64_t GetY()const noexcept;
	void SolidRectangle(const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height, const Color& fill_color);
	void Line(int x, int y, int _x, int _y, const Color& color)noexcept;
	void Create(const HWND parent_hWnd)noexcept(false)override;
	void SetCanvasProc(ProcessMessage process_canvas)noexcept;
	void SetPixel(int x, int y, const Pixel& pixel)noexcept;
	void ChangeSize(const int width, const int height);
	void ChangePosition(const int x, const int y);
	void Fill(const Color& color)noexcept(true);
	void Show(int nCmdShow)override;
	void Destroy()override;
	explicit CanvasImplementation();
	void Flush();
	
};