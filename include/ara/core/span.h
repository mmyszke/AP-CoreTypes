/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_SPAN_H_
#define ARA_CORE_SPAN_H_
#include "ara/core/array.h"
#include "ara/core/utility.h"
#include <limits>
#include <memory>
#include <span>
#include <type_traits>

namespace ara::core {
/**
 * @brief A constant for creating Spans with dynamic sizes.
 *
 * @req {SWS_CORE_01901}
 */
constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

/**
 * @brief A view over a contiguous sequence of objects.
 *
 * @req {SWS_CORE_01900}
 */
template<typename T, std::size_t Extent = dynamic_extent> class Span
{
    using span_t = std::span<T, Extent>;
    span_t sp;


 public:
    /**
     * @brief Alias for the type of values in this Span.
     *
     * @req {SWS_CORE_01911}
     */
    using element_type = T;

    /**
     * @brief Alias for the type of values in this Span.
     *
     * @req {SWS_CORE_01912}
     */
    using value_type = typename std::remove_cv<element_type>::type;

    /**
     * @brief Alias for the type of parameters that indicate an index into the
     * Span.
     *
     * @req {SWS_CORE_01913}
     */
    using index_type = std::size_t;

    /**
     * @brief Alias for the type of parameters that indicate a difference of
     * indexes into the Span.
     *
     * @req {SWS_CORE_01914}
     */
    using difference_type = std::ptrdiff_t;

    /**
     * @brief Alias for the type of parameters that indicate a size or a number
     * of values.
     *
     * @req {SWS_CORE_01921}
     */
    using size_type = index_type;

    /**
     * @brief Alias type for a pointer to an element.
     *
     * @req {SWS_CORE_01915}
     */
    using pointer = element_type*;

    /**
     * @brief Alias type for a reference to an element.
     *
     * @req {SWS_CORE_01916}
     */
    using reference = element_type&;

    /**
     * @brief The type of an iterator to elements.
     *
     * @req {SWS_CORE_01917}
     */

    using iterator = typename span_t::iterator;

    /**
     * @brief The type of a const_iterator to elements.
     *
     * @req {SWS_CORE_01918}
     */

    using const_iterator = typename span_t::iterator const;

    /**
     * @brief The type of a reverse_iterator to elements.
     *
     * @req {SWS_CORE_01919}
     */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /**
     * @brief The type of a const_reverse_iterator to elements.
     *
     * @req {SWS_CORE_01920}
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * @brief A constant reflecting the configured Extent of this Span.
     *
     * @req {SWS_CORE_01931}
     */
    static constexpr index_type extent = Extent;

    /**
     * @brief Default constructor.
     *
     * @req {SWS_CORE_01941}
     */
    constexpr Span() noexcept : sp() {}

    /**
     * @brief Construct a new Span from the given pointer and size.
     *
     * @req {SWS_CORE_01942}
     * @param[in] ptr - the pointer
     * @param[in] count - the number of elements to take from ptr
     */
    constexpr Span(pointer ptr, index_type count) : sp(span_t{ptr, count}) {}
    /**
     * @brief Construct a new Span from the open range between [firstElem,
     * lastElem).
     *
     * @req {SWS_CORE_01943}
     * @param[in] firstElem - pointer to the first element
     * @param[in] lastElem - pointer to past the last element
     */
    constexpr Span(pointer firstElem, pointer lastElem)
      : sp(span_t{firstElem, lastElem})
    {}

    /**
     * @brief Construct a new Span from the given raw array.
     *
     * @req {SWS_CORE_01944}
     * @tparam[in] N - the size of the raw array
     * @param[in] arr - the raw array
     */
    template<std::size_t N> constexpr Span(element_type (&arr)[N]) noexcept
      : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given Array.
     *
     * @req {SWS_CORE_01945}
     * @tparam[in] N - the size of the Array
     * @param[in] arr - the array
     */
    template<std::size_t N> constexpr Span(
      ara::core::Array<value_type, N>& arr,
      std::enable_if<
        Extent == dynamic_extent || N == Extent,
        std::is_convertible<typename std::remove_pointer<typename decltype(
                              ara::core::data(arr))::type>::type (*)[],
                            T (*)[]>>) noexcept
      : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given Array.
     *
     * @req {SWS_CORE_01946}
     * @tparam[in] N - the size of the Array
     * @param[in] arr - the array
     */
    template<std::size_t N>
    constexpr Span(ara::core::Array<value_type, N> const& arr) noexcept
      : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given container.
     *
     * @req {SWS_CORE_01947}
     * @tparam[in] Container - the type of container
     * @param[in] count - the container
     */
    template<typename Container> constexpr Span(Container& cont)
      : sp({span_t{cont}})
    {}

    /**
     * @brief Construct a new Span from the given container.
     *
     * @req {SWS_CORE_01948}
     * @tparam[in] Container - the type of container
     * @param[in] count - the container
     */
    template<typename Container> constexpr Span(Container const& cont)
      : sp(span_t{cont})
    {}


    /**
     * @brief Copy construct a new Span from another instance.
     *
     * @req {SWS_CORE_01949}
     * @param[in] other - the other instance
     */
    constexpr Span(Span const& other) : sp(other.sp) {}
    /**
     * @brief Converting constructor.
     *
     * @req {SWS_CORE_01950}
     * @tparam[in] U - the type of elements within the other Span
     * @tparam[in] N - the Extent of the other Span
     * @param[in] s - the other Span instance
     */
    template<typename U, std::size_t N>
    constexpr Span(Span<U, N> const& s) noexcept : sp(span_t{s})
    {}

    /**
     * @brief Destructor.
     *
     * @req {SWS_CORE_01951}
     */
    ~Span() noexcept = default;

    /**
     * @brief Copy assignment operator.
     *
     * @req {SWS_CORE_01952}
     * @param[in] other - the other instance
     *
     * @return *this
     */
    Span& operator=(Span const& other)
    {
        if (this != &other)
        {
            sp = other.sp;
        }
        return *this;
    }
    /**
     * @brief Return a subspan containing only the first elements of this Span.
     *
     * @req {SWS_CORE_01961}
     * @tparam[in] Count - the number of elements to take over
     *
     * @return the subspan
     */
    template<std::size_t Count> constexpr Span<element_type, Count>
    first() const
    {
        return sp.first();
    }

    /**
     * @brief Return a subspan containing only the first elements of this Span.
     *
     * @req {SWS_CORE_01962}
     * @param[in] count - the number of elements to take over
     *
     * @return the subspan
     */
    constexpr Span<element_type, dynamic_extent> first(index_type count) const
    {
        return sp.first(count);
    }

    /**
     * @brief Return a subspan containing only the last elements of this Span.
     *
     * @req {SWS_CORE_01963}
     * @tparam[in] Count - the number of elements to take over
     *
     * @return the subspan
     */
    template<std::size_t Count> constexpr Span<element_type, Count> last() const
    {
        return sp.last();
    }

    /**
     * @brief Return a subspan containing only the last elements of this Span.
     *
     * @req {SWS_CORE_01964}
     * @param[in] count - the number of elements to take over
     *
     * @return the subspan
     */
    constexpr Span<element_type, dynamic_extent> last(index_type count) const
    {
        return sp.last(count);
    }

    /**
     * @brief Return a subspan of this Span.
     *
     * @req {SWS_CORE_01965}
     * @tparam[in] Offset - offset into this Span from which to start
     * @tparam[in] Count - the number of elements to take over
     *
     * @return the subspan
     */
    template<std::size_t Offset, std::size_t Count = dynamic_extent>
    constexpr auto subspan() const
      -> Span<element_type,
              Count != dynamic_extent
                ? Count
                : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent)>
    {
        return Span::subspan(Offset, Count);
    }

