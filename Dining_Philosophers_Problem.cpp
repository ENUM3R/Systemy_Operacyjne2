#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <semaphore>

using namespace std;
//Autor: Cyprian Kozubek 272959, poniedziałek gr.2 7.30 TN, Projekt 1: problem ucztujących filozofów

//Synchronization of cout
mutex synchronizer;
//Function simulating dinning philosophers problem
void philosopher(int id, mutex* forks, int philosophers_number, counting_semaphore<>& eating_semaphore) {
        int left_fork = id;
        int right_fork = (id + 1) % philosophers_number;
        while (true) {
            {
                lock_guard<mutex> lock(synchronizer);
                //Simulating philosopher thinking
                cout<<"Philosopher " <<id<<" is thinking"<<endl;
            }

            this_thread::sleep_for(chrono::seconds(2));
            //Waiting to eat and picking up forks
            eating_semaphore.acquire();
            forks[left_fork].lock();
            forks[right_fork].lock();
            {
                lock_guard<mutex> lock(synchronizer);
                //Simulating philosopher eating
                cout<<"Philosopher " <<id<<" is eating"<<endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            //Putting down forks
            forks[left_fork].unlock();
            forks[right_fork].unlock();
            //Freeing space for other philosophers to eat
            eating_semaphore.release();
        }
}
int main() {
    int philosophers_number;
    cout << "Give number of philosophers: ";
    cin >> philosophers_number;
    //Number of currently possible number of eating philosophers
    counting_semaphore<> eating_semaphore(philosophers_number-1);
    //Dynamic threads and mutex arrays
    thread* philosophers_threads = new thread[philosophers_number];
    mutex* forks = new mutex[philosophers_number];
    //Creating threads
    for (int i = 0; i < philosophers_number; i++) {
        philosophers_threads[i] = thread(philosopher, i,forks,
            philosophers_number, ref(eating_semaphore));
    }
    //Threads joining
    for (int i = 0; i < philosophers_number; i++) {
        philosophers_threads[i].join();
    }
    delete[] philosophers_threads;
    delete[] forks;
    return 0;
}