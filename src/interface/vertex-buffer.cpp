#include "vertex-buffer.hpp"

#include "graphics-include.hpp"

namespace Interface {

	VertexBuffer::BoundToken::BoundToken(const GLuint key) : bound(BindType(true,
#		ifndef NDEBUG
			[](const bool bound) {
				if (bound)
					glBindBuffer(GL_ARRAY_BUFFER, 0u);
			}
#		else // NDEBUG
			euleristic::NoOp<GLuint>
#		endif // NDEBUG
		)) {
		glBindBuffer(GL_ARRAY_BUFFER, key);
	}

	/*VertexBuffer::BoundToken::BoundToken(const std::span<VertexBuffer> buffers) : bound(BindType(true,
#		ifndef NDEBUG
			[](const bool bound) {
				if (bound)
					glBindBuffer(GL_ARRAY_BUFFER, 0u);
			}
#		else // NDEBUG
			euleristic::NoOp<GLuint>
#		endif // NDEBUG
		)) {
		glBindVertexBuffers(0, buffers.size(), buffers.front(),);
	}*/

	VertexBuffer::VertexBuffer(const void* data, const size_t size) :
		handle(HandleType([]() {
			GLuint key;
			glGenBuffers(1, &key);
			return key;
		}(), [](const GLuint key) {
			glDeleteBuffers(1, &key);
		})) {
			auto token = Bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

	GLuint VertexBuffer::Key() const {
		return *handle;
	}

	VertexBuffer::BoundToken VertexBuffer::Bind() {
		return BoundToken(Key());
	}

	/*VertexBuffer::BoundToken VertexBuffer::Bind(std::span<VertexBuffer> buffers) {
		//if (buffers.empty()) throw std::runtime_error("Attempt to bind
	
	}*/
}
