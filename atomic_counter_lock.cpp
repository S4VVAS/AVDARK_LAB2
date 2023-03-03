#include "atomic_counters.hpp"


std::mutex lock;

atomic_counter_lock::atomic_counter_lock()
    : atomic_counter()
    , m_value(0)
    , m_lock() {
}

int atomic_counter_lock::increment() {
    // TODO: Add locks here
    std::lock_guard<std::mutex> lk(lock);
    int prev_value = m_value;
    m_value = m_value + 1;
    return prev_value;
}

int atomic_counter_lock::decrement() {
    // TODO: Add locks here
    std::lock_guard<std::mutex> lk(lock);
    int prev_value = m_value;
    m_value = m_value - 1;
    return prev_value;
}

void atomic_counter_lock::set(int value) {
    // TODO: Add locks here
    std::lock_guard<std::mutex> lk(lock);
    m_value = value;
}

int atomic_counter_lock::get() {
    // TODO: Add locks here
    std::lock_guard<std::mutex> lk(lock);
    int val = m_value;
    return val;
}

//Lock guards are active locks that are monitored and released whenever 
//  the current thread exits the function the lock was locked in.
//This feature is good in case a thread crashes, as the lock will be
//  released even if a crash happends. If no lock guards were used then
//  if a crash did eventually happen, that lock wouldnt have been released
//  for other threads to be able to start working, creating a deadlock-like
//  situation.
//However compared to normal locks, lock guards are worse performing.
