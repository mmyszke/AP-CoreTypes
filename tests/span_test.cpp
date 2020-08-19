#include "ara/core/span.h"
#include <catch2/catch.hpp>
#include <vector>


TEST_CASE("Span test / array / construct", "[SWS_CORE], [SWS_CORE_01944]")

{
  constexpr int arr[]{0, 1, 2, 3, 4};
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
