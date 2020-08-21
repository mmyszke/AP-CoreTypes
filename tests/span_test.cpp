#include "ara/core/span.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
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
    ara::core::Span span(arr);

    CHECK(span.data() == arr);
    CHECK(span[3] == arr[3]);
}

TEST_CASE("Span std::array construct", "[SWS_CORE], [SWS_CORE_01945]")

{
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    ara::core::Span<int> span(arr);

    CHECK(span.data() != NULL);
    CHECK(span.size() == arr.size());
    CHECK(span[3] == arr.at(3));
}

TEST_CASE("Span std::array construct const ", "[SWS_CORE], [SWS_CORE_01946]")

{
    std::array<int, 5> const arr = {1, 2, 3, 4, 5};

    ara::core::Span<int const> span(arr);

    CHECK(span.data() != NULL);
    CHECK(span.size() == arr.size());
    CHECK(span[3] == arr.at(3));
}
TEST_CASE("Span container construct {}", "[SWS_CORE], [SWS_CORE_01947]")

{
    std::vector<int>     vect{1, 2, 3, 4, 5};
    ara::core::Span<int> span_a{vect};


    CHECK(span_a.data() != NULL);
    CHECK(span_a.size() == vect.size());
    CHECK(span_a[3] == vect.at(3));
}
TEST_CASE("Span container const construct {}", "[SWS_CORE], [SWS_CORE_01948]")

{
    std::vector<int> const     vect{1, 2, 3, 4, 5};
    ara::core::Span<const int> span_a{vect};


    CHECK(span_a.data() != NULL);
    CHECK(span_a.size() == vect.size());
    CHECK(span_a[3] == vect.at(3));
}

TEST_CASE("Subspan first(par)", "[SWS_CORE], [SWS_CORE_01962]")

{
    int            tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::span<int> span{tab};

    ara::core::Span<int, 4> span_a = span.first(4);

    CHECK(span_a.data() != NULL);
    CHECK(*span_a.begin() == *span.begin());
    CHECK(*span_a.end() == span[4]);
}

TEST_CASE("Subspan last(par)", "[SWS_CORE], [SWS_CORE_01963]")

{
    int tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::span<int>          span{tab};
    ara::core::Span<int, 4> span_a = span.last(4);

    CHECK(span_a.data() != NULL);
    CHECK(*span_a.begin() == span[span.size() - 4]);
    CHECK(*span_a.end() == *span.end());
}
