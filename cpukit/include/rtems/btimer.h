/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @brief RTEMS Benchmark Timer API for all Boards
 */

/*
 *  COPYRIGHT (c) 2011 Ralf Corsepius Ulm/Germany
 *
 *  Derived from libcsupport/include/timerdrv.h:
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * All the functions declared as extern after this comment
 * MUST be implemented in each BSP.
 */

#ifndef _RTEMS_BTIMER_H
#define _RTEMS_BTIMER_H

#include <stdbool.h>
#include <stdint.h>
#include <rtems/rtems/status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup BenchmarkTimer Benchmark Timer Driver Interface
 *
 * @ingroup RTEMSLegacyBenchmarkDrivers
 *
 * This module defines the interface for the Benchmark Timer Driver.
 *
 * The following methods in this module must be provided by each BSP:
 *
 *   - benchmark_timer_initialize
 *   - benchmark_timer_read
 *   - benchmark_timer_disable_subtracting_average_overhead
 *
 * The units measured are BSP specific but should be at the highest
 * granularity possible.
 *
 * The Benchmark Timer may use the same hardware as the Clock Driver.
 * No RTEMS Timing Tests will use both drivers at the same time.
 */

/**
 * @brief This type is used to return a Benchmark Timer value.
 *
 * This type is used to contain benchmark times. The units are BSP specific.
 */
typedef uint32_t benchmark_timer_t;

/**
 * @brief Initialize the Benchmark Timer
 *
 * This method initializes the benchmark timer and resets it to begin
 * counting.
 */
extern void benchmark_timer_initialize( void );

/**
 * @brief Read the Benchmark Timer
 *
 * This method stops the benchmark timer and returns the number of
 * units that have passed since @a benchmark_timer_initialize was invoked.
 *
 * @return This method returns the number of units with the average overhead
 *          removed. If the value is below the minimum trusted value, zero
 *          is returned.
 */
extern benchmark_timer_t benchmark_timer_read( void );

/**
 * @brief Benchmark Timer Empty Function
 *
 * This method is used to determine loop overhead.
 */
extern rtems_status_code benchmark_timer_empty_function( void );

/**
 * @brief Disable Average Overhead Removal from the Benchmark Timer
 *
 * This method places the benchmark timer in a "raw" mode where it
 * returns the actual number of units which have passed between
 * calls to @a benchmark_timer_initialize and @a benchmark_timer_read
 * counting.
 *
 * @param[in] find_flag indicates to enable or disable the mode
 */
extern void benchmark_timer_disable_subtracting_average_overhead(
  bool find_flag
);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
