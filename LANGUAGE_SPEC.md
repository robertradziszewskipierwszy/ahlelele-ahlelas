# Specyfikacja Języka Ahlelele Ahlelas

## Przegląd

**Ahlelele Ahlelas** to minimalistyczny, ezoteryczny język programowania oparty na stosie (stack-based), używający jedynie dwóch słów kluczowych: `ahlelele` i `ahlelas`.

## Filozofia

Język został zaprojektowany z myślą o:
- **Minimalizmie składniowym** - tylko 2 słowa kluczowe
- **Kompletności Turinga** - możliwość wykonania dowolnych obliczeń
- **Prostocie implementacji** - łatwy do zrozumienia i zaimplementowania kompilator

## Składnia

### Instrukcje

Język posiada dwie podstawowe instrukcje:

#### 1. `ahlelele <liczba>`
Umieszcza wartość na stosie (PUSH operation).

**Przykład:**
```
ahlelele 42      # Umieszcza 42 na stosie
ahlelele -10     # Umieszcza -10 na stosie
```

#### 2. `ahlelas <liczba>`
Wykonuje operację o podanym kodzie (EXECUTE operation).

**Przykład:**
```
ahlelas 0        # Wykonuje operację PRINT_CHAR
ahlelas 2        # Wykonuje operację ADD
```

### Komentarze

Linie rozpoczynające się od `#` są komentarzami i są ignorowane przez kompilator.

```
# To jest komentarz
ahlelele 10      # Komentarz może być też na końcu linii
```

### Białe znaki

Spacje, tabulatory i nowe linie są ignorowane (poza separacją tokenów).

## Semantyka

### Model Wykonania

Program operuje na stosie wartości typu `int64_t`. Instrukcje modyfikują stos poprzez:
- Dodawanie wartości (PUSH)
- Pobieranie wartości (POP)
- Wykonywanie operacji na wartościach

### Opcodes (Kody Operacji)

| Kod | Nazwa | Opis | Efekt na stosie |
|-----|-------|------|-----------------|
| 0 | PRINT_CHAR | Wypisuje znak ASCII | Pop 1 → wypisz jako char |
| 1 | PRINT_NUM | Wypisuje liczbę | Pop 1 → wypisz jako int64 |
| 2 | ADD | Dodawanie | Pop 2 (a, b) → Push (a + b) |
| 3 | SUB | Odejmowanie | Pop 2 (a, b) → Push (a - b) |
| 4 | MUL | Mnożenie | Pop 2 (a, b) → Push (a * b) |
| 5 | DIV | Dzielenie | Pop 2 (a, b) → Push (a / b) |
| 6 | DUP | Duplikacja | Peek 1 (a) → Push (a) |
| 7 | SWAP | Zamiana | Pop 2 (a, b) → Push (b, a) |
| 8 | DROP | Usunięcie | Pop 1 → (nic) |
| 9 | HALT | Zakończenie | Kończy program |

### Kolejność Operacji

Operacje binarne (ADD, SUB, MUL, DIV) pobierają argumenty w kolejności:
1. Pierwszy POP → drugi argument (b)
2. Drugi POP → pierwszy argument (a)
3. Wynik: a OP b

**Przykład:**
```
ahlelele 10      # Stos: [10]
ahlelele 5       # Stos: [10, 5]
ahlelas 3        # SUB: 10 - 5 = 5, Stos: [5]
```

## Przykłady Programów

### Hello World

```
ahlelele 72      # 'H'
ahlelas 0
ahlelele 101     # 'e'
ahlelas 0
ahlelele 108     # 'l'
ahlelas 0
ahlelele 108     # 'l'
ahlelas 0
ahlelele 111     # 'o'
ahlelas 0
ahlelele 10      # '\n'
ahlelas 0
```

### Kalkulator: (10 + 5) * 2

```
ahlelele 10
ahlelele 5
ahlelas 2        # ADD: 10 + 5 = 15
ahlelele 2
ahlelas 4        # MUL: 15 * 2 = 30
ahlelas 1        # PRINT_NUM: wypisz 30
```

### Duplikacja i Swap

```
ahlelele 42
ahlelas 6        # DUP: [42, 42]
ahlelas 1        # PRINT_NUM: 42
ahlelele 32      # spacja
ahlelas 0
ahlelas 1        # PRINT_NUM: 42

ahlelele 65      # 'A'
ahlelele 66      # 'B'
ahlelas 7        # SWAP: ['B', 'A']
ahlelas 0        # PRINT: A
ahlelas 0        # PRINT: B
```

## Błędy Wykonania

Program może zakończyć się błędem w następujących przypadkach:

1. **Stack Underflow** - próba pobrania wartości z pustego stosu
2. **Division by Zero** - dzielenie przez zero
3. **Unknown Opcode** - nieznany kod operacji
4. **Unexpected EOF** - nieoczekiwany koniec bytecode

## Format Plików

### Pliki Źródłowe (.ahl)

- Kodowanie: UTF-8
- Rozszerzenie: `.ahl`
- Struktura: dowolna liczba instrukcji i komentarzy

### Pliki Wykonywalne (.ahlx)

Skompilowane programy mają następującą strukturę binarną:

```
[Magic Number: 4 bajty] = 0x414C4841 ("AHLA")
[Rozmiar bytecode: 8 bajtów] = uint64_t
[Bytecode: N bajtów] = sekwencja instrukcji
```

#### Bytecode Instructions

- `PUSH <int64>`: 1 bajt (0xFF) + 8 bajtów (wartość)
- `OPCODE`: 1 bajt (kod operacji 0-9)
- `HALT`: 1 bajt (0x09) - automatycznie dodawany na końcu

## Rozszerzalność

Język można łatwo rozszerzyć o nowe opcodes:
- 10-254: zarezerwowane dla przyszłych operacji
- Możliwe rozszerzenia: I/O, pętle, warunkowe skoki, operacje bitowe

## Ograniczenia

1. Brak bezpośredniej obsługi pętli (wymaga rozwinięcia w czasie kompilacji)
2. Brak instrukcji warunkowych (wymaga symulacji przez operacje arytmetyczne)
3. Brak zmiennych nazwanych (tylko stos)
4. Brak funkcji/procedur (tylko liniowy przepływ)

## Kompletność Turinga

Mimo ograniczeń, język jest teoretycznie Turing-complete poprzez:
- Nieograniczony stos (ograniczony tylko pamięcią)
- Operacje arytmetyczne umożliwiające symulację logiki
- Możliwość implementacji dowolnych struktur danych na stosie

