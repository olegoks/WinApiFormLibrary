#pragma once
#ifndef WINDOW_TYPES_HPP
#define WINDOW_TYPES_HPP

#include <windows.h>
#include <functional>

#define CALLBACK __stdcall

#define COMPILING_DLL

#ifdef COMPILING_DLL
#define EXPIMP __declspec(dllexport)
#else
#define EXPIMP __declspec(dllimport)
#endif

	enum class Key : uint32_t {

		Nothing = 0,
		ArrowLeft,
		ArrowRight,
		ArrowUp,
		ArrowDown,
		WheelDown,
		WheelUp,
		MouseLeft,
		MouseRight,
		A,
		S,
		D,
		W

	};

	enum class Action : unsigned int {

		Nothing = 0,
		KeyDown,
		KeyUp,
		MouseMove,
		LMouseDown,
		LMouseUp,
		RMouseDown,
		RMouseUp

	};

	class Coordinats final {

	};

	class KeyAction final {
	public:

		Key key_;
		Action action_;

		UINT message_;
		WPARAM wParam_;
		LPARAM lParam_;

		explicit KeyAction(UINT Message, WPARAM wParam, LPARAM lParam)noexcept(true);

		explicit KeyAction()noexcept(true);

		explicit KeyAction(Key key, Action action)noexcept(true);

		bool operator !=(const KeyAction& key_action)noexcept(true);

	};

	struct Message {

		KeyAction key_type;
		int x_;
		int y_;


		explicit Message()noexcept(true);

		explicit Message(KeyAction key, const int x = 0, const int y = 0)noexcept(true);

		bool IsUsefull()const noexcept(true) {

			return key_type.action_ != Action::Nothing;

		}

		int X()const noexcept(true) { return x_; }
		int Y()const noexcept(true) { return y_; }

	};


	class FormExcep final {
	private:

		std::string_view error_message_;

	public:

		explicit FormExcep(const char* const message)noexcept(true) :
			error_message_{ message } {


		}

		const std::string_view& What()const noexcept(true) { return error_message_; };

	};

	using FormProc = std::function<bool(Message&)>;

	class Pixel final {
	public:

		explicit Pixel(unsigned char r, unsigned char g, unsigned char b)noexcept(true) :
			rgba_{ 0 } {

			rgba_.r = r;
			rgba_.g = g;
			rgba_.b = b;

		}

		explicit Pixel()noexcept(true) :
			Pixel{ 0, 0, 0 } {

		}

		union rgba {

			unsigned char bgra[4];
			
			struct {
				
				unsigned char b;
				unsigned char g;
				unsigned char r;
				unsigned char a;

			};

		};

		rgba rgba_ = { 0 };

	};

#endif //WINDOW_TYPES_HPP