#pragma once
#include <filesystem>
#include <windows.h>

#include <FormTypes.hpp>

using FileDialogException = ComponentException;

EXPIMP class FileDialog final{
private:

	OPENFILENAME init_struct_;
	std::filesystem::path file_path_ = L"";
	std::wstring file_name_ = L"";

public:

	EXPIMP explicit FileDialog()noexcept;
	EXPIMP void FindFile(const HWND parent_hWnd);
	EXPIMP std::filesystem::path GetPath()const noexcept;
	EXPIMP std::wstring GetName()const noexcept;

};