# Ahlelele Ahlelas Compiler

Nasze motto

> Przydałoby się trochę polotu i finezji w tym smutnym jak pizda mieście…

Minimalistyczny kompilator dla ezoterycznego języka programowania opartego na dwóch słowach - ahlelele ahlelas.

## Specyfikacja Języka

Język **Ahlelele Ahlelas** składa się z zaledwie dwóch instrukcji:

### Składnia

- `ahlelele <liczba>` - umieszcza wartość na stosie (PUSH)
- `ahlelas <liczba>` - wykonuje operację o podanym kodzie (EXECUTE)

### Opcodes (Kody Operacji)

| Kod | Operacja | Opis |
|-----|----------|------|
| 0 | PRINT_CHAR | Wypisuje znak (pobiera kod ASCII ze stosu) |
| 1 | PRINT_NUM | Wypisuje liczbę (pobiera wartość ze stosu) |
| 2 | ADD | Dodaje dwie wartości ze stosu |
| 3 | SUB | Odejmuje dwie wartości ze stosu |
| 4 | MUL | Mnoży dwie wartości ze stosu |
| 5 | DIV | Dzieli dwie wartości ze stosu |
| 6 | DUP | Duplikuje wartość na szczycie stosu |
| 7 | SWAP | Zamienia dwie górne wartości na stosie |
| 8 | DROP | Usuwa wartość ze stosu |
| 9 | HALT | Kończy wykonanie programu |

### Komentarze

Linie zaczynające się od `#` są komentarzami i są ignorowane.

## Kompilacja

### Wymagania

- CMake 3.20+
- Kompilator C++20 (GCC 10+, Clang 12+, MSVC 2019+)

### Budowanie

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Cross-compilation

Kompilator działa natywnie na Windows i Linux.

## Użycie

### Kompilacja programu

```bash
ahlelele --in program.ahl --out program.ahlx
```

### Wykonanie skompilowanego programu

```bash
ahlelele --exec program.ahlx
```

### Pomoc

```bash
ahlelele --help
```

## Przykłady

### Hello World

Plik: `examples/hello_world.ahl`

Program wypisuje: "Ahlelele ahlelas. Hello World!"

```
ahlelele 65
ahlelas 0
ahlelele 104
ahlelas 0
# ... pozostałe znaki
```

### Kalkulator

```
# Oblicza (10 + 5) * 2
ahlelele 10
ahlelele 5
ahlelas 2    # ADD
ahlelele 2
ahlelas 4    # MUL
ahlelas 1    # PRINT_NUM
```

## Architektura

Kompilator składa się z następujących komponentów:

1. **Lexer** - tokenizacja kodu źródłowego
2. **Parser** - analiza składniowa i budowa AST
3. **CodeGenerator** - generowanie bytecode
4. **VirtualMachine** - wykonywanie bytecode
5. **Compiler** - orkiestracja całego procesu

### Format Bytecode

Skompilowane pliki `.ahlx` zawierają:
- Magic number: `0x414C4841` ("AHLA")
- Rozmiar bytecode: 64-bit unsigned integer
- Bytecode: sekwencja instrukcji

## Licencja

Projekt stworzony jako demonstracja kompilacji języków ezoterycznych.

