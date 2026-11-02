extern volatile unsigned sink;
void light(void) {
sink = sink + 1u;
}
void medium(void) {
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
}
void heavy(void) {
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
sink = sink + 3u;
sink = sink + 4u;
sink = sink + 5u;
sink = sink + 1u;
sink = sink + 2u;
}
