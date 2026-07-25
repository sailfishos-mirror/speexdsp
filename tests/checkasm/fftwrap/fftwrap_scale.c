#include <stdio.h>
#include <string.h>
#include "../internal.h"
#include "../smallft/wrap.h"

#ifdef HAVE_RVV_SMALLFT
#include "fftwrap_rvv.h"
#endif

/* fftwrap.c's USE_SMALLFT spx_fft pre-scale (out[i] = scale*in[i]),
 * C vs RVV. Both do one multiply per element, so outputs are bit-exact
 * and compared with memcmp. The n set covers the AEC shapes (2*frame =
 * 256/512), power-of-two sweeps, ragged vsetvli tails, and sub-VLMAX
 * sizes; the in-place (out == in) call spx_fft warns about is checked
 * too. The C baseline lives in wrap_smallft_c.c (no-autovec TU), the
 * kernel in smallft_rvv_asm.S (linked via the smallft RVV wrap). */

enum { MAX_N = 2048 };

static const int configs[] = { 8, 33, 64, 128, 256, 480, 512, 1024, 2048 };

void checkasm_check_fftwrap_scale(void)
{
#ifdef HAVE_RVV_SMALLFT
    checkasm_declare(void, float *, const float *, const float *, int);

    CHECKASM_ALIGN(float in[MAX_N]);
    CHECKASM_ALIGN(float out_ref[MAX_N]);
    CHECKASM_ALIGN(float out_new[MAX_N]);

    for (size_t c = 0; c < sizeof(configs) / sizeof(configs[0]); c++) {
        const int n = configs[c];
        const float scale = 1. / n;   /* as spx_fft computes it */

        smallft_fill_input(in, n);

        if (checkasm_check_func(fftwrap_scale_c, "fft_scale_n%d", n))
            checkasm_bench_new(out_new, in, &scale, n);

        if (active_flags & SPEEXDSP_CPU_FLAG_RVV) {
            if (checkasm_check_func(spx_drft_rvv_scale_f32, "fft_scale_n%d", n)) {
                checkasm_call_ref(out_ref, in, &scale, n);
                checkasm_call_new(out_new, in, &scale, n);
                if (memcmp(out_ref, out_new, n * sizeof *out_ref))
                    checkasm_fail();

                memcpy(out_ref, in, n * sizeof *out_ref);
                memcpy(out_new, in, n * sizeof *out_new);
                checkasm_call_ref(out_ref, out_ref, &scale, n);
                checkasm_call_new(out_new, out_new, &scale, n);
                if (memcmp(out_ref, out_new, n * sizeof *out_ref))
                    checkasm_fail();

                checkasm_bench_new(out_new, in, &scale, n);
            }
        }
    }

    checkasm_report("fftwrap_scale");
#endif /* HAVE_RVV_SMALLFT */
}
