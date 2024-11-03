Topic: Application, Arbitrary precision calculator

== Semester work

Aim of this semester work to create application: calculator with unlimited precision.
Calculator implements:

1. Work with integer and float numbers
2. For both type numbers implemented adding, substracting , multiplication, exponintation, where exponent is positive, integer number and rounding
3. For integer numbers implemented integer division, modulo division, factorial
4. In calculator must be variables, that contains certain value
5. Variables in calculator can be exported to file, and can be imported from file
6. Numbers in calculator must be saved in memory effitively.

Application process expression according to one of the following principles:

1. Basic operation (at least adding, subtarcting, multiplication) must be nested uisng parentheses (e.g (2+2) \* 2), brackets can be nested arbitrarily. More complex operation and functions can work in the form of individual commands without additional parentheses (20! - 5)
2. Use prefix (or postfix) notation for the written expression, benefits of this princip, that do not have to specify parentheses and. In this case, all operations and functions must go write in one expression

Example of program running:
X = 100!
20 + 20
RESULT: 40
A = 2 \* (2+2)
B = X / A^20
C = B~
#EXPORT memory.calc
#EXIT

Where you can use polymorphism
Representation of number : sparse numbers, dense numbers ...
Operation: adding, subtracting, multiplication, division ...
Export format: text, binary ...
User interface: console, ncurses, SDL ...

== Polymorphism
Polymorphism is used in hierarchy of class 'CBigNumber', that has two children 'CBigInt' and 'CBigFloat'. Class 'CBigNumber' has pure virtual methods 'add', 'subtract', 'multiply', 'division', 'divMod', 'exponentation', 'round', 'factorial'. Those methods is implemented in children classes and will return pointer to children class of 'CBigNumber' depending on operation and operands. Some methods always throw exception depengin on operation(e.g factorial for float does not exist and etc).
