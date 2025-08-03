#include <random>
#include <thread>
#include <iostream>
#include <atomic>

namespace CoinNs {

class Coin {
    public:
        // ctor
        Coin(std::atomic<bool> &stopFlag) : stopFlag(stopFlag) {}
        // worker
        void StartWorker() {
            thr = std::thread(&Coin::WorkerFunc, this);
        }
        void WorkerFunc() {
            // random
            std::random_device rd;
            std::mt19937 gen;
            std::bernoulli_distribution dist;
            // loop
            while (!stopFlag) {
                if (dist(gen)) {
                    h++;
                } else {
                    t++;
                }
            }
        }
        void JoinWorker() {
            thr.join();
        }
        // get data
        uint64_t GetH() {
            return h;
        }
        uint64_t GetT() {
            return t;
        }
    private:
        // thread
        std::thread thr;
        // stop flag reference
        std::atomic<bool> &stopFlag;
        // data
        uint64_t h = 0;
        uint64_t t = 0;
};

}