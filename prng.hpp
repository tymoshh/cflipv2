#include <cstdint>
#include <stdexcept>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <wincrypt.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

namespace PrngNs {

uint32_t getSeed() {
#if defined(_WIN32) || defined(_WIN64)
    HCRYPTPROV hProvider = 0;
    if (!CryptAcquireContext(&hProvider, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("CryptAcquireContext failed");
    }

    uint32_t seed = 0;
    if (!CryptGenRandom(hProvider, sizeof(seed), reinterpret_cast<BYTE*>(&seed))) {
        CryptReleaseContext(hProvider, 0);
        throw std::runtime_error("CryptGenRandom failed");
    }

    CryptReleaseContext(hProvider, 0);
    return seed;

#else
    // Unix-like /dev/urandom
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        throw std::runtime_error("Failed to open /dev/urandom");
    }

    uint32_t seed = 0;
    ssize_t result = read(fd, &seed, sizeof(seed));
    close(fd);

    if (result != sizeof(seed)) {
        throw std::runtime_error("Failed to read enough bytes from /dev/urandom");
    }

    return seed;
#endif
}

struct XorShift32 {
    // vars
    uint32_t currentSeed;
    uint32_t bitBuffer = 0;
    uint32_t bitsLeft = 0;
    // constructor
    XorShift32() : currentSeed(getSeed()) {}
    // state changer
    inline uint32_t ChangeState() {
        uint32_t x = currentSeed;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        currentSeed = x;
        return x;
    }
    // getbool
    inline bool GetBoolByBit() {
        if (bitsLeft == 0) {
            bitBuffer = ChangeState();
            bitsLeft = 32;
        }
        bool result = bitBuffer & 1;
        bitBuffer >>= 1;
        --bitsLeft;
        return result;
    }
    inline bool GetBool() {
        return ChangeState() & 1;
    }
};

}