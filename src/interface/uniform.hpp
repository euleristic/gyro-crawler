#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <glm/glm.hpp>

#include "program.hpp"
#include "types.hpp"

namespace Interface {

	template <UniformType T>
	class Uniform {
	public:
		using Type = T;
		Uniform(Program& program, const char* identifier);
		[[nodiscard]] Program::BoundToken Set(const Type value);
		[[nodiscard]] Program::BoundToken Set(const Type value, Program::BoundToken&& token);
	private:
		Program& program;
		int32_t location;
	};
}

#endif // !UNIFORM_HPP
