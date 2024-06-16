#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void example() {
    register int reg_var = 10;
    volatile int vol_var = 20;

    printf("Inside example function:\n");
    printf("Register variable (before setjmp): %d\n", reg_var);
    printf("Volatile variable (before setjmp): %d\n", vol_var);

    if (setjmp(env) == 0) {
        // Code executed after setjmp
        reg_var = 30;
        vol_var = 40;
        printf("After setjmp:\n");
        printf("Register variable: %d\n", reg_var);
        printf("Volatile variable: %d\n", vol_var);

        // Simulate change in variables
        reg_var = 50;
        vol_var = 60;
    } else {
        // Code executed after longjmp
        printf("After longjmp:\n");
        printf("Register variable: %d\n", reg_var);
        printf("Volatile variable: %d\n", vol_var);
    }
}

int main() {
    example();

    // Perform longjmp to return to the setjmp state
    longjmp(env, 1);

    // This part of code is never executed after longjmp
    printf("Back in main function after longjmp.\n");

    return 0;
}
