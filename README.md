# MinesWeeper

## Summary

C implementation of the famous "MinesWeeper" game to be played in the console.

## Build

This leverages the `ncurses` library. It can be installed with:

```bash
sudo apt-get install libncurses-dev
```

The build uses `cmake`. Run the following command from the repo's root:

```bash
mkdir build
cd build
cmake ..
make
```

## Run

```
./minesweeper
```

