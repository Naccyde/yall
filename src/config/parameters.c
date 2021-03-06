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

#include "yall/config/parameters.h"

#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <syslog.h>
#endif

#include "yall/debug.h"
#include "yall/header.h"

/*
 * Default values
 */
static const struct yall_config default_config = {
	.std_header_template = "%-16.16s ::: %-9l :: %-17.17f :: %d : ",
	.call_header_template = "%-16.16s ::: %-9l :: %-17.17f :: %d : ",
	.tab_width = 4,
	.syslog_ident = "yall",
	.syslog_facility = yall_fac_user
};

/*
 * Current values
 */
static struct yall_config current_config = {
	.std_header_template = NULL,
	.call_header_template = NULL,
	.tab_width = 0,
	.syslog_ident = NULL,
	.syslog_facility = 0
};

/*
 * Setup
 */
void config_setup(void)
{
	yall_config_reset_std_header_template();
	yall_config_reset_call_header_template();
	yall_config_reset_tab_width();
	yall_config_reset_syslog_ident();
	yall_config_reset_syslog_facility();
}

void config_clean(void)
{
	free((void *)current_config.std_header_template);
	current_config.std_header_template = NULL;

	free((void *)current_config.call_header_template);
	current_config.call_header_template = NULL;

	current_config.tab_width = 0;

	free((void *)current_config.syslog_ident);
	current_config.syslog_ident = NULL;

	current_config.syslog_facility = 0;
}

/*
 * Configuration parameters
 */
void yall_config_set_std_header_template(const char *std_header_template)
{
	free((void *)current_config.std_header_template);

	current_config.std_header_template = strdup(std_header_template);
	header_compile_format(std_header, current_config.std_header_template);
}

void yall_config_reset_std_header_template(void)
{
	yall_config_set_std_header_template(default_config.std_header_template);
}

const char *yall_config_get_std_header_template(void)
{
	return current_config.std_header_template;
}

void yall_config_set_call_header_template(const char *call_header_template)
{
	free((void *)current_config.call_header_template);

	current_config.call_header_template = strdup(call_header_template);
	header_compile_format(call_header, current_config.call_header_template);
}

void yall_config_reset_call_header_template(void)
{
	yall_config_set_call_header_template(
		default_config.call_header_template);
}

const char *yall_config_get_call_header_template(void)
{
	return current_config.call_header_template;
}

void yall_config_set_tab_width(uint8_t tab_width)
{
	current_config.tab_width = tab_width;
}

void yall_config_reset_tab_width(void)
{
	yall_config_set_tab_width(default_config.tab_width);
}

uint8_t yall_config_get_tab_width(void)
{
	return current_config.tab_width;
}

void yall_config_set_syslog_ident(const char *ident)
{
	if (! ident)
		return;

	free((void *)current_config.syslog_ident);
	current_config.syslog_ident = strdup(ident);

#ifdef __linux__
	closelog();
	openlog(current_config.syslog_ident, 0, current_config.syslog_facility);
#endif
}

void yall_config_reset_syslog_ident(void)
{
	yall_config_set_syslog_ident(default_config.syslog_ident);
}

const char *yall_config_get_syslog_ident(void)
{
	return current_config.syslog_ident;
}

void yall_config_set_syslog_facility(enum yall_syslog_facility f)
{
	current_config.syslog_facility = f;

#ifdef __linux__
	closelog();
	openlog(current_config.syslog_ident, 0, current_config.syslog_facility);
#endif
}

void yall_config_reset_syslog_facility(void)
{
	yall_config_set_syslog_facility(default_config.syslog_facility);
}

enum yall_syslog_facility yall_config_get_syslog_facility(void)
{
	return current_config.syslog_facility;
}
