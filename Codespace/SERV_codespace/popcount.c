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
    uint32_t reg_x1 = 19149;

    // 调用带返回值的 popcount，并写入 volatile sink，避免 -O2 删除计算
    popcount_sink = popcount(reg_x1);

    return popcount_sink; 
}
