#include "ara/core/span.h"
#include <catch2/catch.hpp>
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
TEST_CASE("Span from span ", "[SWS_CORE], [SWS_CORE_01944]")

{
    std::vector<int> vect{1, 2, 3, 4, 5};

    ara::core::Span<int> span{vect};
    ara::core::Span<int> span2{span};


    CHECK(span2.data() != NULL);
    CHECK(span2.size() == vect.size());
    CHECK(span2[3] == vect.at(3));
}
TEST_CASE("Span string test ", "[SWS_CORE], [SWS_CORE_01944]")

{
    std::string test_str{"Test string"};

    ara::core::Span<std::string> span{test_str};


    CHECK(span.data() != NULL);
    CHECK(span.size() == test_str.size());
    CHECK(span[3] == test_str.at(3));
}