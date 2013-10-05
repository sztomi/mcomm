#include "gtest/gtest.h"
#include "glog/logging.h"

#include "tests/simulation/components/test_spritecomponent.h"
#include "tests/simulation/components/test_textcomponent.h"
#include "tests/simulation/components/test_transformcomponent.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::google::InitGoogleLogging(argv[0]);
    return RUN_ALL_TESTS();
}
