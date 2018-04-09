# Data Structures Homework 0 - Simple Infix Calculator

## Prerequisites

- UNIX/UNIX-like operating system
- C/C++ development environment

## Specifications

This homework offers an opportunity to familiarize with
C/C++ before writing complex data structures with these
languages.

You are required to complete a simple calculator that 
can calculate simple 
[infix expressions](https://en.wikipedia.org/wiki/Infix_notation).

### Input specifications

[EBNF](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form)
```
Expression = Expression BinaryOp Expression | "(" Expression ")" | Numerical
Numerical = Integer | Floating
Integer = Digits
Floating = Digits "." Digits | "." Digits | Digits "."
Digits = Digit Digits | Digit
Digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
BinaryOp = "+" | "-" | "*" | "/"
```

### Output specifications

Output the result in one line.

## Submission

We will use Autolab for homework grading. The system is currently under construction and will be available soon.

## Deadline

23:59:59 CST (Beijing Time), March 17th 2018
