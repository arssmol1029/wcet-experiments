# Public whole-block contract, N=4096

Pinned upstream zstd1.5.7 commit f8745da6ff1ad1e7bab384bd1f9d742439278e99.
Entry: `task_zstd_block` calls public `ZSTD_compressBlock` exactly once.
No upstream C source is edited or renamed. A real ZSTD_createCCtx and
ZSTD_compressBegin_advanced prepare the context before task. Storage has
two prefix bytes, arbitrary4096 immutable source bytes and64 initialized
suffix bytes; output capacity5152. This is one block, without batch work.

The entry includes public validation, window update, first-block
overflow check, buildSeqStore, unchanged btultra parser, last literals,
HUF/FSE entropy coding and rep/entropy commit. It excludes allocator/init,
input construction, output checking and subsequent decompression.
Frame construction/checksum are outside this raw-block API. The returned
0 for an incompressible block remains a legitimate result.

## Fresh context and source reachability

The prepared boundary checks strategybtultra,minMatch4,searchLog5,
targetLength64,window/hash/chain≤16/14/16,initial indices2,nextToUpdate2,
zero loaded dictionary, NULL dictMatchState/LDM/ext producer, empty raw
external store, no sequence collector, repeat modes HUF/FSE none,
tmpWorkspace≥ENTROPY_WORKSPACE_SIZE, SeqStore capacities1024/4096,
fresh opt.litLengthSum0, stageinit/consumed0/produced0, bmi2=0.
SeqStore cursors are deliberately reset by upstream buildSeqStore inside
task; requiring them empty at this earlier boundary would be incorrect.

ZSTD_window_update sees the first source discontinuity and an old prefix
of length2. It assigns base=source−2 (a valid address in supplied storage),
dictLimit=lowLimit2,nextSrc=source+4096. Then curr=4098. With the release
default ZSTD_WINDOW_OVERFLOW_CORRECT_FREQUENTLY=0 and
ZSTD_CURRENT_MAX much larger than4098, no index reduction branch executes.
The window/property loads must be bound to actual ARM words before any
FF ignore directives. Public API uses frame0, so frame header/frameChunk
and final frame-RLE probe do not execute. Raw/RLE literal fallback remains.

Reachable dispatch sets: blockCompressor={ZSTD_compressBlock_btultra};
parser getAllMatches={ZSTD_btGetAllMatches_noDict_4}; literal callback=
{HUF_compress1X_repeat,HUF_compress4X_repeat}. The latter depends on actual
literal length below/above256 and both targets are necessary. ARM has no
BMI2 dispatch. No kernel allocator or I/O appears on this source route;
ordinary libc and allocation callbacks remain in setup. Native allocator
counts validate this on tested inputs, but are not the source proof.

## Parser and entropy progress

The parser source contract from the admitted btultra case remains the
starting proof, including possible repeated suffix lookahead. In particular
ΣforwardDP≤4096*1024, not4096; effective search positions≤4096,
comparisons≤32*4096 in insert/search, matches≤35/query. New addresses,
inline instances and memcpy bounds must be recovered after this build.

The full source route/loop arguments are in `entropy-source-analysis.md`.
For this public boundary its internal-body route applies after window
update, with frame0. No private-function capture adapter is used.
Constants: nbSeq≤1024, literals≤4096, LL/ML/OF alphabets36/53/32,
FSE table sizes≤512. Encoder main loop handles nbSeq−1≤1023 sequences;
nbSeq0 exits before encoder, nbSeq1 gives unsigned n=SIZE_MAX and skips.
HUF optimal-depth probes≤11 and final build/write adds1: at most12 of
each. FSE normalization/NCount writes≤18 (12 HUF +3 cost +3 final);
FSE table builds≤15 (12 HUF +3 final).

HUF sort buckets166..190 contain only histogram counts≥165. Their total
symbol count M≤floor4096/165=24. Each quicksort partition removes a new
pivot; recursive and iterative leftovers are disjoint. Across a bucket
of m symbols partitions≤m−1, total calls including root/empty/base≤m.
Hence HUF_simpleQuickSort total calls≤24/build, **≤288/task**. The smaller
side recurses:24→≤11→≤5, yielding **≤3 active frames**. This proves calls,
not only depth. Installed recurse semantics and its actual IPET rows still
need to be checked on this ELF. Partition/insertion comparisons≤276/build.

FSE step is odd modulo a power-of-two table (logs5..9), so spreading visits
every cell once; correct normalization Σabs(norm)=tableSize gives a
per-build sum of low-prob skip bodies≤tableSize. Round-robin normalizeM2
bound≤53*512=27136/invocation additionally needs the valid positive-norm
existence invariant. U64/U32 division in normalization can introduce real
libgcc helpers; their complete machine closure is required.

## Memory and arithmetic obligations before admission

No allocations occur in the native task for all24release+24ASan/UBSan
cases. All use unchanged pinned upstream library objects, exact direct
block bytes, exact independently generated frame payload, independent LZ
replay and upstream roundtrip. Result native-attempt05/review.json PASS.
Earlier controller failures and corrected precondition are preserved.

The prepared tables/workspace exist before task. Old ARM ABI measurement
from the same upstream source/release configuration: CCtx3800,
two CBlock4596 each, tmpWorkspace8920, DP/matches/frequencies149248,
hash/chain upper327680, fixed workspace overhead. Conservative prior
object estimate for N4096 (including input/output and64KiBstack)589208
bytes remains a plausible capacity bound; it is **not yet a whole-block
stack proof**. New ABI probe and actual recursive stack path are required.
Buffers are genuine upstream capacities, not hand-sized surrogate arrays.

HUF_setMaxHeight needs a canonical-tree/rankLast safety review. A greedy
Huffman path doubles weight at least every two ancestor edges; positive
integer weights sum≤4096, giving largestBits≤24. target≥floorlog2(card)+1
and card≤256 imply unscaled clipping cost<2^largestBits≤2^24, with safe
signed shifts. After normalization cost<card≤256, so positive correction
iterations≤255. Rank searches are bounded by HUF_TABLELOG_MAX12. The
overshoot loop increases cost by1, but its exact array/rankLast invariant
and sufficient rank0 symbols must be independently established; upstream's
comment has an unfinished justification here. Do not turn assertions into
path exclusions. Finish code-table indices, bitstream writes and compiler
runtime closure as part of actual admission. Native48PASS alone does not
discharge these universal obligations.

This package intentionally contains no generated FF, IPET or claimed
solver hardness. Status: NATIVE_VERIFIED_ARM_BUILD_READY_NOT_ADMITTED.
