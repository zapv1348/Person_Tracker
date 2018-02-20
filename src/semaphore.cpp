#include "semaphore.hpp"

semaphore::semaphore(int count){
    this->count=count;
}

void semaphore::give_Mult(int to_give){
    this->sem_mutex.lock();
    this->count+=to_give;
    this->sem_mutex.unlock();
}

void semaphore::take(){
    this->sem_mutex.lock();
    while (this->count==0); 
    this->count--;
    this->sem_mutex.unlock();
}

bool semaphore::try_Take(){
   if(this->sem_mutex.try_lock()){
        this->count--;
        this->sem_mutex.unlock();
        return true;
   }
   return false;
}

bool semaphore::is_Done(){
   if(this->try_Take()){
        this->give_Mult(1);
        return true;
   }
   return false; 
}
