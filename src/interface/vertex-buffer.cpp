#include "vertex-buffer.hpp"

#include "graphics-include.hpp"

namespace Interface {

	VertexBuffer::BoundToken::BoundToken(const GLuint key, const GLintptr offset, const GLsizei stride) : bound(BindType(true,
#		ifndef NDEBUG
			[](const bool bound) {
				if (bound)
					glBindVertexBuffer(0, 0, 0, 0);
			}
#		else // NDEBUG
			euleristic::NoOp<GLuint>
#		endif // NDEBUG
		)) {
		glBindVertexBuffer(0, key, offset, stride);
	}

	void VertexBuffer::Init(const size_t size, const void* data) {
		handle = HandleType([]() {
			GLuint key;
			glGenBuffers(1, &key);
			return key;
		}(), [](const GLuint key) {
			glDeleteBuffers(1, &key);
		});
		// auto token = Bind();
		glBindBuffer(GL_ARRAY_BUFFER, Key());
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0u);
	}

	GLuint VertexBuffer::Key() const {
		return *handle;
	}

	size_t VertexBuffer::Size() const {
		return size;
	}

	size_t VertexBuffer::ElementSize() const {
		return elemSize;
	}

	VertexBuffer::BoundToken VertexBuffer::Bind() {
		return BoundToken(Key(), 0, ElementSize());
	}
}
