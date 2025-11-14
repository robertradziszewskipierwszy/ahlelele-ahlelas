# Architektura Kompilatora Ahlelele Ahlelas

## Przegląd

Kompilator Ahlelele Ahlelas to pełny pipeline kompilacji składający się z 5 głównych komponentów:

```
Kod źródłowy (.ahl)
        ↓
    [LEXER] → Tokeny
        ↓
    [PARSER] → AST (Abstract Syntax Tree)
        ↓
  [CODEGEN] → Bytecode
        ↓
      [VM] → Wykonanie
```

## Komponenty

### 1. Lexer (Tokenizer)

**Plik:** `src/lexer.cpp`, `include/lexer.hpp`

**Odpowiedzialność:**
- Przekształcenie surowego tekstu źródłowego w strumień tokenów
- Rozpoznawanie słów kluczowych (`ahlelele`, `ahlelas`)
- Parsowanie liczb (int64_t, w tym ujemne)
- Obsługa komentarzy (linie zaczynające się od `#`)
- Śledzenie pozycji (linia, kolumna) dla raportowania błędów

**Typy tokenów:**
```cpp
enum class TokenType {
    AHLELELE,    // Słowo kluczowe 'ahlelele'
    AHLELAS,     // Słowo kluczowe 'ahlelas'
    NUMBER,      // Literał liczbowy
    END_OF_FILE, // Koniec pliku
    INVALID      // Nieprawidłowy token
};
```

**Proces:**
1. Pomijanie białych znaków
2. Pomijanie komentarzy
3. Rozpoznawanie tokenów:
   - Liczby (cyfry, opcjonalnie poprzedzone `-`)
   - Słowa kluczowe (sekwencje liter)
4. Walidacja i raportowanie błędów

### 2. Parser (Syntax Analyzer)

**Plik:** `src/parser.cpp`, `include/parser.hpp`

**Odpowiedzialność:**
- Analiza składniowa strumienia tokenów
- Budowa Abstract Syntax Tree (AST)
- Walidacja poprawności składniowej
- Raportowanie błędów składniowych

**Struktura AST:**
```cpp
enum class InstructionType {
    PUSH,     // ahlelele <liczba>
    EXECUTE   // ahlelas <liczba>
};

struct Instruction {
    InstructionType type;
    int64_t value;
};

using Program = std::vector<Instruction>;
```

**Gramatyka:**
```
Program     → Instruction*
Instruction → AHLELELE NUMBER | AHLELAS NUMBER
```

**Proces:**
1. Iteracja przez tokeny
2. Dla każdego tokenu:
   - `AHLELELE` → oczekuj NUMBER → utwórz PUSH instruction
   - `AHLELAS` → oczekuj NUMBER → utwórz EXECUTE instruction
3. Walidacja kompletności instrukcji
4. Zwróć Program (lista instrukcji)

### 3. Code Generator (Bytecode Generator)

**Plik:** `src/codegen.cpp`, `include/codegen.hpp`

**Odpowiedzialność:**
- Przekształcenie AST w bytecode
- Optymalizacja (obecnie brak)
- Generowanie instrukcji dla VM

**Format Bytecode:**
```
PUSH <value>:
    [0xFF] [8 bajtów: int64_t value]

EXECUTE <opcode>:
    [1 bajt: opcode 0-9]

HALT:
    [0x09]
```

**Proces:**
1. Iteracja przez instrukcje AST
2. Dla każdej instrukcji:
   - PUSH → emit byte(0xFF) + emit int64(value)
   - EXECUTE → emit byte(opcode)
3. Dodaj HALT na końcu
4. Zwróć wektor bajtów

### 4. Virtual Machine (Executor)

**Plik:** `src/vm.cpp`, `include/vm.hpp`

**Odpowiedzialność:**
- Wykonywanie bytecode
- Zarządzanie stosem
- Implementacja operacji
- Obsługa błędów wykonania

**Architektura VM:**
```
┌─────────────────┐
│  Instruction    │
│    Pointer      │
└─────────────────┘
        ↓
┌─────────────────┐
│    Bytecode     │
│   [Memory]      │
└─────────────────┘
        ↓
┌─────────────────┐
│     Stack       │
│  [int64_t...]   │
└─────────────────┘
```

**Opcodes:**
```cpp
enum class OpCode : uint8_t {
    PRINT_CHAR = 0,  // Pop → print as char
    PRINT_NUM = 1,   // Pop → print as int64
    ADD = 2,         // Pop b, Pop a → Push (a+b)
    SUB = 3,         // Pop b, Pop a → Push (a-b)
    MUL = 4,         // Pop b, Pop a → Push (a*b)
    DIV = 5,         // Pop b, Pop a → Push (a/b)
    DUP = 6,         // Peek a → Push a
    SWAP = 7,        // Pop a, Pop b → Push a, Push b
    DROP = 8,        // Pop (discard)
    HALT = 9,        // Stop execution
    PUSH = 255       // Push <int64>
};
```

**Cykl Wykonania:**
```
while (running) {
    opcode = read_byte()
    switch (opcode) {
        case PUSH: value = read_int64(); push(value)
        case PRINT_CHAR: print(pop() as char)
        case ADD: b = pop(); a = pop(); push(a + b)
        // ... etc
        case HALT: running = false
    }
}
```

### 5. Compiler (Orchestrator)

**Plik:** `src/compiler.cpp`, `include/compiler.hpp`

**Odpowiedzialność:**
- Orkiestracja całego procesu kompilacji
- Odczyt pliku źródłowego
- Zapis pliku wykonywalnego
- Obsługa błędów na wszystkich etapach

