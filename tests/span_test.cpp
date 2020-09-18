#include "ara/core/span.h"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Subspan pointer size", "[SWS_CORE], [SWS_CORE_01942]")
{
    int tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::span<int>       span{tab};
    ara::core::Span<int> span_a{span.subspan(1, span.size() - 3)};
    std::span<int>       subspan{span.subspan(1, span.size() - 3)};

    CHECK(span_a.data() == subspan.data());
    CHECK(span_a.begin() == subspan.begin());
}

TEST_CASE("Subspan pointer range", "[SWS_CORE], [SWS_CORE_01943]")
{
    int tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::span<int>       span{tab};
    ara::core::Span<int> span_a{span.subspan(1, 5)};
    std::span<int>       subspan{span.subspan(1, 5)};

    CHECK(span_a.data() == subspan.data());
    CHECK(span_a.begin() == subspan.begin());
}

TEST_CASE("Span test raw array construct", "[SWS_CORE], [SWS_CORE_01944]")
{
    int             arr[]{0, 1, 2, 3, 4};
    ara::core::Span<int> span(arr);

    CHECK(span.data() == arr);
    CHECK(span[3] == arr[3]);
}

TEST_CASE("Span std::array construct", "[SWS_CORE], [SWS_CORE_01945]")
{
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    ara::core::Span<int> span(arr);

    CHECK(span.data() != nullptr);
    CHECK(span.size() == arr.size());
    CHECK(span[3] == arr.at(3));
}

TEST_CASE("Span std::array construct const ", "[SWS_CORE], [SWS_CORE_01946]")
{
    std::array<int, 5> const arr = {1, 2, 3, 4, 5};

    ara::core::Span<int const> span(arr);

    CHECK(span.data() != nullptr);
    CHECK(span.size() == arr.size());
    CHECK(span[3] == arr.at(3));
}

TEST_CASE("Span container construct {}", "[SWS_CORE], [SWS_CORE_01947]")
{
    std::vector<int>     vect{1, 2, 3, 4, 5};
    ara::core::Span<int> span_a{vect};


    CHECK(span_a.data() != nullptr);
    CHECK(span_a.size() == vect.size());
    CHECK(span_a[3] == vect.at(3));
}

TEST_CASE("Span container const construct {}", "[SWS_CORE], [SWS_CORE_01948]")
{
    std::vector<int> const     vect{1, 2, 3, 4, 5};
    ara::core::Span<const int> span_a{vect};


    CHECK(span_a.data() != nullptr);
    CHECK(span_a.size() == vect.size());
    CHECK(span_a[3] == vect.at(3));
}

TEST_CASE("Copy construct a new Span from another instance",
          "[SWS_CORE], [SWS_CORE_01949]")
{
    std::vector<int> const     vect{1, 2, 3, 4, 5};
    ara::core::Span<const int> span_a{vect};
    ara::core::Span<const int> span_b(span_a);


    CHECK(span_a.data() == span_b.data());
    CHECK(span_a.size() == span_b.size());
    CHECK(span_a.begin() == span_b.begin());
    CHECK(span_a.end() == span_b.end());
    CHECK(span_a[3] == span_b[3]);
}

TEST_CASE("Converting constructor", "[SWS_CORE], [SWS_CORE_01950]")
{

    int                     arr[]{0, 1, 2, 3, 4};
    ara::core::Span<int, 5> span_a(arr);
    ara::core::Span<int>    span_b(span_a);


    CHECK(span_a.data() == span_b.data());
    CHECK(span_a.size() == span_b.size());
    CHECK(span_a[3] == span_b[3]);
}

TEST_CASE("Copy assignment operator", "[SWS_CORE], [SWS_CORE_01952]")
{

    int                     arr[]{0, 1, 2, 3, 4};
    ara::core::Span<int, 5> span_a(arr);
    ara::core::Span<int>    span_b = span_a;


    CHECK(span_a.data() == span_b.data());
    CHECK(span_a.size() == span_b.size());
    CHECK(span_a[3] == span_b[3]);
}

TEST_CASE("Return a subspan containing only the first elements of this Span",
          "[SWS_CORE], [SWS_CORE_01961]")
{

    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int, 4> span_b = span_a.first(4);

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == *span_a.begin());
    int index = 0;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Subspan first(par) dynamic", "[SWS_CORE], [SWS_CORE_01962]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int> span_b = span_a.first(4);

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == *span_a.begin());
    int index = 0;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Subspan last(par) static", "[SWS_CORE], [SWS_CORE_01963]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int, 4> span_b = span_a.last(4);

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == span_b[span_b.size() - 4]);
    int index = 5;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Subspan last(par) dynamic", "[SWS_CORE], [SWS_CORE_01964]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int> span_b = span_a.last(4);

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == span_b[span_b.size() - 4]);
    int index = 5;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Return a subspan of this Span<>", "[SWS_CORE], [SWS_CORE_01965]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int> span_b = span_a.subspan<2, 4>();

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == span_b[span_b.size() - 4]);
    int index = 2;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Return a subspan of this Span()", "[SWS_CORE], [SWS_CORE_01966]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};

    ara::core::Span<int> span_b = span_a.subspan(2, 4);

    CHECK(span_b.data() != nullptr);
    CHECK(*span_b.begin() == span_b[span_b.size() - 4]);
    int index = 2;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Return the size of this Span.", "[SWS_CORE], [SWS_CORE_01967]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};
    CHECK(span_a.data() != nullptr);
    CHECK(span_a.size() == sizeof(tab) / sizeof(int));
}

TEST_CASE(" Return the size of this Span in bytes.",
          "[SWS_CORE], [SWS_CORE_01968]")
{
    int                     tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ara::core::Span<int, 9> span_a{tab};
    CHECK(span_a.data() != nullptr);
    CHECK(span_a.size_bytes() == sizeof(tab));
}

TEST_CASE("Create a new Span from the given pointer and size.",
          "[SWS_CORE], [SWS_CORE_01990]")
{
    int  tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto span_a = ara::core::MakeSpan(tab, 4);
    CHECK(span_a.data() != nullptr);
    int index = 0;
    for (auto it = span_a.begin(); it != span_a.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Create a new Span from the open range",
          "[SWS_CORE], [SWS_CORE_01991]")
{
    int  tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto span_a = ara::core::MakeSpan(&tab[2], &tab[7]);
    CHECK(span_a.data() != nullptr);
    int index = 2;
    for (auto it = span_a.begin(); it != span_a.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Create a new Span from the given raw array.",
          "[SWS_CORE], [SWS_CORE_01992]")
{
    int  tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto span_b = ara::core::MakeSpan(tab);
    CHECK(span_b.data() != nullptr);
    int index = 0;
    for (auto it = span_b.begin(); it != span_b.end(); ++it)
    {
        CHECK(*it == tab[index]);
        ++index;
    }
}

TEST_CASE("Create a new Span from the given constcontainer.",
          "[SWS_CORE], [SWS_CORE_01994]")
{
    std::vector<int> const vect{1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto span_a = ara::core::MakeSpan(vect);
    CHECK(span_a.data() == vect.data());
}