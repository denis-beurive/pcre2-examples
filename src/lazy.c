#include <stdio.h>
#include "toolbox.h"

int main() {

    printf("'(a+?)' looks for as few as possible of what's to the left\n\n");

    match_and_print("aaaa", "(a+?)");
    printf("────────────────────────────────────────\n");
    match_and_print("aaaa", "(a+)");
}