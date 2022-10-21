#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "library.h"
#include <doctest/doctest.h>



TEST_CASE("testing the library") {
    CHECK(library_function() == 42);
}


