Tested on WSL on Windows 11 22H2 only at time of writing.

Demo instructions:

1. Ensure `wasienv` is installed.
    - macOS, Linux installation instructions [here](https://github.com/wasienv/wasienv).
    - No native Windows support at time of writing, [use these instructions](https://medium.com/wasmer/wasienv-wasi-development-workflow-for-humans-1811d9a50345#:~:text=you%20can%20also%20install%20wasienv%20from%20source%20like%20this%3A) for WSL.
2. Ensure `extism` is installed.
    - macOS, Linux installation instructions [here](https://extism.org/docs/install/).
    - No native Windows support at time of writing, use Linux instructions for WSL.
3. Build and run either unixvfs or memvfs versions.
    - **unixvfs** reads database from disk:
      1. Get a SQLite database file and replace /path/to/your.db in unixvfs/main.c.
      2. `make memvfs`
      3. `extism call --allow-path /path/to --wasi unixvfs/out/example.wasm _start`
    - **memvfs** reads database from bytes:
      1. Get the bytes for a SQLite database file and replace dbbytes[] in memvfs/main.c.
      2. `make memvfs`
      3. `make memvfs-run`

If using this repo as a template please use your own copy of the SQLite amalgamation and SQLite extension files.
These sources are included only for convenience and no guarantees are made for correctness or being kept up-to-date.
