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

#include "config/reader/test.h"

/*
 * O.K.
 */
Test(config_reader, test_parse_subsystems0, .init=test_init_with_json_subsystems, .fini=test_yall_close)
{
	/* Root subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "root"));
	struct yall_subsystem *root = subsystems;

	cr_assert_eq(root->parent, NULL);
	cr_assert_eq(root->log_level, yall_debug);
	cr_assert_eq(root->output_type, yall_console_output);
	cr_assert_eq(root->file.filename, NULL);
	cr_assert_str_eq(root->name, "root");

	/* Root's first child subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "first_child"));
	struct yall_subsystem *first_child = root->childs;

	cr_assert_eq(first_child->parent, root);;
	cr_assert_eq(first_child->log_level, yall_inherited_level);
	cr_assert_eq(first_child->output_type, yall_console_output);
	cr_assert_eq(first_child->file.filename, NULL);
	cr_assert_str_eq(first_child->name, "first_child");

	/* Root's second child subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "second_child"));
	struct yall_subsystem *second_child = first_child->next;

	cr_assert_eq(second_child->parent, root);
	cr_assert_eq(second_child->log_level, yall_info);
	cr_assert_eq(second_child->output_type, yall_inherited_output);
	cr_assert_eq(second_child->file.filename, NULL);
	cr_assert_str_eq(second_child->name, "second_child");

	/* Second root subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "second_root"));
	struct yall_subsystem *second_root = subsystems->next;

	cr_assert_eq(second_root->parent, NULL);
	cr_assert_eq(second_root->log_level, yall_info);
	cr_assert_eq(second_root->output_type, yall_inherited_output);
	cr_assert_eq(second_root->file.filename, NULL);
	cr_assert_str_eq(second_root->name, "second_root");

	/* Second root's first child subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "third_child"));
	struct yall_subsystem *third_child = second_root->childs;

	cr_assert_eq(third_child->parent, second_root);
	cr_assert_eq(third_child->log_level, yall_inherited_level);
	cr_assert_eq(third_child->output_type, yall_inherited_output);
	cr_assert_eq(third_child->file.filename, NULL);
	cr_assert_str_eq(third_child->name, "third_child");

	/* Second root's second child subsystem */
	cr_assert_eq(YALL_SUCCESS, parse_subsystems(json_subsys_root, "fourth_child"));
	struct yall_subsystem *fourth_child = third_child->next;

	cr_assert_eq(fourth_child->parent, second_root);
	cr_assert_eq(fourth_child->log_level, yall_debug);
	cr_assert_eq(fourth_child->output_type, yall_console_output);
	cr_assert_eq(fourth_child->file.filename, NULL);
	cr_assert_str_eq(fourth_child->name, "fourth_child");
}

/*
 * Calling with undeclared subsystem
 */
Test(config_reader, test_parse_subsystems1, .init=test_yall_init, .fini=test_yall_close)
{
	cr_assert_eq(YALL_JSON_UNDECLARED_SUBSYS, parse_subsystems(json_subsys_root, "invalid"));
}
/*
 * Calling with NULL JSON object
 */
Test(config_reader, test_parse_subsystems2)
{
	cr_assert_eq(YALL_JSON_UNDECLARED_SUBSYS, parse_subsystems(NULL, "invalid"));
}

/*
 * Circle dependencies between subsystems :
 *	"a" : { "parent" : "b" },
 *	"b" : { "parent" : "a" }
 * yall have to be initialized as parse_subsystem() call yall_set_subsystem()
 */
Test(config_reader, test_parse_subsystems3, .init=test_yall_init, .fini=test_yall_close)
{
	json_t *r = json_object();
	json_t *a = json_object();
	json_t *b = json_object();
	json_object_set(a, "parent", json_string("b"));
	json_object_set(b, "parent", json_string("a"));
	json_object_set(r, "a", a);
	json_object_set(r, "b", b);

	cr_assert_eq(YALL_SUCCESS, parse_subsystems(r, "a"));
}
