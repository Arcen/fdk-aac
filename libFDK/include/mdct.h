/***************************  Fraunhofer IIS FDK Tools  **********************

                        (C) Copyright Fraunhofer IIS (2011)
                               All Rights Reserved

    Please be advised that this software and/or program delivery is
    Confidential Information of Fraunhofer and subject to and covered by the

    Fraunhofer IIS Software Evaluation Agreement
    between Google Inc. and  Fraunhofer
    effective and in full force since March 1, 2012.

    You may use this software and/or program only under the terms and
    conditions described in the above mentioned Fraunhofer IIS Software
    Evaluation Agreement. Any other and/or further use requires a separate agreement.


   $Id$
   Author(s):   Manuel Jander, Josef Hoepfl
   Description: MDCT routines

   This software and/or program is protected by copyright law and international
   treaties. Any reproduction or distribution of this software and/or program,
   or any portion of it, may result in severe civil and criminal penalties, and
   will be prosecuted to the maximum extent possible under law.

******************************************************************************/

#ifndef __MDCT_H__
#define __MDCT_H__



#include "common_fix.h"

#define MDCT_OUT_HEADROOM     2 /* Output additional headroom */
#define MDCT_OUTPUT_SCALE    (DFRACT_BITS-SAMPLE_BITS-MDCT_OUT_HEADROOM)
/* Refer to "Output word length" in ISO/IEC 14496-3:2008(E) 23.2.3.6 */
#define MDCT_OUTPUT_GAIN      16

#if (SAMPLE_BITS == DFRACT_BITS)
#define IMDCT_SCALE(x) (INT_PCM)SATURATE_LEFT_SHIFT(x, -MDCT_OUTPUT_SCALE, SAMPLE_BITS)
#else
#define IMDCT_SCALE(x) (INT_PCM)SATURATE_RIGHT_SHIFT(x, MDCT_OUTPUT_SCALE, SAMPLE_BITS)
#endif
#define IMDCT_SCALE_DBL(x) (FIXP_DBL)(x)

/**
 * \brief MDCT persistent data
 */
typedef struct {
  union {
    FIXP_DBL *freq;
    FIXP_DBL *time;
  } overlap;                       /**< Pointer to overlap memory */

  const FIXP_WTP *prev_wrs;        /**< pointer to previous right window slope  */
  int prev_tl;                     /**< previous tranform length */
  int prev_nr;                     /**< previous right window offset */
  int prev_fr;                     /**< previous right window slope length */
  int ov_offset;                   /**< overlap time data fill level */
  int ov_size;                     /**< Overlap buffer size in words */

} mdct_t;

typedef mdct_t* H_MDCT;

/**
 * \brief Initialize as valid MDCT handle
 *
 * \param hMdct handle of an allocated MDCT handle.
 * \param overlap pointer to FIXP_DBL overlap buffer.
 * \param overlapBufferSize size in FIXP_DBLs of the given overlap buffer.
 * \return void
 */
void mdct_init( H_MDCT hMdct,
                FIXP_DBL *overlap,
                INT overlapBufferSize );

/**
 * \brief perform MDCT transform (time domain to frequency domain) with given parameters.
 *
 * \param hMdct handle of an allocated MDCT handle.
 * \param spectrum pointer to where the resulting MDCT spectrum will be stored into.
 * \param scalefactor pointer to the input scale shift value. Updated accordingly on return.
 * \param input pointer to input time domain signal
 * \param tl transformation length.
 * \param nr right window slope offset (amount of window coefficients assumed to be 1.0)
 * \param fr right overlap window slope length
 * \param wrs pointer to the right side overlap window coefficients.
 * \return number of input samples processed.
 */
INT  mdct_block(
        H_MDCT hMdct,
        FIXP_DBL *spectrum,
        INT *scalefactor,
        INT_PCM *input,
        INT tl,
        INT nr,
        INT fr,
        const FIXP_WTB *wrs );


/**
 * \brief add/multiply 2/N transform gain and MPEG4 part 3 defined output gain (see definition
 *        of MDCT_OUTPUT_GAIN) to given mantissa factor and exponent.
 * \param pGain pointer to the mantissa of a gain factor to be applied to IMDCT data.
 * \param pExponent pointer to the exponent of a gain factor to be applied to IMDCT data.
 * \param tl length of the IMDCT where the gain *pGain * (2 ^ *pExponent) will be applied to.
 */
void imdct_gain(
        FIXP_DBL *pGain,
        int *pExponent,
        int tl
        );

/**
 * \brief drain buffered output samples into given buffer. Changes the MDCT state.
 */
INT imdct_drain(
        H_MDCT hMdct,
        FIXP_DBL * pTimeData,
        INT nrSamplesRoom
        );


/**
 * \brief Copy overlap time domain data to given buffer. Does not change the MDCT state.
 * \return number of actually copied samples (ov + nr).
 */
INT imdct_copy_ov_and_nr(
        H_MDCT hMdct,
        FIXP_DBL * pTimeData,
        INT nrSamples
        );

/**
 * \brief Adapt MDCT parameters for non-matching window slopes.
 * \param hMdct handle of an allocated MDCT handle.
 * \param pfl pointer to left overlap window side length.
 * \param pnl pointer to length of the left n part of the window.
 * \param tl transform length.
 * \param wls pointer to the left side overlap window coefficients.
 * \param noOutSamples desired number of output samples.
 */
void imdct_adapt_parameters(H_MDCT hMdct, int *pfl, int *pnl, int tl, const FIXP_WTP *wls, int noOutSamples);

/**
 * \brief perform several inverse MDCT transforms (frequency domain to time domain) with given parameters.
 *
 * \param hMdct handle of an allocated MDCT handle.
 * \param output pointer to where the output time domain signal will be stored into.
 * \param stride the stride factor for accessing time domain samples in output.
 * \param spectrum pointer to the input MDCT spectra.
 * \param scalefactors scale shift values of the input spectrum.
 * \param nSpec number of MDCT spectrums.
 * \param noOutSamples desired number of output samples.
 * \param tl transform length.
 * \param wls pointer to the left side overlap window coefficients.
 * \param fl left overlap window side length.
 * \param wrs pointer to the right side overlap window coefficients of all individual IMDCTs.
 * \param fr right overlap window side length of all individual IMDCTs.
 * \param gain factor to apply to output samples (if != 0).
 * \return number of output samples returned.
 */
INT  imdct_block(
        H_MDCT hMdct,
        FIXP_DBL *output,
        FIXP_DBL *spectrum,
        const SHORT scalefactor[],
        const INT nSpec,
        const INT noOutSamples,
        const INT tl,
        const FIXP_WTP *wls,
        INT fl,
        const FIXP_WTP *wrs,
        const INT fr,
        FIXP_DBL gain );


#endif /* __MDCT_H__ */