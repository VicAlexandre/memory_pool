# mem_pool: Efficient Fixed-Size Memory Pool in C

A simple and efficient memory pool implemented in C for fast fixed-size block allocations and deallocations. Based on the publication [Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead](http://www.thinkmind.org/index.php?view=article&articleid=computation_tools_2012_1_10_80006).

## 📝 Table of Contents

- [Installation](#installation)
- [Examples](#examples)
- [Contributing](#contributing)

## 🛠 Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your_username/mem_pool.git
   cd mem_pool
   ```

2. **Compile the library**:

   ```bash
   make
   ```

   This will generate the `libmem_pool.a` static library inside the `obj` directory and a test binary named `test_driver` at the root of the repository.

   You can then run the test binary to verify that the library is working correctly:

   ```bash
    ./test_driver
   ```

## 📖 Examples

Includes a sample program that uses the library to allocate and deallocate memory blocks of different sizes. More examples will be added soon.

## 👥 Contribution

This project is a work-in-progress. Feedback, suggestions, and contributions are highly appreciated.
