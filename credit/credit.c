#include <stdint.h>
#include <stdio.h>

enum CardType {INVALID = 0, AMEX, MASTERCARD, VISA};

enum CardType validCreditCards(int* C){
    enum CardType cardType;
    int8_t mulTwoVal[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9}; // {0*2, 1*2, 2*2, 3*2, 4*2, 1+0, 1+2, 1+4, 1+6, 1+8}
    int8_t i = 0;
    uint8_t bucket0_0 = 0;
    uint8_t bucket0_1 = 0;
    uint8_t bucket1_0 = 0;
    uint8_t bucket1_1 = 0;
    int8_t flag = 0;
    uint8_t checkSum = 0;

    // check prefix
    if (C[0] < 3 || C[0] > 5){
        return INVALID;
    }

    if (C[0] == 5){
        if (C[1] < 1 || C[1] > 5){
            return INVALID;
        } else {
            cardType = MASTERCARD;
        }
    } else if (C[0] == 3){
        if (!(C[1] == 4 || C[1] == 7)){
            return INVALID;
        } else {
            cardType = AMEX;
        }
    } else {
        cardType = VISA;
    }
    // finish check prefix

    // check sum and length
    while (C[i] != -1 && i < 17){
        if (flag == 0){
            bucket0_0 += C[i];
            bucket0_1 += mulTwoVal[C[i]];
            flag = 1;
        } else {
            bucket1_0 += C[i];
            bucket1_1 += mulTwoVal[C[i]];
            flag = 0;
        }
        i++;
    }

    if (i > 16) return INVALID;

    if ((i - 1) % 2 == 0){
        checkSum = bucket0_0 + bucket1_1;
    } else {
        checkSum = bucket0_1 + bucket1_0;
    }

    if (checkSum % 10 != 0) return INVALID;

    if (cardType == VISA && (i == 13 || i == 16)) return VISA;
    if (cardType == AMEX && i == 15) return AMEX;
    if (cardType == MASTERCARD && i == 16) return MASTERCARD;
    return INVALID;
}

int main(void) 
{   
    int creditCards[32] = {4, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, -1};
    enum CardType res = validCreditCards(creditCards);

    if (!res){
        // invalid format
        printf("INVALID");
        return 0;
    }

    if (res == AMEX){
        printf("AMEX");
    } else if (res == MASTERCARD){
        printf("MASTERCARD");
    } else if (res == VISA){
        printf("VISA");
    }

    return 0;
}