#include <iostream>
#include <memory>

using namespace std;

int main()
{
    cout << "sizeof(auto_ptr<int>): "<< sizeof(auto_ptr<int>) << endl;
    cout << "sizeof(unique_ptr<int>): "<< sizeof(unique_ptr<int>) << endl;
    cout << "sizeof(auto_ptr<double>): "<< sizeof(auto_ptr<double>) << endl;
    cout << "sizeof(unique_ptr<double>): "<< sizeof(unique_ptr<double>) << endl;
    cout << "sizeof(shared_ptr<int>): "<< sizeof(shared_ptr<int>) << endl;
    cout << "sizeof(weak_ptr<int>): "<< sizeof(weak_ptr<int>) << endl;
    cout << "sizeof(shared_ptr<double>): "<< sizeof(shared_ptr<double>) << endl;
    cout << "sizeof(weak_ptr<double>): "<< sizeof(weak_ptr<double>) << endl;
    return 0;
}
