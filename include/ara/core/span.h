/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_SPAN_H_
#define ARA_CORE_SPAN_H_

namespace ara::core {
/**
 * @brief A constant for creating Spans with dynamic sizes.
 *
 * @req {SWS_CORE_01901}
 */
constexpr std::size_t ara::core::dynamic_extent= std::numeric_limits<std::size_t>::max();

/**
 * @brief A view over a contiguous sequence of objects.
 *
 * @req {SWS_CORE_01900}
 */
template<typename T, std::size_t Extent = dynamic_extent> class Span
{

/**
 * @brief Alias for the type of values in this Span.
 *
 * @req {SWS_CORE_01911}
 */
using ara::core::Span< T, Extent >::element_type = T;

/**
 * @brief Alias for the type of values in this Span.
 *
 * @req {SWS_CORE_01912}
 */
using ara::core::Span< T, Extent >::value_type = typename std::remove_cv<element_type>::type;
}

/**
 * @brief Alias for the type of parameters that indicate an index into the Span.
 *
 * @req {SWS_CORE_01913}
 */
using ara::core::Span< T, Extent >::index_type = std::size_t;

/**
 * @brief Alias for the type of parameters that indicate a difference of indexes into the Span.
 *
 * @req {SWS_CORE_01914}
 */
using ara::core::Span< T, Extent >::difference_type = std::ptrdiff_t;

/**
 * @brief Alias for the type of parameters that indicate a size or a number of values.
 *
 * @req {SWS_CORE_01921}
 */
using ara::core::Span< T, Extent >::size_type = index_type;

/**
 * @brief Alias type for a pointer to an element.
 *
 * @req {SWS_CORE_01915}
 */
using ara::core::Span< T, Extent >::pointer = element_type*;

/**
 * @brief Alias type for a reference to an element.
 *
 * @req {SWS_CORE_01916}
 */
using ara::core::Span< T, Extent >::reference = element_type&;

/**
 * @brief The type of an iterator to elements.
 *
 * @req {SWS_CORE_01917}
 */
using ara::core::Span< T, Extent >::iterator = implementation_defined;

/**
 * @brief The type of a const_iterator to elements.
 *
 * @req {SWS_CORE_01918}
 */
using ara::core::Span< T, Extent >::const_iterator = implementation_defined;

/**
 * @brief The type of a reverse_iterator to elements.
 *
 * @req {SWS_CORE_01919}
 */
using ara::core::Span< T, Extent >::reverse_iterator = std::reverse_iterator<iterator>;

/**
 * @brief The type of a const_reverse_iterator to elements.
 *
 * @req {SWS_CORE_01920}
 */
using ara::core::Span< T, Extent >::const_reverse_iterator =
std::reverse_iterator<const_iterator>;

/**
 * @brief A constant reflecting the configured Extent of this Span.
 *
 * @req {SWS_CORE_01931}
 */
constexpr index_type ara::core::Span< T, Extent >::extent= Extent;

/**
 * @brief Default constructor.
 *
 * @req {SWS_CORE_01941}
 */
constexpr ara::core::Span< T, Extent >::Span () noexcept;

/**
 * @brief Construct a new Span from the given pointer and size.
 *
 * @req {SWS_CORE_01942}
 */
constexpr ara::core::Span< T, Extent >::Span (pointer ptr, index_type count);

/**
 * @brief Construct a new Span from the open range between [firstElem, lastElem).
 *
 * @req {SWS_CORE_01943}
 */
constexpr ara::core::Span< T, Extent >::Span (pointer firstElem, pointer lastElem);

/**
 * @brief Construct a new Span from the given raw array.
 *
 * @req {SWS_CORE_01944}
 */
template <std::size_t N>
constexpr ara::core::Span< T, Extent >::Span (element_type(&arr)[N]) noexcept;

/**
 * @brief Construct a new Span from the given Array.
 *
 * @req {SWS_CORE_01945}
 */
template <std::size_t N>
constexpr ara::core::Span< T, Extent >::Span (Array<value_type, N>&arr) noexcept;

/**
 * @brief Construct a new Span from the given Array.
 *
 * @req {SWS_CORE_01946}
 */
template <std::size_t N>
constexpr ara::core::Span< T, Extent >::Span (Array< value_type,N> const &arr) noexcept;

/**
 * @brief Construct a new Span from the given container.
 *
 * @req {SWS_CORE_01947}
 */
template <typename Container>
constexpr ara::core::Span< T, Extent >::Span (Container &cont);

/**
 * @brief Construct a new Span from the given container.
 *
 * @req {SWS_CORE_01947}
 */
template <typename Container>
constexpr ara::core::Span< T, Extent >::Span (Container &cont);

/**
 * @brief Construct a new Span from the given container.
 *
 * @req {SWS_CORE_01948}
 */
template <typename Container>
constexpr ara::core::Span< T, Extent >::Span (Container const &cont);

/**
 * @brief Copy construct a new Span from another instance.
 *
 * @req {SWS_CORE_01949}
 */
constexpr ara::core::Span< T, Extent >::Span (Span const &other) noexcept=default;

/**
 * @brief Converting constructor.
 *
 * @req {SWS_CORE_01950}
 */
template <typename U, std::size_t N>
constexpr ara::core::Span< T, Extent >::Span (Span< U, N > const &s) noexcept;

/**
 * @brief Destructor.
 *
 * @req {SWS_CORE_01951}
 */
ara::core::Span< T, Extent >::~Span () noexcept=default;

/**
 * @brief Copy assignment operator.
 *
 * @req {SWS_CORE_01952}
 */
Span& ara::core::Span< T, Extent >::operator= (Span const &other)
noexcept=default;

/**
 * @brief Return a subspan containing only the first elements of this Span.
 *
 * @req {SWS_CORE_01961}
 */
template <std::size_t Count>
constexpr Span<element_type, Count> ara::core::Span< T, Extent >::first () const;

/**
 * @brief Return a subspan containing only the first elements of this Span.
 *
 * @req {SWS_CORE_01962}
 */
constexpr Span<element_type, dynamic_extent> ara::core::Span< T, Extent >::first (index_type count) const;

/**
 * @brief Return a subspan containing only the last elements of this Span.
 *
 * @req {SWS_CORE_01963}
 */
template <std::size_t Count>
constexpr Span<element_type, Count> ara::core::Span< T, Extent >::last() const;

/**
 * @brief Return a subspan containing only the last elements of this Span.
 *
 * @req {SWS_CORE_01964}
 */
constexpr Span<element_type, dynamic_extent> ara::core::Span< T, Extent >::last (index_type count) const;

/**
 * @brief Return a subspan of this Span.
 *
 * @req {SWS_CORE_01965}
 */
template <std::size_t Offset, std::size_t Count = dynamic_extent>
constexpr auto ara::core::Span< T, Extent >::subspan () const -> Span< element_type, SEE_BELOW >;

/**
 * @brief Return a subspan of this Span.
 *
 * @req {SWS_CORE_01966}
 */
constexpr Span<element_type, dynamic_extent> ara::core::Span< T, Extent >::subspan (index_type offset, index_type count=dynamic_extent)const;

/**
 * @brief Return the size of this Span.
 *
 * @req {SWS_CORE_01967}
 */
constexpr index_type ara::core::Span< T, Extent >::size () const noexcept;

/**
 * @brief Return the size of this Span in bytes.
 *
 * @req {SWS_CORE_01968}
 */
constexpr index_type ara::core::Span< T, Extent >::size_bytes () const noexcept;

/**
 * @brief Return whether this Span is empty.
 *
 * @req {SWS_CORE_01969}
 */
constexpr bool ara::core::Span< T, Extent >::empty () const noexcept;

/**
 * @brief Return a reference to the n-th element of this Span.
 *
 * @req {SWS_CORE_01970}
 */
constexpr reference ara::core::Span< T, Extent >::operator[] (index_type idx) const;

/**
 * @brief Return a pointer to the start of the memory block covered by this Span.
 *
 * @req {SWS_CORE_01971}
 */
constexpr pointer ara::core::Span< T, Extent >::data () const noexcept;

/**
 * @brief Return an iterator pointing to the first element of this Span.
 *
 * @req {SWS_CORE_01972}
 */
constexpr iterator ara::core::Span< T, Extent >::begin () const noexcept;

/**
 * @brief Return an iterator pointing past the last element of this Span.
 *
 * @req {SWS_CORE_01973}
 */
constexpr iterator ara::core::Span< T, Extent >::end () const noexcept;

/**
 * @brief Return a const_iterator pointing to the first element of this Span.
 *
 * @req {SWS_CORE_01974}
 */
constexpr const_iterator ara::core::Span< T, Extent >::cbegin () const noexcept;

/**
 * @brief Return a const_iterator pointing past the last element of this Span.
 *
 * @req {SWS_CORE_01975}
 */
constexpr const_iterator ara::core::Span< T, Extent >::cend () const noexcept;

/**
 * @brief Return a reverse_iterator pointing to the last element of this Span.
 *
 * @req {SWS_CORE_01976}
 */
constexpr reverse_iterator ara::core::Span< T, Extent >::rbegin ()const noexcept;

/**
 * @brief Return a reverse_iterator pointing past the first element of this Span.
 *
 * @req {SWS_CORE_01977}
 */
constexpr reverse_iterator ara::core::Span< T, Extent >::rend () const noexcept;

/**
 * @brief Return a const_reverse_iterator pointing to the last element of this Span.
 *
 * @req {SWS_CORE_01978}
 */
constexpr const_reverse_iterator ara::core::Span< T, Extent >::crbegin() const noexcept;

/**
 * @brief Return a const_reverse_iterator pointing past the first element of this Span.
 *
 * @req {SWS_CORE_01979}
 */
constexpr const_reverse_iterator ara::core::Span< T, Extent >::crend() const noexcept;

/**
 * @brief Create a new Span from the given pointer and size.
 *
 * @req {SWS_CORE_01990}
 */
template <typename T>
constexpr Span<T> MakeSpan (T *ptr, typename Span< T >::index_type count);

/**
 * @brief Create a new Span from the open range between [firstElem, lastElem).
 *
 * @req {SWS_CORE_01991}
 */
template <typename T>
constexpr Span<T> MakeSpan (T *firstElem, T *lastElem);

/**
 * @brief Create a new Span from the given raw array.
 *
 * @req {SWS_CORE_01992}
 */
template <typename T, std::size_t N>
constexpr Span<T, N> MakeSpan (T(&arr)[N]) noexcept;

/**
 * @brief Create a new Span from the given container.
 *
 * @req {SWS_CORE_01993}
 */
template <typename Container>
constexpr Span<typename Container::value_type> MakeSpan (Container &cont);

/**
 * @brief Create a new Span from the given const container.
 *
 * @req {SWS_CORE_01994}
 */
template <typename Container>
constexpr Span<typename Container::value_type const> MakeSpan(Container const &cont);

}
}
#endif // ARA_CORE_SPAN_H_
