#include <stdint.h>

int main(void){
    uint32_t reg_x1 = 19149;
    uint32_t count1 = 0;

    for(int i = 0; i < 32; i++){
        uint32_t temp = reg_x1 >> i;
        temp = temp & 1;
        if(temp == 1) {
            count1 = count1 + 1;
        } 
    }

    return count1;
}
