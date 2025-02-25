// future::share
#include <iostream>       // std::cout
#include <future>         // std::async, std::future, std::shared_future

int get_value() { return 10; }

int main ()
{
  std::future<int> fut = std::async (get_value);
  std::shared_future<int> shfut = fut.share();

  // shared futures can be accessed multiple times:
  std::cout << "value: " << shfut.get() << '\n';
  std::cout << "its double: " << shfut.get()*2 << '\n';
  if (fut.valid()) {
    std::cout << "After future::share(), the share state is valid" << std::endl;
  } else {
    std::cout << "After future::share(), the share state is invalid" << std::endl;
  }
  return 0;
}