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
solve "10+4*2" # would output 16
```

Error checking is not implemented yet, so input correct expressions are you will get seg fault.