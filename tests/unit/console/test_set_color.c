#include "test_console.h"

ParameterizedTestParameters(console, test_set_color0) {
    return cr_make_param_array(struct param_set_color, ll_and_colors, 8);
}

ParameterizedTest(struct param_set_color *p, console, test_set_color0)
{
    set_color(p->ll);
    fflush(stderr);

    char output[6] = { 0 };
    sprintf(output, "\033[%dm", p->code);
    cr_assert_stderr_eq_str(output);
}
