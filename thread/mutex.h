#pragma once

#include "pthread.h"

namespace qlib {
namespace thread {

class Mutex {
  public:
    Mutex();
    ~Mutex();

    bool lock();
    bool try_lock();
    bool unlock();

  private:
    pthread_mutex_t id;
};

}
}