    /**
     * @brief Return a subspan of this Span.
     *
     * @req {SWS_CORE_01966}
     * @param[in] offset - offset into this Span from which to start
     * @param[in] count - the number of elements to take over
     *
     * @return the subspan
     */
    constexpr Span<element_type, dynamic_extent>
    subspan(index_type offset, index_type count = dynamic_extent) const
    {
        return {data() + offset, count};
    }

    /**
     * @brief Return the size of this Span.
     *
     * @req {SWS_CORE_01967}
     *
     * @return the number of elements contained in this Span
     */
    constexpr index_type size() const noexcept { return sp.size(); }

    /**
     * @brief Return the size of this Span in bytes.
     *
     * @req {SWS_CORE_01968}
     *
     * @return the number of bytes covered by this Span
     */
    constexpr index_type size_bytes() const noexcept { return sp.size_bytes(); }

    /**
     * @brief Return whether this Span is empty.
     *
     * @req {SWS_CORE_01969}
     *
     * @return true if this Span contains 0 elements, false otherwise
     */
    constexpr bool empty() const noexcept { return sp.empty(); }

    /**
     * @brief Return a reference to the n-th element of this Span.
     *
     * @req {SWS_CORE_01970}
     * @param[in] idx - the index into this Span
     *
     * @return the reference
     */
    constexpr reference operator[](index_type idx) const { return sp[idx]; }

