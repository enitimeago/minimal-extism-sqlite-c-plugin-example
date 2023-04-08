Tested on WSL on Windows 11 22H2 only at time of writing.

Demo instructions:

1. Ensure `wasienv` is installed.
  - macOS, Linux installation instructions [here](https://github.com/wasienv/wasienv).
  - No native Windows support at time of writing, [use these instructions](https://medium.com/wasmer/wasienv-wasi-development-workflow-for-humans-1811d9a50345#:~:text=you%20can%20also%20install%20wasienv%20from%20source%20like%20this%3A) for WSL.
2. Ensure `extism` is installed.
  - macOS, Linux installation instructions [here](https://extism.org/docs/install/).
  - No native Windows support at time of writing, use Linux instructions for WSL.
3. Get bytes for a SQLite database file and replace dbbytes[] in main.c.
  - **TODO:** Supply a sample database and/or support reading from files.
4. Run `make`.
5. Run `make run`.

If using this repo as a template please use your own copy of the SQLite amalgamation and SQLite extension files, these sources are included only for convenience.
