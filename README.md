# Progetto di Programmazione ad Oggetti: E-commerce

## Descrizione

Il progetto consiste nello sviluppo di un’applicazione desktop di e-commerce realizzata in **C++ con Qt**, progettata secondo i principi della **programmazione ad oggetti (OOP)**.

L’obiettivo è simulare la gestione di un negozio online, con un’architettura modulare e scalabile.

### Funzionalità principali

- Gestione di diverse tipologie di prodotti:
  - Abbigliamento (`Clothing`)
  - Elettronica (`Electronics`)
  - Media stampati (`PrintedMedia`)
- Utilizzo di:
  - Ereditarietà
  - Polimorfismo
  - Classi astratte (`Product`)
- Sistema di **filtri**
- Lista **preferiti**
- Interfaccia grafica con **Qt Widgets**
- Salvataggio dati in **JSON**
- Pattern **Visitor**

---

## Struttura del progetto
```

├── Headers/
│   ├── Graphics/
│   └── Logic/
├── Sources/
│   ├── Graphics/
│   └── Logic/
├── resources.qrc
├── CMakeLists.txt
└── README.md
```

---

## Requisiti

- C++17 o superiore
- CMake ≥ 3.16
- Qt 6 (o Qt 5 compatibile)
- Compilatore:
  - macOS: clang++
  - Linux: g++
  - Windows: MSVC / MinGW

## Verifica:

```bash
cmake --version
qmake --version
```

Altrimenti prosegui con i seguenti passaggi in base al tuo sistema operativo

---

## Installazione dipendenze

Di seguito i passaggi per installare tutto il necessario per compilare ed eseguire il progetto.

---

## macOS

#### 1. Installa Homebrew (se non presente)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### 2. Insstalla CMake

```bash
brew install cmake
```

#### 3. Installa Qt

```bash
brew install qt
```

#### 4. Configura il path di Qt ( se non già fatto )

```bash
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
```

## Ubuntu/Debian

#### 1. Aggiorna pacchetti

```bash
sudo apt update
```

#### 2. Installa dipendenze

```bash
sudo apt install cmake build-essential qt6-base-dev
```

#### Per verificare l'installazione

```bash
cmake --version
qmake --version
```

---
# Build e avvio

### 1. Clona il progetto

```bash
git clone https://github.com/zakka00/PaO_project.git
```

### 2. Crea build

```bash
mkdir build
cd build
```

### 3. Configura con CMake

```bash
cmake ..
```

### 4. Compila

```bash
cmake –build .
```

### 5. Avvia

```bash
./ecommerce
```
