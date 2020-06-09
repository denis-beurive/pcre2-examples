# PCRE2 examples

POSIX regex is really limited compared to Perl one. PCRE2 allows C programs to use Perl regex.

## Prerequisites

You need to download the [lasted version of PCRE](https://www.pcre.org/).

Compiling the library is pretty straightforward on most systems.
Please note that we install all the file related to the library under the local directory `lib/pcre2`.

    PROJECT=/home/denis/IdeaProjects/pcre2
    ./configure --prefix=${PROJECT}/lib/pcre2 --exec-prefix=${PROJECT}/lib/pcre2
    make
    make install 

> You should adjust the value of `PROJECT`.

## Build

    cmake . && make
    
## Test programs

* [match1](src/match1.c): simple match with capturing parentheses.
* [positive look ahead](src/positive-look-ahead.c)
* [positive look behind](src/positive-look-behind.c)
* [negative look ahead](src/negative-look-ahead.c)
* [negative look behind](src/negative-look-behind.c)
* [possessive](src/possessive.c)
* [lazy](src/lazy.c)
