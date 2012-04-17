/*************************  Fast MPEG AAC Audio Encoder  **********************

                     (C) Copyright Fraunhofer IIS (1999)
                               All Rights Reserved

    Please be advised that this software and/or program delivery is
    Confidential Information of Fraunhofer and subject to and covered by the

    Fraunhofer IIS Software Evaluation Agreement
    between Google Inc. and  Fraunhofer
    effective and in full force since March 1, 2012.

    You may use this software and/or program only under the terms and
    conditions described in the above mentioned Fraunhofer IIS Software
    Evaluation Agreement. Any other and/or further use requires a separate agreement.


   This software and/or program is protected by copyright law and international
   treaties. Any reproduction or distribution of this software and/or program,
   or any portion of it, may result in severe civil and criminal penalties, and
   will be prosecuted to the maximum extent possible under law.

   $Id$
   Initial author:       M. Schug / A. Groeschel
   contents/description: fast aac coder interface library functions

******************************************************************************/

#ifndef _aacenc_h_
#define _aacenc_h_

#include "common_fix.h"
#include "FDK_audio.h"

#include "tpenc_lib.h"

#include "sbr_encoder.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * AAC-LC error codes.
 */
typedef enum {
  AAC_ENC_OK       = 0x0000,                          /*!< All fine. */

  AAC_ENC_UNKNOWN  = 0x0002,                          /*!< Error condition is of unknown reason, or from another module.              */

  /* initialization errors */
  aac_enc_init_error_start      = 0x2000,
  AAC_ENC_INVALID_HANDLE        = 0x2020,             /*!< The handle passed to the function call was invalid (probably NULL).        */
  AAC_ENC_INVALID_FRAME_LENGTH  = 0x2080,             /*!< Invalid frame length (must be 1024 or 960).                                */
  AAC_ENC_INVALID_N_CHANNELS    = 0x20e0,             /*!< Invalid amount of audio input channels.                                    */
  AAC_ENC_INVALID_SFB_TABLE     = 0x2140,             /*!< Internal encoder error.                                                    */

  AAC_ENC_UNSUPPORTED_AOT            = 0x3000,        /*!< The Audio Object Type (AOT) is not supported.                              */
  AAC_ENC_UNSUPPORTED_BITRATE        = 0x3020,        /*!< The chosen bitrate is not supported.                                       */
  AAC_ENC_UNSUPPORTED_BITRATE_MODE   = 0x3028,        /*!< Unsupported bit rate mode (CBR or VBR).                                    */
  AAC_ENC_UNSUPPORTED_ANC_BITRATE    = 0x3040,        /*!< Unsupported ancillay bitrate.                                              */
  AAC_ENC_UNSUPPORTED_ANC_MODE       = 0x3060,
  AAC_ENC_UNSUPPORTED_TRANSPORT_TYPE = 0x3080,        /*!< The bitstream format is not supported.                                     */
  AAC_ENC_UNSUPPORTED_ER_FORMAT      = 0x30a0,        /*!< The error resilience tool format is not supported.                         */
  AAC_ENC_UNSUPPORTED_EPCONFIG       = 0x30c0,        /*!< The error protection format is not supported.                              */
  AAC_ENC_UNSUPPORTED_CHANNELCONFIG  = 0x30e0,        /*!< The channel configuration (either number or arrangement) is not supported. */
  AAC_ENC_UNSUPPORTED_SAMPLINGRATE   = 0x3100,        /*!< Sample rate of audio input is not supported.                               */
  AAC_ENC_NO_MEMORY                  = 0x3120,        /*!< Could not allocate memory. */
  AAC_ENC_PE_INIT_TABLE_NOT_FOUND    = 0x3140,        /*!< Internal encoder error.    */

  aac_enc_init_error_end,

  /* encode errors */
  aac_enc_error_start                       = 0x4000,
  AAC_ENC_QUANT_ERROR                       = 0x4020,       /*!< Too many bits used in quantization.             */
  AAC_ENC_WRITTEN_BITS_ERROR                = 0x4040,       /*!< Unexpected number of written bits, differs to
                                                                 calculated number of bits.                      */
  AAC_ENC_PNS_TABLE_ERROR                   = 0x4060,       /*!< PNS level out of range.                         */
  AAC_ENC_GLOBAL_GAIN_TOO_HIGH              = 0x4080,       /*!< Internal quantizer error.                       */
  AAC_ENC_BITRES_TOO_LOW                    = 0x40a0,       /*!< Too few  bits in bit reservoir.                 */
  AAC_ENC_BITRES_TOO_HIGH                   = 0x40a1,       /*!< Too many bits in bit reservoir.                 */
  AAC_ENC_INVALID_CHANNEL_BITRATE           = 0x4100,
  AAC_ENC_INVALID_ELEMENTINFO_TYPE          = 0x4120,       /*!< Internal encoder error.                         */

  AAC_ENC_WRITE_SCAL_ERROR                  = 0x41e0,       /*!< Error writing scalefacData.                     */
  AAC_ENC_WRITE_SEC_ERROR                   = 0x4200,       /*!< Error writing sectionData.                      */
  AAC_ENC_WRITE_SPEC_ERROR                  = 0x4220,       /*!< Error writing spectralData.                     */
  aac_enc_error_end

} AAC_ENCODER_ERROR;
/*-------------------------- defines --------------------------------------*/

