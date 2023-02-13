// #include <cs50.h>
#include <stdio.h>
#include <math.h>

void validCreditCards(long long* creditCards){
    char cartType[4][16];
    strcpy(cartType[0], "AMEX");
    strcpy(cartType[1], "MASTERCARD");
    strcpy(cartType[2], "VISA");
    strcpy(cartType[3], "INVALID");
    int mulTwoVal[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9}; // {0*2, 1*2, 2*2, 3*2, 4*2, 1+0, 1+2, 1+4, 1+6, 1+8}
    int cardLength;
    long long creditCard;
    int prefix;
    int isValid;

    for(int i = 0; i < sizeof(creditCards) / sizeof(long long); i++){
        if (creditCards[i] != -1){
            creditCard = creditCards[i];
            printf("%d\n", creditCard);
            isValid = 0;

            if (creditCard < 0 || log10(creditCard) == ceil(log10(creditCard))){
                printf("Card Number: %d", creditCard);
                printf("Type: %s\n", cartType[3]);
                continue;
            }

            cardLength = ceil(log10(creditCard));

            if (checkSum(creditCard, cardLength, mulTwoVal) == 0) continue;

            if (cardLength == 15){
                prefix = creditCard / pow(10, cardLength-2);
                if (prefix == 34 || prefix == 37){
                    printf("Card Number: %d", creditCard);
                    printf("Type: %s\n", cartType[0]);
                    isValid = 1;
                }
            } else if (cardLength == 16){
                // MasterCard
                prefix = creditCard / pow(10, cardLength-2);
                if (prefix == 51 || prefix == 52 || prefix == 53 || prefix == 54 || prefix == 55){
                    printf("Card Number: %d ", creditCard);
                    printf("Type: %s\n", cartType[1]);
                    isValid = 1;
                }
                // VISA
                prefix = creditCard / pow(10, cardLength-1);
                if (prefix == 4){
                    printf("Card Number: %d", creditCard);
                    printf("Type: %s\n", cartType[2]);
                    isValid = 1;
                }
            } else if (cardLength == 13){
                prefix = creditCard / pow(10, cardLength-1);
                if (prefix == 4){
                    printf("Card Number: %d", creditCard);
                    printf("Type: %s\n", cartType[2]);
                    isValid = 1;
                }
            }

            if (!isValid){
                printf("Card Number: %d", creditCard);
                printf("Type: %s\n", cartType[3]);
            }
            
        }
    }
}

int checkSum(long long creditCard, int cardLength, int* mulTwoVal){
    int sumOne = 0;
    int sumTwo = 0;
    int digit;

    while (creditCard > 0){
        digit = creditCard % 10;

        if (digit % 2 == 0){
            sumTwo += digit;
        } else {
            sumOne += mulTwoVal[digit];
        }

        creditCard /= 10;
    }

    printf("%d %d ", creditCard, cardLength);
    printf("%d \n", sumOne + sumTwo);
    return (sumOne + sumTwo) % 10 == 0;

}

int main(void) 
{   
    long long creditCards[1] = {4003600000000014};
    validCreditCards(creditCards);
    return 0;
}