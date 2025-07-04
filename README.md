# TinyCSV

A lightweight and embedded-friendly CSV parsing and writing library written in C.  
**TinyCSV** is designed to work with memory buffers and function pointers, making it ideal for microcontrollers or systems without file systems.

---

## 📦 Project Overview

**TinyCSV** provides basic functionality to:
- Read CSV files line-by-line or by row index.
- Write new rows to the CSV structure.
- Simulate file I/O using memory-mapped functions.
- Handle up to 5 columns and 2048 bytes of CSV data (configurable).

It uses fixed-size buffers for deterministic behavior in resource-constrained environments.

---

## ✨ Features

- 🧵 Lightweight design with zero dynamic memory allocation.
- 📖 CSV line-by-line and row-by-index reading.
- ✍️ Write support with automatic row tracking.
- 🔌 Custom file abstraction via `rfile()` and `wfile()` function pointers.
- ✅ Unit tests using [Ceedling](http://www.throwtheswitch.org/ceedling) and Unity.
- 🧪 Comes with example programs (`basic_read` and `basic_write`).

---

## 🛠️ Setup & Compilation

### Requirements
- GCC or any standard C compiler
- `make`
- Optional: [Ceedling](http://www.throwtheswitch.org/ceedling) for running unit tests

### Directory Structure
```

.
├── examples/
│   ├── basic\_read.c
│   └── basic\_write.c
├── include/
│   └── tinycsv.h
├── src/
│   └── tinycsv.c
├── test/
│   └── test\_tinycsv.c
├── makefile
├── project.yml
└── README.md

````

### Build and Run Examples

```bash
make all
````

This will:

* Compile `basic_read.exe` and `basic_write.exe`
* Run both executables

To clean build artifacts:

```bash
make clean
```

---

## 🧪 Running Unit Tests

Ceedling is used to manage unit tests.

### Run all tests

```bash
make test
```

Or directly via Ceedling if installed:

```bash
ceedling test:all
```

---

## 🧰 Usage Overview

### Define File Access Functions

```c
char rfile(uint32_t addr) {
    return buffer[addr];  // simulate file read
}

int wfile(uint32_t addr, char ch) {
    buffer[addr] = ch;    // simulate file write
    return 0;
}
```

### Initialize `csv_st`

```c
csv_st csv;
csv.rfile = rfile;
csv.wfile = wfile;
csv.cols = 4;

csv_open(&csv);
```

### Read Data

```c
csv_read(&csv);
printf("First field: %s\n", csv.field[0]);
```

### Write Data

```c
strcpy(csv.field[0], "John");
strcpy(csv.field[1], "25");
strcpy(csv.field[2], "Male");
strcpy(csv.field[3], "john@example.com");
csv_write(&csv);
```

---

## 🧱 Limitations

* Fixed max fields: 5
* Max field length: 30 characters
* Max CSV length: 2048 bytes
* No support for quoted fields or embedded commas
* No dynamic memory or delimiter customization

---

## 📜 License

This project is open-source and licensed under the **MIT License**.

---

## 🙌 Contributing

Feel free to open issues, improve the CSV handling, or adapt for specific platforms. PRs are welcome!

---

## 🔗 Related Projects

* [Ceedling](https://github.com/ThrowTheSwitch/Ceedling) – C unit testing framework
* [Unity](https://github.com/ThrowTheSwitch/Unity) – C test assertion library

---
