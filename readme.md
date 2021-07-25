# Solver
A simple math expression solver using the shunting yard algorithm. The parser tokenizes the math input and then constructs the reverse polish notation, then solves it.

## Installation & Usage
Type the following into your terminal (after you have cloned the repo):
```shell
sh compile.sh
make install
```
Then you can use the `solve` command anywhere in your computer by typing:
```shell
solve "10 + 4*2" # would output 16, whitespaces doesn't matter
```

## Currently supported operators:
| Operator        | Example Usage  | Result  |
| ------------- |:-------------:| -----:|
| `+`     | `solve "10+2"` | `12` |
| `-`      | `solve 10-2`      |   `8` |
| `/` | `solve 9/2`      |    `4.5` |
| `*` | `solve 12*4`     |    `48` |
| `^` | `solve 10^2`      |    `100` |

### Some edge case scenarios
Consider the following expression:
`solve 10/2^4` - The result would be `625` since the program first executes `/` operator, then the `^` operator.
To get `0.625` as result, use this:
`solve 10/(2^4)` - The result would be `0.625`

Error checking is not implemented yet, so input correct expressions or you will get seg fault.