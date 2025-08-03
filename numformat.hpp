#include <string>
#include <sstream>
#include <iomanip>

std::string numFormat(uint64_t num) {
    std::string numStr = std::to_string(num);
    std::string resStr;
    int chrCount = 0;
    for (int i = static_cast<int>(numStr.size()) - 1; i >= 0; --i) {
        resStr.insert(0, 1, numStr[i]);
        chrCount++;
        if (chrCount % 3 == 0 && i != 0) {
            resStr.insert(0, 1, ' ');
        }
    }
    return resStr;
}