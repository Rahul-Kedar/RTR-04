#include <stdio.h>

int main(void)
{
    //variable declarations
    int a_RAK;
    int b_RAK;
    int c_RAK;
    int result_RAK;

    //code
    printf("\n\n");
    printf("Enter First Integer : ");
    scanf("%d", &a_RAK);

    printf("\n\n");
    printf("Enter Second Integer : ");
    scanf("%d", &b_RAK);
    
    printf("\n\n");
    printf("Enter Third Integer : ");
    scanf("%d", &c_RAK);

    printf("\n\n");
    printf("If Answer = 0, It Is 'FALSE'. \n");
    printf("If Answer = 1, It Is 'TRUE'. \n\n");

    result_RAK = (a_RAK <= b_RAK) && (b_RAK != c_RAK);
    printf("LOGICAL AND (&&) : Answer is TRUE (1) If And Only If BOTH Conditions Are True. The Answer is FALSE (0), IF Any Or Both Conditions Are False.\n\n");
    printf("a_RAK = %d Is Less Than Or Equal To b_RAK = %d AND b_RAK = %d Is NOT Equal To c_RAK = %d    \t Answer = %d\n\n", a_RAK, b_RAK, b_RAK, c_RAK, result_RAK);

    result_RAK = (b_RAK >= a_RAK) || (a_RAK == c_RAK);
    printf("LOGICAL OR (||) : Answer is FALSE (0) If And Only If BOTH Conditions Are False. The Answer is TRUE (1), If Any One Or Both Conditions Are True.\n\n");
    printf("Either b_RAK = %d Is Greater Than Or Equal To a_RAK = %d OR a_RAK = %d Is Equal To c_RAK = %d \t Answer = %d \n\n", b_RAK, a_RAK, a_RAK, c_RAK, result_RAK);

    result_RAK = !a_RAK;
    printf("a_RAK = %d And Using Logical NOT (!) Operator on a_RAK Gives Result = %d\n\n", a_RAK, result_RAK);

    result_RAK = !b_RAK;
    printf("b_RAK = %d And Using Logical NOT (!) Operator on b_RAK Gives Result = %d\n\n", b_RAK, result_RAK);
    
    result_RAK = !c_RAK;
    printf("c_RAK = %d And Using Logical NOT (!) Operator on a_RAK Gives Result = %d\n\n", c_RAK, result_RAK);

    result_RAK = (!(a_RAK <= b_RAK) && !(b_RAK != c_RAK));
    printf("Using Logical NOT (!) On (a_RAK <= b_RAK) And Also On (b_RAK != c_RAK) And then ANDing Them Afterwards Gives Result = %d\n", result_RAK);

    printf("\n\n");

    result_RAK = !((b_RAK >= a_RAK) || (a_RAK == c_RAK));
    printf("Using Logical NOT (!) On Entire Logical Expression (b_RAK >= a_RAK) || (a_RAK == c_RAK) Gives Result = %d\n", result_RAK);

    printf("\n\n");

    return 0;
}