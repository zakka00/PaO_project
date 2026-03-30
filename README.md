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
- Sistema di **filtri avanzati**
- Lista **preferiti**
- Interfaccia grafica con **Qt Widgets**
- Salvataggio dati in **JSON**
- Pattern **Visitor**

---

## Struttura del progetto
.
├── Headers/
│   ├── Graphics/
│   └── Logic/
├── Sources/
│   ├── Graphics/
│   └── Logic/
├── resources.qrc
├── CMakeLists.txt
└── README.md

---

## Requisiti

- C++17 o superiore
- CMake ≥ 3.16
- Qt 6 (o Qt 5 compatibile)
- Compilatore:
  - macOS: clang++
  - Linux: g++
  - Windows: MSVC / MinGW

Verifica:
cmake –version
qmake –version
---

## Build e avvio

La cartella `build/` NON è inclusa nel repository.

### 1. Clona il progetto
git clone 
cd 
---

### 2. Crea build
mkdir build
cd build
---

### 3. Configura con CMake
cmake ..
---

### 4. Compila
cmake –build .
---

### 5. Avvia

#### macOS
open ecommerce.app