> Historical source-only internal-function boundary exploration. The selected public API boundary, tested native and built by this package, is defined in source-contract.md. No private capture adapter is used.

# Следующее расширение: настоящий первый ZSTD_compressBlock_internal

Статус: **SOURCE_ONLY_NOT_ADMITTED**. Это разбор pinned zstd v1.5.7
`f8745da6ff1ad1e7bab384bd1f9d742439278e99`; новый ELF и IPET не строились,
тяжесть не измерялась. Результаты btultra/export02 остаются отдельным лёгким
примером. Ни одно ограничение из этого документа пока не является `.ff`.

## Граница, сохраняющая настоящую задачу

Оставить прежний upstream ZSTD_compress2 setup и его параметры: один блок
4096 bytes, noDict, btultra, minMatch4, searchLog5, targetLength64,
window/hash/chain≤16/14/16, workers0, LDM/row matchfinder/sequence splitter
off. Начальный вход — произвольные неизменяемые bytes и прежние 64 bytes
padding. SplitterLevel1 и splitAfterSequences disabled уже использовались
в проверенном main; они ведут к обычной ветке frameChunk.

Перенести границу с вызова parser на единственный вызов
`ZSTD_compressBlock_internal` из `ZSTD_compress_frameChunk` (zstd_compress.c
4383–4448, call4646). Внешний caller уже подготовил window и буферы.
Анализируемый task должен выполнить неизменённое тело internal, включая
buildSeqStore, parser, сохранение последних literals, HUF/FSE, проверку
compressibility, подтверждение repcodes/entropy tables. Возвраты0/error
сохраняются. Запись frame header/checksum/сырого fallback остаётся в caller
за выбранной границей; это явно исключённое окружение.

Технически static original можно сохранить в derived zstd_compress.c под
отдельным именем и добавить в том же TU тонкий exported wrapper. Только
его два исходных callers перенаправляются в bridge, сохраняющий аргументы
для task. Содержимое original function не заменять и не переносить в
ручную реализацию. Старую rename/parser adapter нужно выключить, иначе
вложенный parser стал бы отдельной исследовательской границей.
Новый adapter требует собственного stock/release/sanitizer сравнения.

Перед task bridge обязан проверить не только прежний MatchState contract,
но и `isFirstBlock=1`, `frame=1`, seqCollector disabled, extSeqStore empty,
extSeqProdFunc NULL, prevHUF/FSE repeat modes none, реальные next/prev
CBlock и tmpWorkspace/capacities. Старые parser checks становятся
инвариантом после настоящего buildSeqStore внутри task. Не переносить их
как начальное состояние напрямую: opt.symbolCosts устанавливается именно
buildSeqStore, а nextCBlock->rep копируется там.

## Достижимые ветки и функции

Основная цепочка:

```
ZSTD_compressBlock_internal
  ZSTD_buildSeqStore
    ZSTD_resetSeqStore / copy 3 repcodes
    ZSTD_selectBlockCompressor -> ZSTD_compressBlock_btultra
    ZSTD_storeLastLiterals
  ZSTD_entropyCompressSeqStore[_wExtLitBuffer/_internal]
    ZSTD_compressLiterals
      HUF_compress1X_repeat OR HUF_compress4X_repeat
        HUF_compress_internal
          HIST_count_wksp
          HUF_optimalTableLog
            HUF_buildCTable_wksp
              HUF_sort -> HUF_simpleQuickSort (real recursion)
              HUF_buildTree / HUF_setMaxHeight
              HUF_buildCTableFromTree
            HUF_writeCTable_wksp -> HUF_compressWeights
              FSE_normalizeCount / FSE_writeNCount / FSE_buildCTable_wksp
              FSE_compress_usingCTable
          final HUF_buildCTable_wksp / HUF_writeCTable_wksp
          HUF_compress1X_usingCTable OR HUF_compress4X_usingCTable
      raw/RLE literals fallback
    ZSTD_buildSequencesStatistics
      ZSTD_seqToCodes / HIST_countFast_wksp
      ZSTD_selectEncodingType (LL,OF,ML)
        ZSTD_crossEntropyCost / ZSTD_NCountCost / ZSTD_entropyCost
      ZSTD_buildCTable (LL,OF,ML)
        FSE_normalizeCount / FSE_writeNCount / FSE_buildCTable_wksp
    ZSTD_encodeSequences -> default ARM32 encoder
  ZSTD_blockState_confirmRepcodesAndEntropyTables
```

