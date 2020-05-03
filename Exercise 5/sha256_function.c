#include <stdio.h>
#include <string.h>
#include <string.h>
#include <omp.h>
#include <openssl/sha.h>

int main(void)
{
    const unsigned char s[5] = "tan0";
    unsigned char *d = SHA256(s, strlen(s), 0);

    int i;

    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02x-", d[i]);
    }
    putchar('\n');
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%d-", d[i]);
    }
    putchar('\n');
    return 0;
}