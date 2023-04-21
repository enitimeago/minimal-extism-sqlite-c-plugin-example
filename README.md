Tested on WSL on Windows 11 22H2 only at time of writing.

Demo instructions:

1. Ensure `wasi-sdk` is installed. Tested with version 20 only, version 8 is known not to work with SQLite's usage of lstat.
    - Follow installation instructions from [here](https://github.com/WebAssembly/wasi-sdk).
    - Windows appears to be supported but is untested.
2. Ensure `extism` is installed.
    - macOS, Linux installation instructions [here](https://extism.org/docs/install/).
      - **At time of writing, you will need the [`init-wasi`](https://github.com/extism/extism/pull/311) branch.** Install with `extism install git --branch init-wasi`.
    - No native Windows support at time of writing, use Linux instructions for WSL.
3. Build and run either unixvfs or memvfs versions.
    - **unixvfs** reads database from disk:
      1. Get a SQLite database file and place an example database "your.db" in this directory.
      2. Run `WASICC=~/wasi-sdk-20.0/bin/clang make unixvfs && make unixvfs-run` (replace WASICC var with where you installed wasi-sdk)
    - **memvfs** reads database from bytes:
      1. Get the bytes for a SQLite database file and replace dbbytes[] in memvfs/main.c.
      2. Run `WASICC=~/wasi-sdk-20.0/bin/clang make memvfs && make memvfs-run` (replace WASICC var with where you installed wasi-sdk)

If using this repo as a template please use your own copy of the SQLite amalgamation and SQLite extension files.
These sources are included only for convenience and no guarantees are made for correctness or being kept up-to-date.
