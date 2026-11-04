#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {
    printf("Loading shared encryption library at runtime via dlopen()...\n");
    void *handle = dlopen("./libencrypt.so", RTLD_LAZY);
    if (!handle) handle = dlopen("./Q1/libencrypt.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }

    void (*enc_func)(const char *, char *) = dlsym(handle, "encrypt_data");
    char *err = dlerror();
    if (err) {
        fprintf(stderr, "dlsym error: %s\n", err);
        dlclose(handle);
        return 1;
    }

    char secret[] = "DynamicEncryptedPayload-RuntimeBinding";
    char enc[64];
    enc_func(secret, enc);
    printf("dlopen runtime loaded successfully!\nOriginal:  %s\nEncrypted: %s\n", secret, enc);
    dlclose(handle);
    return 0;
}
