/* Pure-C reference build of the mdf.c spectral kernels. #undef USE_RVV
 * keeps the loops scalar; this TU is the benchmark baseline, so it is
 * built with the no-autovec flags (checkasm_c_ref_args in
 * tests/meson.build). */
#define CKA_PREFIX ckamc_
#include "wrap_mdf_rename.h"
#include "wrap.h"

#undef USE_RVV

#include "wrap_mdf_impl.h"

void mdf_smul_accum_c(const spx_word16_t *X, const spx_word32_t *Y,
                      spx_word16_t *acc, int N, int M)
{
    spectral_mul_accum(X, Y, acc, N, M);
}

void mdf_smul_accum16_c(const spx_word16_t *X, const spx_word16_t *Y,
                        spx_word16_t *acc, int N, int M)
{
    spectral_mul_accum16(X, Y, acc, N, M);
}

void mdf_wsmul_conj_c(const spx_float_t *w, const spx_float_t *p,
                      const spx_word16_t *X, const spx_word16_t *Y,
                      spx_word32_t *prod, int N)
{
    weighted_spectral_mul_conj(w, *p, X, Y, prod, N);
}

void mdf_power_spectrum_c(const spx_word16_t *X, spx_word32_t *ps, int N)
{
    power_spectrum(X, ps, N);
}

void mdf_power_spectrum_accum_c(const spx_word16_t *X, spx_word32_t *ps, int N)
{
    power_spectrum_accum(X, ps, N);
}

spx_word32_t mdf_inner_prod_c(const spx_word16_t *x, const spx_word16_t *y, int len)
{
    return mdf_inner_prod(x, y, len);
}

void mdf_adjust_prop_c(const spx_word32_t *W, int N, int M, int P,
                       spx_word16_t *prop)
{
    mdf_adjust_prop(W, N, M, P, prop);
}

void mdf_res_window_c(spx_word16_t *y, const spx_word16_t *window,
                      const spx_word16_t *last_y, int N)
{
    mdf_residual_window(y, window, last_y, N);
}

void mdf_res_scale_c(spx_word32_t *residual_echo, const spx_word16_t *leak2, int len)
{
    mdf_residual_scale(residual_echo, *leak2, len);
}

void mdf_weight_update_c(spx_word32_t *w, const spx_word32_t *phi, int N)
{
    mdf_weight_update(w, phi, N);
}

spx_word16_t mdf_deemph_output_c(spx_int16_t *out, const spx_word16_t *input,
                                 const spx_word16_t *e, const spx_word16_t *preemph,
                                 const spx_word16_t *mem, int len, int stride)
{
    return mdf_deemph_output(out, input, e, *preemph, *mem, len, stride);
}
