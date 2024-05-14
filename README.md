### MEMORIZER

Really simple project to test Raylib.
There is a 3x3 grid of squares which changes colors based on random order.
The player needs to follow that order to win.

## System used

Ubuntu Linux x64

## Prerequisites

- C compiler
- Raylib library instated

## Usage

1. Clone the repository

2. Give permission to the ./build.sh

```bash
~/your_path/memorizer$ sudo chmod +x build.sh
```

3. Run build.sh

```bash
~/your_path/memorizer$ ./build.sh
```

4. Run main

```bash
~/your_path/memorizer$ ./main
```

(
You can just run the command if you prefer:

```bash
~/your_path/memorizer$ gcc -std=c99 -Wall -I/usr/include -L/usr/local/lib/libraylib.so -o main src/main.c src/game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

)
