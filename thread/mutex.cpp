#include "mutex.h"

using namespace qlib::thread;

Mutex::Mutex() {
    pthread_mutex_init(&id, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&id);
}

bool Mutex::lock() {
    return (pthread_mutex_lock(&id) == 0);
}

bool Mutex::try_lock() {
    return (pthread_mutex_trylock(&id) == 0);
}

bool Mutex::unlock() {
    return (pthread_mutex_unlock(&id) == 0);
}
