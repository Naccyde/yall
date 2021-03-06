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

#ifndef _YALL_OUTPUT_TYPES_H
#define _YALL_OUTPUT_TYPES_H

#include "yall/output/console.h"
#include "yall/output/file.h"

/**
 * \enum yall_output_type
 * \brief This enum stores all the different output types for the subsystems.
 *	These values has to be power of 2, as they can be combined to write on
 *	multiple outputs.
 * \var yall_output_type::yall_inherited_output
 *	\brief Subsystem inherit its output type from its parent.
 * \var yall_output_type::yall_console_output
 *	\brief Subsystem log message will be wrote on console.
 * \var yall_output_type::yall_file_output
 *	\brief Subsystem log message will be wrote in file.
 * \var yall_output_type::yall_syslog_output
 *	\brief Subsystem log message will be redirected to syslog.
 */
enum yall_output_type {
	yall_inherited_output	= 0,
	yall_console_output	= 1 << 0,
	yall_file_output	= 1 << 1,
	yall_syslog_output	= 1 << 2
};

/**
 * \brief Returns the output type corresponding to the given output type string.
 * \param str Output type as a string.
 * \retun Output type as a yall_output_type.
 */
enum yall_output_type str_to_output_type(const char *str);

#endif
