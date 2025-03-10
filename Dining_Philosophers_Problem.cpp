#include <iostream>
#include <thread>

using namespace std;

int main() {
    int philosophers_number = 0;
    cout << "Give number of philosophers: ";
    cin >> philosophers_number;

    thread philosophers_threads[philosophers_number];

    return 0;
}