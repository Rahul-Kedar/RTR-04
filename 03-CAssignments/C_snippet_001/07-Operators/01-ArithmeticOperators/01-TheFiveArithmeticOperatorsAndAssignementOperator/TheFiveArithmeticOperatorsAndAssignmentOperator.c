#include <stdio.h>

int main(void)
{
    //variable declarations
    int a_RAK;
    int b_RAK;
    int result_RAK;

    //code
    printf("\n\n");
    printf("Enter A Number : ");
    scanf("%d", &a_RAK);

    printf("\n\n");
    printf("Enter Another Number : ");
    scanf("%d", &b_RAK);

    printf("\n\n");

    // *** The Following Are The 5 Arithmetic Operators +, -, *, / and % ***
    // *** Also, The Resultants Of The Arithmetic Operations In All The Below Five Cases Have Been Assigned To The Variable 'result_RAK' Using the Assignement Operator(=) ***
    result_RAK = a_RAK + b_RAK;
    printf("Addition Of a_RAK = %d And b_RAK = %d Gives %d.\n", a_RAK, b_RAK, result_RAK);

    result_RAK = a_RAK - b_RAK;
    printf("Subtraction Of a_RAK = %d And b_RAK = %d Gives %d.\n", a_RAK, b_RAK, result_RAK);

    result_RAK = a_RAK * b_RAK;
    printf("Multiplication Of a_RAK = %d And b_RAK = %d Gives %d.\n", a_RAK, b_RAK, result_RAK);

    result_RAK = a_RAK / b_RAK;
    printf("Division Of a_RAK = %d And b_RAK = %d Gives Quotient %d.\n", a_RAK, b_RAK, result_RAK);

    result_RAK = a_RAK % b_RAK;
    printf("Division Of a_RAK = %d And b_RAK = %d Gives Remainder %d.\n", a_RAK, b_RAK, result_RAK);

    printf("\n\n");

    return 0;
}
