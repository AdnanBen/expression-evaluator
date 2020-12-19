# expression-evaluator
The program uses an algorithm based on the shunting yard algorithm to correctly parse and evaluate mathematical expressions including various functions, operators and variables. A struct based stack implementation is used to execute the algorithm.

## Installation

Inside src directory, run:

```bash
make
```

## Usage

The program accepts decimals, positive and negative numbers, each expressed using the double type.

When the program launches, the user is asked to enter the maximum character limit for any entered expression or variable definition of this particular runtime. 200 should be adequate.

Next, the user is either asked to enter an expression or variable definition.

Acceptable expressions include:

Any sequence of numbers separated by the operators + - * / ^, the expression will be evaluated using standard precedence rules. These rules can be overwritten using parentheses: ().

Within these expressions the numbers may be passed as arguments to the provided functions. These functions include:

```C
sin(x)
cos(X)
tan(x)
ln(x)
log(x)  // This is [base 10]
sqrt(x)
```

Where x is the number

The user can also set the precision of any results to a certain number of decimal places. This is done using the p variable.

E.g. 
p = 2 will cause all future evaluated expressions to be given to 2 decimal places.

Finally, the user can set the variables X,Y,Z to any value and then use them within their expressions. These variables are set to 0 at runtime. Variables can be defined in various ways however as a rule when using multiple equality signs in a single definition, only the rightmost expression should contain anything other than the sole variables.
 
Examples of definitions:
```C
X = 2
X = Y – 2
X = Y + X * 2
X = Y = Z = 2
X = Y = (Z + 3)*sin(2)
```

The user can use ‘Q’ to quit the program at any time by typing it in place of an expression or variable definition

Additional usage notes:

-	All variables, functions and commands (Q , p) are case sensitive
-	Please take caution when copy and pasting expressions from other sources as character codes for operators, etc. may differ

