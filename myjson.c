/**
 * @file myjson.c
 * @brief JSON  parser library header for C/C++.
 * This is a  C/C++ Json Parser Library Source @c myjson.h.
 * @details This header provides all public API, types, macros, and
 * configuration for YAML and supports both C and C++ usage.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @date Thur 02 12:43:15 Oct GMT 2025
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myjson
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Usage:
 * @code
 *  #include <myjson.h>
 * @endcode
 *
 * Index of this file:
 *
 *  Internal:
 *
 *  [SECTION] Includes
 *  [SECTION] Macro Defines
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *  [SECTION] C++ Only Classes
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *
 *  Myyaml:
 *
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/myjson
 * - Releases & changelog ....... https://github.com/djoezeke/myjson/releases
 * - Issues & support ........... https://github.com/djoezeke/myjson/issues
 *
 */

//-------------------------------------------------------------------------
// [SECTION] INCLUDES
//-------------------------------------------------------------------------

#include "myjson.h"

#pragma region Internal

//-------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#pragma region C Dec

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

#pragma endregion  // C Declarations

#pragma region C Def

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

#pragma endregion  // C Definations

#ifdef __cplusplus
}
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

#pragma region Cpp Dec

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

#pragma endregion  // Cpp Declarations

#pragma region Cpp Def

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

#pragma endregion  // Cpp Definations

#endif  //__cplusplus

#pragma endregion

#pragma region Myjson

#pragma region C

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#pragma region Json

#pragma endregion  // Json

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region Encoding

#pragma endregion  // Encoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

#ifdef __cplusplus
}
#endif  // __cplusplus

#pragma endregion  // C

#pragma region Cpp

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace myjson {

#pragma region Json

#pragma endregion  // Json

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region Encoding

#pragma endregion  // Encoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

}  // namespace myjson

#endif  //__cplusplus

#pragma endregion  // Cpp

#pragma endregion  // Myjson
