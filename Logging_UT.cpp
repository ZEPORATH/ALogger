#include <iostream>
#include "alogger.h"
#include <spdlog/spdlog.h>
#include <gtest/gtest.h>
void setup()
{

}
TEST(Logger, GlobalLogging)
{
    spdlog::info("{} An info message;", __PRETTY_FUNCTION__);
    spdlog::warn("{} A Warning message;", __PRETTY_FUNCTION__);
    spdlog::error("{} An Error message;", __PRETTY_FUNCTION__);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();;
}
