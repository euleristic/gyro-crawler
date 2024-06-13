#ifndef SHADER_HPP
#define SHADER_HPP

#include <string_view>

#include "unique-key/unique-key.hpp"

namespace Interface {
	enum class ShaderType {
		VERTEX,
		FRAGMENT
	};

	template <ShaderType TYPE_PARAM>
	class Shader {
	public:
		static constexpr auto TYPE = TYPE_PARAM;
		Shader() = default;
		Shader(const std::string_view source);
		[[nodiscard]] unsigned int Key() const;
	private:
		using HandleType = euleristic::UniqueKey<unsigned int, 0u, false>;
		HandleType handle;
	};
	
	using VertexShader = Shader<ShaderType::VERTEX>;
	using FragmentShader = Shader<ShaderType::FRAGMENT>;
}

#endif // !SHADER_HPP
