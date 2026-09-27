#include <stdint.h>
uint8_t enable(uint8_t ctrl) { return 0x01u; }
uint8_t set_mode(uint8_t ctrl, uint8_t mode) {
    return ctrl | (mode << 1);
}
uint8_t disable(uint8_t ctrl) { return 0; }
uint8_t is_ready(uint8_t status) {
    return status == 0x08u;
}
