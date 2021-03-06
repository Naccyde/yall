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

#include "container/queue/test.h"

struct test_queue_data *q_nodes[3] = { 0 };

static void tests_container_queue_setup(void)
{

}

static void tests_container_queue_clean(void)
{

}

TestSuite(container_queue, .init=tests_container_queue_setup, .fini=tests_container_queue_clean);

void test_queue_data_deleter(void *data)
{
	free(data);
}

queue_t *test_queue_empty_queue(void)
{
	return q_new();
}

queue_t *test_queue_queue(void)
{
	queue_t *q = q_new();

	CREATE_QUEUE_DATA(a, 0, 1, 2);
	CREATE_QUEUE_DATA(b, 3, 4, 5);
	CREATE_QUEUE_DATA(c, 6, 7, 8);

	q_nodes[0] = a;
	q_nodes[1] = b;
	q_nodes[2] = c;

	q_enqueue(q, a);
	q_enqueue(q, b);
	q_enqueue(q, c);

	return q;
}
