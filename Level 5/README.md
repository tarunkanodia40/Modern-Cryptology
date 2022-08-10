# Level 5

To find password, run `make` in the current directory. If `plaintexts.txt` and `output.txt` are missing (after running `make clean`), run `make inputs` and then `make outputs`.  The complete description of files:

- `generate_inputs.py` : Generates all plaintexts.
- `script.sh` and `init.py`: Basic starter code to fetch outputs of the generated inputs.

- `find_matrix`: Finds complete matrix `A` and `E`.

- `decrypt`: Uses `A` and `E` found by `find_matrix` to find the password.
