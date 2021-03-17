#include <CanvasImplementation.hpp>

CanvasImplementation::CanvasImplementation():
	AbstractComponent::AbstractComponent{ },
	canvas_info_{ 0 },
	device_context_{ NULL },
	buffer_width_{ 0 },
	buffer_height_{ 0 },
	pixels_number_{ 0 },
	buffer_{ nullptr } {

	//try {

	//	buffer_ = new Pixel[pixels_number_];

	//	ChangeCanvasInfo(buffer_width_, buffer_height_);

	//} catch (std::bad_alloc& new_exception) {

	//	throw ComponentException{ std::string{ u8"Bad allocation memory: " }
	//		+ std::string{ new_exception.what() } };

	//} catch (const ComponentException&) {

	//	throw ComponentException{ u8"Canvas constructor error." };

	//}

}

void CanvasImplementation::ChangePosition(const int x, const int y)noexcept(false) {

	try {

		AbstractComponent::ChangePosition(x, y);

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Canvas changing position error." };

	}

}

void CanvasImplementation::Fill(const Color& color)noexcept{

	std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

		pixel = color;

		});

}

const uint64_t CanvasImplementation::GetWidth() const noexcept{

	return AbstractComponent::GetWidth();
}

const uint64_t CanvasImplementation::GetHeight() const noexcept{

	return AbstractComponent::GetHeight();
}

const uint64_t CanvasImplementation::GetX() const noexcept
{
	return AbstractComponent::GetX();
}

const uint64_t CanvasImplementation::GetY() const noexcept
{
	return AbstractComponent::GetY();
}

void CanvasImplementation::SolidRectangle(const uint64_t x, const uint64_t y, const uint64_t width, const uint64_t height, const Color& fill_color){


	//...


}

void CanvasImplementation::Line(int x, int y, int _x, int _y, const Color& color)noexcept {

	const int deltaX = abs(_x - x);
	const int deltaY = abs(_y - y);
	const int signX = x < _x ? 1 : -1;
	const int signY = y < _y ? 1 : -1;

	int error = deltaX - deltaY;

	SetPixel(x, y, color);

	while (x != _x || y != _y) {

		const int error2 = error * 2;

		SetPixel(x, y, color);

		if (error2 > -deltaY) {

			error -= deltaY;
			x += signX;

		}

		if (error2 < deltaX) {

			error += deltaX;
			y += signY;

		}

	}

}

void CanvasImplementation::SetPixel(int x, int y, const Pixel& pixel)noexcept {

	int index = y * buffer_width_+ x;

	if (0 < x && x < buffer_width_ && 0 < y && y < buffer_height_)
		buffer_[index] = pixel;

}

void CanvasImplementation::Flush() {

	try {

		ShowFrame(buffer_);

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Canvas show error." };

	}

}

void CanvasImplementation::Create(const HWND parent_hWnd) {

	try {

		AbstractComponent::ChangeStyle(NULL, WS_CHILD | WS_THICKFRAME);
		AbstractComponent::RegisterComponentClass(L"Canvas");
		AbstractComponent::CreateComponent(parent_hWnd);
		
		const std::uint64_t new_buffer_width = AbstractComponent::GetClientWidth();
		const std::uint64_t	new_buffer_height = AbstractComponent::GetClientHeight();

		device_context_ = GetDC(GetHandle());

		if (device_context_ == NULL)
			throw ComponentException{ u8"GetDC error." };

		ChangeBufferSize(new_buffer_width, new_buffer_height);
		ChangeCanvasInfo(new_buffer_width, new_buffer_height);

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Creating canvas error." };

	}

}

void CanvasImplementation::Show(int nCmdShow) {

	try {

		AbstractComponent::ShowComponent(SW_SHOW);
		Flush();

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Canvas show error." };

	}

}

