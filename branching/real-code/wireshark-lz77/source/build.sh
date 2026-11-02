#!/usr/bin/env bash
set -euo pipefail
task_dir=$(cd -- "$(dirname -- "$0")" && pwd)
task_out=${OUT_DIR:-"$task_dir/build"}
mkdir -p "$task_out"
python3 "$task_dir/extract.py"
task_cc=${CC:-cc}
if [[ ${1:-native} == native ]]; then
    "$task_cc" -std=c11 -O1 -g -Wall -Wextra -fsanitize=address,undefined \
        "$task_dir/native_test.c" -o "$task_out/native_test"
    "$task_out/native_test"
elif [[ $1 == arm ]]; then
    : "${CC:?Set CC to configured ARM compiler}"
    task_scale=${BENCHMARK_SCALE:-3}
    [[ $task_scale =~ ^[0-3]$ ]] || { printf 'BENCHMARK_SCALE must be 0..3\n' >&2; exit 2; }
    "$CC" -std=c11 "${OPT_LEVEL:--O2}" -g -fno-inline -fno-builtin -fno-stack-protector \
        -fno-jump-tables -fno-tree-switch-conversion -fno-optimize-sibling-calls \
        -march=armv5te -marm -mfloat-abi=soft \
        "-DBENCHMARK_PRESET_HEADER=\"preset${task_scale}.h\"" \
        -DBENCHMARK_STANDALONE "$task_dir/harness.c" \
        ${ARM_LINK_FLAGS:--static} -o "$task_out/wireshark_lz77.elf"
else
    printf 'usage: %s native|arm\n' "$0" >&2
    exit 2
fi
