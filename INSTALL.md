# Instrukcja Instalacji i Użycia

## Wymagania Systemowe

### Linux

- **System:** Linux (kernel 3.0+)
- **Kompilator:** GCC 10+ lub Clang 12+
- **CMake:** wersja 3.20 lub nowsza
- **Make:** GNU Make

**Instalacja zależności (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install build-essential cmake g++
```

**Instalacja zależności (Arch Linux):**
```bash
sudo pacman -S base-devel cmake gcc
```

**Instalacja zależności (Fedora):**
```bash
sudo dnf install gcc-c++ cmake make
```

### Windows

- **System:** Windows 10/11
- **Kompilator:** Visual Studio 2019+ lub MinGW-w64
- **CMake:** wersja 3.20 lub nowsza

**Opcja 1: Visual Studio**
1. Pobierz Visual Studio Community (darmowe)
2. Zainstaluj "Desktop development with C++"
3. Pobierz CMake z https://cmake.org/download/

**Opcja 2: MinGW-w64**
1. Pobierz MSYS2 z https://www.msys2.org/
2. Zainstaluj MinGW-w64:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make
```

## Instalacja

### Krok 1: Pobranie Projektu

```bash
cd /progs
git clone <repository-url> allehas
cd allehas
```

Lub jeśli już masz projekt:
```bash
cd /progs/allehas
```

### Krok 2: Kompilacja

#### Linux:

```bash
chmod +x build.sh
./build.sh
```

Lub manualnie:
```bash
mkdir -p build
cd build
cmake ..
cmake --build . -j$(nproc)
```

#### Windows (CMD):

```cmd
build.bat
```

Lub manualnie:
```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Windows (PowerShell):

```powershell
New-Item -ItemType Directory -Force -Path build
Set-Location build
cmake ..
cmake --build . --config Release
```

### Krok 3: Weryfikacja Instalacji

#### Linux:
```bash
./build/ahlelele --help
```

#### Windows:
```cmd
.\build\Release\ahlelele.exe --help
```

Powinieneś zobaczyć:
```
Ahlelele Ahlelas Compiler v1.0.0

Usage:
  Compile: ahlelele --in <source.ahl> --out <executable>
  Execute: ahlelele --exec <executable>

Description:
  Compiles Ahlelele Ahlelas source code to bytecode executable
  or executes a compiled bytecode file.
```

## Użycie

### Podstawowe Komendy

#### 1. Kompilacja Programu

**Linux:**
```bash
./build/ahlelele --in program.ahl --out program.ahlx
```

**Windows:**
```cmd
.\build\Release\ahlelele.exe --in program.ahl --out program.ahlx
```

#### 2. Wykonanie Skompilowanego Programu

**Linux:**
```bash
./build/ahlelele --exec program.ahlx
```

**Windows:**
```cmd
.\build\Release\ahlelele.exe --exec program.ahlx
```

#### 3. Wyświetlenie Pomocy

**Linux:**
```bash
./build/ahlelele --help
```

**Windows:**
```cmd
.\build\Release\ahlelele.exe --help
```

### Przykłady Użycia

#### Przykład 1: Hello World

**Linux:**
```bash
./build/ahlelele --in examples/hello_world.ahl --out hello.ahlx
./build/ahlelele --exec hello.ahlx
```

**Windows:**
```cmd
.\build\Release\ahlelele.exe --in examples\hello_world.ahl --out hello.ahlx
.\build\Release\ahlelele.exe --exec hello.ahlx
```

**Oczekiwany wynik:**
```
Ahlelele ahlelas. Hello World!
```

#### Przykład 2: Kalkulator

**Linux:**
```bash
./build/ahlelele --in examples/calculator.ahl --out calc.ahlx
./build/ahlelele --exec calc.ahlx
```

**Oczekiwany wynik:**
```
30
```

#### Przykład 3: Operacje na Stosie

**Linux:**
```bash
./build/ahlelele --in examples/stack_operations.ahl --out stack.ahlx
./build/ahlelele --exec stack.ahlx
```

**Oczekiwany wynik:**
```
42 42
AB
```

## Instalacja Globalna (Opcjonalnie)

### Linux

Skopiuj wykonywalny plik do katalogu systemowego:

```bash
sudo cp build/ahlelele /usr/local/bin/
sudo chmod +x /usr/local/bin/ahlelele
```

Teraz możesz używać kompilatora z dowolnego miejsca:
```bash
ahlelele --in program.ahl --out program.ahlx
```

### Windows

Dodaj katalog z kompilatorem do zmiennej PATH:

1. Skopiuj `build\Release\ahlelele.exe` do `C:\Program Files\Ahlelele\`
2. Dodaj `C:\Program Files\Ahlelele\` do zmiennej środowiskowej PATH
3. Otwórz nowy terminal i użyj:
```cmd
ahlelele --in program.ahl --out program.ahlx
```

## Rozwiązywanie Problemów

### Problem: "CMake not found"

**Rozwiązanie:**
- Zainstaluj CMake zgodnie z instrukcjami dla Twojego systemu
- Upewnij się, że CMake jest w PATH

### Problem: "Compiler not found"

**Linux:**
```bash
sudo apt install build-essential g++
```

**Windows:**
- Zainstaluj Visual Studio lub MinGW-w64

### Problem: "Permission denied" (Linux)

**Rozwiązanie:**
```bash
chmod +x build.sh
chmod +x build/ahlelele
```

### Problem: Błędy kompilacji C++20

**Rozwiązanie:**
- Upewnij się, że używasz GCC 10+ lub Clang 12+
- Sprawdź wersję: `g++ --version` lub `clang++ --version`

### Problem: "Cannot open source file"

**Rozwiązanie:**
- Sprawdź ścieżkę do pliku źródłowego
- Upewnij się, że plik ma rozszerzenie `.ahl`
- Użyj pełnej ścieżki lub względnej od bieżącego katalogu

### Problem: "Stack underflow" podczas wykonania

**Rozwiązanie:**
- Sprawdź kod źródłowy
- Upewnij się, że przed każdą operacją są odpowiednie wartości na stosie
- Użyj komentarzy do śledzenia stanu stosu

## Deinstalacja

### Linux

```bash
# Usuń katalog projektu
rm -rf /progs/allehas

# Usuń globalny plik wykonywalny (jeśli zainstalowany)
sudo rm /usr/local/bin/ahlelele
```

### Windows

```cmd
# Usuń katalog projektu
rmdir /s /q C:\progs\allehas

# Usuń globalny plik wykonywalny (jeśli zainstalowany)
del "C:\Program Files\Ahlelele\ahlelele.exe"
```

## Aktualizacja

```bash
cd /progs/allehas
git pull
./build.sh  # lub build.bat na Windows
```

## Wsparcie

Jeśli napotkasz problemy:

1. Sprawdź dokumentację: `README.md`, `QUICK_START.md`
2. Przeczytaj specyfikację języka: `LANGUAGE_SPEC.md`
3. Sprawdź architekturę: `ARCHITECTURE.md`
4. Przejrzyj przykłady w katalogu `examples/`

## Następne Kroki

Po instalacji:

1. Przeczytaj `QUICK_START.md` - szybki start z językiem
2. Eksploruj `examples/` - przykładowe programy
3. Przeczytaj `LANGUAGE_SPEC.md` - pełna specyfikacja języka
4. Stwórz własny program w Ahlelele Ahlelas!

---

**Gratulacje! Kompilator Ahlelele Ahlelas jest gotowy do użycia!** 🎉

