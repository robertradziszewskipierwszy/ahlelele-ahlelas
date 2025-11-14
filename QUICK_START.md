# Ahlelele Ahlelas - Quick Start Guide

## Szybki Start

### 1. Kompilacja Kompilatora

#### Linux:
```bash
./build.sh
```

#### Windows:
```cmd
build.bat
```

### 2. Twój Pierwszy Program

Stwórz plik `test.ahl`:

```
# Mój pierwszy program
ahlelele 72      # 'H'
ahlelas 0
ahlelele 105     # 'i'
ahlelas 0
ahlelele 33      # '!'
ahlelas 0
ahlelele 10      # '\n'
ahlelas 0
```

### 3. Kompilacja i Uruchomienie

```bash
# Kompilacja
./build/ahlelele --in test.ahl --out test.ahlx

# Wykonanie
./build/ahlelele --exec test.ahlx
```

## Podstawowe Operacje

### Wypisywanie Tekstu

Każdy znak to jego kod ASCII:

```
ahlelele 65      # 'A'
ahlelas 0        # Wypisz znak
```

### Operacje Arytmetyczne

```
# Oblicz: 5 + 3
ahlelele 5
ahlelele 3
ahlelas 2        # ADD
ahlelas 1        # Wypisz wynik
```

### Operacje na Stosie

```
# Duplikuj wartość
ahlelele 42
ahlelas 6        # DUP - teraz mamy [42, 42]

# Zamień miejscami
ahlelele 1
ahlelele 2
ahlelas 7        # SWAP - teraz [2, 1]
```

## Tabela Kodów ASCII (Przydatne Znaki)

| Znak | Kod | Znak | Kod | Znak | Kod |
|------|-----|------|-----|------|-----|
| \n   | 10  | !    | 33  | A    | 65  |
| \r   | 13  | .    | 46  | a    | 97  |
| spacja | 32 | 0    | 48  | H    | 72  |

## Tabela Operacji

| Kod | Operacja | Przykład |
|-----|----------|----------|
| 0   | PRINT_CHAR | `ahlelas 0` |
| 1   | PRINT_NUM  | `ahlelas 1` |
| 2   | ADD        | `ahlelas 2` |
| 3   | SUB        | `ahlelas 3` |
| 4   | MUL        | `ahlelas 4` |
| 5   | DIV        | `ahlelas 5` |
| 6   | DUP        | `ahlelas 6` |
| 7   | SWAP       | `ahlelas 7` |
| 8   | DROP       | `ahlelas 8` |
| 9   | HALT       | `ahlelas 9` |

## Przykłady

### Kalkulator
```
# (10 + 5) * 2 = 30
ahlelele 10
ahlelele 5
ahlelas 2        # ADD
ahlelele 2
ahlelas 4        # MUL
ahlelas 1        # PRINT
```

### Wypisz "OK"
```
ahlelele 79      # 'O'
ahlelas 0
ahlelele 75      # 'K'
ahlelas 0
ahlelele 10      # '\n'
ahlelas 0
```

## Debugowanie

### Częste Błędy

1. **Stack Underflow**
   - Próba użycia operacji bez wystarczającej liczby wartości na stosie
   - Rozwiązanie: Upewnij się, że przed operacją są odpowiednie wartości

2. **Division by Zero**
   - Dzielenie przez 0
   - Rozwiązanie: Sprawdź wartości przed operacją DIV

3. **Unknown Opcode**
   - Użycie nieistniejącego kodu operacji
   - Rozwiązanie: Używaj tylko kodów 0-9

### Wskazówki

- Używaj komentarzy (`#`) do dokumentowania kodu
- Testuj małe fragmenty przed budowaniem większych programów
- Pamiętaj o kolejności na stosie (LIFO - Last In, First Out)

## Zaawansowane Techniki

### Wypisywanie Liczb Wielocyfrowych

```
# Wypisz "123"
ahlelele 49      # '1'
ahlelas 0
ahlelele 50      # '2'
ahlelas 0
ahlelele 51      # '3'
ahlelas 0
```

### Obliczenia Złożone

```
# (a + b) * (c - d)
# Załóżmy: a=5, b=3, c=10, d=2

ahlelele 5
ahlelele 3
ahlelas 2        # a + b = 8

ahlelele 10
ahlelele 2
ahlelas 3        # c - d = 8

ahlelas 4        # 8 * 8 = 64
ahlelas 1        # Wypisz 64
```

## Dalsze Kroki

1. Przeczytaj pełną specyfikację: `LANGUAGE_SPEC.md`
2. Eksploruj przykłady w katalogu `examples/`
3. Stwórz własne programy!
4. Podziel się swoimi projektami

## Pomoc

```bash
./build/ahlelele --help
```

---

**Miłego programowania w Ahlelele Ahlelas!** 🎉

