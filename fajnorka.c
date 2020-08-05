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

#include "fajnorka.h"

/**
 * string_holder_init()
 * 
 * inicializacia parametrov string_holdera
 * */
#undef string_holder_init
void string_holder_init()
{
    strings = malloc(sizeof(string_holder) + SIZE * sizeof(strings->array));
    strings->count = 0;
    strings->allocation = SIZE;
    strings->array = malloc(strings->allocation * sizeof(strings->array));
}

/**
 * string_holder_resize()
 * 
 * Ak treba zvacit pole string array v string_holderi 
 * */
#undef string_holder_resize
void string_holder_resize()
{
    strings->allocation = 2 * strings->allocation;
    strings = realloc(strings, sizeof(string_holder) + strings->allocation * sizeof(strings->array));
    check_mem(strings);
    strings->array = realloc(strings->array, strings->allocation * sizeof(strings->array));
    check_mem(strings->array)
}

/**
 * string_holder_destroy()
 * 
 * Uvolnenie pamati celeho string_holdera
 * */
#undef string_holder_destroy
void string_holder_destroy()
{
    for (unsigned int i = 0; i < strings->count; ++i)
    {
        free(strings->array[i]);
    }
    free(strings->array);
    free(strings);
}

/**
 * string_holder_free_last()
 * 
 * Uvolnenie pamati posledneho miesta v pameti v string array
 * v string_holderi (Ak nepotrebujeme drzat string v pamati dlho)
 * */
#undef string_holder_free_last
void string_holder_free_last()
{
    free(strings->array[--strings->count]);
    // strings->count--;
}

/**
 * void construct(void)
 * 
 * Constructor volany pred main()
 * inicializuje string_holder
 * */
#undef construct
void __attribute__((constructor)) construct(void) // @ignore
{
    string_holder_init();
}

/**
 * void destructor(void)
 * 
 * Destructor volany po ukonceni main()
 * uvolni string_holder
 * */
#undef destructor
void __attribute__((destructor)) destructor(void) // @ignore
{

    /* VYMAZ V PRODUKCII */
    puts("\n\n\nTest version of library.");
    /*Vymaz potialto*/
    string_holder_destroy();
}

/**
 * void conversion_error(const char *msg)
 * 
 * Funkcia volana pri konverzii zo string na "Number"
 * Vypíše aj const char *msg
 * */
#undef conversion_error
void conversion_error(const char *msg)
{
    printf("%s Skus este raz: ", msg);
    string_holder_free_last();
}

/**
 * string get_string(void)
 * 
 * vrati string co uzivatel zadal do stdin
 * */
#undef get_string
string get_string(void)
{
    // Veľkost buffera je allocation
    int allocation = BUFFER_SIZE;
    string buffer = calloc(allocation, sizeof(string));
    check_mem(buffer);

    unsigned int counter = 0;
    // c musi byt int lebo getchar vracia -1 pri EOF
    int c;
    while (((c = getchar()) != EOF && c != '\n' && c != '\r'))
    {

        *(buffer + counter++) = c;

        if (counter == allocation)
        {
            allocation = 2 * allocation;
            buffer = realloc(buffer, allocation);
            check_mem(buffer);
        }
    }
    // aj posledny char - '\0'
    buffer[counter] = '\0';

    // sprav miesto v pamati pre presnu velkost textu
    string text = calloc(counter, sizeof(string));
    check_mem(text);

    // skopiruj buffer do text
    // malo by stacit strcpy, ale mozme uvazovat nad memcpy
    memcpy(text, buffer, counter);
    // strcpy(text, buffer);

    // uvolni buffer
    free(buffer);

    // ulož ukazovatel na text do struktury string_holder strings
    // aby som mohol potom text uvolnit pri ukonceni programu
    *(strings->array + strings->count++) = text;

    // ak treba realokuj strings
    if (strings->count == strings->allocation)
    {
        string_holder_resize();
    }
    return text;
}

