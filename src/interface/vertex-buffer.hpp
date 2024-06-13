#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "unique-key/unique-key.hpp"
#include <cstdint>
#include <span>

namespace Interface {
	class VertexBuffer {
		using HandleType = euleristic::UniqueKey<uint32_t, 0u, false>;
		void Init(const size_t size, const void* data);
	public:
		class BoundToken {
			friend VertexBuffer;
			BoundToken(const uint32_t key);
			BoundToken(const std::span<VertexBuffer> buffers);
			using BindType = euleristic::UniqueKey<bool, false, false>;
			BindType bound;
		};
		VertexBuffer() = default;
		template <typename Vertex, size_t size>
		VertexBuffer(const std::span<Vertex, size> buffer) {
			Init(buffer.size() * sizeof(Vertex), buffer.data());
		};
		unsigned int Key() const;
		BoundToken Bind();
		// static BoundToken Bind(const std::span<VertexBuffer> buffers);
	private:
		HandleType handle;
	};
}
#endif // !VERTEX_BUFFER_HPP