Это source route, не утверждение о числе машинных functions после inlining.
HIST helpers, bitstream helpers, реальный memcpy/memset и compiler runtime
обязаны войти в последующий полный ARM callgraph. В частности, FSE
normalization делает U64/U32 division через ZSTD_div64; ARMv5TE может
потребовать `__aeabi_uldivmod` и связанные libgcc functions. Их нельзя
исключить `nocall`.

Косвенные вызовы имеют конечные точные наборы:

| Site | Возможные targets | Основание |
|---|---|---|
| buildSeqStore blockCompressor | btultra | noDict, strategy8, row disabled; selector table [dictMode0][strategy8] |
| Два parser getAllMatches | noDict4 | прежний MatchState minMatch4/noDict; доказательство source сохраняется, ARM offsets перепривязать |
| compressLiterals huf_compress | HUF_compress1X_repeat / HUF_compress4X_repeat | `singleStream = litSize<256`; ни один target нельзя удалить для всех входов |

External sequence producer исключён свойством подготовленного context,
LDM/raw external store пусты. На ARM BMI2 отсутствует; default encoding
остаётся настоящим C. `isFirstBlock=1` делает финальный RLE test первого
frame block недостижимым, но raw/RLE literals внутри HUF сохраняются.
Previous FSE repeat none исключает использование старых CTable как repeat;
не нужно вырезать обычные basic/rle/compressed варианты.

## Полезные source bounds для N=4096

Все числа ниже — source body/call bounds. Binary backedges и contexts ещё
проверить; старые absolute addresses и checksum не переносить.

| Область | Безопасный предел | Причина |
|---|---:|---|
| btultra | прежние source obligations | один parser call, тот же домен; не подменять ΣDP на N |
| repcode initialization | 3 | ZSTD_REP_NUM |
| Последние literals | ≤4096 bytes | parser вернул suffix≤N; memcpy MAX144 из старого kernel более неприменим |
| sequences | ≤1024 | каждый настоящий match потребляет минимум4 input bytes |
| LL/ML/OF symbol scans | 36/53/32 | MaxLL35,MaxML52,MaxOff31 |
| ZSTD_seqToCodes | ≤1024 | один проход по настоящему SeqStore |
| ZSTD_encodeSequences reverse body | ≤1023 | последний sequence кодируется до цикла; unsigned n=nbSeq−2 затем decrement и guard n<nbSeq корректно завершает также nbSeq1 |
| HUF оптимальный depth probe | ≤11 | optLogGuess монотонно увеличивается от ≥1 до LitHufLog11 |
| HUF table builds / writes | ≤12 каждого | ≤11 probes + один final build/write, без рекурсии между probes |
| HUF symbol scans | ≤256/build | BYTE alphabet |
| HUF sort rank pass | 191/build | rankPosition192, n191..1 |
| HUF sorted-bucket pass | 25/build | n166..190 |
| FSE normalization / NCount write | ≤18 каждого/task | ≤12 HUF weight tables +3 encoding-cost probes +3 actual sequence tables |
| FSE table build | ≤15/task | ≤12 HUF weight tables +3 actual sequence tables |
| FSE tableSize | ≤512 | LL/ML tableLog≤9,OF≤8,HUF weight tableLog≤6 |
| FSE symbol-domain scan | ≤53/invocation | sequence alphabet dominates HUF weights alphabet13 |
| FSE normalizeM2 total0 round robin | ≤27136/invocation | ≤512 remaining units, ≤53 positions до каждой положительной norm; инвариант existence ещё оформить независимо |

