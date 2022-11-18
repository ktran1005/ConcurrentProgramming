
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
using namespace std;

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_ready = false;

void workThread() {
  std::this_thread::sleep_for(std::chrono::seconds(60));
  std::unique_lock<std::mutex> ul(g_mutex);
  g_ready = true;
//   ul.unlock();
  g_cv.notify_all();
}

void waitThread(int n) {
  std::unique_lock<std::mutex> ul(g_mutex);
  g_cv.wait(ul, [] { return g_ready; });
  std::cout << "Wait Thread "<< n<<" Executed! \n";
//   g_cv.notify_one();
}

int main() {
  std::thread t1(workThread);
  std::thread t2(waitThread,2);
  std::thread t3(waitThread,3);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}