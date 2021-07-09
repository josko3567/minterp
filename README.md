# minterp ->

-> takes a input string of math format and outputs it's result as a string again.

- Operators are

- [-] subtraction

example:
input  = "575 - 50"
output = "+525"

- [+] addition

example:
input  = "575 + 50"
output = "+625"

- [*] multiplication

example:
input  = "5 * 5"
output = "+25"

- [/] divison

example:
input  = "25 / 12.5"
output = "+2.000000"

- [^] the power of

example:
input  = "5^4"
output = "+625"

- [$] the root of

example:
input  = "2$4" // the square root of 4
output = "+2.000000"

input  = "3$27" // the cubic root of 27
output = "+3.000000"

------------------------------------------
additional stdarg characters are

%f (double), %ld (long long), %d (int) for a printf type of inserting variables

or

&fn and &ldn, 

WARNING: don't use & and % at the same time, use only one or the other

&fn takes the n-th number inside ... and interprets it as a double

example:
minterp("&f1 + &f2 - &f1", &output, 4.0, 17.0);
output -> "+17.000000"

same goes for &ldn, but you must cast any integers to long long.
example:
minterp("&ld1 + &ld2 - &ld1", &output, (long long) 4, (long long) 17);
output -> "+17"
