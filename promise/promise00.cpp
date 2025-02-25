// promise example
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

void print_int (std::future<int>& fut) {
  std::cout << "thread " << std::this_thread::get_id() << " waitting for x";
  while (fut.wait_for(std::chrono::seconds(1)) == std::future_status::timeout)
  {
    std::cout <<"."<<std::flush;
  }
  int x = fut.get();
  std::cout << "thread " << std::this_thread::get_id() << " get value: " << x << '\n';
}

int main ()
{
  std::promise<int> prom;                      // create promise

  std::future<int> fut = prom.get_future();    // engagement with future
 
  std::thread th1 (print_int, std::ref(fut));  // send future to new thread
  std::this_thread::sleep_for(std::chrono::seconds(5));
  
  //mutex.lock();
  std::cout << std::endl << "thread " << std::this_thread::get_id() << " ready to set value" << std::endl << std::flush;
 // mutex.unlock();

  prom.set_value (10);                         // fulfill promise
                                               // (synchronizes with getting the future)
  th1.join();
  return 0;
}