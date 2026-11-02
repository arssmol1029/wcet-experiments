#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mode=${1:-native}
blocks=${CASE_BLOCKS:-32}
out=${BUILD_OUT:-build-${mode}-${blocks}}
mkdir -p "$out"
python_bin=${PYTHON:-python3}
"$python_bin" generate_fixture.py --blocks "$blocks" --out "$out"
up=libpcap-libpcap-1.10.5
common=(-O2 -g -std=gnu11 -D_DEFAULT_SOURCE -I. -I"$up" -I"$out" -ffunction-sections -fdata-sections -fno-jump-tables -fno-optimize-sibling-calls)
if [[ "$mode" == native ]]; then
    cc=${CC:-cc}
    if [[ ${SANITIZE:-0} == 1 ]]; then common+=(-fsanitize=address,undefined); fi
    if [[ "$(uname -s)" == Darwin ]]; then dead=(-Wl,-dead_strip); else dead=(-Wl,--gc-sections); fi
    "$cc" "${common[@]}" "${dead[@]}" -DNATIVE_TEST harness.c -o "$out/native-test"
    "$out/native-test" | tee "$out/native-test.log"
elif [[ "$mode" == arm ]]; then
    cc=${CC:-arm-linux-gnueabi-gcc}
    "$cc" "${common[@]}" -fno-builtin -fno-tree-switch-conversion -marm -march=armv5te -mfloat-abi=soft -fno-pie -no-pie -static -nostartfiles -Wl,-e,main -Wl,--gc-sections -fno-stack-protector harness.c portable_runtime.c -o "$out/kernel.elf"
    arm-linux-gnueabi-objdump -d -S "$out/kernel.elf" > "$out/kernel.disasm.txt"
    arm-linux-gnueabi-nm -S "$out/kernel.elf" > "$out/kernel.symbols.txt"
else
    echo 'mode must be native or arm' >&2
    exit 2
fi
