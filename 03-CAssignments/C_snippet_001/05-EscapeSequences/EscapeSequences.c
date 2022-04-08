#include <stdio.h>

int main(void)
{
    //code
    printf("\n\n");
    printf("Going On To Next Line... Using \\n Escape Sequence By Rahul Kedar\n\n");
    printf("Demonstrating \t Horizontal \t Tab \t Using \t \\t Escape Sequence !!! By Rahul Kedar\n\n");
    printf("\"This Is A Double Quoted Output\" Done Using \\\" \\\" Escape Sequence By Rahul Kedar\n\n");
    printf("\'This Is A Single Quoted Output\' Done Using \\\' \\\' Escape Sequence By Rahul Kedar\n\n");
    printf("BACKSPACE Turned To BACKSPACE\b Using Escape Sequence \\b By Rahul Kedar\n");

    printf("\r Demonstrating Carriage Return Using \\r Escape Sequence By Rahul Kedar\n");
    printf("Demonstrating \r Carriage Return Using \\r Escape Sequence By Rahul Kedar\n");
    printf("Demonstrating Carriage \r Return Using \\r Escape Sequence By Rahul Kedar\n");

    printf("Demonstrating \x41 Using \\xhh Escape Sequence By Rahul Kedar\n\n"); //0x41 Is The Hexadecimal Code For Letter 'A'. 'xhh' Is The Place-holder For 'x' Followe By 2 digits (hh), altogether forming a Hexadecimal Number.
    printf("Demonstrating \102 Using \\ooo Escape Sequence By Rahul Kedar\n\n"); //102 Is The Octal Code For Letter 'B'. 'ooo' Is The Place-holder For 3 Digits Forming An Octal Number.

    return 0;
}
