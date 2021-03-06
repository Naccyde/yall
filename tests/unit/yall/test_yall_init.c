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
 * O.K.
 */
Test(yall, test_yall_init0, .fini=test_close_yall)
{
	cr_assert_eq(yall_init(), YALL_SUCCESS);
	cr_assert_eq(initialized, 1);
}

/*
 * O.K.
 * Failed writer_init()
 */
Test(yall, test_yall_init1, .fini=test_close_yall)
{
	disable_pthread_create();

	cr_assert_eq(yall_init(), YALL_CANT_CREATE_THREAD);
	cr_assert_eq(initialized, 0);

	enable_pthread_create();
}

/*
 * O.K.
 * Already initialized
 */
Test(yall, test_yall_init2, .init=test_init_yall, .fini=test_close_yall)
{
	cr_assert_eq(yall_init(), YALL_ALREADY_INIT);
	cr_assert_eq(initialized, 2);
}
