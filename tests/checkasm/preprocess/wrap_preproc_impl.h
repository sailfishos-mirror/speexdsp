/* #includes libspeexdsp/preprocess.c privately into a wrap_preproc_*.c
 * TU. Include AFTER wrap_preproc_rename.h + wrap.h and any per-variant
 * #undef/#define. #undef HAVE_CONFIG_H stops config.h from re-defining
 * the USE_* macros the caller just cleared. */

#undef HAVE_CONFIG_H

#if defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

#include "../../../libspeexdsp/preprocess.c"

#if defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif

/* The kernels under test never touch the FFT, the filterbank or the echo
 * canceller; these (renamed, per-TU) stubs only satisfy the link for
 * preprocess.c's unused public API. */
void *spx_fft_init(int size) { (void) size; return 0; }
void spx_fft_destroy(void *table) { (void) table; }
void spx_fft(void *table, spx_word16_t *in, spx_word16_t *out)
{ (void) table; (void) in; (void) out; }
void spx_ifft(void *table, spx_word16_t *in, spx_word16_t *out)
{ (void) table; (void) in; (void) out; }
FilterBank *filterbank_new(int banks, spx_word32_t sampling, int len, int type)
{ (void) banks; (void) sampling; (void) len; (void) type; return 0; }
void filterbank_destroy(FilterBank *bank) { (void) bank; }
void filterbank_compute_bank32(FilterBank *bank, spx_word32_t *ps, spx_word32_t *mel)
{ (void) bank; (void) ps; (void) mel; }
void filterbank_compute_psd16(FilterBank *bank, spx_word16_t *mel, spx_word16_t *psd)
{ (void) bank; (void) mel; (void) psd; }
void speex_echo_get_residual(SpeexEchoState *st, spx_word32_t *Yout, int len)
{ (void) st; (void) Yout; (void) len; }
