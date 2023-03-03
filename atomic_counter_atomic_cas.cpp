#include "atomic_counters.hpp"

atomic_counter_atomic_cas::atomic_counter_atomic_cas()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_atomic_cas::increment() {
    // TODO: Modify this code using atomic compare and exchange (CAS) operations
    int exVal = m_value.load();
    while(!m_value.compare_exchange_weak(exVal, exVal + 1)){}
    return exVal;
}

int atomic_counter_atomic_cas::decrement() {
    // TODO: Modify this code using atomic compare and exchange (CAS) operations
    int exVal = m_value.load();
    while(!m_value.compare_exchange_weak(exVal, exVal - 1)){}
    return exVal;
}

void atomic_counter_atomic_cas::set(int value) {
    // TODO: Modify this code using atomic store operations
    int exVal = m_value.load();
    while(!m_value.compare_exchange_weak(exVal, value)){}
}

int atomic_counter_atomic_cas::get() {
    // TODO: Modify this code using atomic load operations
    return m_value.load();
}
