#include <ComponentException.hpp>

ComponentException::ComponentException(std::string&& message)noexcept:
	std::exception{ },
	message_{ std::move(message) } {



}

ComponentException::ComponentException(const std::string& message)noexcept:
	std::exception{},
	message_{ message }{


}

ComponentException::ComponentException(const std::string& message, DWORD error_code)noexcept:
	message_{ message }, code_{ error_code } {


}

const std::string& ComponentException::What()const noexcept(true) { return message_; }
DWORD ComponentException::Code() const noexcept
{
	return code_;
};