FSE distribution step `(T>>1)+(T>>3)+3` нечётен при T=2^log,
log5..9. Поэтому перемещение moduloT — перестановка всего table. Для
корректно нормализованных counts с хотя бы одной positive frequency
low-prob skip loop встречает разрешённую ячейку менее чем за T шагов.
Суммарно все allocations и skips обходят эту перестановку один раз:
число skip bodies≤T/build. Это требует сохранить и проверить invariant
`Σabs(norm)=T`; одной границы «depth9» недостаточно.

## Рекурсия HUF: граница числа вызовов, не только глубины

HUF_sort запускает quicksort только для buckets166..190. Вставка элемента
идёт в bucket `HUF_getIndex(count)+1`; для этих buckets count≥165. Сумма
counts равна litSize≤4096. Значит во всех сортируемых buckets вместе
не более `floor(4096/165)=24` symbols, хотя весь alphabet имеет256 cells.

Для bucket длины m>1 partition возвращает idx∈[low,high], удаляет pivot,
а recursive и iterative остатки — непересекающиеся части остальных m−1
элементов. Каждый partition удаляет новый pivot. Поэтому partitions≤m−1;
каждый partition вызывает ровно один recursive call, включая empty calls;
с учётом root всего calls≤m. Складывая по buckets: **≤24 всех вызовов
HUF_simpleQuickSort на один HUF_sort**, включая roots и base/empty calls.
При ≤12 table builds получается **≤288 calls/task**. Условие base
`high-low<8` соответствует m≤8. Рекурсивно выбирается меньшая часть:
24→≤11→≤5, то есть **≤3 одновременно активных frames**. Более общий
alphabet-only bound: ≤256 calls/build и ≤6 frames.

Quicksort partition scan≤23/body для исходного m≤24; суммарные сравнения
всех partitions≤24*23/2=276/build. Insertion-sort shift bodies имеют такую
же консервативную суммарную оценку для disjoint terminal pieces.
Эти аргументы дают конечное source execution, но **ещё не доказывают**, что
установленные OTAWA recurse facts корректно перенесут call budget в IPET.
Требуется проверить это на настоящем recursive CFG и actual matrix или
выполнить доказанное finite call-context unfolding без изменения ELF.

## Память, арифметика и оставшиеся условия допуска

Workspace для entropy уже выделен upstream setup: старый ARM ABI probe
даёт tmpWorkspace8920 bytes. HUF/FSE используют предоставленные scratch
arrays/CCtx tables и автоматические локальные объекты; перечисленные
source routes не вызывают allocator или I/O. Двух прежних CBlock4596,
SeqStore capacities и output capacity из main достаточно как исходных
объектов, но потребности нового task stack нужно пересчитать по его
реальному callgraph с учётом трёх recursive HUF frames. Старые608 bytes
нельзя объявлять оценкой whole-block stack.

HUF_setMaxHeight требует отдельной проверки арифметики и canonical-tree
инвариантов. После clipping нормализованный totalCost<256; positive loop
уменьшает его минимум на1. Rank searches ограничены HUF_TABLELOG_MAX12.
Overshoot исправляется единичными increments. До применения этих bounds
надо независимо обосновать исходную Huffman tree height, signed shift
`1 << (largestBits-targetNbBits)`, unscaled signed totalCost и rankLast
index existence. Нельзя считать assertions доказательством отсутствия UB.
Таблицы LL_bits/ML_bits/CTable и bitstream stores также перепроверить на
реальных codes/нормализованных таблицах. Существующий DP-price certificate
покрывает parser, но не новую entropy арифметику.

Практический порядок продолжения: сначала проверить installed recursion
handling и семантику budget288; затем закончить независимые HUF/FSE
invariants и adapter/native boundary; после этого собирать ARM, полностью
замыкать runtime, заново связывать FF и сравнивать каждую строку IPET.
Без этих шагов расширение остаётся исследовательским кандидатом.
