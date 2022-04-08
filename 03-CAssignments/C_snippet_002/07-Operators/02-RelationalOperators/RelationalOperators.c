#include <stdio.h>

int main(void)
{
    //variable declarations
    int a_RAK;
    int b_RAK;
    int result_RAK;

    //code
    printf("\n\n");
    printf("Enter One Integer : ");
    scanf("%d", &a_RAK);

    printf("\n\n");
    printf("Enter Another Integer : ");
    scanf("%d", &b_RAK);

    printf("\n\n");
    printf("If Answer = 0, It Is 'FALSE'. \n");
    printf("If Answer = 1, It Is 'TRUE'. \n\n");

    result_RAK = (a_RAK < b_RAK);
    printf("(a_RAK < b_RAK)  a_RAK = %d Is Less Than b_RAK = %d                       \t Answer = %d\n", a_RAK, b_RAK, result_RAK);
    
    result_RAK = (a_RAK > b_RAK);
    printf("(a_RAK > b_RAK)  a_RAK = %d Is Greater Than b_RAK = %d                    \t Answer = %d\n", a_RAK, b_RAK, result_RAK);
    
    result_RAK = (a_RAK <= b_RAK);
    printf("(a_RAK <= b_RAK)  a_RAK = %d Is Less Than Or Equal To b_RAK = %d          \t Answer = %d\n", a_RAK, b_RAK, result_RAK);
    
    result_RAK = (a_RAK >= b_RAK);
    printf("(a_RAK >= b_RAK)  a_RAK = %d Is Greater Than Or Equal b_RAK = %d          \t Answer = %d\n", a_RAK, b_RAK, result_RAK);
    
    result_RAK = (a_RAK == b_RAK);
    printf("(a_RAK == b_RAK)  a_RAK = %d Is Equal To RAK = %d                         \t Answer = %d\n", a_RAK, b_RAK, result_RAK);
    
    result_RAK = (a_RAK != b_RAK);
    printf("(a_RAK != b_RAK)  a_RAK = %d Is NOT Equal To b_RAK = %d                   \t Answer = %d\n", a_RAK, b_RAK, result_RAK);

    return 0;
}
