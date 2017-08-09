#pragma once

#include "pthread.h"

namespace qlib {
namespace thread {

void* _thread(void* arg);

class Thread {
  public:
    friend void* _thread(void* arg);

  protected:
    Thread();

  public:
    virtual ~Thread();
    bool cancel();

  protected:
    bool start();
    virtual void run() = 0;

  protected:
    pthread_t id;
    volatile bool running_flag;
};

}
}
