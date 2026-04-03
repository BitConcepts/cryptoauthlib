# zephyr_options.cmake
# Map Zephyr Kconfig symbols (CONFIG_* variables) to CryptoAuthLib CMake options
#
# The list below uses the EXACT CMake option name as defined in lib/CMakeLists.txt.
# The corresponding Kconfig symbol is CONFIG_<cmake_option_name>.

if (ATCA_ZEPHYR_SUPPORT)
    message(STATUS "Mapping Kconfig symbols to CryptoAuthLib CMake options...")

    # Full CMake option names — must match lib/CMakeLists.txt exactly
    set(_opts
        ATCA_HAL_I2C ATCA_HAL_SPI ATCA_HAL_CUSTOM ATCA_HAL_KIT_HID
        ATCA_HAL_KIT_BRIDGE ATCA_HAL_KIT_UART ATCA_HAL_SWI_UART
        ATCA_PRINTF ATCA_NO_HEAP ATCA_CHECK_PARAMS_EN
        ATCA_ENABLE_DEPRECATED ATCA_STRICT_C99 MULTIPART_BUF_EN
        ATCA_MBEDTLS ATCA_WOLFSSL ATCA_OPENSSL ATCA_JWT_EN
        ATCACERT_COMPCERT_EN ATCACERT_FULLSTOREDCERT_EN
        ATCA_TNGTLS_SUPPORT ATCA_TNGLORA_SUPPORT ATCA_TFLEX_SUPPORT
        ATCA_TNG_LEGACY_SUPPORT ATCA_WPC_SUPPORT
        ATCAC_SHA384_EN ATCAC_SHA512_EN
        ATCA_PKCS11
        ATCA_ATSHA204A_SUPPORT ATCA_ATSHA206A_SUPPORT ATCA_ATECC108A_SUPPORT
        ATCA_ATECC508A_SUPPORT ATCA_ATECC608_SUPPORT ATCA_ECC204_SUPPORT
        ATCA_TA010_SUPPORT ATCA_SHA104_SUPPORT ATCA_SHA105_SUPPORT
    )

    foreach(opt IN LISTS _opts)
        # Kconfig symbol name = CONFIG_<opt>, e.g. CONFIG_ATCA_HAL_I2C
        set(_kconfig_var CONFIG_${opt})
        if(DEFINED ${_kconfig_var})
            if(${_kconfig_var})
                set(${opt} ON CACHE BOOL "Auto-set from Kconfig (${_kconfig_var})" FORCE)
            else()
                set(${opt} OFF CACHE BOOL "Auto-clear from Kconfig (${_kconfig_var})" FORCE)
            endif()
        endif()
    endforeach()
endif()
