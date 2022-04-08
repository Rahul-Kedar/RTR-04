#include <stdio.h>

int main(void)
{
    //variable declarations
    int a_RAK = 10;
    int b_RAK = 15;

    //code
    printf("\n\n");
    printf("a_RAK = %d\n", a_RAK);
    printf("a_RAK = %d\n", a_RAK++);
    printf("a_RAK = %d\n", a_RAK);
    printf("a_RAK = %d\n\n", ++a_RAK);
    
    printf("b_RAK = %d\n", b_RAK);
    printf("b_RAK = %d\n", b_RAK--);
    printf("b_RAK = %d\n", b_RAK);
    printf("b_RAK = %d\n\n", --b_RAK);

    return 0;
}
