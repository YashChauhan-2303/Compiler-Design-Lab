# C Programming Labs Collection

This repository contains a set of C programming lab exercises organized by lab number (Lab 01 through Lab 10). Each lab directory typically contains one or more exercises in subfolders (e.g. `q1`, `q2`) and example input/output files.

## Repository structure
- `Lab 01/` … `Lab 10/`: individual lab folders containing exercises and supporting files.

Common file patterns you may see:
- `q1`, `q2`, `q3`, ... — subfolders for exercises
- `q1.c`, `q2.c`, `q.c`, `sample.c` — source files
- `input.txt`, `output.txt`, `sample` — sample input/output files

## How to build and run
1. Change into the lab or exercise directory:

```bash
cd "Lab 09"            # or cd "Lab 02/q1" for nested exercises
```

2. Compile a C source file with `gcc`:

```bash
gcc q.c -o q           # for single-file programs
gcc q1.c -o q1         # or adjust filenames accordingly
```

3. Run the compiled program (optionally redirect input):

```bash
./q < input.txt
./q1
```

Notes:
- If an exercise is inside a subfolder (e.g. `q1/q1.c`), either `cd` into the subfolder or pass the relative path to `gcc`.
- Many exercises include `input.txt` or `sample` files — use input redirection to test easily.

## Tips
- Add a simple `Makefile` in each lab folder to simplify building multiple exercises.
- Keep compiled binaries out of source control (use `.gitignore` if needed).

## Contact / Author
This workspace contains personal lab work. If you want changes or a more detailed per-lab README, I can generate one per lab on request.
