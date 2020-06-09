// This program illustrates a simple match.

// The PCRE2_CODE_UNIT_WIDTH macro must be defined before including pcre2.h.
// For a program that uses only one code unit width, setting it to 8, 16, or 32
// makes it possible to use generic function names such as pcre2_compile(). Note
// that just changing 8 to 16 (for example) is not sufficient to convert this
// program to process 16-bit characters. Even in a fully 16-bit environment, where
// string-handling functions such as strcmp() and printf() work with 16-bit
// characters, the code for handling the table of named substrings will still need
// to be modified.

#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <pcre2.h>
#include <string.h>

int main() {

    // --------------------------------------------------------------------
    // Compile the pattern
    // --------------------------------------------------------------------

    pcre2_code *re;
    PCRE2_SPTR pattern = (PCRE2_SPTR)"^([a,b,c]+)@company\\.com$";
    PCRE2_SIZE error_offset;
    int error_number;

    re = pcre2_compile(
            pattern,               // the pattern
            PCRE2_ZERO_TERMINATED, // indicates pattern is zero-terminated
            0,                     // default options
            &error_number,         // for error number
            &error_offset,         // for error offset
            NULL);                 // use default compile context

    // Options are (https://www.pcre.org/current/doc/html/pcre2_compile.html):
    //
    //  PCRE2_ANCHORED           Force pattern anchoring
    //  PCRE2_ALLOW_EMPTY_CLASS  Allow empty classes
    //  PCRE2_ALT_BSUX           Alternative handling of \u, \U, and \x
    //  PCRE2_ALT_CIRCUMFLEX     Alternative handling of ^ in multiline mode
    //  PCRE2_ALT_VERBNAMES      Process backslashes in verb names
    //  PCRE2_AUTO_CALLOUT       Compile automatic callouts
    //  PCRE2_CASELESS           Do caseless matching
    //  PCRE2_DOLLAR_ENDONLY     $ not to match newline at end
    //  PCRE2_DOTALL             . matches anything including NL
    //  PCRE2_DUPNAMES           Allow duplicate names for subpatterns
    //  PCRE2_ENDANCHORED        Pattern can match only at end of subject
    //  PCRE2_EXTENDED           Ignore white space and # comments
    //  PCRE2_FIRSTLINE          Force matching to be before newline
    //  PCRE2_LITERAL            Pattern characters are all literal
    //  PCRE2_MATCH_INVALID_UTF  Enable support for matching invalid UTF
    //  PCRE2_MATCH_UNSET_BACKREF  Match unset backreferences
    //  PCRE2_MULTILINE          ^ and $ match newlines within data
    //  PCRE2_NEVER_BACKSLASH_C  Lock out the use of \C in patterns
    //  PCRE2_NEVER_UCP          Lock out PCRE2_UCP, e.g. via (*UCP)
    //  PCRE2_NEVER_UTF          Lock out PCRE2_UTF, e.g. via (*UTF)
    //  PCRE2_NO_AUTO_CAPTURE    Disable numbered capturing paren-
    //                            theses (named ones available)
    //  PCRE2_NO_AUTO_POSSESS    Disable auto-possessification
    //  PCRE2_NO_DOTSTAR_ANCHOR  Disable automatic anchoring for .*
    //  PCRE2_NO_START_OPTIMIZE  Disable match-time start optimizations
    //  PCRE2_NO_UTF_CHECK       Do not check the pattern for UTF validity
    //                             (only relevant if PCRE2_UTF is set)
    //  PCRE2_UCP                Use Unicode properties for \d, \w, etc.
    //  PCRE2_UNGREEDY           Invert greediness of quantifiers
    //  PCRE2_USE_OFFSET_LIMIT   Enable offset limit for unanchored matching
    //  PCRE2_UTF                Treat pattern and subjects as UTF strings

    if (re == NULL)
    {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(error_number, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)error_offset,
               buffer);
        return 1;
    }

    // --------------------------------------------------------------------
    // Perform the test
    // --------------------------------------------------------------------

    int rc;
    PCRE2_SPTR subject = (PCRE2_SPTR)"aaabbbccc@company.com";

    // Creates a new match data block, which is used for holding the result of a match.
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
    if (NULL == match_data) {
        printf("Cannot allocate memory!\n");
        return EXIT_FAILURE;
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
    printf("Match succeeded at offset %d\n", (int)v[0]);

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

    // --------------------------------------------------------------------
    // An example that does not match
    // --------------------------------------------------------------------

    subject = (PCRE2_SPTR)"aaabbbccc@company.com-";
    rc = pcre2_match(
            re,                                  // the compiled pattern
            subject,                             // the subject string
            (PCRE2_SIZE)strlen((char *)subject), // the length of the subject
            0,                                   // start at offset 0 in the subject
            0,                                   // default options
            match_data,                          // block for storing the result
            NULL);                               // use default match context

    if (rc < 0) {
        printf("The subject does not match. This is the expected result.\n");
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    return EXIT_SUCCESS;
}
