#define MAX_INPUT_SIZE (16*1024*1024) /* 16MB */

static bool do_uncompress(tvbuff_t *tvb, int offset, int in_size,
			      wmem_array_t *obuf)
{
	unsigned buf_flags = 0, buf_flag_count = 0;
	int in_off = 0;
	int last_length_half_byte = 0;
	unsigned match_bytes, match_len, match_off;
	unsigned i;

	if (!tvb)
		return false;

	if (!in_size || in_size > MAX_INPUT_SIZE)
		return false;

	while (1) {
		if (buf_flag_count == 0) {
			buf_flags = tvb_get_letohl(tvb, offset+in_off);
			in_off += 4;
			buf_flag_count = 32;
		}
		buf_flag_count--;
		if ((buf_flags & (1u << buf_flag_count)) == 0) {
			uint8_t v = tvb_get_uint8(tvb, offset+in_off);
			wmem_array_append_one(obuf, v);
			in_off++;
		} else {
			if (in_off == in_size)
				return true;
			match_bytes = tvb_get_letohs(tvb, offset+in_off);
			in_off += 2;
			match_len = match_bytes % 8;
			match_off = (match_bytes/8) + 1;
			if (match_len == 7) {
				if (last_length_half_byte == 0) {
					match_len = tvb_get_uint8(tvb, offset+in_off);
					match_len = match_len % 16;
					last_length_half_byte = in_off;
					in_off++;
				} else {
					match_len = tvb_get_uint8(tvb, offset+last_length_half_byte);
					match_len = match_len / 16;
					last_length_half_byte = 0;
				}
				if (match_len == 15) {
					match_len = tvb_get_uint8(tvb, offset+in_off);
					in_off++;
					if (match_len == 255) {
						match_len = tvb_get_letohs(tvb, offset+in_off);
						in_off += 2;
						if (match_len == 0) {
							match_len = tvb_get_letohl(tvb, offset+in_off);
							in_off += 4;
						}
						if (match_len < 15+7)
							return false;
						match_len -= (15 + 7);
					}
					match_len += 15;
				}
				match_len += 7;
			}
                        if (match_len > MAX_INPUT_SIZE)
                            return false;
			match_len += 3;
			for (i = 0; i < match_len; i++) {
				uint8_t byte;
				if (match_off > wmem_array_get_count(obuf))
					return false;
				if (wmem_array_try_index(obuf, wmem_array_get_count(obuf)-match_off, &byte))
					return false;
				wmem_array_append_one(obuf, byte);
			}
		}
	}

	return true;
}