#define ANC_DATA_BUFFERSIZE 1024      /* ancBuffer size */
#define DEFAULT_FRAMELENGTH 1024      /* size of AAC core frame in (new) PCM samples */

#define MAX_TOTAL_EXT_PAYLOADS  (((6) * (1)) + (2+2))


typedef enum {
  AACENC_BR_MODE_INVALID = -1,  /*!< Invalid bitrate mode.                            */
  AACENC_BR_MODE_CBR     =  0,  /*!< Constant bitrate mode.                           */
  AACENC_BR_MODE_VBR_1   =  1,  /*!< Variable bitrate mode, about 32 kbps/channel.    */
  AACENC_BR_MODE_VBR_2   =  2,  /*!< Variable bitrate mode, about 40 kbps/channel.    */
  AACENC_BR_MODE_VBR_3   =  3,  /*!< Variable bitrate mode, about 48-56 kbps/channel. */
  AACENC_BR_MODE_VBR_4   =  4,  /*!< Variable bitrate mode, about 64 kbps/channel.    */
  AACENC_BR_MODE_VBR_5   =  5,  /*!< Variable bitrate mode, about 80-96 kbps/channel. */
  AACENC_BR_MODE_FF      =  6,  /*!< Fixed frame mode.                                */
  AACENC_BR_MODE_SFR     =  7   /*!< Superframe mode.                                 */

} AACENC_BITRATE_MODE;

typedef enum {

  CH_ORDER_MPEG = 0,  /*!< MPEG channel ordering (e. g. 5.1: C, L, R, SL, SR, LFE)           */
  CH_ORDER_WAV        /*!< WAV fileformat channel ordering (e. g. 5.1: L, R, C, LFE, SL, SR) */

} CHANNEL_ORDER;

/*-------------------- structure definitions ------------------------------*/

struct AACENC_CONFIG {
  INT   sampleRate;             /* encoder sample rate */
  INT   bitRate;                /* encoder bit rate in bits/sec */
  INT   ancDataBitRate;         /* additional bits consumed by anc data or sbr have to be consiedered while configuration */

  INT   nSubFrames;             /* number of frames in super frame (not ADTS/LATM subframes !) */
  AUDIO_OBJECT_TYPE audioObjectType;   /* Audio Object Type  */

  INT   averageBits;            /* encoder bit rate in bits/superframe */
  INT   bitrateMode;            /* encoder bitrate mode (CBR/VBR) */
  INT   nChannels;              /* number of channels to process */
  CHANNEL_ORDER channelOrder;   /* Input Channel ordering scheme. */
  INT   bandWidth;              /* targeted audio bandwidth in Hz */
  CHANNEL_MODE  channelMode;    /* encoder channel mode configuration */
  INT   framelength;            /* used frame size */

