#include "encrypt_lib.h"

void encrypt_data(const char *in, char *out) {
    int i = 0;
    while (in[i]) {
        out[i] = in[i] ^ 0x5A; /* Simple symmetric XOR cipher */
        i++;
    }
    out[i] = '\0';
}
