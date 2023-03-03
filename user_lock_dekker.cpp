#include "user_locks.hpp"

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0].store(false);
    m_flag[1].store(false);
    m_turn.store(false);
}

void user_lock_dekker::lock(int thread_id) {
    m_flag[thread_id].store(true);
    //TSO fence
    int otherThread = thread_id == 0 ? 1 : 0;
    bool myBool = thread_id == 0 ? false : true;

    while (m_flag[otherThread].load()){
        if (m_turn.compare_exchange_weak(myBool,myBool, std::memory_order_relaxed)){
            m_flag[thread_id].store(false);
            //TSO fence
            while (!m_turn.compare_exchange_weak(myBool,myBool, std::memory_order_relaxed)) {}
            m_flag[thread_id].store(true);
            //TSO fence
        }
    }
}

void user_lock_dekker::unlock(int thread_id) {
    bool oldValue = m_turn.load();
    while (!m_turn.compare_exchange_weak(oldValue, !oldValue)) {}
    //TSO fence
    
    m_flag[thread_id].store(false);
    //TSO fence
}
