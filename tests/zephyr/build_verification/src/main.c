/*
 * Copyright (c) 2025 BitConcepts
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Build-verification tests for CryptoAuthLib Zephyr module integration.
 * These tests verify that the library headers, configuration, and HAL
 * stubs compile and link correctly under a Zephyr build.
 */

#include <zephyr/ztest.h>
#include <zephyr/kernel.h>

#include "cryptoauthlib.h"
#include "atca_status.h"
#include "hal/atca_hal.h"

/*
 * Verify that atca_config.h was generated and key preprocessor symbols
 * are defined as expected from prj.conf / Kconfig.
 */
ZTEST(cryptoauthlib_build, test_config_header_generated)
{
#if !defined(ATCA_HAL_I2C)
	ztest_test_fail();
#endif

#if !defined(ATCA_ATECC608_SUPPORT)
	ztest_test_fail();
#endif

	zassert_true(true, "atca_config.h generated with expected defines");
}

/*
 * Verify that common status codes are accessible and have the expected
 * values (proves atca_status.h linked properly).
 */
ZTEST(cryptoauthlib_build, test_status_codes)
{
	zassert_equal(ATCA_SUCCESS, 0x00,
		      "ATCA_SUCCESS should be 0");
	zassert_not_equal(ATCA_BAD_PARAM, ATCA_SUCCESS,
			  "ATCA_BAD_PARAM must differ from SUCCESS");
	zassert_not_equal(ATCA_COMM_FAIL, ATCA_SUCCESS,
			  "ATCA_COMM_FAIL must differ from SUCCESS");
}

/*
 * Verify that the HAL delay functions are callable (link test).
 * On native_sim these will simply call k_usleep / k_msleep.
 */
ZTEST(cryptoauthlib_build, test_hal_delay_linkage)
{
	/* Calling with 0 should return immediately without error */
	hal_delay_us(0);
	hal_delay_ms(0);

	zassert_true(true, "HAL delay functions linked successfully");
}

/*
 * Verify that hal_create_mutex / hal_destroy_mutex compile and link.
 * Exercises the Zephyr k_mutex path.
 */
ZTEST(cryptoauthlib_build, test_hal_mutex_lifecycle)
{
	ATCA_STATUS status;
	void *mutex = NULL;

	status = hal_create_mutex(&mutex, "test");
	zassert_equal(status, ATCA_SUCCESS,
		      "hal_create_mutex should succeed");
	zassert_not_null(mutex, "Mutex pointer should be non-NULL");

	status = hal_lock_mutex(mutex);
	zassert_equal(status, ATCA_SUCCESS,
		      "hal_lock_mutex should succeed");

	status = hal_unlock_mutex(mutex);
	zassert_equal(status, ATCA_SUCCESS,
		      "hal_unlock_mutex should succeed");

	status = hal_destroy_mutex(mutex);
	zassert_equal(status, ATCA_SUCCESS,
		      "hal_destroy_mutex should succeed");
}

/*
 * Verify NULL-guard behavior of HAL mutex functions.
 */
ZTEST(cryptoauthlib_build, test_hal_mutex_null_guards)
{
	ATCA_STATUS status;

	status = hal_create_mutex(NULL, "null");
	zassert_equal(status, ATCA_BAD_PARAM,
		      "hal_create_mutex(NULL) should return BAD_PARAM");

	status = hal_destroy_mutex(NULL);
	zassert_equal(status, ATCA_BAD_PARAM,
		      "hal_destroy_mutex(NULL) should return BAD_PARAM");

	status = hal_lock_mutex(NULL);
	zassert_equal(status, ATCA_BAD_PARAM,
		      "hal_lock_mutex(NULL) should return BAD_PARAM");

	status = hal_unlock_mutex(NULL);
	zassert_equal(status, ATCA_BAD_PARAM,
		      "hal_unlock_mutex(NULL) should return BAD_PARAM");
}

ZTEST_SUITE(cryptoauthlib_build, NULL, NULL, NULL, NULL, NULL);
