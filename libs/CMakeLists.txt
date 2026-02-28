# zlib
if(USE_INTERNAL_ZLIB)
    add_library(
        internal_zlib
        STATIC
        zlib-1.3.2/adler32.c
        zlib-1.3.2/crc32.c
        zlib-1.3.2/inffast.c
        zlib-1.3.2/inflate.c
        zlib-1.3.2/inftrees.c
        zlib-1.3.2/zutil.c
    )
    target_include_directories(internal_zlib PUBLIC zlib-1.3.2)
    target_compile_definitions(internal_zlib PUBLIC NO_GZIP)
    set_target_properties(internal_zlib PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# JPEG (libjpeg-turbo)
if(USE_INTERNAL_JPEG)
    # Generate jconfig.h from template
    set(JPEG_LIB_VERSION 80)
    set(VERSION "3.1.3")
    set(LIBJPEG_TURBO_VERSION_NUMBER 3001003)
    set(C_ARITH_CODING_SUPPORTED 1)
    set(D_ARITH_CODING_SUPPORTED 1)
    set(MEM_SRCDST_SUPPORTED 1)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/libjpeg-turbo-3.1.3/src/jconfig.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h
    )

    # Generate jconfigint.h from template
    set(BUILD "")
    if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set(INLINE "__inline")
    else()
        set(INLINE "__inline__ __attribute__((always_inline))")
    endif()
    set(THREAD_LOCAL "")
    set(HIDDEN "__attribute__((visibility(\"hidden\")))")
    if(WIN32)
        set(HIDDEN "")
    endif()
    set(SIZE_T ${CMAKE_SIZEOF_VOID_P})
    set(HAVE_BUILTIN_CTZL 1)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/libjpeg-turbo-3.1.3/src/jconfigint.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/jconfigint.h
    )

    # Generate jversion.h from template
    set(COPYRIGHT_YEAR "2024")
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/libjpeg-turbo-3.1.3/src/jversion.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/jversion.h
    )

    add_library(
        internal_jpeg
        STATIC
        # Non-precision-dependent sources
        libjpeg-turbo-3.1.3/src/jaricom.c
        libjpeg-turbo-3.1.3/src/jcapimin.c
        libjpeg-turbo-3.1.3/src/jcarith.c
        libjpeg-turbo-3.1.3/src/jchuff.c
        libjpeg-turbo-3.1.3/src/jcicc.c
        libjpeg-turbo-3.1.3/src/jcinit.c
        libjpeg-turbo-3.1.3/src/jclhuff.c
        libjpeg-turbo-3.1.3/src/jcmarker.c
        libjpeg-turbo-3.1.3/src/jcmaster.c
        libjpeg-turbo-3.1.3/src/jcomapi.c
        libjpeg-turbo-3.1.3/src/jcparam.c
        libjpeg-turbo-3.1.3/src/jcphuff.c
        libjpeg-turbo-3.1.3/src/jctrans.c
        libjpeg-turbo-3.1.3/src/jdapimin.c
        libjpeg-turbo-3.1.3/src/jdarith.c
        libjpeg-turbo-3.1.3/src/jdatadst.c
        libjpeg-turbo-3.1.3/src/jdatasrc.c
        libjpeg-turbo-3.1.3/src/jdhuff.c
        libjpeg-turbo-3.1.3/src/jdicc.c
        libjpeg-turbo-3.1.3/src/jdinput.c
        libjpeg-turbo-3.1.3/src/jdlhuff.c
        libjpeg-turbo-3.1.3/src/jdmarker.c
        libjpeg-turbo-3.1.3/src/jdmaster.c
        libjpeg-turbo-3.1.3/src/jdphuff.c
        libjpeg-turbo-3.1.3/src/jdtrans.c
        libjpeg-turbo-3.1.3/src/jerror.c
        libjpeg-turbo-3.1.3/src/jfdctflt.c
        libjpeg-turbo-3.1.3/src/jmemmgr.c
        libjpeg-turbo-3.1.3/src/jmemnobs.c
        libjpeg-turbo-3.1.3/src/jpeg_nbits.c
        # Precision-dependent wrappers (8-bit)
        libjpeg-turbo-3.1.3/src/wrapper/jcapistd-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jccoefct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jccolor-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jcdctmgr-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jcdiffct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jclossls-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jcmainct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jcprepct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jcsample-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdapistd-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdcoefct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdcolor-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jddctmgr-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jddiffct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdlossls-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdmainct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdmerge-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdpostct-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jdsample-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jfdctfst-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jfdctint-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctflt-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctfst-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctint-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctred-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jquant1-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jquant2-8.c
        libjpeg-turbo-3.1.3/src/wrapper/jutils-8.c
        # Precision-dependent wrappers (12-bit)
        libjpeg-turbo-3.1.3/src/wrapper/jcapistd-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jccoefct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jccolor-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jcdctmgr-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jcdiffct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jclossls-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jcmainct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jcprepct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jcsample-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdapistd-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdcoefct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdcolor-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jddctmgr-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jddiffct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdlossls-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdmainct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdmerge-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdpostct-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jdsample-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jfdctfst-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jfdctint-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctflt-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctfst-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctint-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jidctred-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jquant1-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jquant2-12.c
        libjpeg-turbo-3.1.3/src/wrapper/jutils-12.c
        # Precision-dependent wrappers (16-bit / lossless)
        libjpeg-turbo-3.1.3/src/wrapper/jcapistd-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jccolor-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jcdiffct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jclossls-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jcmainct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jcprepct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jcsample-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdapistd-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdcolor-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jddiffct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdlossls-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdmainct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdpostct-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jdsample-16.c
        libjpeg-turbo-3.1.3/src/wrapper/jutils-16.c
    )
    target_include_directories(
        internal_jpeg
        PUBLIC
            ${CMAKE_CURRENT_BINARY_DIR}
            libjpeg-turbo-3.1.3/src
    )
    set_target_properties(internal_jpeg PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# FreeType
if(USE_INTERNAL_FREETYPE)
    add_library(
        internal_freetype
        STATIC
        freetype-2.14.1/src/base/ftsystem.c
        freetype-2.14.1/src/base/ftdebug.c
        freetype-2.14.1/src/base/ftinit.c
        freetype-2.14.1/src/base/ftbase.c
        freetype-2.14.1/src/base/ftbbox.c
        freetype-2.14.1/src/base/ftbdf.c
        freetype-2.14.1/src/base/ftbitmap.c
        freetype-2.14.1/src/base/ftcid.c
        freetype-2.14.1/src/base/ftfntfmt.c
        freetype-2.14.1/src/base/ftfstype.c
        freetype-2.14.1/src/base/ftgasp.c
        freetype-2.14.1/src/base/ftglyph.c
        freetype-2.14.1/src/base/ftgxval.c
        freetype-2.14.1/src/base/ftlcdfil.c
        freetype-2.14.1/src/base/ftmm.c
        freetype-2.14.1/src/base/ftotval.c
        freetype-2.14.1/src/base/ftpatent.c
        freetype-2.14.1/src/base/ftpfr.c
        freetype-2.14.1/src/base/ftstroke.c
        freetype-2.14.1/src/base/ftsynth.c
        freetype-2.14.1/src/base/fttype1.c
        freetype-2.14.1/src/base/ftwinfnt.c
        freetype-2.14.1/src/truetype/truetype.c
        freetype-2.14.1/src/type1/type1.c
        freetype-2.14.1/src/cff/cff.c
        freetype-2.14.1/src/cid/type1cid.c
        freetype-2.14.1/src/pfr/pfr.c
        freetype-2.14.1/src/type42/type42.c
        freetype-2.14.1/src/winfonts/winfnt.c
        freetype-2.14.1/src/pcf/pcf.c
        freetype-2.14.1/src/bdf/bdf.c
        freetype-2.14.1/src/sfnt/sfnt.c
        freetype-2.14.1/src/autofit/autofit.c
        freetype-2.14.1/src/pshinter/pshinter.c
        freetype-2.14.1/src/raster/raster.c
        freetype-2.14.1/src/smooth/smooth.c
        freetype-2.14.1/src/cache/ftcache.c
        freetype-2.14.1/src/gzip/ftgzip.c
        freetype-2.14.1/src/lzw/ftlzw.c
        freetype-2.14.1/src/bzip2/ftbzip2.c
        freetype-2.14.1/src/psaux/psaux.c
        freetype-2.14.1/src/psnames/psnames.c
        freetype-2.14.1/src/sdf/sdf.c
        freetype-2.14.1/src/svg/svg.c
    )
    target_include_directories(internal_freetype PUBLIC freetype-2.14.1/include)
    target_compile_definitions(internal_freetype PRIVATE FT2_BUILD_LIBRARY)
    set_target_properties(
        internal_freetype
        PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif()

# OGG
if(USE_INTERNAL_OGG)
    # Generate config_types.h for libogg
    include(CheckIncludeFile)
    check_include_file(inttypes.h INCLUDE_INTTYPES_H)
    check_include_file(stdint.h INCLUDE_STDINT_H)
    check_include_file(sys/types.h INCLUDE_SYS_TYPES_H)
    set(SIZE16 int16_t)
    set(USIZE16 uint16_t)
    set(SIZE32 int32_t)
    set(USIZE32 uint32_t)
    set(SIZE64 int64_t)
    set(USIZE64 uint64_t)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/libogg-1.3.6/include/ogg/config_types.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/ogg/config_types.h
    )

    add_library(
        internal_ogg
        STATIC
        libogg-1.3.6/src/bitwise.c
        libogg-1.3.6/src/framing.c
    )
    target_include_directories(
        internal_ogg
        PUBLIC libogg-1.3.6/include ${CMAKE_CURRENT_BINARY_DIR}
    )
    set_target_properties(internal_ogg PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# Vorbis
if(USE_INTERNAL_VORBIS)
    add_library(
        internal_vorbis
        STATIC
        libvorbis-1.3.7/lib/analysis.c
        libvorbis-1.3.7/lib/bitrate.c
        libvorbis-1.3.7/lib/block.c
        libvorbis-1.3.7/lib/codebook.c
        libvorbis-1.3.7/lib/envelope.c
        libvorbis-1.3.7/lib/floor0.c
        libvorbis-1.3.7/lib/floor1.c
        libvorbis-1.3.7/lib/info.c
        libvorbis-1.3.7/lib/lookup.c
        libvorbis-1.3.7/lib/lpc.c
        libvorbis-1.3.7/lib/lsp.c
        libvorbis-1.3.7/lib/mapping0.c
        libvorbis-1.3.7/lib/mdct.c
        libvorbis-1.3.7/lib/psy.c
        libvorbis-1.3.7/lib/registry.c
        libvorbis-1.3.7/lib/res0.c
        libvorbis-1.3.7/lib/sharedbook.c
        libvorbis-1.3.7/lib/smallft.c
        libvorbis-1.3.7/lib/synthesis.c
        libvorbis-1.3.7/lib/vorbisenc.c
        libvorbis-1.3.7/lib/vorbisfile.c
        libvorbis-1.3.7/lib/window.c
    )
    target_include_directories(
        internal_vorbis
        PUBLIC libvorbis-1.3.7/include libvorbis-1.3.7/lib
    )
    if(USE_INTERNAL_OGG)
        target_link_libraries(internal_vorbis PRIVATE internal_ogg)
    else()
        target_include_directories(internal_vorbis PRIVATE ${OGG_INCLUDE_DIRS})
        target_link_libraries(internal_vorbis PRIVATE ${OGG_LIBRARIES})
    endif()
    set_target_properties(
        internal_vorbis
        PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif()

# Opus
if(USE_INTERNAL_OPUS)
    # Create opus/ subdirectory structure so <opus/opus.h> includes work
    set(_opus_inc_dir ${CMAKE_CURRENT_BINARY_DIR}/include)
    file(MAKE_DIRECTORY ${_opus_inc_dir}/opus)
    file(GLOB _opus_hdrs ${CMAKE_CURRENT_SOURCE_DIR}/opus-1.6.1/include/*.h)
    foreach(hdr ${_opus_hdrs})
        get_filename_component(name ${hdr} NAME)
        configure_file(${hdr} ${_opus_inc_dir}/opus/${name} COPYONLY)
    endforeach()
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/opusfile-0.12/include/opusfile.h
        ${_opus_inc_dir}/opus/opusfile.h
        COPYONLY
    )

    add_library(
        internal_opus
        STATIC
        # src/
        opus-1.6.1/src/opus.c
        opus-1.6.1/src/opus_decoder.c
        opus-1.6.1/src/opus_encoder.c
        opus-1.6.1/src/opus_multistream.c
        opus-1.6.1/src/opus_multistream_encoder.c
        opus-1.6.1/src/opus_multistream_decoder.c
        opus-1.6.1/src/opus_projection_encoder.c
        opus-1.6.1/src/opus_projection_decoder.c
        opus-1.6.1/src/mapping_matrix.c
        opus-1.6.1/src/repacketizer.c
        opus-1.6.1/src/extensions.c
        opus-1.6.1/src/analysis.c
        opus-1.6.1/src/mlp.c
        opus-1.6.1/src/mlp_data.c
        # celt/
        opus-1.6.1/celt/bands.c
        opus-1.6.1/celt/celt.c
        opus-1.6.1/celt/celt_encoder.c
        opus-1.6.1/celt/celt_decoder.c
        opus-1.6.1/celt/cwrs.c
        opus-1.6.1/celt/entcode.c
        opus-1.6.1/celt/entdec.c
        opus-1.6.1/celt/entenc.c
        opus-1.6.1/celt/kiss_fft.c
        opus-1.6.1/celt/laplace.c
        opus-1.6.1/celt/mathops.c
        opus-1.6.1/celt/mdct.c
        opus-1.6.1/celt/modes.c
        opus-1.6.1/celt/pitch.c
        opus-1.6.1/celt/celt_lpc.c
        opus-1.6.1/celt/quant_bands.c
        opus-1.6.1/celt/rate.c
        opus-1.6.1/celt/vq.c
        # silk/
        opus-1.6.1/silk/CNG.c
        opus-1.6.1/silk/code_signs.c
        opus-1.6.1/silk/init_decoder.c
        opus-1.6.1/silk/decode_core.c
        opus-1.6.1/silk/decode_frame.c
        opus-1.6.1/silk/decode_parameters.c
        opus-1.6.1/silk/decode_indices.c
        opus-1.6.1/silk/decode_pulses.c
        opus-1.6.1/silk/decoder_set_fs.c
        opus-1.6.1/silk/dec_API.c
        opus-1.6.1/silk/enc_API.c
        opus-1.6.1/silk/encode_indices.c
        opus-1.6.1/silk/encode_pulses.c
        opus-1.6.1/silk/gain_quant.c
        opus-1.6.1/silk/interpolate.c
        opus-1.6.1/silk/LP_variable_cutoff.c
        opus-1.6.1/silk/NLSF_decode.c
        opus-1.6.1/silk/NSQ.c
        opus-1.6.1/silk/NSQ_del_dec.c
        opus-1.6.1/silk/PLC.c
        opus-1.6.1/silk/shell_coder.c
        opus-1.6.1/silk/tables_gain.c
        opus-1.6.1/silk/tables_LTP.c
        opus-1.6.1/silk/tables_NLSF_CB_NB_MB.c
        opus-1.6.1/silk/tables_NLSF_CB_WB.c
        opus-1.6.1/silk/tables_other.c
        opus-1.6.1/silk/tables_pitch_lag.c
        opus-1.6.1/silk/tables_pulses_per_block.c
        opus-1.6.1/silk/VAD.c
        opus-1.6.1/silk/control_audio_bandwidth.c
        opus-1.6.1/silk/quant_LTP_gains.c
        opus-1.6.1/silk/VQ_WMat_EC.c
        opus-1.6.1/silk/HP_variable_cutoff.c
        opus-1.6.1/silk/NLSF_encode.c
        opus-1.6.1/silk/NLSF_VQ.c
        opus-1.6.1/silk/NLSF_unpack.c
        opus-1.6.1/silk/NLSF_del_dec_quant.c
        opus-1.6.1/silk/process_NLSFs.c
        opus-1.6.1/silk/stereo_LR_to_MS.c
        opus-1.6.1/silk/stereo_MS_to_LR.c
        opus-1.6.1/silk/check_control_input.c
        opus-1.6.1/silk/control_SNR.c
        opus-1.6.1/silk/init_encoder.c
        opus-1.6.1/silk/control_codec.c
        opus-1.6.1/silk/A2NLSF.c
        opus-1.6.1/silk/ana_filt_bank_1.c
        opus-1.6.1/silk/biquad_alt.c
        opus-1.6.1/silk/bwexpander_32.c
        opus-1.6.1/silk/bwexpander.c
        opus-1.6.1/silk/debug.c
        opus-1.6.1/silk/decode_pitch.c
        opus-1.6.1/silk/inner_prod_aligned.c
        opus-1.6.1/silk/lin2log.c
        opus-1.6.1/silk/log2lin.c
        opus-1.6.1/silk/LPC_analysis_filter.c
        opus-1.6.1/silk/LPC_inv_pred_gain.c
        opus-1.6.1/silk/table_LSF_cos.c
        opus-1.6.1/silk/NLSF2A.c
        opus-1.6.1/silk/NLSF_stabilize.c
        opus-1.6.1/silk/NLSF_VQ_weights_laroia.c
        opus-1.6.1/silk/pitch_est_tables.c
        opus-1.6.1/silk/resampler.c
        opus-1.6.1/silk/resampler_down2_3.c
        opus-1.6.1/silk/resampler_down2.c
        opus-1.6.1/silk/resampler_private_AR2.c
        opus-1.6.1/silk/resampler_private_down_FIR.c
        opus-1.6.1/silk/resampler_private_IIR_FIR.c
        opus-1.6.1/silk/resampler_private_up2_HQ.c
        opus-1.6.1/silk/resampler_rom.c
        opus-1.6.1/silk/sigm_Q15.c
        opus-1.6.1/silk/sort.c
        opus-1.6.1/silk/sum_sqr_shift.c
        opus-1.6.1/silk/stereo_decode_pred.c
        opus-1.6.1/silk/stereo_encode_pred.c
        opus-1.6.1/silk/stereo_find_predictor.c
        opus-1.6.1/silk/stereo_quant_pred.c
        opus-1.6.1/silk/LPC_fit.c
        # silk/float/
        opus-1.6.1/silk/float/apply_sine_window_FLP.c
        opus-1.6.1/silk/float/corrMatrix_FLP.c
        opus-1.6.1/silk/float/encode_frame_FLP.c
        opus-1.6.1/silk/float/find_LPC_FLP.c
        opus-1.6.1/silk/float/find_LTP_FLP.c
        opus-1.6.1/silk/float/find_pitch_lags_FLP.c
        opus-1.6.1/silk/float/find_pred_coefs_FLP.c
        opus-1.6.1/silk/float/LPC_analysis_filter_FLP.c
        opus-1.6.1/silk/float/LTP_analysis_filter_FLP.c
        opus-1.6.1/silk/float/LTP_scale_ctrl_FLP.c
        opus-1.6.1/silk/float/noise_shape_analysis_FLP.c
        opus-1.6.1/silk/float/process_gains_FLP.c
        opus-1.6.1/silk/float/regularize_correlations_FLP.c
        opus-1.6.1/silk/float/residual_energy_FLP.c
        opus-1.6.1/silk/float/warped_autocorrelation_FLP.c
        opus-1.6.1/silk/float/wrappers_FLP.c
        opus-1.6.1/silk/float/autocorrelation_FLP.c
        opus-1.6.1/silk/float/burg_modified_FLP.c
        opus-1.6.1/silk/float/bwexpander_FLP.c
        opus-1.6.1/silk/float/energy_FLP.c
        opus-1.6.1/silk/float/inner_product_FLP.c
        opus-1.6.1/silk/float/k2a_FLP.c
        opus-1.6.1/silk/float/LPC_inv_pred_gain_FLP.c
        opus-1.6.1/silk/float/pitch_analysis_core_FLP.c
        opus-1.6.1/silk/float/scale_copy_vector_FLP.c
        opus-1.6.1/silk/float/scale_vector_FLP.c
        opus-1.6.1/silk/float/schur_FLP.c
        opus-1.6.1/silk/float/sort_FLP.c
    )
    target_include_directories(
        internal_opus
        PUBLIC ${_opus_inc_dir} ${_opus_inc_dir}/opus
        PRIVATE
            opus-1.6.1/include
            opus-1.6.1/celt
            opus-1.6.1/silk
            opus-1.6.1/silk/float
            opus-1.6.1/src
    )
    target_compile_definitions(
        internal_opus
        PRIVATE OPUS_BUILD HAVE_LRINTF FLOATING_POINT FLOAT_APPROX USE_ALLOCA
    )
    set_target_properties(internal_opus PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# Opusfile
if(USE_INTERNAL_OPUS)
    add_library(
        internal_opusfile
        STATIC
        opusfile-0.12/src/info.c
        opusfile-0.12/src/internal.c
        opusfile-0.12/src/opusfile.c
        opusfile-0.12/src/stream.c
        opusfile-0.12/src/http.c
    )
    target_include_directories(
        internal_opusfile
        PRIVATE opusfile-0.12/include opus-1.6.1/include
    )
    if(WIN32)
        target_sources(internal_opusfile PRIVATE opusfile-0.12/src/wincerts.c)
    endif()
    target_link_libraries(internal_opusfile PRIVATE internal_opus)
    if(USE_INTERNAL_OGG)
        target_link_libraries(internal_opusfile PRIVATE internal_ogg)
    else()
        target_include_directories(
            internal_opusfile
            PRIVATE ${OGG_INCLUDE_DIRS}
        )
        target_link_libraries(internal_opusfile PRIVATE ${OGG_LIBRARIES})
    endif()
    set_target_properties(
        internal_opusfile
        PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif()
