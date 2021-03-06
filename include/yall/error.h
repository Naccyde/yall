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

#ifndef _YALL_ERROR_H
#define _YALL_ERROR_H

#include "yall/utils.h"

typedef enum {
	/* Generic messages */
	YALL_SUCCESS			= 0x00,
	YALL_UNKNOW_ERROR		= 0x01,

	/* Library setup */
	YALL_ALREADY_INIT		= 0x02,
	YALL_NOT_INIT			= 0x03,
	YALL_SEM_INIT_ERR		= 0x04,
	YALL_NO_MEM			= 0x05,
	YALL_LOG_LEVEL_TOO_LOW		= 0x06,

	/* Subsystem errors */
	YALL_SUBSYS_NO_NAME		= 0x07,
	YALL_SUBSYS_NOT_EXISTS		= 0x08,
	YALL_SUBSYS_DISABLED		= 0x09,
	YALL_CANT_CREATE_SUBSYS		= 0x0A,

	/* File output errors */
	YALL_FILE_LOCK_ERR		= 0x0B,
	YALL_FILE_OPEN_ERR		= 0x0C,

	/* Console output errors */
	YALL_CONSOLE_LOCK_ERR		= 0x0D,
	YALL_CONSOLE_WRITE_ERR		= 0x0E,

	/* Threading system */
	YALL_CANT_CREATE_THREAD		= 0x0F,

	/* JSON configuration */
	YALL_JSON_CANT_READ_CONFIG	= 0x10,
	YALL_JSON_UNDECLARED_SUBSYS	= 0x11,
	YALL_JSON_CIRCLE_DEPENDENCY	= 0x12,

	/*
	 * This is used to check if the given code is defined. It is ugly, but
	 * it's the best I can currently find.
	 */
	yall_err_end			= 0x13
} yall_error;

/**
 * \brief Returns a nul-terminated string of an explicit error message about
 *	the given yall_error variable.
 * \param err yall_error we want to get the description string.
 * \return Error message corresponding to the error given. If there is not such
 *	error, returns a default error message.
 */
_YALL_PUBLIC const char *yall_strerror(yall_error err);

#endif
