#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <array>
#include <numeric>

#include "unique-key/unique-key.hpp"

#include "types.hpp"
#include "vertex-buffer.hpp"


namespace Interface {

	class VertexArray {
		using HandleType = euleristic::UniqueKey<uint32_t, 0u, false>;

		template <AttributeType Attribute>
		void AddAttribute(const uint32_t index, const uint32_t relativeOffset);

		HandleType GenerateHandle();
		// Parameter pack helpers
		template <size_t arraySize, typename RemainingMemberType>
		static consteval std::array<size_t, arraySize + 1> EffectiveSizes(const std::array<size_t, arraySize>& precedingSizes = std::array<size_t, 0>{}, const size_t precedingAlignment = 1z);
		template <size_t arraySize, typename NextMemberType, typename...RemainingMemberTypes> requires (sizeof...(RemainingMemberTypes) > 0)
		static consteval std::array<size_t, arraySize + 1 + sizeof...(RemainingMemberTypes)>
			EffectiveSizes(const std::array<size_t, arraySize>& precedingSizes = std::array<size_t, 0>{}, const size_t precedingAlignment = 1z);

		template <size_t arraySize, typename RemainingMemberType>
		void AddAttributeRecurse(const std::array<size_t, arraySize>& sizes, const uint32_t relativeOffset = 0u);
		template <size_t arraySize, typename NextMemberType, typename...RemainingMemberTypes> requires (sizeof...(RemainingMemberTypes) > 0)
		void AddAttributeRecurse(const std::array<size_t, arraySize>& sizes, const uint32_t relativeOffset = 0u);
		template <typename Head, typename...Tail> struct FirstOf { using Type = Head; };
	public:
		class BoundToken {
			friend class VertexArray;
			BoundToken(const uint32_t key);
			using BindType = euleristic::UniqueKey<bool, false, false>;
			BindType bound;
		};
		
		VertexArray() = default;

		template <AttributeType...Attributes>
		static VertexArray WithLayout() {
			VertexArray vertexArray;
			vertexArray.handle = vertexArray.GenerateHandle();
			constexpr auto effectiveSizes = EffectiveSizes<0z, Attributes...>();

			const auto vertexArrayBoundToken = vertexArray.Bind();

			vertexArray.AddAttributeRecurse<effectiveSizes.size(), Attributes...>(effectiveSizes);
			
			return vertexArray;
		}

		uint32_t Key() const;
		BoundToken Bind();
	private:
		HandleType handle;
	};

	template <size_t arraySize, typename RemainingMemberType> 
	consteval std::array<size_t, arraySize + 1> VertexArray::EffectiveSizes(const std::array<size_t, arraySize>& precedingSizes, const size_t precedingAlignment) {
		std::array<size_t, arraySize + 1> completeArray;
		std::copy(precedingSizes.cbegin(), precedingSizes.cend(), completeArray.begin());

		constexpr auto lastSize = sizeof(RemainingMemberType);
		const auto totalSize = std::reduce(precedingSizes.cbegin(), precedingSizes.cend(), 0z) + lastSize;
		const auto alignment = std::max(alignof(RemainingMemberType), precedingAlignment);

		// Pad if needed
		completeArray.back() = (totalSize % alignment) ? lastSize + alignment - (totalSize % alignment) : lastSize;

		return completeArray;
	}

	template <size_t arraySize, typename NextMemberType, typename...RemainingMemberTypes> requires (sizeof...(RemainingMemberTypes) > 0)
	consteval std::array<size_t, arraySize + 1 + sizeof...(RemainingMemberTypes)> VertexArray::EffectiveSizes(const std::array<size_t, arraySize>& precedingSizes, const size_t precedingAlignment) {
		std::array<size_t, arraySize + 1> nextArray;
		std::copy(precedingSizes.cbegin(), precedingSizes.cend(), nextArray.begin());

		constexpr auto alignment = alignof(typename FirstOf<RemainingMemberTypes...>::Type);
		constexpr auto nextSize = sizeof(NextMemberType);
		const auto partialSize = std::reduce(precedingSizes.cbegin(), precedingSizes.cend(), 0z) + nextSize;

		// Pad if needed
		nextArray.back() = (partialSize % alignment) ? nextSize + alignment - (partialSize % alignment) : nextSize;

		return EffectiveSizes<arraySize + 1, RemainingMemberTypes...>(nextArray, std::max(alignof(NextMemberType), precedingAlignment));
	}

	template <size_t arraySize, typename RemainingMemberType>
	void VertexArray::AddAttributeRecurse([[maybe_unused]] const std::array<size_t, arraySize>& sizes, const uint32_t relativeOffset) {
		AddAttribute<RemainingMemberType>(arraySize - 1, relativeOffset);
	}

	template <size_t arraySize, typename NextMemberType, typename...RemainingMemberTypes> requires (sizeof...(RemainingMemberTypes) > 0)
	void VertexArray::AddAttributeRecurse(const std::array<size_t, arraySize>& sizes, const uint32_t relativeOffset) {
		constexpr auto index = arraySize - 1 - sizeof...(RemainingMemberTypes);
		AddAttribute<NextMemberType>(index, relativeOffset);
		AddAttributeRecurse<arraySize, RemainingMemberTypes...>(sizes, relativeOffset + sizes[index]);
	}
}
#endif // !VERTEX_ARRAY_HPP
