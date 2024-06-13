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
			BoundToken(const uint32_t key, const ptrdiff_t offset, const int32_t stride);
			using BindType = euleristic::UniqueKey<bool, false, false>;
			BindType bound;
		};
		VertexBuffer() = default;
		template <typename Vertex, size_t size>
		VertexBuffer(const std::span<Vertex, size> buffer) : size(size), elemSize(sizeof(Vertex)) {
			Init(buffer.size() * sizeof(Vertex), buffer.data());
		};
		uint32_t Key() const;
		size_t Size() const;
		size_t ElementSize() const;
		BoundToken Bind();
	private:
		HandleType handle;
		size_t size;
		size_t elemSize;
	};
}
#endif // !VERTEX_BUFFER_HPP
