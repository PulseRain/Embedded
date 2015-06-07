#include <iostream>
#include <atomic>

int main()
{
   volatile std::atomic<uint16_t> aaa {1234};
        
    uint16_t bbb;
    
    bbb = aaa.load();
    std::cout << "bbb = " << bbb << "\n";

    aaa.store(2346); bbb = aaa.load();
    std::cout << "bbb again = " << bbb << "\n";
}
