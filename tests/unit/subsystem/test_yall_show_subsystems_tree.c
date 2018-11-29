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

#include "subsystem/test.h"

/*
 * O.K.
 * No debug mode
 */
Test(subsystem, test_show_subsystems_tree0, .init=test_init_yall, .fini=test_close_yall)
{
	yall_disable_debug();

	yall_show_subsystems_tree();
	cr_assert(1);

	cr_assert_stderr_eq_str("");
}

/*
 * Debug mode
 */
Test(subsystem, test_show_subsystems_tree1, .init=test_init_yall, .fini=test_close_yall)
{
	yall_set_subsystem("test", NULL, yall_debug, yall_console_output, NULL);
	yall_enable_debug("test");

	yall_show_subsystems_tree();
	cr_assert(1);

	yall_disable_debug();

	cr_assert_stderr_neq_str("");
}
