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

#include "yall/test.h"

/*
 * Library not initialized
 */
Test(yall, test_yall_set_subsystem0)
{
	cr_assert_eq(yall_set_subsystem(NULL, NULL, yall_debug, yall_console_output, NULL), YALL_NOT_INIT);
}

/*
 * Bad name
 */
Test(yall, test_yall_set_subsystem1, .init=test_init_yall, .fini=test_close_yall)
{
	cr_assert_eq(yall_set_subsystem(NULL, NULL, yall_debug, yall_console_output, NULL), YALL_SUBSYS_NO_NAME);
}

/*
 * O.K.
 * Need to update an existing subsystem
 */
Test(yall, test_yall_set_subsystem2, .init=test_init_yall, .fini=test_close_yall)
{
	yall_set_subsystem("0", NULL, yall_emerg, yall_file_output, "HEHEH");
	cr_assert_eq(yall_set_subsystem("0", NULL, yall_debug, yall_console_output, NULL), YALL_SUCCESS);
}

/*
 * O.K.
 * Need to create a subsystem
 */
Test(yall, test_yall_set_subsystem3, .init=test_init_yall, .fini=test_close_yall)
{
	cr_assert_eq(yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL), YALL_SUCCESS);
}
