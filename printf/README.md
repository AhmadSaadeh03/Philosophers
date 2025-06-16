# ft_printf

## Project Description
**ft_printf** is a project from the 42 curriculum where you are tasked with creating your own version of the standard C function `printf`. The objective is to implement a custom formatted output function that handles various data types and formatting options. This project allows you to improve your understanding of the C language, especially with regard to handling variable arguments, memory management, and type conversion.

The goal is to replicate the behavior of the standard `printf` function by handling common specifiers such as `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, and more, while ensuring that your implementation is efficient and works with different input formats.

## What I Did
In this project, I created a custom `printf` function that replicates the behavior of the standard C `printf`, with some additional flexibility and optimizations. Here are the key features of my implementation:

### 1. **Format Specifiers Supported**
   - **%c**: Character output.
   - **%s**: String output.
   - **%d**: Signed decimal integer.
   - **%i**: Signed integer (same as `%d`).
   - **%u**: Unsigned decimal integer.
   - **%x**: Unsigned hexadecimal integer (lowercase).
   - **%X**: Unsigned hexadecimal integer (uppercase).
   - **%p**: Pointer address in hexadecimal.
   - **%%**: A literal percent symbol.

### 2. **Variable Argument Handling**
   - Used `va_list`, `va_start`, `va_arg`, and `va_end` to handle a variable number of arguments passed to the function.
   - Designed my implementation to iterate over the format string, checking for format specifiers and corresponding argument types.
   
### 3. **Custom Output Formatting**
   - Implemented various formatting options such as width, precision, and left/right alignment for specifiers.
   - Ensured that the output was correctly formatted and adheres to the specifications of the standard `printf`.

### 4. **Memory Management**
   - Efficiently handled dynamic memory allocation and string formatting.
   - Ensured that no memory leaks occurred during the output generation process.

### 5. **Edge Case Handling**
   - Handled edge cases like null pointers, invalid format specifiers, and empty strings.
   - Managed different lengths of output (e.g., large numbers, long strings).

## Features
- Custom implementation of the `printf` function.
- Supports multiple format specifiers such as `%d`, `%s`, `%x`, `%c`, and others.
- Handles variable argument lists efficiently.
- Supports flags and width for formatting the output (e.g., left alignment, right alignment, precision).
- Handles special edge cases such as null pointers and invalid specifiers.

## Requirements
- A C compiler (e.g., `gcc`).
- Make utility for building the project.
- Basic knowledge of C, `varargs`, and formatting in C.

## Installation
To set up and compile the custom `printf` library on your local machine, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/AhmadSaadeh03/ft_printf.git
