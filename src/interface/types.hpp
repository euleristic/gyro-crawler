#ifndef INTERFACE_CONCEPTS_HPP
#define INTERFACE_CONCEPTS_HPP

#include <cstdint>
#include <concepts>
#include <type_traits>
#include <span>

#include <glm/glm.hpp>

namespace Interface {
	template <typename T, typename...U>
	concept AnyOf = (std::same_as<T, U> || ...);

	template <typename T> struct IsVec : std::false_type {};
	template <glm::length_t D, typename T, glm::qualifier Q> requires (2 <= D && D <= 4)
	struct IsVec<glm::vec<D, T, Q>> : std::true_type {};

	template <typename T> struct IsMat : std::false_type {};
	template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q> requires (2 <= C && C <= 4 && 2 <= R && R <= 4)
	struct IsMat<glm::mat<C, R, T, Q>> : std::true_type {};

	template <typename T> concept UniformScalarType = AnyOf<T, float, int32_t, uint32_t>;
	template <typename T> concept UniformElementType = UniformScalarType<T>
		|| (IsVec<T>::value && UniformScalarType<typename T::value_type>)
		|| (IsMat<T>::value && UniformScalarType<typename T::value_type>);

	template <typename T> struct IsUniformSpan : std::false_type {};
	template <UniformElementType T> struct IsUniformSpan<std::span<T>> : std::true_type {};

	template <typename T> concept UniformType = UniformElementType<T> || IsUniformSpan<T>::value;

	template <typename T> concept AttributeScalarType = AnyOf<T,
		int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
		float, double>;
	template <typename T> concept AttributeType = AttributeScalarType<T>
		|| (IsVec<T>::value && AttributeScalarType<typename T::value_type>);
}
#endif // !INTERFACE_CONCEPTS_HPP