**Format Pliku Wykonywalnego (.ahlx):**
```
┌──────────────────────────────┐
│ Magic Number (4 bajty)       │  0x414C4841 ("AHLA")
├──────────────────────────────┤
│ Bytecode Size (8 bajtów)     │  uint64_t
├──────────────────────────────┤
│ Bytecode (N bajtów)          │  Instrukcje VM
└──────────────────────────────┘
```

**Proces Kompilacji:**
```cpp
bool compile(input_path, output_path) {
    source = read_file(input_path)
    tokens = Lexer(source).tokenize()
    program = Parser(tokens).parse()
    bytecode = CodeGenerator().generate(program)
    write_executable(output_path, bytecode)
}
```

### 6. Main (CLI Interface)

**Plik:** `src/main.cpp`

**Odpowiedzialność:**
- Parsowanie argumentów wiersza poleceń
- Wybór trybu (kompilacja vs wykonanie)
- Wywołanie odpowiednich komponentów
- Obsługa błędów i wyświetlanie pomocy

**Tryby Działania:**

1. **Tryb Kompilacji:**
```bash
ahlelele --in source.ahl --out executable.ahlx
```

2. **Tryb Wykonania:**
```bash
ahlelele --exec executable.ahlx
```

## Wzorce Projektowe

### 1. RAII (Resource Acquisition Is Initialization)

Wszystkie zasoby (pliki, pamięć) są zarządzane przez obiekty RAII:
- `std::ifstream`, `std::ofstream` - automatyczne zamykanie plików
- `std::vector` - automatyczne zarządzanie pamięcią
- `std::string` - automatyczne zarządzanie buforem

### 2. Value Semantics

Dane przekazywane są przez wartość lub const reference:
```cpp
Lexer(std::string source)           // Move semantics
Program parse()                      // Return by value (RVO)
void execute(const Bytecode& bc)    // Const reference
```

### 3. Strong Type Safety

- `enum class` zamiast `enum`
- `std::variant` dla wartości tokenów
- Brak C-style castów
- Explicit constructors

### 4. Error Handling

- Wyjątki dla błędów kompilacji/wykonania
- `std::optional` dla wartości opcjonalnych
- Walidacja na każdym etapie pipeline

## Bezpieczeństwo

### Memory Safety

1. **Brak surowych wskaźników:**
   - Wszystkie wskaźniki to `const uint8_t*` (non-owning)
   - Właścicielstwo przez `std::vector`

2. **Bounds Checking:**
   - Sprawdzanie granic przed odczytem bytecode
   - Sprawdzanie stosu przed POP

3. **Integer Safety:**
   - Sprawdzanie dzielenia przez zero
   - Użycie `int64_t` (określony rozmiar)

### Type Safety

1. **Silne typy:**
```cpp
enum class OpCode : uint8_t { ... };
enum class TokenType : uint8_t { ... };
```

2. **Const Correctness:**
```cpp
const Token& current_token() const;
int64_t peek() const;
```

## Wydajność

### Optymalizacje

1. **Move Semantics:**
   - Przekazywanie dużych obiektów przez move
   - RVO (Return Value Optimization)

2. **Reserve:**
   - Pre-alokacja wektorów gdzie możliwe

3. **Inline Operations:**
   - Małe funkcje jako inline (compiler decision)

### Złożoność

- **Lexer:** O(n) - jeden przebieg przez źródło
- **Parser:** O(n) - jeden przebieg przez tokeny
- **CodeGen:** O(n) - jeden przebieg przez AST
- **VM:** O(m) - jeden przebieg przez bytecode

**Całkowita złożoność:** O(n + m), gdzie n = rozmiar źródła, m = rozmiar bytecode

## Rozszerzalność

### Dodawanie Nowych Opcodes

1. Dodaj do `enum class OpCode` w `bytecode.hpp`
2. Dodaj case w `VirtualMachine::execute()` w `vm.cpp`
3. Zaktualizuj dokumentację

### Dodawanie Optymalizacji

Miejsce: `CodeGenerator::generate()`

Przykładowe optymalizacje:
- Constant folding
- Dead code elimination
- Peephole optimization

### Dodawanie Nowych Instrukcji

1. Rozszerz `TokenType` i `InstructionType`
2. Zaktualizuj Lexer i Parser
3. Zaktualizuj CodeGenerator
4. Dodaj testy

## Testowanie

### Testy Manualne

```bash
# Test kompilacji
./build/ahlelele --in examples/hello_world.ahl --out test.ahlx

# Test wykonania
./build/ahlelele --exec test.ahlx
```

### Testy Jednostkowe (TODO)

Potencjalne frameworki:
- Google Test
- Catch2
- Doctest

## Zależności

### Wymagane

- C++20 compiler (GCC 10+, Clang 12+, MSVC 2019+)
- CMake 3.20+
- Standard Library (STL)

### Opcjonalne

- Brak

## Build System

### CMake Configuration

```cmake
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### Flagi Kompilacji

**GCC/Clang:**
```
-Wall -Wextra -Wpedantic -Werror
```

**MSVC:**
```
/W4 /WX
```

## Metryki Projektu

- **Pliki nagłówkowe:** 8
- **Pliki źródłowe:** 6
- **Linie kodu:** ~1200 (bez komentarzy)
- **Klasy:** 5 głównych
- **Funkcje:** ~40
- **Opcodes:** 10

## Przyszłe Rozszerzenia

1. **Optymalizator:**
   - Constant folding
   - Dead code elimination
   - Peephole optimization

2. **Debugger:**
   - Breakpoints
   - Step execution
   - Stack inspection

3. **Profiler:**
   - Instruction counting
   - Performance analysis

4. **Extended Opcodes:**
   - Conditional jumps
   - Loops
   - Functions/procedures
   - I/O operations

5. **JIT Compilation:**
   - Runtime compilation do kodu natywnego
   - Znaczne przyspieszenie wykonania