/**
 * long long get_long_long(void)
 * 
 * Vrati long long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_long_long
long long get_long_long(void)
{
    long long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtoll(text, &end, 10);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE)
        {
            conversion_error("Long long overflow.");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}

/**
 * unsigned long long get_ulong_long(void)
 * 
 * Vrati unsigned long long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_ulong_long
unsigned long long get_ulong_long(void)
{
    unsigned long long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtoull(text, &end, 10);
        if (text[0] == '-')
        {
            errno = ERANGE;
        }
        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE || text[0] == '-')
        {
            conversion_error("Unsigned long long overflow.");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}

/**
 * long get_long(void)
 * 
 * Vrati long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_long
long get_long(void)
{
    long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtol(text, &end, 10);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE)
        {
            conversion_error("Long overflow.");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}

/**
 * unsigned long get_ulong(void)
 * 
 * Vrati unsigned long konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_ulong
unsigned long get_ulong(void)
{
    unsigned long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtoul(text, &end, 10);
        if (text[0] == '-')
        {
            errno = ERANGE;
        }
        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE)
        {
            conversion_error("Unsigned long overflow.");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}

/**
 * int get_int(void)
 * 
 * Vrati integer konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_int
int get_int(void)
{
    long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtol(text, &end, 10);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (number > INT_MAX || number < INT_MIN)
        {
            conversion_error("Integer overflow.");
        }

    } while (text == end || number > INT_MAX || number < INT_MIN);
    string_holder_free_last();
    return (int)number;
}

/**
 * unsigned int get_int(void)
 * 
 * Vrati unsigned integer konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_uint
unsigned int get_uint(void)
{
    unsigned long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtoul(text, &end, 10);

        if (text[0] == '-' || number > UINT_MAX)
        {
            errno = ERANGE;
        }
        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == ERANGE)
        {
            conversion_error("Unsigned integer overflow.");
        }

    } while (text == end || errno == ERANGE);
    string_holder_free_last();
    return (unsigned int)number;
}

/**
 * short get_short(void)
 * 
 * Vrati short konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_short
short get_short(void)
{
    long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtol(text, &end, 10);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (number > SHRT_MAX || number < SHRT_MIN)
        {
            conversion_error("Short overflow.");
        }

    } while (text == end || number > SHRT_MAX || number < SHRT_MIN);
    string_holder_free_last();
    return (short)number;
}

/**
 * unsigned short get_ushort(void)
 * 
 * Vrati unsigned short konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_ushort
unsigned short get_ushort(void)
{
    unsigned long number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtol(text, &end, 10);

        if (text[0] == '-' || number > USHRT_MAX)
        {
            errno = ERANGE;
        }
        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == ERANGE)
        {
            conversion_error("Usigned short overflow.");
        }

    } while (text == end || errno == ERANGE);
    string_holder_free_last();
    return (unsigned short)number;
}

/**
 * char get_char(void)
 * 
 * Vrati char konvertovany zo string (prvy character)
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_char
char get_char(void)
{
    string text = get_string();
    char c = text[0];
    string_holder_free_last();
    return c;
}

/**
 * float get_float(void)
 * 
 * Vrati float  konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_float
float get_float(void)
{
    float number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtof(text, &end);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE)
        {
            conversion_error("Overflow. (Try double?).");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}

/**
 * double get_double(void)
 * 
 * Vrati double  konvertovany zo string
 * Funkcia vo vnutri vola string get_string(void); 
 * */
#undef get_double
double get_double(void)
{
    double number;
    string text;
    string end;

    do
    {
        errno = 0;
        text = get_string();
        number = strtod(text, &end);

        if (text == end)
        {
            conversion_error("Nie je cislo.");
        }
        if (errno == EINVAL || errno == ERANGE)
        {
            conversion_error("Overflow.");
        }

    } while (text == end || errno == EINVAL || errno == ERANGE);
    string_holder_free_last();
    return number;
}
