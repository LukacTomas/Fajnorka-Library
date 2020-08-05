# Knižnica Fajnorka pre C

- Knižnica implementuje funkcie pre načítanie základných dátových typov.
- Knižnica definuje typ `string` ako `#define string char*`

## Funckie

Zoznam funkcii

- [get_string](#get_string)
- [get_long_long](#get_long_long)
- [get_ulong_long](#get_ulong_long)
- [get_long](#get_long)
- [get_ulong](#get_ulong)
- [get_int](#get_int)
- [get_uint](#get_uint)
- [get_short](#get_short)
- [get_ushort](#get_ushort)
- [get_char](#get_char)
- [get_float](#get_float)
- [get_double](#get_double)

### get_string

```c
string get_string(void)
```

> Načíta text z stdin a vráti ho ako string

#### Príklad

```c
printf("Zadaj svoje meno: ");
string meno = get_string();
print("Tvoje meno je  %s", meno);
```

### get_long_long

```c
long long get_long_long(void)
```

> vráti long long ekvivalent textu načítaného z stdin medzi [LLONG_MIN, LLONG_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj long long: ");
long long llNumber = get_long_long();
print("Zadal si %lli", llNumber);
```

### get_ulong_long

```c
unsigned long long get_ulong_long(void)
```

> vráti unsigned long long ekvivalent textu načítaného z stdin medzi [0, ULLONG_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj unsigned long long: ");
unsigned long long ullNumber = get_ulong_long();
print("Zadal si %llu", ullNumber);
```

### get_long

```c
long get_long(void)
```

> vráti long ekvivalent textu načítaného z stdin medzi [LONG_MIN, LONG_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj long: ");
long  lNumber = get_long();
print("Zadal si %li", lNumber);
```

### get_ulong_long

```c
unsigned long get_ulong(void)
```

> vráti unsigned long ekvivalent textu načítaného z stdin medzi [0, ULONG_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj unsigned long: ");
unsigned long ulNumber = get_ulong();
print("Zadal si %lu", ulNumber);
```

### get_int

```c
int get_int(void)
```

> vráti integer ekvivalent textu načítaného z stdin medzi [INT_MIN,INT_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj integer: ");
int intNumber = get_int();
print("Zadal si %i, intNumber);
```

### get_int

```c
int get_uint(void)
```

> vráti unsigned integer ekvivalent textu načítaného z stdin medzi [0,UINT_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj unsigned integer: ");
int uintNumber = get_uint();
print("Zadal si %u, uintNumber);
```

### get_short

```c
short get_short(void)
```

> vráti short ekvivalent textu načítaného z stdin medzi [SHRT_MIN, SHRT_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj short: ");
short shortNumber = get_short();
print("Zadal si %i, shortNumber);
```

### get_ushort

```c
unsigned short get_ushort(void)
```

> vráti unsigned short ekvivalent textu načítaného z stdin medzi [0, USHRT_MAX], pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj unsgined short: ");
unsigned short uShortNumber = get_ushort();
print("Zadal si %u, uShortNumber);
```

### get_char

```c
char get_char(void)
```

> vráti prvy charakter z textu načítaného z stdin.

#### Príklad

```c
printf("Zadaj jedno pismeno: ");
char c = get_char();
print("Zadal si %c, c);
```

### get_float

```c
float get_float(void)
```

> vráti float ekvivalent textu načítaného z stdin, pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj float: ");
float floatNumber = get_float();
print("Zadal si %f, floatNumber);
```

### get_double

```c
double get_double(void)
```

> vráti double ekvivalent textu načítaného z stdin, pri chybe sa pýta znova na hodnotu

#### Príklad

```c
printf("Zadaj double: ");
double doubleNumber = get_double();
print("Zadal si %f, doubleNumber);
```
