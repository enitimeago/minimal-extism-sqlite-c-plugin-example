WASICC?=wasicc

.PHONY: memvfs
memvfs:
	$(WASICC) -g -o memvfs/out/example.wasm -Wl,--export=count_vowels -Wl,--allow-undefined -isystem sqlite3 -I. -DHAVE_UTIME=1 memvfs/main.c sqlite3/sqlite3.c sqlite3/memvfs.c

.PHONY: memvfs-run
memvfs-run:
	extism call --input 'abcdefg' memvfs/out/example.wasm count_vowels --wasi

.PHONY: unixvfs
unixvfs:
	$(WASICC) -g -o unixvfs/out/example.wasm -Wl,--allow-undefined -I sqlite3 -I. -DHAVE_UTIME=1 unixvfs/main.c sqlite3/sqlite3.c

.PHONY: unixvfs-run
# TODO: change back to count_vowels instead of _start once fix landed wrt __wasm_call_ctors?
unixvfs-run:
	extism call --input 'abcdefg' unixvfs/out/example.wasm _start --wasi
