/*
 * MIT License
 *
 * Copyright (c) 2017 Quentin "Naccyde" Deslandes.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "yall/log_level.h"

#include <string.h>
#include <stdint.h>

static struct log_level_str_set {
	const char *log_level_name;
	const char *log_level_pretty_name;
} log_level_str[9] = {
	{ "yall_debug", "DEBUG" },
	{ "yall_info", "INFO" },
	{ "yall_notice", "NOTICE" },
	{ "yall_warning", "WARNING" },
	{ "yall_error", "ERROR" },
	{ "yall_crit", "CRITICAL" },
	{ "yall_alert", "ALERT" },
	{ "yall_emerg", "EMERGENCY" },
	{ "yall_inherited_level", "INHERIT" }
};

const char *log_level_to_pretty_str(enum yall_log_level log_level)
{
	return log_level_str[log_level].log_level_pretty_name;
}

enum yall_log_level str_to_log_level(const char *str)
{
	enum yall_log_level ll = yall_debug;

	if (! str)
		return ll;

	for (uint16_t i = 0; i < 9; ++i) {
		if (strcmp(log_level_str[i].log_level_name, str) == 0) {
			ll = i;
			break;
		}
	}

	return ll;
}
