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

#include "config/parameters/test.h"

/*
 * O.K.
 * Setter.
 */
Test(config_parameters, test_yall_config_set_syslog_facility0, .init=test_yall_init, .fini=test_yall_close)
{
	yall_config_set_syslog_facility(yall_fac_user);
	cr_assert_eq(current_config.syslog_facility, yall_fac_user);

	yall_config_set_syslog_facility(yall_fac_lpr);
	cr_assert_eq(current_config.syslog_facility, yall_fac_lpr);
}

/*
 * O.K.
 * Getter.
 */
Test(config_parameters, test_yall_config_get_syslog_facility0, .init=test_yall_init, .fini=test_yall_close)
{
	cr_assert_eq(yall_config_get_syslog_facility(), current_config.syslog_facility);
	cr_assert_eq(yall_config_get_syslog_facility(), default_config.syslog_facility);

	yall_config_set_syslog_facility(yall_fac_lpr);
	cr_assert_eq(yall_config_get_syslog_facility(), yall_fac_lpr);

	yall_config_set_syslog_facility(yall_fac_lpr);
	cr_assert_eq(yall_config_get_syslog_facility(), yall_fac_lpr);
}

/*
 * O.K.
 * Resetter.
 */
Test(config_parameters, test_yall_config_reset_syslog_facility0, .init=test_yall_init, .fini=test_yall_close)
{
	yall_config_set_syslog_facility(yall_fac_lpr);
	cr_assert_eq(yall_config_get_syslog_facility(), yall_fac_lpr);

	yall_config_reset_syslog_facility();
	cr_assert_eq(current_config.syslog_facility, default_config.syslog_facility);
}
