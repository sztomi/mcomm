#include "gtest/gtest.h"
#include "glog/logging.h"

#include "reflection/metaobjectmanager.h"

#include "tests/simulation/components/test_spritecomponent.h"
#include "tests/simulation/components/test_textcomponent.h"
#include "tests/simulation/components/test_transformcomponent.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::google::InitGoogleLogging(argv[0]);
    mcomm::MetaObjectManager::instance().bindClasses();
    return RUN_ALL_TESTS();
}
