#include "vertex-array.hpp"

#include "graphics-include.hpp"

namespace Interface {
	
	VertexArray::BoundToken::BoundToken(const GLuint key) : bound(BindType(true,
#		ifndef NDEBUG
			[](const bool bound) {
				if (bound)
					glBindVertexArray(0u);
			}
#		else // NDEBUG
			euleristic::NoOp<GLuint>
#		endif // !NDEBUG
		)) {
		glBindVertexArray(key);
	}

	GLuint VertexArray::Key() const {
		return *handle;
	}
	
	VertexArray::BoundToken VertexArray::Bind() {
		return BoundToken(Key());
	}

#	define SCALAR_TYPES_ELEMS \
	X(GLbyte, GL_BYTE) \
	X(GLubyte, GL_UNSIGNED_BYTE) \
	X(GLshort, GL_SHORT) \
	X(GLushort, GL_UNSIGNED_SHORT) \
	X(GLint, GL_INT) \
	X(GLuint, GL_UNSIGNED_INT) \
	X(GLfloat, GL_FLOAT) \
	X(GLdouble, GL_DOUBLE) 

	template <AttributeScalarType T>
	consteval GLenum Symbol() {

#		define X(Type, symbolicConstant) \
		if constexpr (std::same_as<Type, T>) return symbolicConstant;

		SCALAR_TYPES_ELEMS

#		undef X
	}

	VertexArray::HandleType VertexArray::GenerateHandle() {
		return HandleType([]() { 
				GLuint key;
				glGenVertexArrays(1, &key);
				return key;
			}(), [](const GLuint key) {
				glDeleteVertexArrays(1, &key);
			});
	}

	template <AttributeScalarType T>
	void AddScalarAttribute(const GLuint index, const GLsizei stride, const void* pointer) {
		glVertexAttribPointer(index, 1, Symbol<T>(), GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(index);
	}

	template <AttributeType T> requires (!AttributeScalarType<T>)
	void AddVectorAttribute(const GLuint index, const GLsizei stride, const void* pointer) {
		glVertexAttribPointer(index, T::length(), Symbol<typename T::value_type>(), GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(index);
	}

	template <AttributeType T>
	void VertexArray::AddAttribute(const GLuint index, const GLsizei stride, const void* pointer) {
		if constexpr (AttributeScalarType<T>) {
			AddScalarAttribute<T>(index, stride, pointer);
		}
		else {
			AddVectorAttribute<T>(index, stride, pointer);
		}
	}

	// Instantiate all AddAttribute AttributeType

	// First, the scalar types

#	define X(Type, _) \
	template void VertexArray::AddAttribute<Type>(const GLuint index, const GLsizei stride, const void* pointer);
	SCALAR_TYPES_ELEMS
#	undef X

	// Now, the rest of the cartesian product
#	define X(Type, _) \
	P(2, Type) \
	P(3, Type) \
	P(4, Type)

#	define P(dims, Type) \
	template void VertexArray::AddAttribute<glm::vec<dims, Type>>(const GLuint index, const GLsizei stride, const void* pointer);
	SCALAR_TYPES_ELEMS
#	undef P
#	undef X
}
