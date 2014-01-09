#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

uint8_t rotate_right(uint8_t byte);

void dump(uint8_t byte);

void main(int argc, uint8_t **argv)
{
    uint8_t *key = NULL;
    uint8_t *plain = NULL;
    uint8_t *cipher = NULL;

    uint8_t *seed = NULL;
    uint8_t *rec_key = NULL;

    uint8_t temp1, temp2, byte;

    int i, j, k;
    i = j = k = 0;

    seed = malloc(11);
    key = malloc(11);
    rec_key = malloc(11);

    plain = malloc(17);
    cipher = malloc(17);

    seed[10] = '\0';
    key[10] = '\0';
    rec_key[10] = '\0';

    plain[16] = '\0';
    cipher[16] = '\0';

    for (i = 0; i < 16; i++) {
        plain[i] = argv[1][i];
    }

    for (i = 0; i < 10; i++) {
        key[i] = argv[2][i];
        seed[i] = argv[2][i];
    }

    printf("key: ");

    for (i = 0; i < 10; i++) {
        printf("%c", key[i]);
    }
    printf("\nplain: ");
    for (i = 0; i < 16; i++) {
        printf("%c", plain[i]);
    }
    printf("\n");



    for (i = 0; i < 16; i++) {

        cipher[i] = plain[i] ^ (seed[i % 10] + seed[(i + 3) % 10]);
        seed[i % 10] = rotate_right(seed[i % 10] ^ seed[(i + 5) % 10]); 

    }


    printf("\ncipher: ");
    for (i = 0; i < 16; i++) {
        printf("%c", cipher[i]);
    }

    printf("\nseed: ");
    for (i = 0; i < 10; i++) {
        printf("%c", seed[i]);
    }
    printf("\n");

    rotate_right('A');
    rotate_right(15);

    for (i = 0; i < 16; i++) {

        byte = plain[i] ^ cipher[i];
        switch (i) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                temp1 = (key[i % 10] + key[(i + 3) % 10]) % 0x100;

                if (temp1 == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                }
                /*
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                temp1 = (key[i % 10] + key[(i + 3) % 10]) % 0x100;

                if (temp1 == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                }
                */
                break;
            case 7:
            case 8:
            case 9:
                temp1 = rotate_right(key[(i + 3) % 10] ^ key[(i + 8) % 10]);
                temp2 = (key[i % 10] + temp1) % 0x100;

                if (temp2 == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                }
                break;
            case 10:
            case 11:

                temp1 = rotate_right((key[i % 10] ^ key[(i + 5) % 10]));
                temp2 = rotate_right((key[(i + 3) % 10] ^ key[(i + 8) % 10]));
                //temp1 = rotate_right((rotate_right((key[i % 10] ^ key[(i + 5) % 10])) ^ key[(i + 5)]));
                //temp2 = rotate_right((rotate_right((key[(i + 3) % 10] ^ key[(i + 8) % 10])) ^ key[(i + 8) % 10])); 

                if ((temp1 + temp2) == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                }
                break;

            case 12:
            case 13:
            case 14:
                //temp1 = rotate_right((rotate_right((key[i % 10] ^ key[(i + 5) % 10]))) ^ (rotate_right((rotate_right(
                 //               (key[(i + 8) % 10] ^ key[(i + 11) % 10]))) ^ (key[(i + 3)]))));


                //temp1 = rotate_right((rotate_right((key[i % 10] ^ key[(i + 5) % 10]))) ^ key[i % 10]);
                //temp2 = rotate_right((rotate_right((key[(i + 3) % 10] ^ key[(i + 8) % 10]))) ^ key[(i + 3) % 10]);

                temp1 = rotate_right((key[i % 10] ^ key[(i + 5) % 10]));
                temp2 = rotate_right(((key[(i + 3) % 10]) ^ (rotate_right(key[(i + 8) % 10] ^ key[(i + 3) % 10]))));

                temp1 = (temp1 + temp2) % 0x100;

                if (temp1 == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                    dump((temp1 + temp2));
                    dump(byte);
                    printf("\n");
                }
                break;
            case 15:
            default:
                temp1 = rotate_right((key[i % 10] ^ (rotate_right(key[(i + 5) % 10] ^ key[i % 10]))));
                temp2 = rotate_right((key[(i + 3) % 10] ^ (rotate_right(key[(i + 8) % 10] ^ key[(i + 3) % 10]))));

                temp1 = (temp1 + temp2) % 0x100;

                if (temp1 == byte) {
                    printf("ok\n");
                } else {
                    printf("Som Ting Wong in %d\n", i);
                    dump((temp1 + temp2));
                    dump(byte);
                    printf("\n");
                }

                printf("in default\n");

                break;
        }

    }
}

uint8_t rotate_right(uint8_t byte) {
    uint8_t temp;
    dump(byte);

    temp =  ((byte>>5) | (byte<<3)) % 0x100;
    dump(temp);

    return temp;
}
/*
uint8_t rotate_right(uint8_t byte) {
    uint8_t temp;

    temp = byte;

    dump(byte);

    byte = temp % 0x20;     // 32 = 2^5
    byte = byte * 0x08;		// 8 = 2^3
    temp = temp / 0x20;		// 32 = 2^5
    byte = byte ^ temp;

    dump(byte);

    return byte;
}
*/

void dump(uint8_t byte) {
    int i = 0;
    printf("%02x ", byte);
    for (i = 7; i >= 0; i--) {
	printf("%d", (byte >> i) & 1);
    }
    printf("\n");

}
