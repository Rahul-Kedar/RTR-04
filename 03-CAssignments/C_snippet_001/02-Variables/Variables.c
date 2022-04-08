#include <stdio.h>

int main(void)
{
    // variable  declarations
    int i_RAK = 10;
    float f_RAK = 5.7f;
    double d_RAK = 4.1526;
    char c_RAK = 'R';

    //code 
    printf("\n\n");
    
    printf("i_RAK = %d\n", i_RAK);
    printf("f_RAK = %f\n", f_RAK);
    printf("d_RAK = %lf\n", d_RAK);
    printf("c_RAK = %c\n", c_RAK);

    printf("\n\n");

    i_RAK = 57;
    f_RAK = 6.15f;
    d_RAK = 62.1537;
    c_RAK = 'K';

    printf("i_RAK = %d\n", i_RAK);
    printf("f_RAK = %f\n", f_RAK);
    printf("d_RAK = %lf\n", d_RAK);
    printf("c_RAK = %c\n", c_RAK);

    printf("\n\n");

    return 0;
}
