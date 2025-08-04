#define NDEBUG

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>

#include "coinh.hpp"
#include "numformat.hpp"

using namespace std;

int HWCONC = std::thread::hardware_concurrency();

int main() {

    cout << "\033[1m" << "coinFlip" << "\033[0m" << endl;
    cout << endl;

    // pick hardware concurrency
    if (HWCONC >= 16) {
        HWCONC = HWCONC - 8;
    } else {
        HWCONC = HWCONC / 2;
    }

    // result variables
    uint64_t h;
    uint64_t t;

    // stop flag
    atomic<bool> stopFlag = false;

    // vector of coins
    vector<CoinNs::Coin> coinVec;
    coinVec.reserve(HWCONC);
    for (int HWCONCit = 0; HWCONCit < HWCONC; HWCONCit++) {
        coinVec.emplace_back(CoinNs::Coin(stopFlag));
    }

    // starting workers
    for (auto &myCoin : coinVec) {
        myCoin.StartWorker();
    }

    // console loop
    string ans = "";
    while (!stopFlag) {
        // input
        cout << "\033[1m" << "cflip ~ " << "\033[0m";
        cin >> ans;
        // options
        if (ans == "stop") {
            stopFlag = true;
        } else if (ans == "hwconc") {
            cout << HWCONC << endl;
            cout << endl;
        } else if (ans == "stat") {
            h = 0; t = 0;
            for (auto &myCoin : coinVec) {
                h += myCoin.GetH();
                t += myCoin.GetT();
            }
            cout << numFormat(h + t) << endl;
            cout << endl;
        }
    }

    // join threads
    for (auto &myCoin : coinVec) {
        myCoin.JoinWorker();
    }

    // zero variables
    h = 0; t = 0;
    
    // catching data
    for (auto &myCoin : coinVec) {
        h += myCoin.GetH();
        t += myCoin.GetT();
    }

    // long double
    long double hd = h;
    long double td = t;

    // output
    cout << numFormat(h + t) << endl;
    cout << hd / td << endl;
    cout << (hd / (hd + td)) * 100 << "%" << " / " << (td / (hd + td)) * 100 << "%" << endl;
    cout << numFormat(h) << "  /  " << numFormat(t) << endl;
    cout << endl;
    
    // return
    return 0;
    
}