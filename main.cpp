#include <iostream>
#include "alogger.h"

using namespace std;
#define fname INFO(__PRETTY_FUNCTION__);
#define TOSTRING(val) val
bool appExit = false;

void test_1()
{
    fname;
    LOG(Alogging::ALogger::err, "LAG gayi");
    LOG(Alogging::ALogger::info,"{} An info message;", "LAG gayi");
    INFO("An info message;");
    WARN("A Warning message;");
    ERROR("An Error message;");
    DEBUG("A Debug message");
}
int main()
{
    cout << "Hello World!" << endl;
    spdlog::info("From hello");
    test_1();

    appExit = true;
    return 0;
}
