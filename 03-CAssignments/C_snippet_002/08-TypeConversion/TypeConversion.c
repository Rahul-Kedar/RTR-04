#include <stdio.h>

int main(void)
{
    //variable declarations
    int i_RAK, j_RAK;
    char ch_01_RAK, ch_02_RAK;

    int a_RAK, result_int_RAK;
    float f_RAK, result_float_RAK;

    int i_explicit_RAK;
    float f_explicit_RAK;

    //code
    printf("\n\n");

    //INTERCONVERSION AND IMPLICIT TYPE-CASTING BETWEEN 'char' AND 'int' TYPES...
    i_RAK = 65;
    ch_01_RAK = i_RAK;
    printf("i_RAK = %d\n", i_RAK);
    printf("Character 1 (after ch_01_RAK = i_RAK) = %c\n\n", ch_01_RAK);

    ch_02_RAK = 'R';
    j_RAK = ch_02_RAK;
    printf("Character 2 = %c\n", ch_02_RAK);
    printf("j_RAK (after j_RAK = ch_02_RAK) = %d\n\n", j_RAK);

    //IMPLICIT CONVERSION OF 'int' TO 'float'...
    a_RAK = 7;
    f_RAK = 5.4f;
    result_float_RAK = a_RAK + f_RAK;
    printf("Integer a_RAK = %d And Floating-Point Number %f Added Gives Floating-Point Sum = %f\n\n", a_RAK, f_RAK, result_float_RAK);

    result_int_RAK = a_RAK + f_RAK;
    printf("Integer a_RAK = %d And Floating-Point Number %f Added Gives Integer Sum = %d\n\n", a_RAK, f_RAK, result_int_RAK);

    //EXPLICIT TYPE-CASTING USING CAST OPERATOR...
    f_explicit_RAK = 15.45715f;
    i_explicit_RAK = (int)f_explicit_RAK;
    printf("Floating Point Number Which will Be Type Casted Explicitly = %f\n", f_explicit_RAK);
    printf("Resultant Integer After Explicit Type Casting Of %f = %d\n\n", f_explicit_RAK, i_explicit_RAK);

    return 0;
}
