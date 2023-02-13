// #include <cs50.h>
#include <stdio.h>
#include <math.h>

int checkSum(long long creditCard, int cardLength, int* mulTwoVal){
    int sumOne = 0;
    int sumTwo = 0;
    int digit;
    int idx = 0;

    while (creditCard > 0){
        digit = creditCard % 10;
        
        if (idx % 2 == 0){
            sumTwo += digit;
        } else {
            sumOne += mulTwoVal[digit];
        }

        creditCard /= 10;
        idx ++;
    }

    if ((sumOne + sumTwo) % 10 == 0){
        return 1;
    } else {
        return 0;
    }

}

void validCreditCards(long long* creditCards, int arrSize){
    // char cartType[4][16];
    // strcpy(cartType[0], "AMEX");
    // strcpy(cartType[1], "MASTERCARD");
    // strcpy(cartType[2], "VISA");
    // strcpy(cartType[3], "INVALID");
    int mulTwoVal[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9}; // {0*2, 1*2, 2*2, 3*2, 4*2, 1+0, 1+2, 1+4, 1+6, 1+8}
    int cardLength;
    long long creditCard;
    int prefix;
    int isValid;

    for(int i = 0; i < arrSize; i++){
        
        if (creditCards[i] != -1){
            creditCard = creditCards[i];
            isValid = 0;

            cardLength = ceil(log10(creditCard));

            if (creditCard < 0 || checkSum(creditCard, cardLength, mulTwoVal) == 0){
                printf("Card Number: %lld ", creditCard);
                printf("Type: %s\n", "INVALID");
                printf("\n");
                continue;
            }

            if (cardLength == 15){
                prefix = creditCard / pow(10, cardLength-2);
                if (prefix == 34 || prefix == 37){
                    printf("Card Number: %lld ", creditCard);
                    printf("Type: %s\n", "AMEX");
                    printf("\n");
                    isValid = 1;
                }
            } else if (cardLength == 16){
                // MasterCard
                prefix = creditCard / pow(10, cardLength-2);
                if (prefix == 51 || prefix == 52 || prefix == 53 || prefix == 54 || prefix == 55){
                    printf("Card Number: %lld ", creditCard);
                    printf("Type: %s\n", "MASTERCARD");
                    printf("\n");
                    isValid = 1;
                }
                // VISA
                prefix = creditCard / pow(10, cardLength-1);
                if (prefix == 4){
                    printf("Card Number: %lld ", creditCard);
                    printf("Type: %s\n", "VISA");
                    printf("\n");
                    isValid = 1;
                }
            } else if (cardLength == 13){
                prefix = creditCard / pow(10, cardLength-1);
                if (prefix == 4){
                    printf("Card Number: %lld ", creditCard);
                    printf("Type: %s\n", "VISA");
                    printf("\n");
                    isValid = 1;
                }
            }

            if (!isValid){
                printf("Card Number: %lld ", creditCard);
                printf("Type: %s\n", "INVALID");
                printf("\n");
            }
            
        }
    }
}

int main(void) 
{   
    long long creditCards[4] = {33333, 4003600000000014, -1, 6176292929};
    validCreditCards(creditCards, 4);
    return 0;
}