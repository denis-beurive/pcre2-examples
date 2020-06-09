#include <stdio.h>
#include "toolbox.h"

int main() {

    printf("'(?<=a)b' looks for b preceded by a\n\n");

    match_and_print("b","(?<=a)b");
    printf("────────────────────────────────────────\n");
    match_and_print("ab","(?<=a)b");
    printf("────────────────────────────────────────\n");
    match_and_print("cb","(?<=a)b");
}