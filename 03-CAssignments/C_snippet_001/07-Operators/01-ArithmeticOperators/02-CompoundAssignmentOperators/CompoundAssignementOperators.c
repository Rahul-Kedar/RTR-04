#include <stdio.h>

int main(void)
{
    //variable declarations
    int a_RAK;
    int b_RAK;
    int x_RAK;

    //code
    printf("\n\n");
    printf("Enter A Number : ");
    scanf("%d", &a_RAK);
    
    printf("\n\n");
    printf("Enter Another Number : ");
    scanf("%d", &b_RAK);

    printf("\n\n");

    //Since, In All The Following 5 Cases, The Operator On The Left 'a_RAK' Is Getting Repeated Immeiately On The Right (e.g a_RAK = a_RAK + b_RAK or a_RAK = a_RAK - b_RAK),
    //We Are Using Compound Assignement Operator +=, -=, *=, /= and %=

    //Since, 'a_RAK' will Be Assigned The Value of (a_RAK + b_RAK) At The Expression (a_RAK += b_RAK), We Must Save The Orignal Value Of 'a_RAK' To Another Variable (x_RAK)
    x_RAK = a_RAK;
    a_RAK += b_RAK; // a_RAK = a_RAK + b_RAK
    printf("Addition Of a_RAK = %d And b_RAK = %d Gives %d.\n", x_RAK, b_RAK, a_RAK);

    //Value Of 'a_RAK' Altered In The Above Expression Is Used Here...
    //Since, 'a_RAK' will Be Assigned The Value of (a_RAK - b_RAK) At The Expression (a_RAK -= b_RAK), We Must Save The Orignal Value Of 'a_RAK' To Another Variable (x_RAK)
    x_RAK = a_RAK;
    a_RAK -= b_RAK; // a_RAK = a_RAK - b_RAK
    printf("Subtraction Of a_RAK = %d And b_RAK = %d Gives %d.\n", x_RAK, b_RAK, a_RAK);
    
    //Value Of 'a_RAK' Altered In The Above Expression Is Used Here...
    //Since, 'a_RAK' will Be Assigned The Value of (a_RAK * b_RAK) At The Expression (a_RAK *= b_RAK), We Must Save The Orignal Value Of 'a_RAK' To Another Variable (x_RAK)
    x_RAK = a_RAK;
    a_RAK *= b_RAK; // a_RAK = a_RAK * b_RAK
    printf("Multiplication Of a_RAK = %d And b_RAK = %d Gives %d.\n", x_RAK, b_RAK, a_RAK);
    
    //Value Of 'a_RAK' Altered In The Above Expression Is Used Here...
    //Since, 'a_RAK' will Be Assigned The Value of (a_RAK / b_RAK) At The Expression (a_RAK /= b_RAK), We Must Save The Orignal Value Of 'a_RAK' To Another Variable (x_RAK)
    x_RAK = a_RAK;
    a_RAK /= b_RAK; // a_RAK = a_RAK / b_RAK
    printf("Division Of a_RAK = %d And b_RAK = %d Gives Quotient %d.\n", x_RAK, b_RAK, a_RAK);
    
    //Value Of 'a_RAK' Altered In The Above Expression Is Used Here...
    //Since, 'a_RAK' will Be Assigned The Value of (a_RAK % b_RAK) At The Expression (a_RAK %= b_RAK), We Must Save The Orignal Value Of 'a_RAK' To Another Variable (x_RAK)
    x_RAK = a_RAK;
    a_RAK %= b_RAK; // a_RAK = a_RAK % b_RAK
    printf("Division Of a_RAK = %d And b_RAK = %d Gives Remainder %d.\n", x_RAK, b_RAK, a_RAK);

    printf("\n\n");

    return 0;
}