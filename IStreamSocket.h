#ifndef ISTREAMSOCKET_H
#define ISTREAMSOCKET_H
#include <iostream>
using namespace std;
struct IStreamSocket {
    void send(const std::string& data) { cout << __PRETTY_FUNCTION__ << " " << data << endl;};
    void flush(){};
};

#endif // ISTREAMSOCKET_H
