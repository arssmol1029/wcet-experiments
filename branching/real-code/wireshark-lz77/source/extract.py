#!/usr/bin/env python3
"""Verify or recreate an exact upstream computational-function slice."""
from pathlib import Path
import hashlib
import difflib
import sys

base = Path(__file__).resolve().parent
source = base.parent / "sources/wireshark_v4.6.5_tvbuff_lz77.c"
raw = source.read_bytes()
assert hashlib.sha256(raw).hexdigest() == "8319d0ec9a5fc60121d46a39a88a13daa5a61dff72bd9ad81635bbec72df8dc9"
s = raw.decode()
a = s.index("#define MAX_INPUT_SIZE")
b = s.index("\ntvbuff_t *", a)
if "--write" in sys.argv:
    (base / "core.inc").write_bytes(s[a:b].encode())
if "--diff" in sys.argv:
    (base / "upstream-core.diff").write_text("".join(difflib.unified_diff(
        s[a:b].splitlines(keepends=True),
        (base / "core.inc").read_text().splitlines(keepends=True),
        fromfile="upstream/do_uncompress", tofile="port/do_uncompress")))
assert (base / "core.inc").read_bytes() == s[a:b].encode(), "core.inc differs from exact upstream slice"
print("PASS: core.inc byte-identical upstream computational function")
