#include <stdio.h>
#include "toolbox.h"

int main() {

    printf("'a++' matches as many \"a\" as possible, but never gives back\n\n");

    // 'a++' matches "aaaa".
    // Thus "aaaa" does not match 'a++.' because there is no more character for the last ".".
    match_and_print("aaaa", "a++.");
    printf("────────────────────────────────────────\n");
    match_and_print("aaaa", "a++");
}