  UINT  syntaxFlags;            /* bitstreams syntax configuration */
  SCHAR epConfig;               /* error protection configuration */

  INT   anc_Rate;               /* ancillary rate, 0 (disabled), -1 (default) else desired rate */
  UINT  maxAncBytesPerAU;
  INT   minBitsPerFrame;        /* minimum number of bits in AU */
  INT   maxBitsPerFrame;        /* maximum number of bits in AU */
  INT   bitreservoir;           /* size of bitreservoir */

  UCHAR useTns;                 /* flag: use temporal noise shaping */
  UCHAR usePns;                 /* flag: use perceptual noise substitution */
  UCHAR useIS;                  /* flag: use intensity coding */

  UCHAR useRequant;             /* flag: use afterburner */
};

typedef struct {
  UCHAR            *pData;      /* pointer to extension payload data */
  UINT              dataSize;   /* extension payload data size in bits */
  EXT_PAYLOAD_TYPE  dataType;   /* extension payload data type */
  INT               associatedChElement;  /* number of the channel element the data is assigned to */
} AACENC_EXT_PAYLOAD;

typedef struct AAC_ENC *HANDLE_AAC_ENC;

 /*-----------------------------------------------------------------------------

     functionname: FDKaacEnc_GetVBRBitrate
     description:  Get VBR bitrate from vbr quality
     input params: int vbrQuality (VBR0, VBR1, VBR2)
                   channelMode
     returns:      vbr bitrate

 ------------------------------------------------------------------------------*/
 INT FDKaacEnc_GetVBRBitrate(INT bitrateMode, CHANNEL_MODE channelMode);


/*-----------------------------------------------------------------------------

     functionname: FDKaacEnc_AacInitDefaultConfig
     description:  gives reasonable default configuration
     returns:      ---

 ------------------------------------------------------------------------------*/
void FDKaacEnc_AacInitDefaultConfig(AACENC_CONFIG     *config);

/*---------------------------------------------------------------------------

	    functionname:FDKaacEnc_Open
    description: allocate and initialize a new encoder instance
    returns:     0 if success

  ---------------------------------------------------------------------------*/
AAC_ENCODER_ERROR FDKaacEnc_Open(HANDLE_AAC_ENC  *phAacEnc,              /* pointer to an encoder handle, initialized on return */
                                 const INT        nElements,             /* number of maximal elements in instance to support */
                                 const INT        nChannels,             /* number of maximal channels in instance to support */
                                 const INT        nSubFrames);           /* support superframing in instance */


AAC_ENCODER_ERROR FDKaacEnc_Initialize(HANDLE_AAC_ENC     hAacEncoder,   /* pointer to an encoder handle, initialized on return */
                                       AACENC_CONFIG    *config,         /* pre-initialized config struct */
                                       HANDLE_TRANSPORTENC hTpEnc,
                                       ULONG               initFlags);


/*---------------------------------------------------------------------------

    functionname: FDKaacEnc_EncodeFrame
    description:  encode one frame
    returns:      0 if success

  ---------------------------------------------------------------------------*/

AAC_ENCODER_ERROR FDKaacEnc_EncodeFrame( HANDLE_AAC_ENC       hAacEnc,         /* encoder handle */
                                         HANDLE_TRANSPORTENC  hTpEnc,
                                         INT_PCM*             inputBuffer,
                                         INT*                 numOutBytes,
                                         AACENC_EXT_PAYLOAD   extPayload[MAX_TOTAL_EXT_PAYLOADS]
                                       );

/*---------------------------------------------------------------------------

    functionname:FDKaacEnc_Close
    description: delete encoder instance
    returns:

  ---------------------------------------------------------------------------*/

void FDKaacEnc_Close( HANDLE_AAC_ENC*  phAacEnc);   /* encoder handle */

#ifdef __cplusplus
}
#endif

#endif /* _aacenc_h_ */