void CanvasImplementation::Destroy(){
	
	try {
	
		AbstractComponent::DestroyComponent();
	
	} catch (const ComponentException&) {

		throw ComponentException{ u8"Destroy component error." };

	}

}

void CanvasImplementation::ChangeSize(const int width, const int height) {

	AbstractComponent::ChangeSize(width, height);

}

void CanvasImplementation::ChangeBufferSize(const uint64_t new_width, const uint64_t new_height) {

	Pixel* new_buffer = nullptr;

	try {

		const uint64_t new_pixels_number = (uint64_t)new_width * (uint64_t)new_height;
		new_buffer = new Pixel[new_pixels_number];
		std::fill(new_buffer, new_buffer + new_pixels_number, kDefaultBackgroundColor);

		const uint64_t previos_width = buffer_width_;
		const uint64_t previos_height = buffer_height_;

		//Copy current canvas content to new buffer
		const uint64_t nLinesToCopy = (previos_height < new_height) ? (previos_height) : (new_height);
		const uint64_t nLineWidthToCopy = (previos_width < new_width) ? (previos_width) : (new_width);

		uint64_t new_buffer_offset = 0;
		uint64_t previos_buffer_offset = 0;

		for (uint64_t nLine = 0; nLine < nLinesToCopy; ++nLine) {

			std::memcpy(new_buffer + new_buffer_offset, buffer_ + previos_buffer_offset, nLineWidthToCopy * sizeof Pixel);
			previos_buffer_offset += previos_width;
			new_buffer_offset += new_width;

		}

		delete[] buffer_;
		buffer_ = new_buffer;
		buffer_width_ = new_width;
		buffer_height_ = new_height;
		pixels_number_ = (int)new_pixels_number;

	} catch (const std::bad_alloc& bad_alloc) {

		throw ComponentException{ u8"Bad memory allocation error." };

	} catch (const ComponentException&) {

		delete[] new_buffer;

		throw ComponentException{ u8"Canvas changing style error." };

	}

}

void CanvasImplementation::SetCanvasProc(ProcessMessage process_canvas)noexcept(true) {

	AbstractComponent::SetProcessFunction([this, process_canvas](Message& message)noexcept->bool {

		if (message.GetAction() == Action::Resized) {

			const std::uint64_t new_buffer_width = AbstractComponent::GetClientWidth();
			const std::uint64_t new_buffer_height = AbstractComponent::GetClientHeight();

			ChangeBufferSize(new_buffer_width, new_buffer_height);
			ChangeCanvasInfo(new_buffer_width, new_buffer_height);

		}
		if (message.GetAction() == Action::Repaint) {

			//Исключаю клиентскую область из региона обновления экрана.
			//Если это не сделать сообщение WM_PAINT будет отправляться до вызова PaintBegin/PaintEnd.
			ValidateRect(AbstractComponent::GetHandle(), NULL);

		}

		return process_canvas(message);
		 
		});

}

void CanvasImplementation::ShowFrame(const void* const frame_buffer)noexcept(false) {

	if (!SetDIBitsToDevice(
		device_context_,
		0,
		0,
		buffer_width_,
		buffer_height_,
		0,
		0,
		0,
		buffer_height_,
		frame_buffer,
		&canvas_info_,
		DIB_PAL_COLORS
	)) throw ComponentException{ u8"SetDIBitsToDevice exception." };

}

void CanvasImplementation::ChangeCanvasInfo(const int width, const int height) noexcept{

	canvas_info_ = CANVASINFO{ 0 };
	canvas_info_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	canvas_info_.bmiHeader.biWidth = width;
	canvas_info_.bmiHeader.biHeight = -(static_cast<int>(height));
	canvas_info_.bmiHeader.biPlanes = 1;
	canvas_info_.bmiHeader.biBitCount = 32;
	canvas_info_.bmiHeader.biCompression = BI_RGB;
	canvas_info_.bmiHeader.biSizeImage = ((width * 24 + 31) & ~31) / 8 * height;

}


