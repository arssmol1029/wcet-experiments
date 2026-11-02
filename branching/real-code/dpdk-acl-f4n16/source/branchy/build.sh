#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
mode=${1:-native}
out=${BUILD_OUT:?Set a fresh absolute BUILD_OUT}
rules=${CASE_RULES:-16}
families=${CASE_FAMILIES:-4}
if [[ "$out" != /* || -e "$out" ]]; then echo 'BUILD_OUT must be a NEW absolute path' >&2; exit 2; fi
case "$families:$rules" in 2:16|4:16|4:64|4:256) ;; *) echo 'Unsupported finite profile' >&2; exit 2;; esac
mkdir -p "$out"
common=../dpdk-acl-port
flags=(-std=gnu11 -O2 -g -fno-strict-aliasing -ffunction-sections -fdata-sections -I"$common" -I"$common/upstream" -include "$common/compat.h" -DCASE_RULES="$rules" -DCASE_FAMILIES="$families")
if [[ "$mode" == native ]]; then
  cc=${CC:-cc}
  extra=(-DNATIVE_TEST)
  if [[ ${SANITIZE:-0} == 1 ]]; then extra+=(-fsanitize=address,undefined); fi
  "$cc" "${flags[@]}" "${extra[@]}" harness.c "$common/upstream/tb_mem.c" -o "$out/native"
  "$out/native"
elif [[ "$mode" == arm ]]; then
  cc=${CC:-arm-linux-gnueabi-gcc}
  flags+=(-marm -march=armv5te -mfloat-abi=soft -fno-pie -fno-builtin -fno-jump-tables -fno-tree-switch-conversion -fno-optimize-sibling-calls -fno-stack-protector)
  "$cc" "${flags[@]}" -c harness.c -o "$out/harness.o"
  "$cc" "${flags[@]}" -c "$common/upstream/tb_mem.c" -o "$out/tb_mem.o"
  "$cc" "${flags[@]}" -c "$common/portable_runtime.c" -o "$out/runtime.o"
  "$cc" -static -no-pie -Wl,--gc-sections,-Map,"$out/kernel.map" "$out/harness.o" "$out/tb_mem.o" "$out/runtime.o" -o "$out/kernel.elf"
  arm-linux-gnueabi-nm -S "$out/harness.o" > "$out/object-symbols.txt"
  arm-linux-gnueabi-nm -S "$out/kernel.elf" > "$out/symbols.txt"
  arm-linux-gnueabi-objdump -d -S "$out/kernel.elf" > "$out/disassembly.txt"
else
  echo 'native or arm required' >&2
  exit 2
fi
