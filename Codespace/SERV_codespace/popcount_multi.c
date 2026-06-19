#include <stdint.h>

volatile uint32_t popcount_sink;

__attribute__((noinline, used)) uint32_t popcount(uint32_t in_reg){
    uint32_t count0 = 0;
    uint32_t count1 = 0;

    for(int i = 0; i < 32; i++){
        uint32_t temp = in_reg >> i;
        temp = temp & 1;
        if(temp == 1) {
            count1 = count1 + 1;
        } else {
            count0 = count0 + 1;
        }
    }

    return count1;
}

int main(void){
    for (uint32_t i = 1; i <= 200; i++) {
        popcount_sink = popcount(i);
    }

    return popcount_sink; 
}
