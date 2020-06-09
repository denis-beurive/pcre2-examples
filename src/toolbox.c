#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <pcre2.h>
#include <string.h>
#include "toolbox.h"

/**
 * Match a subject against a pattern and print the captured matches.
 * @param in_subject The subject.
 * @param in_pattern The pattern.
 */

void match_and_print(char *in_subject, char *in_pattern) {

    printf("╭──\n");
    printf("│ Subject: %s\n", in_subject);
    printf("│ Pattern: %s\n", in_pattern);
    printf("╰──\n");

    pcre2_code *re;
    PCRE2_SPTR pattern = (PCRE2_SPTR)in_pattern;
    PCRE2_SIZE error_offset;
    int error_number;

    re = pcre2_compile(
            pattern,               // the pattern
            PCRE2_ZERO_TERMINATED, // indicates pattern is zero-terminated
            0,                     // default options
            &error_number,         // for error number
            &error_offset,         // for error offset
            NULL);                 // use default compile context

    if (re == NULL)
    {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(error_number, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)error_offset,
               buffer);
        return;
    }

    // --------------------------------------------------------------------
    // Perform the test
    // --------------------------------------------------------------------

    int rc;
    PCRE2_SPTR subject = (PCRE2_SPTR)in_subject;

    // Creates a new match data block, which is used for holding the result of a match.
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    if (NULL == match_data) {
        printf("Cannot allocate memory!\n");
        return;
    }

    // rc represents the number of matches.

    rc = pcre2_match(
            re,                                  // the compiled pattern
            subject,                             // the subject string
            (PCRE2_SIZE)strlen((char *)subject), // the length of the subject
            0,                                   // start at offset 0 in the subject
            0,                                   // default options
            match_data,                          // block for storing the result
            NULL);                               // use default match context

    // rc < 0: no match or error.

    if (rc < 0) {
        if (PCRE2_ERROR_NOMATCH == rc) { printf("No match\n"); }
        else { printf("An error occurred. Error code: %d\n", rc); }
        pcre2_match_data_free(match_data); // Release memory used for the match data
        pcre2_code_free(re);               // Release memory used for the compiled pattern
    }

    // rc >= 0: the subject matches.
    // - First match will be: "aaabbbccc@company.com"
    // - Second match will be: "aaabbbccc"

    PCRE2_SIZE *v = pcre2_get_ovector_pointer(match_data);

    // v[0]: start of the first match.
    // v[1]: end of the first match (last character).
    // v[2]: start of the second match.
    // v[3]: end of the second match (last character).
    //
    // v[0]     v[1] v[2]      v[3]
    // ╰───────────╯ ╰────────────╯
    //  first match   second march


    for (int i = 0; i < rc; i++)
    {
        PCRE2_SPTR substring_start = subject + v[2 * i];
        PCRE2_SIZE substring_length = v[2 * i + 1] - v[2 * i];
        printf("%2d: %.*s\n", i, (int)substring_length, (char *)substring_start);
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
}


