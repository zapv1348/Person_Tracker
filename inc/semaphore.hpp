#include <mutex>

class semaphore{
    private:
        int count;
        std::mutex sem_mutex;
    public:
        semaphore(int count=0);
        void give_Mult(int to_give);
        void take();
        bool try_Take();
        bool is_Done();
};
