# Team Happiness Club - EvalEx

## Team Members
***Tommy Lam***
- Contact: tommy.lam59@ku.edu
- Availability:
  - Monday's: 1:00 pm and later
  - Tuesday's, Wednesday's and Thursday's: 4:00 pm and later
  - Saturday's and Sunday's: Anytime
- Computer Science major - Sophmore (2025)
- Relevant Coursework: EECS 140, 168, 210, 268, currently enrolled in EECS 330, 348, 388, 468
- Programming Languages/Libraries: C, Javascript, HTML, Python

***William Whitehead***
- Contact: w412w955@ku.edu
- Availability:
  - Monday: 3:00 pm and later
  - Tuesday: 3:00 pm and later
  - Wednesday: 3:00 pm and later
  - Thursday's: 3:00 pm and later
  - Saturday / Sunday: Anytime
- Computer Science major - Sophmore (Dec 2025)
- Relevant Coursework: EECS 168, 268, 140, currently enrolled in EECS 348, 388, 290
- Programming Languages/Libraries: Python, C, Javascript, HTML, CSS

***Joshua Lee***
- Contact: joshua.lee@ku.edu
- Availability:
  - Monday: 1:00 pm and later
  - Tuesday: 4:00 pm - 5:15 pm ; 7:00 pm and later
  - Wednesday: 1:00 pm - 2:00 pm ; 4:00 pm - 6:00 pm ; 7:00 pm and later
  - Thursday: 5:00 pm and later
  - Friday: 2:00 pm - 3:00 pm ; 5:00 pm and later
  - Saturday / Sunday: Anytime
- Computer Science major - Sophomore (Dec 2025)
- Relevant Coursework: EECS 168, 268, 141, currently enrolled in EECS 348, 388, 210
- Programming Languages/Libraries: Python, C, HTML, CSS

***Joe Hotze***
- Contact: jmhotze@ku.edu
- Availability:
  - Monday: 2:00 pm and later
  - Tuesday: Before 11 am
  - Wednesday: 2:00 pm and later
  - Thursday: Before 11 am
  - Friday: 2:00 pm and later
  - Saturday / Sunday: All day
- Computer Science major - Sophomore (Spring 2026)
- Relevant Coursework: EECS 169, 268, 140, Enrolled in EECS 348, 210
- Programming Language: Python

  ***Max Biundo***
- Contact: m679b014@home.ku.edu
- Availability:
  - Monday: 1:00 pm- 5:00 pm
  - Tuesday: 4:00 pm- 6:00 pm
  - Wednesday: 4:00 pm- 6:00 pm
  - Thursday: 4:00 pm- 8:00 pm
  - Saturday / Sunday: 10:00 am- 6:00 pm
- Computer Science major - Sophmore (May 2026)
- Relevant Coursework: EECS 168, 268, 140, currently enrolled in EECS 348
- Programming Languages/Libraries: Python, C

## Roles & Responsibilities
#### Project Leader - Max Biundo:
- Guides the rest of the group through the project
#### Risk Manager - Joe Hotze:
- Finds any and all risks that could arise throughout the course of the development
#### Quality Control - Will Whitehead:
- Searches for bugs or possible errors in the code to fix before they become significant issues
#### Configuration Management: Joshua Lee
- Make sure project artifacts are sufficiently named and marked for submission. Make sure work is readable to people who didn’t write the program
#### Programmer: Tommy Lam and Gunther Leuchtefeld
- Write the code for the project

# Getting Started

**EvalEx** is a simple-to-use system that can be executed on an operating system capable of running C++. To use the program, follow these steps:

1. **Start the Program**: Run the executable, and you will be presented with a small menu.

2. **Calculator Usage**: To use the calculator features of the program, simply type in an expression as you would into a normal calculator. Many operations are supported, including:

   - Addition `+`
   - Subtraction `-`
   - Multiplication `*`
   - Division `/`
   - Modulo `%`
   - Exponentiation `^`
   - Parentheses `()`
   - Positive or Negative `+/-`

   **Important:** Pay attention to spaces when entering expressions. Spaces matter to distinguish between attaching a positive or negative operator to an integer and addition or subtraction. Negative and positive operators should be attached directly to an integer or set of parentheses, while spaces should be placed between expressions. Parentheses should also directly connect to the integers within them. For example:

   - Correct: `8 - (5 / -2)`
   - Incorrect: `10 + - 2`

   Additionally, parentheses multiplication, such as in the case of `4(5 + 3)`, is not supported. Please utilize the multiplication operator `*` for situations like these. For example: `4 * (5 + 3)` would work without errors.

3. **Examples**: You can find further examples of expressions that can be entered into the calculator in the "Examples" section below.

# Advanced Features

**EvalEx** has been extensively tested to ensure accuracy and precision. Advanced features that set **EvalEx** apart from others in the market include its state-of-the-art handling of extraneous parentheses, the inclusion of the modulo operator, and support for unary operators.

# Troubleshooting

Most problems within **EvalEx** have straightforward solutions:

- Check for unmatched parentheses, letters, or special characters that **EvalEx** cannot handle.
- Consistent errors not related to syntactical errors can often be fixed by recompiling the source code into a new executable. To do this:

  1. Open the folder containing **EvalEx** in a terminal window.
  2. Input the following command:
     ```
     g++ EvalEx.cpp -o evalex.exe
     ```
     This will recompile the code and create a new executable that is free from memory leaks and may work better.

**Example 1: Simple Operators**
Input:




