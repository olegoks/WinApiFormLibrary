#include "Canvas.hpp"
#include "CanvasImplementation.hpp"

Color Canvas::GetDefaultBackgroundColor() const noexcept{

    return CanvasImplementation::kDefaultBackgroundColor;
    
}

void Canvas::Line(int x, int y, int _x, int _y, const Color& color) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->Line(x, y, _x, _y, color);

}

void Canvas::Create(const HWND parent_hWnd) {

    std::any_cast<CanvasImplementation*>(impl_)->Create(parent_hWnd);

}

void Canvas::SetCanvasProc(ProcessMessage process_canvas) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->SetCanvasProc(process_canvas);

}

void Canvas::SetPixel(int x, int y, const Pixel& pixel) noexcept{

    std::any_cast<CanvasImplementation*>(impl_)->SetPixel(x, y, pixel);

}

void Canvas::ChangeSize(const int width, const int height){

    std::any_cast<CanvasImplementation*>(impl_)->ChangeSize(width, height);

}

void Canvas::ChangePosition(const int x, const int y){

    std::any_cast<CanvasImplementation*>(impl_)->ChangePosition(x, y);

}

void Canvas::Fill(const Color& color) noexcept(true){

    std::any_cast<CanvasImplementation*>(impl_)->Fill(color);

}

void Canvas::Show(int nCmdShow){

    std::any_cast<CanvasImplementation*>(impl_)->Show(nCmdShow);

}

void Canvas::Destroy(){

    std::any_cast<CanvasImplementation*>(impl_)->Destroy();

}

Canvas::Canvas(): impl_{ nullptr } {

    try {

        impl_ = new CanvasImplementation{};

    } catch (const std::bad_alloc&) {
    
        throw ComponentException{ u8"Canvas allocation memory error." };

    }

}

void Canvas::Flush(){

    std::any_cast<CanvasImplementation*>(impl_)->Flush();

}
