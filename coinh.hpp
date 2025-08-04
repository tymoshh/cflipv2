#include <random>
#include <thread>
#include <iostream>
#include <atomic>
#include <cstdint>

#include "prng.hpp"

namespace CoinNs {

class Coin {
    public:
        // ctor
        Coin(std::atomic<bool> &stopFlag) : stopFlag(stopFlag) {}
        // worker
        void StartWorker() {
            thr = std::thread(&Coin::WorkerFuncV2, this);
        }
        void WorkerFuncV1() {
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
        void WorkerFuncV2() {
            // random
            PrngNs::XorShift32 LocalRng;
            // loop v1
            while (!stopFlag) {
                if (LocalRng.GetBool()) {
                    h++;
                } else {
                    t++;
                }
            }
        }
        void WorkerFuncV3() {
            // random
            PrngNs::XorShift32 LocalRng;
            // loop v2
            while (!stopFlag) {
                if (LocalRng.GetBoolByBit()) {
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