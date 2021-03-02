#include <CanvasImplementation.hpp>

CanvasImplementation::CanvasImplementation():
	AbstractComponent::AbstractComponent{ },
	buffer_{ nullptr },
	pixels_number_{  GetWidth() * GetHeight() },
	canvas_info_{ 0 },
	device_context_{ NULL }{

	try {

		buffer_ = new Pixel[pixels_number_];

		InitCanvasInfo(GetWidth(), GetHeight());

	} catch (std::bad_alloc& new_exception) {

		throw ComponentException{ std::string{ u8"Bad allocation memory: " }
			+ std::string{ new_exception.what() } };

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Canvas constructor error." };

	}

}

void CanvasImplementation::ChangePosition(const int x, const int y)noexcept(false) {

	try {

		AbstractComponent::ChangePosition(x, y);

	}
	catch (const ComponentException&) {

		throw ComponentException{ u8"Canvas changing position error." };

	}

}

void CanvasImplementation::ChangeSize(const int width, const int height){

	try {

		AbstractComponent::ChangeSize(width, height);

	} catch (const ComponentException&) {
	
		throw ComponentException{ u8"Canvas changing style error." };
	
	}

	InitCanvasInfo(width, height);

}


void CanvasImplementation::Fill(const Color& color)noexcept{

	std::for_each(buffer_, buffer_ + pixels_number_, [&color](Pixel& pixel)noexcept->void {

		pixel = color;

		});

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

	int index = y * AbstractComponent::GetWidth() + x;

	if (0 < index && index <= this->pixels_number_)
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

		AbstractComponent::ChangeStyle(NULL, WS_CHILD | WS_BORDER);
		AbstractComponent::RegisterComponentClass(L"Canvas");
		AbstractComponent::CreateComponent(parent_hWnd);

		Fill(kDefaultBackgroundColor);

	} catch (const ComponentException&) {

		throw ComponentException{ u8"Creating canvas error." };

	}

	device_context_ = GetDC(GetHandle());

	if (device_context_ == NULL)
		throw ComponentException{ u8"GetDC error." };

}

void CanvasImplementation::Show(int nCmdShow) {

	try {

		AbstractComponent::ShowComponent(SW_SHOW);
		Flush();

	}
	catch (const ComponentException&) {

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

void CanvasImplementation::SetCanvasProc(ProcessMessage process_canvas)noexcept(true) {

	AbstractComponent::SetProcessFunction(process_canvas);

}

void CanvasImplementation::ShowFrame(const void* const frame_buffer)noexcept(false) {

	if (!SetDIBitsToDevice(
		device_context_,
		0,
		0,
		GetWidth(),
		GetHeight(),
		0,
		0,
		0,
		GetHeight(),
		frame_buffer,
		&canvas_info_,
		DIB_PAL_COLORS
	)) throw ComponentException{ u8"SetDIBitsToDevice exception." };

}

void CanvasImplementation::InitCanvasInfo(const int width, const int height) noexcept{

	canvas_info_ = CANVASINFO{ 0 };
	canvas_info_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	canvas_info_.bmiHeader.biWidth = width;
	canvas_info_.bmiHeader.biHeight = -(static_cast<int>(height));
	canvas_info_.bmiHeader.biPlanes = 1;
	canvas_info_.bmiHeader.biBitCount = 32;
	canvas_info_.bmiHeader.biCompression = BI_RGB;
	canvas_info_.bmiHeader.biSizeImage = ((width * 24 + 31) & ~31) / 8 * height;

}
