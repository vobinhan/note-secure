#include "note_secure/core.hpp"

#include <gtest/gtest.h>

TEST(CoreTest, ReturnsApplicationVersion) {
    EXPECT_EQ(note_secure::application_version(), "0.1.0");
}
