#ifndef INTERFACE_ERROR_HPP
#define INTERFACE_ERROR_HPP

#include <string>
#include <string_view>
#include <optional>

namespace Interface {
	std::string FormatErrorStringGLFW(const std::string_view prefix);
	std::string FormatErrorStringGL(const std::string_view prefix);
	std::optional<std::string> OpenGLError();
}

#endif // INTERFACE_ERROR_HPP
