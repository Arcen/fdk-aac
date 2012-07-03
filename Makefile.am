lib_LIBRARIES = libfdk_aac.a

libfdk_aac_a_CPPFLAGS = -IlibSYS/include -IlibFDK/include -IlibPCMutils/include -IlibMpegTPEnc/include -IlibSBRenc/include -IlibAACenc/include -IlibMpegTPDec/include -IlibSBRdec/include -IlibAACdec/include
libfdk_aac_a_SOURCES = \
	libSYS/src/cmdl_parser.cpp  libSYS/src/conv_string.cpp  libSYS/src/genericStds.cpp  libSYS/src/wav_file.cpp \
	libSYS/src/linux/FDK_stackload_linux.cpp  libSYS/src/linux/coresup_linux.cpp      libSYS/src/linux/uart_linux.cpp \
	libSYS/src/linux/audio_linux.cpp          libSYS/src/linux/genericStds_linux.cpp \
	libFDK/src/FDK_bitbuffer.cpp  libFDK/src/FDK_hybrid.cpp     libFDK/src/autocorr2nd.cpp  libFDK/src/fft_rad2.cpp       libFDK/src/qmf.cpp \
	libFDK/src/FDK_core.cpp       libFDK/src/FDK_tools_rom.cpp  libFDK/src/dct.cpp          libFDK/src/fixpoint_math.cpp  libFDK/src/scale.cpp \
	libFDK/src/FDK_crc.cpp        libFDK/src/FDK_trigFcts.cpp   libFDK/src/fft.cpp          libFDK/src/mdct.cpp \
	libPCMutils/src/pcmutils_lib.cpp \
	libMpegTPEnc/src/tpenc_adif.cpp  libMpegTPEnc/src/tpenc_asc.cpp   libMpegTPEnc/src/tpenc_lib.cpp \
	libMpegTPEnc/src/tpenc_adts.cpp  libMpegTPEnc/src/tpenc_latm.cpp \
	libSBRenc/src/bit_sbr.cpp   libSBRenc/src/fram_gen.cpp  libSBRenc/src/ps_bitenc.cpp  libSBRenc/src/sbr_encoder.cpp  libSBRenc/src/sbrenc_freq_sca.cpp \
	libSBRenc/src/code_env.cpp  libSBRenc/src/invf_est.cpp  libSBRenc/src/ps_encode.cpp  libSBRenc/src/sbr_misc.cpp     libSBRenc/src/ton_corr.cpp \
	libSBRenc/src/env_bit.cpp   libSBRenc/src/mh_det.cpp    libSBRenc/src/ps_main.cpp    libSBRenc/src/sbr_ram.cpp      libSBRenc/src/tran_det.cpp \
	libSBRenc/src/env_est.cpp   libSBRenc/src/nf_est.cpp    libSBRenc/src/resampler.cpp  libSBRenc/src/sbr_rom.cpp \
	libAACenc/src/aacEnc_ram.cpp  libAACenc/src/bandwidth.cpp     libAACenc/src/line_pe.cpp              libAACenc/src/qc_main.cpp \
	libAACenc/src/aacEnc_rom.cpp  libAACenc/src/bit_cnt.cpp       libAACenc/src/metadata_compressor.cpp  libAACenc/src/quantize.cpp \
	libAACenc/src/aacenc.cpp      libAACenc/src/bitenc.cpp        libAACenc/src/metadata_main.cpp        libAACenc/src/sf_estim.cpp \
	libAACenc/src/aacenc_hcr.cpp  libAACenc/src/block_switch.cpp  libAACenc/src/ms_stereo.cpp            libAACenc/src/spreading.cpp \
	libAACenc/src/aacenc_lib.cpp  libAACenc/src/channel_map.cpp   libAACenc/src/noisedet.cpp             libAACenc/src/tns_param.cpp \
	libAACenc/src/aacenc_pns.cpp  libAACenc/src/chaosmeasure.cpp  libAACenc/src/pnsparam.cpp             libAACenc/src/tonality.cpp \
	libAACenc/src/aacenc_tns.cpp  libAACenc/src/dyn_bits.cpp      libAACenc/src/pre_echo_control.cpp     libAACenc/src/transform.cpp \
	libAACenc/src/adj_thr.cpp     libAACenc/src/grp_data.cpp      libAACenc/src/psy_configuration.cpp \
	libAACenc/src/band_nrg.cpp    libAACenc/src/intensity.cpp     libAACenc/src/psy_main.cpp \
	libMpegTPDec/src/tpdec_adif.cpp  libMpegTPDec/src/tpdec_asc.cpp   libMpegTPDec/src/tpdec_lib.cpp \
	libMpegTPDec/src/tpdec_adts.cpp  libMpegTPDec/src/tpdec_latm.cpp \
	libSBRdec/src/env_calc.cpp  libSBRdec/src/lpp_tran.cpp      libSBRdec/src/sbr_crc.cpp  libSBRdec/src/sbr_rom_dec.cpp \
	libSBRdec/src/env_dec.cpp   libSBRdec/src/psbitdec.cpp      libSBRdec/src/sbr_deb.cpp  libSBRdec/src/sbrdec_drc.cpp \
	libSBRdec/src/env_extr.cpp  libSBRdec/src/psdec.cpp         libSBRdec/src/sbr_dec.cpp  libSBRdec/src/sbrdec_freq_sca.cpp \
	libSBRdec/src/huff_dec.cpp  libSBRdec/src/psdec_hybrid.cpp  libSBRdec/src/sbr_ram_dec.cpp  libSBRdec/src/sbrdecoder.cpp \
	libAACdec/src/aac_ram.cpp     libAACdec/src/aacdec_hcr_bit.cpp  libAACdec/src/aacdecoder.cpp      libAACdec/src/channelinfo.cpp  libAACdec/src/rvlc.cpp \
	libAACdec/src/aac_rom.cpp     libAACdec/src/aacdec_hcrs.cpp     libAACdec/src/aacdecoder_lib.cpp  libAACdec/src/conceal.cpp      libAACdec/src/rvlcbit.cpp \
	libAACdec/src/aacdec_drc.cpp  libAACdec/src/aacdec_pns.cpp      libAACdec/src/block.cpp           libAACdec/src/ldfiltbank.cpp   libAACdec/src/rvlcconceal.cpp \
	libAACdec/src/aacdec_hcr.cpp  libAACdec/src/aacdec_tns.cpp      libAACdec/src/channel.cpp         libAACdec/src/pulsedata.cpp    libAACdec/src/stereo.cpp

nobase_includedir=$(includedir)/fdk-aac

