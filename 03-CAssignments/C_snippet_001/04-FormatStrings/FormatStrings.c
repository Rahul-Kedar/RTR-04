#include <stdio.h>

int main(void)
{
    //code
    printf("\n\n");
    printf("***************************************************************************************************");
    printf("\n\n");

    printf("Hello World !!! \n\n");

    int a_RAK = 25;
    printf("Integer Decimal Value of 'a_RAK'                                         = %d\n", a_RAK);
    printf("Integer Octal Value of 'a_RAK'                                           = %o\n", a_RAK);
    printf("Integer Hexadecimal Value of 'a_RAK' (Hexadecimal Letters In Lower Case) = %x\n", a_RAK);
    printf("Integer Hexadecimal Value of 'a_RAK' (Hexadecimal Letters In Upper Case) = %X\n\n", a_RAK);

    char ch_RAK = 'R';
    printf("Character ch_RAK = %c\n", ch_RAK);
    char str_RAK[] = "AstroMediComp's Real Time Rendering Batch";
    printf("String str_RAK   = %s\n\n", str_RAK);

    long num_RAK = 145311647L;
    printf("Long Intger = %ld\n\n", num_RAK);

    unsigned int b_RAK = 45;
    printf("Unsinged Integer 'b_RAK' = %u\n\n", b_RAK);

    float f_num_RAK = 214.451f;
    printf("Floating Point Number With Just %%f 'f_num_RAK' = %f\n", f_num_RAK);
    printf("Floating Point Number With %%4.2f 'f_num_RAK'   = %4.2f\n", f_num_RAK);
    printf("Floating Point Number With %%6.5f 'f_num_RAK'   = %6.5f\n\n", f_num_RAK);

    double d_pi_RAK = 3.14159265358979323846;
    printf("Double Precision Floating Point Number Without Exponential                  = %g\n", d_pi_RAK);
    printf("Double Precision Floating Point Number With Exponential (Lower Case)        = %e\n", d_pi_RAK);
    printf("Double Precision Floating Point Number With Exponential (Upper CAse)        = %E\n", d_pi_RAK);
    printf("Double Hexadecimal Value Of 'd_pi_RAK' (Hexadecimal Letters In Lower Case)  = %a\n", d_pi_RAK);
    printf("Double Hexadecimal Value Of 'd_pi_RAK' (Hexadecimal Letters In Upper Case)  = %A\n", d_pi_RAK);

    printf("***************************************************************************************************");
    printf("\n\n");

    return 0;
}
