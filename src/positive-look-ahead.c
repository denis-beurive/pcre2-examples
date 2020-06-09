#include <stdio.h>
#include "toolbox.h"

int main() {

    printf("'a(?=b)' looks for a followed by b\n\n");

    match_and_print("a","a(?=b)");
    printf("────────────────────────────────────────\n");
    match_and_print("abc","a(?=b)");
}