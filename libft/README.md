# libft

## Project Description
**libft** is a project from the 42 curriculum where you are tasked with implementing a custom standard library in C. The goal is to create a set of utility functions commonly found in the C Standard Library (libc), but you implement them yourself. These functions include string manipulation, memory handling, type conversion, and more.

This project allows you to understand how low-level functions work and helps improve your C programming skills.

## What I Did
In this project, I created several C functions that implement core parts of the C Standard Library. Here are the key elements I worked on:

### 1. **Memory Management Functions**
   - **ft_memset**: Initializes a block of memory with a specified value.
   - **ft_bzero**: Sets a block of memory to zero.
   - **ft_memcpy**: Copies memory from one location to another.
   - **ft_memmove**: Safely moves memory from one location to another, even if the memory regions overlap.
   - **ft_memchr**: Searches for the first occurrence of a byte in a block of memory.
   - **ft_memcmp**: Compares two blocks of memory.

### 2. **String Manipulation Functions**
   - **ft_strlen**: Returns the length of a string.
   - **ft_strdup**: Allocates memory for a string and copies the contents of another string into it.
   - **ft_strcpy**: Copies one string into another.
   - **ft_strncpy**: Copies a specified number of characters from one string to another.
   - **ft_strcat**: Concatenates two strings.
   - **ft_strncat**: Concatenates a specified number of characters from one string to another.
   - **ft_strchr**: Searches for the first occurrence of a character in a string.
   - **ft_strrchr**: Searches for the last occurrence of a character in a string.
   - **ft_strstr**: Finds the first occurrence of a substring in a string.
   - **ft_strcmp**: Compares two strings.
   - **ft_strncmp**: Compares the first `n` characters of two strings.

### 3. **Character and Type Conversion Functions**
   - **ft_isalpha**: Checks if a character is alphabetic.
   - **ft_isdigit**: Checks if a character is a digit.
   - **ft_isalnum**: Checks if a character is alphanumeric.
   - **ft_isascii**: Checks if a character is a valid ASCII character.
   - **ft_isprint**: Checks if a character is printable.
   - **ft_toupper**: Converts a character to uppercase.
   - **ft_tolower**: Converts a character to lowercase.
   - **ft_atoi**: Converts a string to an integer.

### 4. **Linked List Functions**
   - **ft_lstnew**: Creates a new list element.
   - **ft_lstadd_front**: Adds a new element to the front of the list.
   - **ft_lstsize**: Returns the size of the list.
   - **ft_lstlast**: Returns the last element of the list.
   - **ft_lstadd_back**: Adds a new element to the end of the list.
   - **ft_lstdelone**: Deletes a single list element.
   - **ft_lstclear**: Clears the entire list.
   - **ft_lstiter**: Iterates through the list and applies a function to each element.
   - **ft_lstmap**: Iterates through the list and applies a function to each element, creating a new list.

## Features
- A complete custom C library with utility functions for memory handling, string manipulation, character classification, type conversion, and linked list operations.
- Implemented from scratch, following the 42 curriculum's specifications.
- Modular and reusable code that can be used in various C projects.

## Requirements
- A C compiler (e.g., `gcc`).
- Make utility for building the library.
- Basic understanding of C and memory management.

## Installation
To set up and compile the library on your local machine, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/AhmadSaadeh03/libft.git
