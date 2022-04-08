#include <stdio.h>

int main(void)
{
    //function prototypes
    void PrintBinaryFormOfNumber(unsigned int);

    //Variable declarations
    unsigned int a_RAK;
    unsigned int result_RAK;

    //code
    printf("\n\n");
    printf("Enter An Integer = ");
    scanf("%u", &a_RAK);

    printf("\n\n\n\n");
    result_RAK = ~a_RAK;
    printf("Bitwise COMPLEMENTING Of \n a_RAK = %d (Decimal) gives result %d (Decimal).\n\n", a_RAK, result_RAK);

    PrintBinaryFormOfNumber(a_RAK);
    PrintBinaryFormOfNumber(result_RAK);

    return 0;
}

void PrintBinaryFormOfNumber(unsigned int decimal_number)
{
    //variable declarations
    unsigned int quotient_RAK, remainder_RAK;
    unsigned int num_RAK;
    unsigned int binary_array_RAK[8];
    int i_RAK;

    //code
    for(int i = 0; i < 8; i++)
    {
        binary_array_RAK[i] = 0;
    }

    printf("The Binary Form Of The Decimal Integer %d Is\t=\t", decimal_number);
    num_RAK = decimal_number;
    i_RAK = 7;

    while (num_RAK != 0)
    {
        quotient_RAK = num_RAK / 2;
        remainder_RAK = num_RAK % 2;
        binary_array_RAK[i_RAK] = remainder_RAK;
        num_RAK = quotient_RAK;
        i_RAK--;
    }
    
    for (i_RAK = 0; i_RAK < 8; i_RAK++)
    {
        printf("%u", binary_array_RAK[i_RAK]);
    }

    printf("\n\n");   
}