    /**
     * @brief Return a pointer to the start of the memory block covered by this
     * Span.
     *
     * @req {SWS_CORE_01971}
     *
     * @return the pointer
     */
    constexpr pointer data() const noexcept { return sp.data(); }

    /**
     * @brief Return an iterator pointing to the first element of this Span.
     *
     * @req {SWS_CORE_01972}
     *
     * @return the iterator
     */
    constexpr iterator begin() const noexcept { return sp.begin(); }

    /**
     * @brief Return an iterator pointing past the last element of this Span.
     *
     * @req {SWS_CORE_01973}
     *
     * @return the iterator
     */
    constexpr iterator end() const noexcept { return sp.end(); }

    /**
     * @brief Return a const_iterator pointing to the first element of this Span.
     *
     * @req {SWS_CORE_01974}
     *
     * @return the const_iterator
     */
    constexpr pointer cbegin() const noexcept { return sp.cbegin(); }

    /**
     * @brief Return a const_iterator pointing past the last element of this
     * Span.
     *
     * @req {SWS_CORE_01975}
     *
     * @return the const_iterator
     */
    constexpr pointer cend() const noexcept { return sp.cend(); }

    /**
     * @brief Return a reverse_iterator pointing to the last element of this
     * Span.
     *
     * @req {SWS_CORE_01976}
     *
     * @return the the reverse_iterator
     */
    constexpr reverse_iterator rbegin() const noexcept { return sp.rbegin(); }

    /**
     * @brief Return a reverse_iterator pointing past the first element of this
     * Span.
     *
     * @req {SWS_CORE_01977}
     *
     * @return the the reverse_iterator
     */
    constexpr reverse_iterator rend() const noexcept { return sp.rend(); }

    /**
     * @brief Return a const_reverse_iterator pointing to the last element of
     * this Span.
     *
     * @req {SWS_CORE_01978}
     *
     * @return the const_reverse_iterator
     */
    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return sp.crbegin();
    }

    /**
     * @brief Return a const_reverse_iterator pointing past the first element of
     * this Span.
     *
     * @req {SWS_CORE_01979}
     *
     * @return the reverse_iterator
     */
    constexpr const_reverse_iterator crend() const noexcept
    {
        return sp.crend();
    }
};
/**
 * @brief Create a new Span from the given pointer and size.
 *
 * @req {SWS_CORE_01990}
 * @param[in] T - the type of elements
 * @param[in] ptr - the pointer
 * @param[in] count - the number of elements to take from ptr
 *
 * @return the new Span
 */
template<typename T> constexpr Span<T>
MakeSpan(T* ptr, typename Span<T>::index_type count)
{
    return {ptr, count};
}

/**
 * @brief Create a new Span from the open range between [firstElem,
 * lastElem).
 *
 * @req {SWS_CORE_01991}
 * @param[in] T - the type of elements
 * @param[in] firstElem - pointer to the first element
 * @param[in] lastElem - pointer to past the last element
 *
 * @return the new Span
 */
template<typename T> constexpr Span<T> MakeSpan(T* firstElem, T* lastElem)
{
    return {firstElem, lastElem};
}

/**
 * @brief Create a new Span from the given raw array.
 *
 * @req {SWS_CORE_01992}
 * @param[in] T - the type of elements
 * @param[in] N - the size of the raw array
 * @param[in] arr - the raw array
 *
 * @return the new Span
 */
template<typename T, std::size_t N> constexpr Span<T, N>
  MakeSpan(T (&arr)[N]) noexcept
{
    return arr;
}

/**
 * @brief Create a new Span from the given container.
 *
 * @req {SWS_CORE_01993}
 * @param[in] cont - the container
 *
 * @return the new Span
 */
template<typename Container> constexpr Span<typename Container::value_type>
MakeSpan(Container& cont)
{
    return cont;
}

/**
 * @brief Create a new Span from the given const container.
 *
 * @req {SWS_CORE_01994}
 * @param[in] cont - the container
 *
 * @return the new Span
 */
template<typename Container>
constexpr Span<typename Container::value_type const>
MakeSpan(Container const& cont)
{
    return cont;
}

}  // namespace ara::core

#endif  // ARA_CORE_SPAN_H_