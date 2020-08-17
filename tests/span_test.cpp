#include <catch2/catch.hpp>

#include "ara/core/span.h"

TEST_CASE("Span test / insert / at",
          "[SWS_CORE], [SWS_CORE_01944]")
>>>>>>> Add test file
{
    constexpr int arr[] { 0, 1, 2, 3, 4 };
    ara::core::Span span{arr};


    CHECK(span.data() == arr);
}

