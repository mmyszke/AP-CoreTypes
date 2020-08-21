#include "ara/core/span.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
#include <vector>

TEST_CASE("Span test / array / construct", "[SWS_CORE], [SWS_CORE_01944]")

{
    constexpr int   arr[]{0, 1, 2, 3, 4};
    ara::core::Span span{arr};

    CHECK(span.data() == arr);
    CHECK(span[3] == arr[3]);
}

TEST_CASE("Span vector construct", "[SWS_CORE], [SWS_CORE_01944]")

{
    std::vector<int> vect{1, 2, 3, 4, 5};

    ara::core::Span<int> span;
    span = vect;

    CHECK(span.data() != NULL);
    CHECK(span.size() == vect.size());
    CHECK(span[3] == vect.at(3));
}

TEST_CASE("Span vector construct {}", "[SWS_CORE], [SWS_CORE_01944]")

{
    std::vector<int> vect{1, 2, 3, 4, 5};

    ara::core::Span<int> span{vect};


    CHECK(span.data() != NULL);
    CHECK(span.size() == vect.size());
    CHECK(span[3] == vect.at(3));
}

TEST_CASE("Subspan first(par)", "[SWS_CORE], [SWS_CORE_01962]")

{
    int tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    ara::core::Span<int> span{tab};

    ara::core::Span<int, 4> span_f = span.first(4);

    CHECK(span_f.data() != NULL);
    CHECK(*span_f.end() == tab[4]);
}

TEST_CASE("Subspan last(par)", "[SWS_CORE], [SWS_CORE_01963]")

{
    int tab[9]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    ara::core::Span<int> span{tab};

    ara::core::Span<int, 4> span_f = span.last(4);

    CHECK(span_f.data() != NULL);
    CHECK(*span_f.end() == tab[9]);
}