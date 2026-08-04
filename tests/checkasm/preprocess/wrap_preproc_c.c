/* Pure-C reference build of the preprocess.c per-bin kernels. #undef
 * USE_RVV keeps the loops scalar; this TU is the benchmark baseline, so
 * it is built with the no-autovec flags (checkasm_c_ref_args in
 * tests/meson.build). */
#define CKA_PREFIX ckapc_
#include "wrap_preproc_rename.h"
#include "wrap.h"

#undef USE_RVV

#include "wrap_preproc_impl.h"

#ifndef FIXED_POINT

void preproc_window_c(float *frame, const float *window, int len)
{
    preproc_window(frame, window, len);
}

void preproc_power_spectrum_c(const float *ft, float *ps, int N)
{
    preproc_power_spectrum(ft, ps, N);
}

void preproc_smooth_spectrum_c(float *S, const float *ps, int N)
{
    preproc_smooth_spectrum(S, ps, N);
}

void preproc_min_track_swap_c(float *Smin, float *Stmp, const float *S, int N)
{
    preproc_min_track_swap(Smin, Stmp, S, N);
}

void preproc_min_track_c(float *Smin, float *Stmp, const float *S, int N)
{
    preproc_min_track(Smin, Stmp, S, N);
}

void preproc_update_prob_c(const float *S, const float *Smin, int *update_prob, int N)
{
    preproc_update_prob(S, Smin, update_prob, N);
}

void preproc_noise_update_c(const int *update_prob, const float *ps, float *noise,
                            const float *beta, int N)
{
    preproc_noise_update(update_prob, ps, noise, beta[0], beta[1], N);
}

void preproc_snr_update_c(const float *ps, const float *noise, const float *echo_noise,
                          const float *reverb_estimate, const float *old_ps,
                          float *post, float *prior, int len)
{
    preproc_snr_update(ps, noise, echo_noise, reverb_estimate, old_ps, post, prior, len);
}

void preproc_zeta_smooth_c(float *zeta, const float *prior, int N, int M)
{
    preproc_zeta_smooth(zeta, prior, N, M);
}

void preproc_em_gain_c(const float *prior, const float *post, const float *ps,
                       const float *gain_floor, float *gain, float *gain2,
                       float *old_ps, int N)
{
    preproc_em_gain(prior, post, ps, gain_floor, gain, gain2, old_ps, N);
}

void preproc_apply_gain_c(const float *gain2, float *ft, int N)
{
    preproc_apply_gain(gain2, ft, N);
}

void preproc_overlap_output_c(spx_int16_t *x, const float *outbuf,
                              const float *frame, int len)
{
    preproc_overlap_output(x, outbuf, frame, len);
}

#endif /* !FIXED_POINT */
