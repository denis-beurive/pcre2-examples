#include <stdio.h>
#include "toolbox.h"

int main() {

    printf("'a(?!b)' looks for a not followed by b\n\n");

    match_and_print("a","a(?!b)");
    printf("────────────────────────────────────────\n");
    match_and_print("a","^a(?!b)$");
    printf("────────────────────────────────────────\n");
    match_and_print("ac","a(?!b)");
    printf("────────────────────────────────────────\n");
    match_and_print("ac","a(?!b)$");
    printf("────────────────────────────────────────\n");
    match_and_print("ac","a(?!b).");
    printf("────────────────────────────────────────\n");
    match_and_print("ac","^a(?!b).$");
}