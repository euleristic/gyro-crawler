#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "unique-key/unique-key.hpp"
#include <cstdint>
#include <span>

namespace Interface {
	class VertexBuffer {
		using HandleType = euleristic::UniqueKey<uint32_t, 0u, false>;
	public:
		class BoundToken {
			friend VertexBuffer;
			BoundToken(const uint32_t key);
			BoundToken(const std::span<VertexBuffer> buffers);
			using BindType = euleristic::UniqueKey<bool, false, false>;
			BindType bound;
		};
		VertexBuffer() = default;
		VertexBuffer(const void* data, const size_t size);
		unsigned int Key() const;
		BoundToken Bind();
		// static BoundToken Bind(const std::span<VertexBuffer> buffers);
	private:
		HandleType handle;
	};
}
#endif // !VERTEX_BUFFER_HPP
