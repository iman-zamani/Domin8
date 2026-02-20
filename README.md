# Domin8

**Domin8 Chess Engine** is a UCI-compatible chess engine crafted in C for dynamic, aggressive gameplay. Designed to minimize draws, this engine strives for decisive outcomes, pushing for either a win or loss in every game. Its unique algorithms enhance aggressive tactics, making it an ideal choice for enthusiastic players and competitive environments looking to challenge traditional playing styles. Perfect for those seeking to transform every chess match into a thrilling battle!

## Features

- UCI (Universal Chess Interface) compatible  
- Aggressive evaluation and move selection  
- Minimal-draw design for decisive results  

## Build Instructions

Domin8 uses a simple Makefile for compiling the engine. You’ll need `gcc` installed on your system.

### To build the engine:

```bash
make
```

The compiled executable will be placed in the `build/` directory as `Domin8`.

### To run the engine (after building):

```bash
make run
```

### To clean all build artifacts:

```bash
make clean
```

## License

This project is licensed under [Apache-2.0 license](./LICENSE).
