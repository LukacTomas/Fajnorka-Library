/**
 * Fajnorka Library for C
 * https://github.com/LukacTomas/Fajnorka-Library.git
 * 
 * Library inspired by cs50 library 
 * and Learn the C hard way book by Zed Shaw 
 * 
 * Author: Lukac Tomas
 * email: lukactv@gmail.com
 * 
 *  Copyright (c) 2020
 *  All rights reserved
 * 
 * BSD 3-Clause License
 * http://www.opensource.org/licenses/BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of CS50 nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef FAJNORKA_H_INCLUDED
#define FAJNORKA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
/* Debuging macros from Learn the C hard way */
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", \
                              __FILE__, __LINE__, ##__VA_ARGS__)
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,                              \
                                "[WARN] (%s:%d: errno: %s) " M "\n", \
                                __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...)           \
    if (!(A))                      \
    {                              \
        log_err(M, ##__VA_ARGS__); \
        errno = 0;                 \
        exit(0);                   \
    }

#define check_mem(A) check((A), "Nemam pamat na vykonanie operacie.")
/* DEBUG MACROS END */
// Nas string
#undef string
#define string char *

/**
 * Velkost buffera pri nacitavani znakov
 * Pri mensej hodnote sa castejsie vola realloc
 * Zrejme ale nebudeme mat dlhe texty
 * A nejde nam (az tak) o rychlost programu
 * Ak je vobec realloc pomaly
 * */

#define BUFFER_SIZE 100

/**
 * Maximalny pocet stringov co moze zadat
 * nemal by byt vacsi ako 10
 * ale budeme dynamicky reallocovat
 * ak by bolo treba
 * */
#define SIZE 10

/**
 * Struct string_holder, 
 * bude drzat alokovane "string"
 * */
typedef struct
{
    // string array
    string *array;
    // pocet stringov
    unsigned int count;
    // alokovane miesto v string array
    unsigned int allocation;

} string_holder;

#undef strings
string_holder *strings = NULL;

/**
 * string_holder_init()
 * 
 * inicializacia parametrov string_holdera
 * */
void string_holder_init();

/**
 * string_holder_resize()
 * 
 * Ak treba zvacit pole string array v string_holderi 
 * */
void string_holder_resize();

/**
 * string_holder_destroy()
 * 
 * Uvolnenie pamati celeho string_holdera
 * */
void string_holder_destroy();

/**
 * string_holder_free_last()
 * 
 * Uvolnenie pamati posledneho miesta v pameti v string array
 * v string_holderi (Ak nepotrebujeme drzat string v pamati dlho)
 * */
void string_holder_free_last();

/**
 * void construct(void)
 * 
 * Constructor volany pred main()
 * inicializuje string_holder
 * */
void __attribute__((constructor)) construct(void);

/**
 * void destructor(void)
 * 
 * Destructor volany po ukonceni main()
 * uvolni string_holder
 * */
void __attribute__((destructor)) destructor(void);

/**
 * void conversion_error(const char *msg)
 * 
 * Funkcia volana pri konverzii zo string na "Number"
 * Vypíše aj const char *msg
 * */
void conversion_error(const char *msg);

/**
 * string get_string(void)
 * 
 * vrati string co uzivatel zadal do stdin
 * */
string get_string(void);

/**
 * long long get_long_long(void)
 * 
 * Vrati long long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
long long get_long_long(void);

/**
 * unsigned long long get_ulong_long(void)
 * 
 * Vrati unsigned long long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
unsigned long long get_ulong_long(void);

/**
 * long get_long(void)
 * 
 * Vrati long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
long get_long(void);

/**
 * unsigned long get_ulong(void)
 * 
 * Vrati unsigned long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
unsigned long get_ulong(void);

/**
 * int get_int(void)
 * 
 * Vrati integer konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
int get_int(void);

/**
 * unsigned int get_int(void)
 * 
 * Vrati unsigned integer konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
unsigned int get_uint(void);

/**
 * short get_short(void)
 * 
 * Vrati short konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
short get_short(void);

/**
 * unsigned short get_ushort(void)
 * 
 * Vrati unsigned short konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
unsigned short get_ushort(void);

/**
 * char get_char(void)
 * 
 * Vrati char konvertovany zo string (prvy character)
 * Funkcia vo vnutri vola string get_string(void); 
 * */
char get_char(void);

/**
 * float get_float(void)
 * 
 * Vrati float  konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
float get_float(void);

/**
 * double get_double(void)
 * 
 * Vrati double  konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
double get_double(void);

#endif // FAJNORKA_H_INCLUDED
