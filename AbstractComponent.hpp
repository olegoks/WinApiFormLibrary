#pragma once

#ifndef ABSTRACTCOMPONENT_HPP
#define ABSTRACTCOMPONENT_HPP

#include <windows.h>
#include <string>
#include <FormTypes.hpp>
#include <ComponentException.hpp>
#include <Message.hpp>

class AbstractComponent {
private:

	ProcessMessage process_messages_ = [this](Message& message)noexcept->bool { 
		
		return false;
	
	};
	
	std::wstring class_name_  = kDefaultClassName;
	HINSTANCE	 hInstance_	  = NULL;
	std::wstring text_		  = kDefaultText;
	HWND		 parent_hWnd_ = NULL;
	HWND		 self_hWnd_	  = NULL;

	static LRESULT CALLBACK ComponentProc(HWND hWnd, UINT message, WPARAM  wParam, LPARAM lParam);

protected:

	bool CallProcessMessage(Message& message);
	void RegisterComponentClass(const std::wstring& class_name);
	void ShowComponent(int nCmdShow = SW_SHOWNORMAL);
	void CreateComponent(const HWND parent_hWnd_ = NULL, const std::wstring& class_name = L"Component");
	const HWND GetHandle()const noexcept;
	void DestroyComponent();

public:
	
	explicit AbstractComponent();
	~AbstractComponent();

public:

	static inline const std::wstring kDefaultText = L"Default text.";
	static inline const uint64_t	 kDefaultWidth = 600;
	static inline const uint64_t	 kDefaultHeight = 300;
	static inline const uint64_t	 kDefaultX = 0;
	static inline const uint64_t	 kDefaultY = 0;
	static inline const DWORD		 kDefaultStyle = NULL;
	static inline const DWORD		 kDefaultExStyle = NULL;
	static inline const std::wstring kDefaultClassName = L"Component";
	static inline const Color		 kDefaultBackgroundColor{ 255, 255, 255 };

	void SetProcessFunction(ProcessMessage messages_processing)noexcept;
	void ChangeSize(const uint64_t width, const uint64_t height);
	void ChangeStyle(DWORD ex_dwStyle, DWORD dwStyle);
	void ChangePosition(const uint64_t x, const uint64_t y);
	void ChangeText(const std::wstring& text);
	bool WasCreated()const noexcept;
	DWORD GetStyle()const;
	DWORD GetExtendedStyle()const;
	int GetHeight()const;
	int GetWidth()const;
	const std::uint64_t GetClientHeight()const;
	const std::uint64_t GetClientWidth()const;
	int GetX()const;
	int GetY()const;

	virtual void Create(const HWND parent_hWnd = NULL) = 0;
	virtual void Show(int nCmdShow = SW_SHOWNORMAL)= 0;
	virtual void Destroy() = 0;

};

#endif //ABSTRACTCOMPONENT_HPP