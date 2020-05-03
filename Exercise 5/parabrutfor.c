// Complie: $ gcc -fopenmp parabrutfor.c -o parabrutfor -lssl -lcrypto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <openssl/sha.h>

typedef unsigned char byte; // ASCII [0->255]

int checks(byte *a, byte *b)
{
	for (int i = 0; i < 32; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}

byte *StringHashToByteArray(const char *s)
{
	byte *hash = (byte *)malloc(32);
	char two[3];
	two[2] = 0; // two[2] = NULL.
	char *stop;
	for (int i = 0; i < 32; i++)
	{
		two[0] = s[i * 2];
		two[1] = s[i * 2 + 1];
		hash[i] = (byte)strtol(two, &stop, 16); // chuyển đổi string sang byte array[32] [ASCII]
	}
	return hash;
}

void printResult(byte *password, byte *hash)
{
	printf("%s =sha256=> ", password);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		printf("%02x", hash[i]); // chuyển ký tự hash[i] sang cơ số 16 có 2 chữ số.
	printf("\n");
}

int main(int argc, char **argv)
{
	byte *one = StringHashToByteArray("6f32ebbc1ee9cf3867df5f86f071ee147c6190ac7bfd88330fd8996a0abb512e");
	byte *two = StringHashToByteArray("33c35f8c8515b13ce15324718eccea7fb10e0c8848df3e3e0a7c0e529303828d");
	byte *three = StringHashToByteArray("dc348085d14fefa692adf1e7d97e2d59253c01189359873186d376ebe0f3ad3a");
	byte *four = StringHashToByteArray("435006d9f697e80c9b41332131b1c751523df0f1c900eb6a660294c8f52110dd");

	omp_set_dynamic(1);
	// omp_set_num_threads(4);
#pragma omp parallel
	{
		int a;
		byte password[5];
		password[4] = 0;
#pragma omp for schedule(dynamic) private(a)
		for (a = 0; a < 75; a++)
		{
			password[0] = 48 + a;
			for (password[1] = 48; password[1] < 123; password[1]++)
				for (password[2] = 48; password[2] < 123; password[2]++)
					for (password[3] = 48; password[3] < 123; password[3]++)
					{
						byte *hash = (byte *)malloc(32);
						hash = SHA256(password, strlen(password), hash);
						if (checks(one, hash) || checks(two, hash) || checks(three, hash) || checks(four, hash))
						{
							printResult(password, hash);
							// printf("\nin thread: %d", omp_get_thread_num());
						}
					}
		}
		free(one);
		free(two);
		free(three);
		free(four);
	}

	return 0;
}
