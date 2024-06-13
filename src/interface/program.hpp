#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "unique-key/unique-key.hpp"
#include "shader.hpp"
#include "vertex-array.hpp"

namespace Interface {

	class Program {
		using HandleType = euleristic::UniqueKey<uint32_t, 0u, false>;

	public:
		class BoundToken {
			friend Program;
			BoundToken(const uint32_t key);
			using BindType = euleristic::UniqueKey<bool, false, false>;
			BindType bound;
		};

		enum class DrawingMode {
			POINTS,
			LINE_STRIP,
			LINE_LOOP,
			LINES,
			LINE_STRIP_ADJACENCY,
			LINES_ADJACENCY,
			TRIANGLE_STRIP,
			TRIANGLE_FAN,
			TRIANGLES,
			TRIANGLE_STRIP_ADJACENCY,
			TRIANGLES_ADJACENCY
		};

		Program() = default;
		Program(const VertexShader& vertexShader, const FragmentShader& fragmentShader);
		[[nodiscard]] uint32_t Key() const;
		[[nodiscard]] BoundToken Bind();
		template <DrawingMode mode>
		[[nodiscard]] BoundToken Run(VertexArray& vertexArray, const int32_t first, const int32_t count);
		template <DrawingMode mode>
		[[nodiscard]] BoundToken Run(VertexArray& vertexArray, const int32_t first, const int32_t count, BoundToken&& boundToken);
	private:
		HandleType handle;
	};
}

#endif // !PROGRAM_HPP
