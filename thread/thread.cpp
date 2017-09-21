#include "thread.h"

using namespace qlib::thread;

void* qlib::thread::_thread(void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    if (thread != nullptr) {
        thread->run();
    }

    return arg;
}

Thread::Thread() :
    id(0),
    running_flag(false)
{
}

Thread::~Thread() {
}

bool Thread::cancel() {
    int r = pthread_cancel(id);
    if (r == 0) {
        running_flag = false;
    }

    return (r == 0);
}

bool Thread::start() {
    bool flag = false;

    int rc = pthread_create(&id, nullptr, qlib::thread::_thread, this);
    if (rc == 0) {
        flag = true;
    }

    running_flag = flag;

    return flag;
}

