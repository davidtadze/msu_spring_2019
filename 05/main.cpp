#include<mutex>
#include<thread>
#include<iostream>

const int MAX_HITS = 100000;

std::mutex m;
int counter = 0;

void ping(){
  while(counter < MAX_HITS - 1){
    if(counter % 2 == 0){
      std::lock_guard<std::mutex> lock(m);
      std::cout << "ping" << std::endl;

      ++counter;
    }

    std::this_thread::yield();
  }
}

void pong(){
  while(counter < MAX_HITS){
    if(counter % 2 == 1){
      std::lock_guard<std::mutex> lock(m);
      std::cout << "pong" << std::endl;

      ++counter;
    }

    std::this_thread::yield();
  }
}


int main(){
  std::thread t1(ping);
  std::thread t2(pong);

  t1.join();
  t2.join();

  return 0;
}