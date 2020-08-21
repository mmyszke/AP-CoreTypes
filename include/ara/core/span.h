/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#include <array>
#include <limits>
#include <memory>
#include <span>
#ifndef ARA_CORE_SPAN_H_
#    define ARA_CORE_SPAN_H_

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
template<typename T_type, std::size_t Extent = dynamic_extent> class Span
{
    using span_t = std::span<T_type, Extent>;
    span_t sp;


 public:
    /**
     * @brief Alias for the type of values in this Span.
     *
     * @req {SWS_CORE_01911}
     */
    using element_type = T_type;

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
     */
    constexpr Span(pointer ptr, index_type count) : sp(span_t{ptr, count}) {}
    /**
     * @brief Construct a new Span from the open range between [firstElem,
     * lastElem).
     *
     * @req {SWS_CORE_01943}
     */
    constexpr Span(pointer firstElem, pointer lastElem)
      : sp(span_t{firstElem, lastElem})
    {}

    /**
     * @brief Construct a new Span from the given raw array.
     *
     * @req {SWS_CORE_01944}
     */
    template<std::size_t N> constexpr Span(element_type (&arr)[N]) noexcept
      : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given Array.
     *
     * @req {SWS_CORE_01945}
     */
    template<std::size_t N>
    constexpr Span(std::array<value_type, N>& arr) noexcept : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given Array.
     *
     * @req {SWS_CORE_01946}
     */
    template<std::size_t N>
    constexpr Span(std::array<value_type, N> const& arr) noexcept
      : sp(span_t{arr})
    {}

    /**
     * @brief Construct a new Span from the given container.
     *
     * @req {SWS_CORE_01947}
     */
    template<typename Container> constexpr Span(Container& cont)
      : sp(std::span<typename Container::value_type, Extent>(cont))
    {}

    /**
     * @brief Construct a new Span from the given container.
     *
     * @req {SWS_CORE_01948}
     */
    template<typename Container> constexpr Span(Container const& cont)
      : sp(std::span<T_type>(cont))
    {}


    /**
     * @brief Copy construct a new Span from another instance.
     *
     * @req {SWS_CORE_01949}
     */
    constexpr Span(Span const& other) : sp(other.sp) {}
    /**
     * @brief Converting constructor.
     *
     * @req {SWS_CORE_01950}
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
     */
    Span& operator=(Span const& other)
    {
        if (this != &other)
        {
            sp = std::move(other.sp);
        }
        return *this;
    }
    /**
     * @brief Return a subspan containing only the first elements of this Span.
     *
     * @req {SWS_CORE_01961}
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
     */
    constexpr Span<element_type, dynamic_extent> first(index_type count) const
    {
        return sp.first(count);
    }

    /**
     * @brief Return a subspan containing only the last elements of this Span.
     *
     * @req {SWS_CORE_01963}
     */
    template<std::size_t Count> constexpr Span<element_type, Count> last() const
    {
        return sp.last();
    }

    /**
     * @brief Return a subspan containing only the last elements of this Span.
     *
     * @req {SWS_CORE_01964}
     */
    constexpr Span<element_type, dynamic_extent> last(index_type count) const
    {
        return sp.last(count);
    }

    /**
     * @brief Return a subspan of this Span.
     *
     * @req {SWS_CORE_01965}
     */
    template<std::size_t Offset, std::size_t Count = dynamic_extent>
    constexpr auto subspan() const
      -> Span<element_type,
              Count != dynamic_extent
                ? Count
                : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent)>;

    /**
     * @brief Return a subspan of this Span.
     *
     * @req {SWS_CORE_01966}
     */
    constexpr Span<element_type, dynamic_extent>
    subspan(index_type offset, index_type count = dynamic_extent) const
    {
        return sp = span_t(offset, count);
    }

    /**
     * @brief Return the size of this Span.
     *
     * @req {SWS_CORE_01967}
     */
    constexpr index_type size() const noexcept { return sp.size(); }

    /**
     * @brief Return the size of this Span in bytes.
     *
     * @req {SWS_CORE_01968}
     */
    constexpr index_type size_bytes() const noexcept { return sp.size_bytes(); }

    /**
     * @brief Return whether this Span is empty.
     *
     * @req {SWS_CORE_01969}
     */
    constexpr bool empty() const noexcept { return sp.empty(); }

    /**
     * @brief Return a reference to the n-th element of this Span.
     *
     * @req {SWS_CORE_01970}
     */
    constexpr reference operator[](index_type idx) const { return sp[idx]; }

    /**
     * @brief Return a pointer to the start of the memory block covered by this
     * Span.
     *
     * @req {SWS_CORE_01971}
     */
    constexpr pointer data() const noexcept { return sp.data(); }

    /**
     * @brief Return an iterator pointing to the first element of this Span.
     *
     * @req {SWS_CORE_01972}
     */
    constexpr iterator begin() const noexcept { return sp.begin(); }

    /**
     * @brief Return an iterator pointing past the last element of this Span.
     *
     * @req {SWS_CORE_01973}ech
     */
    constexpr iterator end() const noexcept { return sp.end(); }

    /**
     * @brief Return a const_iterator pointing to the first element of this Span.
     *
     * @req {SWS_CORE_01974}
     */
    constexpr pointer cbegin() const noexcept { return sp.cbegin(); }

    /**
     * @brief Return a const_iterator pointing past the last element of this
     * Span.
     *
     * @req {SWS_CORE_01975}
     */
    constexpr pointer cend() const noexcept { return sp.cend(); }

    /**
     * @brief Return a reverse_iterator pointing to the last element of this
     * Span.
     *
     * @req {SWS_CORE_01976}
     */
    constexpr reverse_iterator rbegin() const noexcept { return sp.rbegin(); }

    /**
     * @brief Return a reverse_iterator pointing past the first element of this
     * Span.
     *
     * @req {SWS_CORE_01977}
     */
    constexpr reverse_iterator rend() const noexcept { return sp.rend(); }

    /**
     * @brief Return a const_reverse_iterator pointing to the last element of
     * this Span.
     *
     * @req {SWS_CORE_01978}
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
     */
    constexpr const_reverse_iterator crend() const noexcept
    {
        return sp.crend();
    }

    /**
     * @brief Create a new Span from the given pointer and size.
     *
     * @req {SWS_CORE_01990}
     */
    template<typename T> constexpr Span<T>
    MakeSpan(T* ptr, typename Span<T>::index_type count)
    {
        sp = element_type(ptr, count);
        return sp;
    }

    /**
     * @brief Create a new Span from the open range between [firstElem,
     * lastElem).
     *
     * @req {SWS_CORE_01991}
     */
    template<typename T> constexpr Span<T> MakeSpan(T* firstElem, T* lastElem)
    {
        sp = element_type(firstElem, lastElem);
        return sp;
    }

    /**
     * @brief Create a new Span from the given raw array.
     *
     * @req {SWS_CORE_01992}
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
     */
    template<typename Container>
    constexpr Span<typename Container::value_type const>
    MakeSpan(Container const& cont)
    {
        return cont;
    }
};
}  // namespace ara::core

#endif  // ARA_CORE_SPAN_H_