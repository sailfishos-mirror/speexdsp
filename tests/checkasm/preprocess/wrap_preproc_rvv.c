/* RVV build of the preprocess.c per-bin kernels for checkasm: base-ISA C,
 * the V instructions live in preprocess_rvv_asm.S (linked alongside).
 * PREPROC_RVV_FORCE_ON pins the dispatch on so the asm is tested
 * deterministically, not per the build host's getauxval. */
#define CKA_PREFIX ckaprvv_
#include "wrap_preproc_rename.h"
#include "wrap.h"

#ifdef USE_RVV
#  define PREPROC_RVV_FORCE_ON
#endif

#include "wrap_preproc_impl.h"

#ifdef HAVE_RVV_PREPROC

void preproc_window_rvv(float *frame, const float *window, int len)
{
    preproc_window(frame, window, len);
}

void preproc_power_spectrum_rvv(const float *ft, float *ps, int N)
{
    preproc_power_spectrum(ft, ps, N);
}

void preproc_smooth_spectrum_rvv(float *S, const float *ps, int N)
{
    preproc_smooth_spectrum(S, ps, N);
}

void preproc_min_track_swap_rvv(float *Smin, float *Stmp, const float *S, int N)
{
    preproc_min_track_swap(Smin, Stmp, S, N);
}

void preproc_min_track_rvv(float *Smin, float *Stmp, const float *S, int N)
{
    preproc_min_track(Smin, Stmp, S, N);
}

void preproc_update_prob_rvv(const float *S, const float *Smin, int *update_prob, int N)
{
    preproc_update_prob(S, Smin, update_prob, N);
}

void preproc_noise_update_rvv(const int *update_prob, const float *ps, float *noise,
                              const float *beta, int N)
{
    preproc_noise_update(update_prob, ps, noise, beta[0], beta[1], N);
}

void preproc_snr_update_rvv(const float *ps, const float *noise, const float *echo_noise,
                            const float *reverb_estimate, const float *old_ps,
                            float *post, float *prior, int len)
{
    preproc_snr_update(ps, noise, echo_noise, reverb_estimate, old_ps, post, prior, len);
}

void preproc_zeta_smooth_rvv(float *zeta, const float *prior, int N, int M)
{
    preproc_zeta_smooth(zeta, prior, N, M);
}

void preproc_em_gain_rvv(const float *prior, const float *post, const float *ps,
                         const float *gain_floor, float *gain, float *gain2,
                         float *old_ps, int N)
{
    preproc_em_gain(prior, post, ps, gain_floor, gain, gain2, old_ps, N);
}

void preproc_apply_gain_rvv(const float *gain2, float *ft, int N)
{
    preproc_apply_gain(gain2, ft, N);
}

#endif /* HAVE_RVV_PREPROC */
