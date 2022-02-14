#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

class A
{
public:
    A(double money = 100):m_money(money) {}
    void dis()
    {
        cout << "m_money: " << m_money << endl;
    }
//private:
    double m_money;
    std::mutex m_mutex;
};
//class B
//{
//public:
//    B(double money = 200):m_money(money) {}

//    double m_money;
//    std::mutex m_mutex;
//};
void transfermoney(A& a,A& b,double money)
{
    if(&a == &b)
    {
        return;
    }
   // std::lock(a.m_mutex,b.m_mutex);
    //lock_guard<mutex> locka(a.m_mutex,std::adopt_lock);
//	this_thread::sleep_for(chrono::seconds(0));
  //  lock_guard<mutex> lockb(b.m_mutex,std::adopt_lock);


	lock_guard<mutex> locka(a.m_mutex);
	this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lockb(b.m_mutex);
    a.m_money -= money;
    b.m_money += money;
}
int main(int argc, char *argv[])
{
    A a;
    A b;
    thread t1([&](){transfermoney(a,b,10);});
    thread t2([&](){transfermoney(b,a,50);});
    t1.join();
    t2.join();
    cout << "transfer finished" << endl;
    a.dis();
    b.dis();
    return 0;
}


#if 0
class Count
{
public:
    Count() {}
    int getcount() const
    {
        m_mutex.lock();
        return m_count;
        m_mutex.unlock();
    }
private:
    int m_count;
    mutable std::mutex m_mutex;
};
void func()
{

}
int main()
{
    thread t(func);
    t.join();
    return 0;
}
#endif
