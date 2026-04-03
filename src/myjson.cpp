/**
 * @file myjson.cpp
 * @brief JSON For Modern C/C++.
 * @details All public API, types, macros, and configuration.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/myjson
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Developed by Sackey Ezekiel Etrue and every direct or indirect contributors to the GitHub.
 * See LICENSE for copyright and licensing details (standard MIT License).
 *
 * SECTIONS: Index of this file
 *
 *      Details: Details Namespace
 *
 *          [SECTION] Details : Encoding
 *          [SECTION] Details : Input
 *          [SECTION] Details : Output
 *          [SECTION] Details : Iterators
 *          [SECTION] Details : Conversions
 *          [SECTION] Details : Functions
 *
 *      Myjson: Myjson Namespace
 *
 *          [SECTION] Myjson : Classes
 *          [SECTION] Myjson : Functions
 *          [SECTION] Myjson : Exceptions
 *
 *      Literals: Literals Namespace
 *
 *          [SECTION] Literals : Json
 *
 * CONTRIBUTORS:
 *
 * TODO:
 *
 * HELP:
 *    - See links below.
 *    - Read top of myjson.hpp for more details and comments.
 *
 *  Has only had a few tests run, may have issues.
 *
 *  If having issues compiling/linking/running raise an issue (https://github.com/djoezeke/myjson/issues).
 *  Please post data https://github.com/djoezeke/myjson/discussions if you cannot find a solution data resources above.
 *
 * RESOURCES:
 * - Homepage ................... https://github.com/djoezeke/myjson
 * - Releases & changelog ....... https://github.com/djoezeke/myjson/releases
 * - Issues & support ........... https://github.com/djoezeke/myjson/issues
 *
 */

// clang-format off

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
    #define _CRT_SECURE_NO_WARNINGS
#endif

// clang-format on

//-------------------------------------------------------------------------
// [SECTION] INCLUDES
//-------------------------------------------------------------------------

#include "../include/myjson/myjson.hpp"

#ifdef MYJSON_IMPLEMENTATION

// #include <MYJSON_ASSERT.h>
// #include <ctype.h>
// #include <limits.h>
#include <stdarg.h>
// #include <stdbool.h>
#include <cmath>
#include <functional>
#include <iomanip>
#include <optional>
#include <sstream>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>  //
#include <stdlib.h> //
#include <string.h> //

//-------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

// clang-format off

/** Byte order marks. */

#ifndef MYJSON_BOM_UTF8
    #define MYJSON_BOM_UTF8 "\xef\xbb\xbf"
#endif // MYJSON_BOM_UTF8

#ifndef MYJSON_BOM_UTF16LE
    #define MYJSON_BOM_UTF16LE "\xff\xfe"
#endif // MYJSON_BOM_UTF16LE

#ifndef MYJSON_BOM_UTF16BE
    #define MYJSON_BOM_UTF16BE "\xfe\xff"
#endif // MYJSON_BOM_UTF16BE

#ifndef MYJSON_BOM_UTF32LE
    #define MYJSON_BOM_UTF32LE "\xff\xfe\x00\x00"
#endif // MYJSON_BOM_UTF32LE

#ifndef MYJSON_BOM_UTF32BE
    #define MYJSON_BOM_UTF32BE "\x00\x00\xfe\xff"
#endif // MYJSON_BOM_UTF32BE

// clang-format on

#pragma region Detail

namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    namespace detail
    {

        //-------------------------------------------------------------------------
        // [SECTION] Details : Encoding
        //-------------------------------------------------------------------------

        encoding determine_encoding(void *data, size_t size)
        {
            if (size >= 4 && !memcmp(data, MYJSON_BOM_UTF32BE, 4))
            {
                return encoding::utf32be;
            }
            if (size >= 4 && !memcmp(data, MYJSON_BOM_UTF32LE, 4))
            {
                return encoding::utf32le;
            }
            if (size >= 3 && !memcmp(data, MYJSON_BOM_UTF8, 3))
            {
                return encoding::utf8;
            }
            if (size >= 2 && !memcmp(data, MYJSON_BOM_UTF16BE, 2))
            {
                return encoding::utf16be;
            }
            if (size >= 2 && !memcmp(data, MYJSON_BOM_UTF16LE, 2))
            {
                return encoding::utf16le;
            }
            return encoding::unspecified;
        };

        /*
         * Decode a UTF-8 character.  Check RFC 3629
         * (https://datatracker.ietf.org/doc/html/rfc3629) for more details.
         *
         * The following table (taken from the RFC) is used for
         * decoding.
         *
         * The table below summarizes the format of these different octet types.
         * The letter x indicates bits available for encoding bits of the
         * character number.

         *    Char. number range |        UTF-8 octet sequence
         *      (hexadecimal)    |              (binary)
         *   --------------------+------------------------------------
         *   0000 0000-0000 007F | 0xxxxxxx
         *   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
         *   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
         *   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
         *
         * The definition of UTF-8 prohibits encoding character numbers between
         * U+D800 and U+DFFF, which are reserved for use with the UTF-16
         * encoding form (as surrogate pairs) and do not directly represent
         * characters. When encoding in UTF-8 from UTF-16 data, it is necessary
         * to first decode the UTF-16 data to obtain character numbers, which
         * are then encoded in UTF-8 as described above.
         *
         * (https://en.wikipedia.org/wiki/UTF-8)
         */

        int utf8::decode(const char *data, size_t size, unsigned int &value)
        {
            if (size == 0 || data == nullptr)
            {
                value = 0;
                return -1;
            }

            unsigned char byte = static_cast<unsigned char>(data[0]);
            if (byte < 0x80)
            {
                value = byte;
                return 1;
            }
            if ((byte & 0xE0) == 0xC0)
            {
                if (size < 2)
                {
                    value = 0;
                    return -1;
                }
                value = ((byte & 0x1F) << 6) | (static_cast<unsigned char>(data[1]) & 0x3F);
                return 2;
            }
            if ((byte & 0xF0) == 0xE0)
            {
                if (size < 3)
                {
                    value = 0;
                    return -1;
                }
                value = ((byte & 0x0F) << 12) | ((static_cast<unsigned char>(data[1]) & 0x3F) << 6) |
                        (static_cast<unsigned char>(data[2]) & 0x3F);
                return 3;
            }
            if ((byte & 0xF8) == 0xF0)
            {
                if (size < 4)
                {
                    value = 0;
                    return -1;
                }
                value = ((byte & 0x07) << 18) | ((static_cast<unsigned char>(data[1]) & 0x3F) << 12) |
                        ((static_cast<unsigned char>(data[2]) & 0x3F) << 6) |
                        (static_cast<unsigned char>(data[3]) & 0x3F);
                return 4;
            }
            value = 0;
            return -1;
        };

        int utf8::encode(unsigned int codepoint, utf8::char_t *output, size_t size)
        {
            if (size < 1)
            {
                return -1;
            }

            if (codepoint < 0x80)
            {
                output[0] = static_cast<char>(codepoint);
                return 1;
            }

            if (codepoint < 0x800)
            {
                if (size < 2)
                {
                    return -1;
                }
                output[0] = static_cast<char>((codepoint >> 6) | 0xC0);
                output[1] = static_cast<char>((codepoint & 0x3F) | 0x80);
                return 2;
            }

            if (codepoint < 0x10000)
            {
                if (size < 3)
                {
                    return -1;
                }
                output[0] = static_cast<char>((codepoint >> 12) | 0xE0);
                output[1] = static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80);
                output[2] = static_cast<char>((codepoint & 0x3F) | 0x80);
                return 3;
            }

            if (codepoint <= 0x10FFFF)
            {
                if (size < 4)
                {
                    return -1;
                }
                output[0] = static_cast<char>((codepoint >> 18) | 0xF0);
                output[1] = static_cast<char>(((codepoint >> 12) & 0x3F) | 0x80);
                output[2] = static_cast<char>(((codepoint >> 6) & 0x3F) | 0x80);
                output[3] = static_cast<char>((codepoint & 0x3F) | 0x80);
                return 4;
            }

            return -1;
        };

        std::vector<unsigned char> utf8::to_utf16(const std::string &string, myjson_endian_value_t order)
        {
            std::vector<unsigned char> out;
            size_t idx = 0;
            while (idx < string.size())
            {
                unsigned int cp = 0;
                int dec = utf8::decode(string.data() + idx, string.size() - idx, cp);
                MYJSON_ASSERT(dec > 0);
                char tmp[4];
                int enc = utf16::encode(cp, reinterpret_cast<utf16::char_t *>(tmp), sizeof(tmp), order);
                MYJSON_ASSERT(enc > 0);
                for (int i = 0; i < enc * 2; ++i)
                    out.push_back(static_cast<unsigned char>(tmp[i]));
                idx += static_cast<size_t>(dec);
            }
            return out;
        };

        std::vector<unsigned char> utf8::to_utf32(const std::string &string, myjson_endian_value_t order)
        {
            std::vector<unsigned char> out;
            size_t idx = 0;
            while (idx < string.size())
            {
                unsigned int cp = 0;
                int dec = utf8::decode(string.data() + idx, string.size() - idx, cp);
                MYJSON_ASSERT(dec > 0);
                char tmp[4];
                int enc = utf32::encode(cp, reinterpret_cast<utf32::char_t *>(tmp), sizeof(tmp), order);
                MYJSON_ASSERT(enc > 0);
                for (int i = 0; i < 4; ++i)
                    out.push_back(static_cast<unsigned char>(tmp[i]));
                idx += static_cast<size_t>(dec);
            }
            return out;
        };

        /*
         * Decode a UTF-16 character.  Check RFC 2781
         * (https://datatracker.ietf.org/doc/html/rfc2781).
         *
         * Normally, two subsequent bytes describe a Unicode
         * character.  However a special technique (called a
         * surrogate pair) is used for specifying character
         * values larger than 0xFFFF.
         *
         * A surrogate pair consists of two pseudo-characters:
         *      high surrogate area (0xD800-0xDBFF)
         *      low surrogate area (0xDC00-0xDFFF)
         *
         * The following formulas are used for decoding
         * and encoding characters using surrogate pairs:
         *
         *  U  = U' + 0x10000   (0x01 00 00 <= U <= 0x10 FF FF)
         *  U' = yyyyyyyyyyxxxxxxxxxx   (0 <= U' <= 0x0F FF FF)
         *  W1 = 110110yyyyyyyyyy
         *  W2 = 110111xxxxxxxxxx
         *
         * where U is the character value, W1 is the high surrogate
         * area, W2 is the low surrogate area.
         *
         * (https://en.wikipedia.org/wiki/UTF-16)
         *
         */

        int utf16::decode(const char *data, size_t size, unsigned int &value, myjson_endian_value_t order)
        {
            if (size < 2 || data == nullptr)
            {
                value = 0;
                return -1;
            }

            const unsigned char *b = reinterpret_cast<const unsigned char *>(data);

            auto read_u16 = [&](size_t offset) -> uint16_t
            {
                if (order == myjson_endian_t::native)
                {
                    uint16_t tmp = 0;
                    memcpy(&tmp, b + offset, 2);
                    return tmp;
                }
                else if (order == myjson_endian_t::little)
                {
                    return static_cast<uint16_t>(b[offset] | (b[offset + 1] << 8));
                }
                else // big-endian
                {
                    return static_cast<uint16_t>((b[offset] << 8) | b[offset + 1]);
                }
            };

            uint16_t w1 = read_u16(0);

            // Check for surrogate pair (high surrogate 0xD800-0xDBFF)
            if (w1 >= 0xD800 && w1 <= 0xDBFF)
            {
                if (size < 4)
                {
                    value = 0;
                    return -1;
                }
                uint16_t w2 = read_u16(2);
                if (!(w2 >= 0xDC00 && w2 <= 0xDFFF))
                {
                    value = 0;
                    return -1;
                }
                unsigned int high = static_cast<unsigned int>(w1);
                unsigned int low = static_cast<unsigned int>(w2);
                value = ((high - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
                return 4;
            }

            value = static_cast<unsigned int>(w1);
            return 2;
        };

        int utf16::encode(unsigned int codepoint, utf16::char_t *output, size_t size, myjson_endian_value_t order)
        {
            if (size < 2 || output == nullptr)
            {
                return -1;
            }

            unsigned char *out = reinterpret_cast<unsigned char *>(output);

            auto write_u16 = [&](size_t offset, uint16_t val)
            {
                if (order == myjson_endian_t::native)
                {
                    memcpy(out + offset, &val, 2);
                }
                else if (order == myjson_endian_t::little)
                {
                    out[offset] = static_cast<unsigned char>(val & 0xFF);
                    out[offset + 1] = static_cast<unsigned char>((val >> 8) & 0xFF);
                }
                else // big-endian
                {
                    out[offset] = static_cast<unsigned char>((val >> 8) & 0xFF);
                    out[offset + 1] = static_cast<unsigned char>(val & 0xFF);
                }
            };

            if (codepoint < 0x10000)
            {
                uint16_t val = static_cast<uint16_t>(codepoint);
                write_u16(0, val);
                return 1;
            }

            if (codepoint > 0x10FFFF)
            {
                return -1;
            }

            if (size < 4)
            {
                return -1;
            }

            unsigned int cp = codepoint - 0x10000;
            uint16_t w1 = static_cast<uint16_t>((cp >> 10) + 0xD800);
            uint16_t w2 = static_cast<uint16_t>((cp & 0x3FF) + 0xDC00);
            write_u16(0, w1);
            write_u16(2, w2);
            return 2;
        };

        std::string utf16::to_utf8(const std::vector<unsigned char> &bytes, myjson_endian_value_t order)
        {
            std::string out;
            size_t idx = 0;
            while (idx < bytes.size())
            {
                unsigned int cp = 0;
                int dec = utf16::decode(reinterpret_cast<const char *>(bytes.data() + idx), bytes.size() - idx, cp, order);
                MYJSON_ASSERT(dec > 0);
                char tmp[4];
                int enc = utf8::encode(cp, reinterpret_cast<utf8::char_t *>(tmp), sizeof(tmp));
                MYJSON_ASSERT(enc > 0);
                out.append(tmp, tmp + enc);
                idx += static_cast<size_t>(dec);
            }
            return out;
        };

        int utf32::decode(const char *data, size_t size, unsigned int &value, myjson_endian_value_t order)
        {
            if (size < 4 || data == nullptr)
            {
                value = 0;
                return -1;
            }

            const unsigned char *b = reinterpret_cast<const unsigned char *>(data);
            uint32_t tmp = 0;

            if (order == myjson_endian_t::native)
            {
                memcpy(&tmp, b, 4);
            }
            else if (order == myjson_endian_t::little)
            {
                tmp = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
            }
            else // big-endian
            {
                tmp = ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | (uint32_t)b[3];
            }

            value = static_cast<unsigned int>(tmp);
            return 4;
        };

        int utf32::encode(unsigned int codepoint, utf32::char_t *output, size_t size, myjson_endian_value_t order)
        {
            if (size < 4 || output == nullptr)
            {
                return -1;
            }

            uint32_t cp = static_cast<uint32_t>(codepoint);
            unsigned char *out = reinterpret_cast<unsigned char *>(output);

            if (order == myjson_endian_t::native)
            {
                memcpy(out, &cp, 4);
            }
            else if (order == myjson_endian_t::little)
            {
                out[0] = static_cast<unsigned char>(cp & 0xFF);
                out[1] = static_cast<unsigned char>((cp >> 8) & 0xFF);
                out[2] = static_cast<unsigned char>((cp >> 16) & 0xFF);
                out[3] = static_cast<unsigned char>((cp >> 24) & 0xFF);
            }
            else // big-endian
            {
                out[0] = static_cast<unsigned char>((cp >> 24) & 0xFF);
                out[1] = static_cast<unsigned char>((cp >> 16) & 0xFF);
                out[2] = static_cast<unsigned char>((cp >> 8) & 0xFF);
                out[3] = static_cast<unsigned char>(cp & 0xFF);
            }

            return 1;
        };

        std::string utf32::to_utf8(const std::vector<unsigned char> &bytes, myjson_endian_value_t order)
        {
            std::string out;
            size_t idx = 0;
            while (idx + 4 <= bytes.size())
            {
                unsigned int cp = 0;
                int dec = utf32::decode(reinterpret_cast<const char *>(bytes.data() + idx), bytes.size() - idx, cp, order);
                MYJSON_ASSERT(dec == 4);
                char tmp[4];
                int enc = utf8::encode(cp, reinterpret_cast<utf8::char_t *>(tmp), sizeof(tmp));
                MYJSON_ASSERT(enc > 0);
                out.append(tmp, tmp + enc);
                idx += 4;
            }
            return out;
        };

        //-------------------------------------------------------------------------
        // [SECTION] Details : Input
        //-------------------------------------------------------------------------

        //-----------------------------------------------------------------------------
        // [Class] file_iadapter
        //-----------------------------------------------------------------------------
        // - file_iadapter()
        // - read()
        //-----------------------------------------------------------------------------

        file_iadapter::file_iadapter(FILE *file)
            : m_file(file) {};

        size_t file_iadapter::read(void *data, size_t size)
        {
            if (m_file == nullptr || data == nullptr || size == 0)
            {
                return 0;
            }
            // fread returns number of elements read; using 1-byte elements.
            const size_t nsize = fread(data, 1, size, m_file);
            return nsize;
        };

#ifndef MYJSON_NO_STL

        //-----------------------------------------------------------------------------
        // [Class] stream_iadapter
        //-----------------------------------------------------------------------------
        // - stream_iadapter()
        // - read()
        //-----------------------------------------------------------------------------

        stream_iadapter::stream_iadapter(std::istream &stream)
            : m_stream(&stream) {};

        size_t stream_iadapter::read(void *data, size_t size)
        {
            if ((m_stream == nullptr) || (data == nullptr) || size == 0)
            {
                return 0;
            }
            // Read using istream::readsome when available to avoid blocking, but
            // fall back to read() which will block until requested size or EOF.
            std::istream &stream = *m_stream;
            stream.read(static_cast<char *>(data), static_cast<std::streamsize>(size));
            const std::streamsize got = stream.gcount();
            if (got < 0)
            {
                return 0;
            }
            return static_cast<size_t>(got);
        };

#endif // MYJSON_NO_STL

        //-----------------------------------------------------------------------------
        // [Class] memory_iadapter
        //-----------------------------------------------------------------------------
        // - memory_iadapter()
        // - read()
        //-----------------------------------------------------------------------------

        memory_iadapter::memory_iadapter(void *data, size_t size)
            : m_pos(0), m_size(size), m_data(data) {};

        size_t memory_iadapter::read(void *data, size_t size)
        {
            if ((data == nullptr) || size == 0 || m_data == nullptr)
            {
                return 0;
            }
            // remaining bytes
            if (m_pos >= m_size)
            {
                return 0;
            }
            const size_t remaining = m_size - m_pos;
            const size_t to_copy = (size < remaining) ? size : remaining;
            memcpy(data, static_cast<char *>(m_data) + m_pos, to_copy);
            m_pos += to_copy;
            return to_copy;
        };

        //-----------------------------------------------------------------------------
        // [Class] lexer
        //-----------------------------------------------------------------------------
        // - lexer()
        //-----------------------------------------------------------------------------

        lexer::lexer(iadapter *adapter)
            : m_position{}, m_token{}, m_string(), m_adapter(adapter), m_encoding(myjson::encoding::unspecified), m_putback(-1)
        {
            if (!m_adapter)
            {
                m_input_pos = 0;
                return;
            }

            // Read a small header to probe encoding (BOM detection)
            unsigned char header[4] = {0};
            size_t got_header = m_adapter->read(header, sizeof(header));
            if (got_header > 0)
            {
                m_encoding = determine_encoding(header, got_header);
            }

            // Read the rest of the adapter into a raw buffer. We already
            // consumed header bytes from the adapter by reading them above,
            // so append the remainder as well.
            std::vector<unsigned char> raw;
            // start with header bytes we read (they came from adapter)
            for (size_t i = 0; i < got_header; ++i)
                raw.push_back(header[i]);

            // Read until adapter returns 0
            while (true)
            {
                char buf[4096];
                size_t n = m_adapter->read(buf, sizeof(buf));
                if (n == 0)
                    break;
                raw.insert(raw.end(), reinterpret_cast<unsigned char *>(buf), reinterpret_cast<unsigned char *>(buf) + n);
            }

            // Strip BOM bytes if present and convert to UTF-8 when needed.
            // If encoding is unspecified, prefer UTF-8 semantics (no conversion).
            size_t skip = 0;
            switch (m_encoding)
            {
            case myjson::encoding::utf8:
                // UTF-8 BOM is 3 bytes
                if (raw.size() >= 3 && !memcmp(raw.data(), MYJSON_BOM_UTF8, 3))
                    skip = 3;
                break;
            case myjson::encoding::utf16le:
            case myjson::encoding::utf16be:
                // UTF-16 BOM is 2 bytes
                if (raw.size() >= 2 && (!memcmp(raw.data(), MYJSON_BOM_UTF16LE, 2) || !memcmp(raw.data(), MYJSON_BOM_UTF16BE, 2)))
                    skip = 2;
                break;
            case myjson::encoding::utf32le:
            case myjson::encoding::utf32be:
                // UTF-32 BOM is 4 bytes
                if (raw.size() >= 4 && (!memcmp(raw.data(), MYJSON_BOM_UTF32LE, 4) || !memcmp(raw.data(), MYJSON_BOM_UTF32BE, 4)))
                    skip = 4;
                break;
            default:
                break;
            }

            // Create a vector without BOM for conversion/consumption
            std::vector<unsigned char> payload;
            if (skip < raw.size())
                payload.insert(payload.end(), raw.begin() + skip, raw.end());

            // Convert to UTF-8 if necessary, otherwise copy bytes directly.
            if (m_encoding == myjson::encoding::utf16le || m_encoding == myjson::encoding::utf16be || m_encoding == myjson::encoding::utf16)
            {
                myjson_endian_value_t order = (m_encoding == myjson::encoding::utf16be) ? myjson_endian_t::big : myjson_endian_t::little;
                std::string utf8 = utf16::to_utf8(payload, order);
                m_input.assign(utf8.begin(), utf8.end());
            }
            else if (m_encoding == myjson::encoding::utf32le || m_encoding == myjson::encoding::utf32be || m_encoding == myjson::encoding::utf32)
            {
                myjson_endian_value_t order = (m_encoding == myjson::encoding::utf32be) ? myjson_endian_t::big : myjson_endian_t::little;
                std::string utf8 = utf32::to_utf8(payload, order);
                m_input.assign(utf8.begin(), utf8.end());
            }
            else
            {
                // Treat as UTF-8 or unspecified: copy bytes directly
                m_input.assign(reinterpret_cast<char *>(payload.data()), reinterpret_cast<char *>(payload.data()) + payload.size());
            }

            m_input_pos = 0;
        };

        token lexer::scan()
        {
            return next_token();
        };

        mark lexer::position() const
        {
            return m_position;
        };

        void lexer::advance(size_t amount)
        {
            while (amount-- > 0 && m_input_pos < m_input.size())
            {
                const char ch = m_input[m_input_pos++];
                ++m_position.index;
                if (ch == '\n')
                {
                    ++m_position.line;
                    m_position.column = 0;
                }
                else
                {
                    ++m_position.column;
                }
                m_char = static_cast<unsigned char>(ch);
            }
        };

        void lexer::reverse(size_t amount)
        {
            while (amount-- > 0 && m_input_pos > 0)
            {
                --m_input_pos;
                --m_position.index;
                const char ch = m_input[m_input_pos];
                if (ch == '\n')
                {
                    if (m_position.line > 0)
                        --m_position.line;
                    m_position.column = 0;
                }
                else if (m_position.column > 0)
                {
                    --m_position.column;
                }
                m_char = static_cast<unsigned char>(ch);
            }
        };

        bool lexer::scan_literal()
        {
            std::string string;
            if ((m_char >= 'a' && m_char <= 'z') || (m_char >= 'A' && m_char <= 'Z'))
            {
                // string.push_back(static_cast<char>(m_char));
                while (true)
                {
                    advance();
                    if (m_char == EOF)
                        break;
                    if ((m_char >= 'a' && m_char <= 'z') || (m_char >= 'A' && m_char <= 'Z'))
                    {
                        string.push_back(static_cast<char>(m_char));
                        continue;
                    }
                    reverse();
                    break;
                }
                if (string == "false")
                {
                    m_token.type = token_t::false_literal;
                    m_token.text = string;
                    return true;
                }
                if (string == "true")
                {
                    m_token.type = token_t::true_literal;
                    m_token.text = string;
                    return true;
                }
                if (string == "null")
                {
                    m_token.type = token_t::null_literal;
                    return true;
                }
            }
            return false;
        };

        bool lexer::scan_comment()
        {
            std::string string;
            switch (m_char)
            {
            case '/':
            {
                while (true)
                {
                    advance();
                    switch (m_char)
                    {
                    case '\n':
                    case '\r':
                    case '\0':
                        return true;
                    default:
                        break;
                    }
                }
            }

            case '*':
            {
                while (true)
                {
                    advance();
                    switch (m_char)
                    {
                    case '\0':
                    {
                        return false;
                    }

                    case '*':
                    {
                        advance();
                        switch (m_char)
                        {
                        case '/':
                            return true;
                        default:
                        {
                            reverse();
                            continue;
                        }
                        }
                    }
                    default:
                        continue;
                    }
                }
            }
            default:
            {
                return false;
            }
            }
        };

        bool lexer::scan_string()
        {
            std::string string;
            while (true)
            {
                advance();
                if (m_char == EOF)
                {
                    m_token.type = token_t::string_value;
                    return true;
                }
                if (m_char == '\\')
                {
                    advance();
                    if (m_char == EOF)
                        break;
                    string.push_back(static_cast<char>('\\'));
                    string.push_back(static_cast<char>(m_char));
                    continue;
                }
                if (m_char == '"')
                {
                    m_token.type = token_t::string_value;
                    m_token.text = string;
                    return true;
                }
                string.push_back(static_cast<char>(m_char));
            }
            return false;
        };

        bool lexer::scan_number()
        {
            std::string string;
            if ((m_char >= '0' && m_char <= '9') || m_char == '-')
            {
                string.push_back(static_cast<char>(m_char));
                while (true)
                {
                    advance();
                    if (m_char == EOF)
                        break;
                    if ((m_char >= '0' && m_char <= '9') || m_char == '+' || m_char == '-' || m_char == 'e' || m_char == 'E' || m_char == '.')
                    {
                        string.push_back(static_cast<char>(m_char));
                        continue;
                    }
                    reverse();
                    break;
                }
                m_token.type = token_t::number_value;
                m_token.text = string;
                return true;
            }
            return false;
        };

        [[nodiscard]] int lexer::get_char()
        {
            // return putback if available
            if (m_putback != -1)
            {
                int c = m_putback;
                m_putback = -1;
                return c;
            }

            // ensure input buffer has data; if empty, read more from adapter
            if (m_input_pos >= m_input.size())
            {
                if (!m_adapter)
                    return EOF;
                char buf[512];
                size_t n = m_adapter->read(buf, sizeof(buf));
                if (n == 0)
                    return EOF;
                m_input.append(buf, buf + n);
            }

            unsigned char c = static_cast<unsigned char>(m_input[m_input_pos++]);
            return static_cast<int>(c);
        }

        void lexer::unget_char()
        {
            // allow single-char putback
            if (m_input_pos > 0)
            {
                --m_input_pos;
            }
        }

        void lexer::add_char(int character)
        {
            m_string.push_back(static_cast<char>(character));
        }

        token lexer::get_token()
        {
            return m_token;
        }

        token_t lexer::get_type() const
        {
            return m_token.type;
        }

        // Helper: skip whitespace and return first non-space character (but
        // leave it buffered via putback semantics)
        int lexer::skip_ws()
        {
            int c;
            do
            {
                c = get_char();
                if (c == EOF)
                    return EOF;
            } while (c == ' ' || c == '\t' || c == '\n' || c == '\r');
            // put it back for caller
            unget_char();
            return c;
        }

        token lexer::next_token()
        {
            m_string.clear();
            m_token.text.clear();
            m_token.type = token_t::unknown;

            int c = skip_ws();
            if (c == EOF)
            {
                m_token.type = token_t::end_of_input;
                return m_token;
            }

            c = get_char();

            switch (c)
            {
            case '{':
                m_token.type = token_t::object_start;
                return m_token;
            case '}':
                m_token.type = token_t::object_end;
                return m_token;
            case '[':
                m_token.type = token_t::array_start;
                return m_token;
            case ']':
                m_token.type = token_t::array_end;
                return m_token;
            case ',':
                m_token.type = token_t::value_separator;
                return m_token;
            case ':':
                m_token.type = token_t::name_separator;
                return m_token;
            case '"':
            {
                // parse string
                while (true)
                {
                    int ch = get_char();
                    if (ch == EOF)
                    {
                        m_token.type = token_t::string_value;
                        return m_token;
                    }
                    if (ch == '\\')
                    {
                        int esc = get_char();
                        if (esc == EOF)
                            break;
                        // handle simple escapes; for brevity we append raw
                        // sequences; a complete implementation would decode
                        // unicode escapes.
                        add_char('\\');
                        add_char(esc);
                        continue;
                    }
                    if (ch == '"')
                    {
                        m_token.type = token_t::string_value;
                        m_token.text = m_string;
                        return m_token;
                    }
                    add_char(ch);
                }
                break;
            }
            default:
                break;
            }

            // numbers, literals (true,false,null)
            if ((c >= '0' && c <= '9') || c == '-')
            {
                // number
                m_string.push_back(static_cast<char>(c));
                while (true)
                {
                    int ch = get_char();
                    if (ch == EOF)
                        break;
                    if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == 'e' || ch == 'E' || ch == '.')
                    {
                        m_string.push_back(static_cast<char>(ch));
                        continue;
                    }
                    unget_char();
                    break;
                }
                m_token.type = token_t::number_value;
                m_token.text = m_string;
                return m_token;
            }

            // true, false, null
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                m_string.push_back(static_cast<char>(c));
                while (true)
                {
                    int ch = get_char();
                    if (ch == EOF)
                        break;
                    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                    {
                        m_string.push_back(static_cast<char>(ch));
                        continue;
                    }
                    unget_char();
                    break;
                }

                if (m_string == "false")
                {
                    m_token.type = token_t::false_literal;
                    m_token.text = m_string;
                    return m_token;
                }

                if (m_string == "true")
                {
                    m_token.type = token_t::true_literal;
                    m_token.text = m_string;
                    return m_token;
                }

                if (m_string == "null")
                {
                    m_token.type = token_t::null_literal;
                    return m_token;
                }
            }

            // unknown single char
            m_token.type = token_t::unknown;
            return m_token;
        }

        //-----------------------------------------------------------------------------
        // [Class] parser
        //-----------------------------------------------------------------------------

        namespace
        {
            static bool is_hex_digit(char ch)
            {
                return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
            }

            static unsigned int hex_value(char ch)
            {
                if (ch >= '0' && ch <= '9')
                {
                    return static_cast<unsigned int>(ch - '0');
                }
                if (ch >= 'a' && ch <= 'f')
                {
                    return static_cast<unsigned int>(10 + (ch - 'a'));
                }
                return static_cast<unsigned int>(10 + (ch - 'A'));
            }

            static unsigned int parse_u16_hex(const std::string &text, size_t index)
            {
                if (index + 4 > text.size())
                {
                    MYJSON_THROW(parse_error("Invalid unicode escape sequence"));
                }

                unsigned int value = 0;
                for (size_t i = 0; i < 4; ++i)
                {
                    const char ch = text[index + i];
                    if (!is_hex_digit(ch))
                    {
                        MYJSON_THROW(parse_error("Invalid unicode escape sequence"));
                    }
                    value = (value << 4U) | hex_value(ch);
                }
                return value;
            }

            static void append_utf8_codepoint(std::string &out, unsigned int cp)
            {
                char tmp[4] = {0, 0, 0, 0};
                const int encoded = utf8::encode(cp, reinterpret_cast<utf8::char_t *>(tmp), sizeof(tmp));
                if (encoded <= 0)
                {
                    MYJSON_THROW(parse_error("Invalid unicode codepoint"));
                }
                out.append(tmp, tmp + encoded);
            }
        } // namespace

        parser::parser(class lexer *lexer)
            : m_lexer(lexer), m_current{}
        {
            if (m_lexer == nullptr)
            {
                MYJSON_THROW(parse_error("Invalid parser state"));
            }
            advance();
        }

        void parser::advance()
        {
            m_current = m_lexer->next_token();
        }

        std::string parser::parse_string(const std::string &text)
        {
            std::string result;
            result.reserve(text.size());

            for (size_t i = 0; i < text.size(); ++i)
            {
                const char ch = text[i];
                if (ch != '\\')
                {
                    result.push_back(ch);
                    continue;
                }

                if (i + 1 >= text.size())
                {
                    MYJSON_THROW(parse_error("Invalid escape sequence"));
                }

                const char esc = text[++i];
                switch (esc)
                {
                case '"':
                    result.push_back('"');
                    break;
                case '\\':
                    result.push_back('\\');
                    break;
                case '/':
                    result.push_back('/');
                    break;
                case 'b':
                    result.push_back('\b');
                    break;
                case 'f':
                    result.push_back('\f');
                    break;
                case 'n':
                    result.push_back('\n');
                    break;
                case 'r':
                    result.push_back('\r');
                    break;
                case 't':
                    result.push_back('\t');
                    break;
                case 'u':
                {
                    unsigned int codepoint = parse_u16_hex(text, i + 1);
                    i += 4;

                    // Handle surrogate pair.
                    if (codepoint >= 0xD800 && codepoint <= 0xDBFF)
                    {
                        if (i + 2 >= text.size() || text[i + 1] != '\\' || text[i + 2] != 'u')
                        {
                            MYJSON_THROW(parse_error("Invalid unicode surrogate pair"));
                        }

                        unsigned int low = parse_u16_hex(text, i + 3);
                        if (low < 0xDC00 || low > 0xDFFF)
                        {
                            MYJSON_THROW(parse_error("Invalid unicode surrogate pair"));
                        }

                        codepoint = 0x10000 + (((codepoint - 0xD800) << 10U) | (low - 0xDC00));
                        i += 6;
                    }

                    append_utf8_codepoint(result, codepoint);
                    break;
                }
                default:
                    MYJSON_THROW(parse_error("Invalid escape sequence"));
                }
            }

            return result;
        }

        myjson::json parser::parse_number(const std::string &text)
        {
            MYJSON_TRY
            {
                const bool is_integer = (text.find('.') == std::string::npos) &&
                                        (text.find('e') == std::string::npos) &&
                                        (text.find('E') == std::string::npos);

                if (is_integer)
                {
                    return myjson::json(static_cast<myjson::json::integer_t>(std::stoll(text)));
                }
                return myjson::json(static_cast<myjson::json::number_t>(std::stod(text)));
            }
            MYJSON_CATCH(const std::exception &)
            {
                MYJSON_THROW(parse_error("Invalid number literal"));
            }
        }

        myjson::json parser::parse_array()
        {
            myjson::json array = myjson::json::array();

            // consume '['
            advance();
            if (m_current.type == token_t::array_end)
            {
                advance();
                return array;
            }

            while (true)
            {
                array.push_back(parse_value());

                if (m_current.type == token_t::value_separator)
                {
                    advance();
                    continue;
                }

                if (m_current.type == token_t::array_end)
                {
                    advance();
                    break;
                }

                MYJSON_THROW(parse_error("Expected ',' or ']' in array"));
            }

            return array;
        }

        myjson::json parser::parse_object()
        {
            myjson::json object = myjson::json::object();

            // consume '{'
            advance();
            if (m_current.type == token_t::object_end)
            {
                advance();
                return object;
            }

            while (true)
            {
                if (m_current.type != token_t::string_value)
                {
                    MYJSON_THROW(parse_error("Expected object key string"));
                }
                const std::string key = parse_string(m_current.text);

                // consume key
                advance();
                if (m_current.type != token_t::name_separator)
                {
                    MYJSON_THROW(parse_error("Expected ':' after object key"));
                }

                // consume ':'
                advance();
                object[key] = parse_value();

                if (m_current.type == token_t::value_separator)
                {
                    advance();
                    continue;
                }

                if (m_current.type == token_t::object_end)
                {
                    advance();
                    break;
                }

                MYJSON_THROW(parse_error("Expected ',' or '}' in object"));
            }

            return object;
        }

        myjson::json parser::parse_value()
        {
            switch (m_current.type)
            {
            case token_t::null_literal:
                advance();
                return myjson::json(nullptr);
            case token_t::true_literal:
                advance();
                return myjson::json(true);
            case token_t::false_literal:
                advance();
                return myjson::json(false);
            case token_t::number_value:
            {
                const std::string value = m_current.text;
                advance();
                return parse_number(value);
            }
            case token_t::string_value:
            {
                const std::string value = parse_string(m_current.text);
                advance();
                return myjson::json(value);
            }
            case token_t::array_start:
                return parse_array();
            case token_t::object_start:
                return parse_object();
            default:
                MYJSON_THROW(parse_error("Unexpected token while parsing value"));
            }
        }

        myjson::json parser::parse()
        {
            myjson::json value = parse_value();
            if (m_current.type != token_t::end_of_input)
            {
                MYJSON_THROW(parse_error("Unexpected trailing tokens"));
            }
            return value;
        }

        deserializer::deserializer(const json &value)
            : m_value(value)
        {
        }

        //-------------------------------------------------------------------------
        // [SECTION] Details : Output
        //-------------------------------------------------------------------------

        //-----------------------------------------------------------------------------
        // [Class] file_oadapter
        //-----------------------------------------------------------------------------
        // - file_oadapter()
        // - write()
        //-----------------------------------------------------------------------------

        file_oadapter::file_oadapter(FILE *file)
            : m_file(file) {};

        size_t file_oadapter::write(const void *data, size_t size)
        {
            if ((m_file == nullptr) || (data == nullptr) || size == 0)
            {
                return 0;
            }
            const size_t nsize = fwrite(data, 1, size, m_file);
            return nsize;
        };

#ifndef MYJSON_NO_STL

        //-----------------------------------------------------------------------------
        // [Class] stream_oadapter
        //-----------------------------------------------------------------------------
        // - stream_oadapter()
        // - write()
        //-----------------------------------------------------------------------------

        stream_oadapter::stream_oadapter(std::ostream &stream)
            : m_stream(&stream) {};

        size_t stream_oadapter::write(const void *data, size_t size)
        {
            if ((m_stream == nullptr) || (data == nullptr) || size == 0)
            {
                return 0;
            }
            std::ostream &stream = *m_stream;
            stream.write(static_cast<const char *>(data), static_cast<std::streamsize>(size));
            if (!stream.good())
            {
                return 0;
            }
            return size;
        };

#endif // MYJSON_NO_STL

        //-----------------------------------------------------------------------------
        // [Class] memory_oadapter
        //-----------------------------------------------------------------------------
        // - memory_oadapter()
        // - write()
        //-----------------------------------------------------------------------------

        memory_oadapter::memory_oadapter(void *data, size_t size)
            : m_pos(0), m_size(size), m_data(data) {};

        size_t memory_oadapter::write(const void *data, size_t size)
        {
            if ((data == nullptr) || size == 0 || m_data == nullptr)
            {
                return 0;
            }
            // remaining space
            if (m_pos >= m_size)
            {
                return 0;
            }
            const size_t remaining = m_size - m_pos;
            const size_t to_copy = (size < remaining) ? size : remaining;
            memcpy(static_cast<char *>(m_data) + m_pos, data, to_copy);
            m_pos += to_copy;
            return to_copy;
        };

        //-----------------------------------------------------------------------------
        // [Class] serializer
        //-----------------------------------------------------------------------------

        serializer::serializer(oadapter *adapter)
            : m_adapter(adapter)
        {
        }

        void serializer::write_raw(const char *text, size_t size)
        {
            if (size == 0)
            {
                return;
            }
            if (m_adapter == nullptr)
            {
                MYJSON_THROW(std::runtime_error("Invalid output adapter"));
            }
            const size_t written = m_adapter->write(text, size);
            if (written != size)
            {
                MYJSON_THROW(std::runtime_error("Failed to write serialized output"));
            }
        }

        void serializer::write_raw(const std::string &text)
        {
            write_raw(text.data(), text.size());
        }

        void serializer::write_indent(int level, int indent)
        {
            if (indent <= 0)
            {
                return;
            }
            write_raw("\n", 1);
            const std::string spaces(static_cast<size_t>(level * indent), ' ');
            write_raw(spaces);
        }

        void serializer::write_escaped(const std::string &text)
        {
            write_raw("\"", 1);
            for (unsigned char ch : text)
            {
                switch (ch)
                {
                case '"':
                    write_raw("\\\"", 2);
                    break;
                case '\\':
                    write_raw("\\\\", 2);
                    break;
                case '\b':
                    write_raw("\\b", 2);
                    break;
                case '\f':
                    write_raw("\\f", 2);
                    break;
                case '\n':
                    write_raw("\\n", 2);
                    break;
                case '\r':
                    write_raw("\\r", 2);
                    break;
                case '\t':
                    write_raw("\\t", 2);
                    break;
                default:
                {
                    if (ch < 0x20)
                    {
                        char escaped[7];
                        snprintf(escaped, sizeof(escaped), "\\u%04x", static_cast<unsigned int>(ch));
                        write_raw(escaped, 6);
                    }
                    else
                    {
                        write_raw(reinterpret_cast<const char *>(&ch), 1);
                    }
                    break;
                }
                }
            }
            write_raw("\"", 1);
        }

        void serializer::write_value(const myjson::json &value, int indent, int level)
        {
            switch (value.type())
            {
            case value_type::null:
                write_raw("null", 4);
                return;
            case value_type::boolean:
                write_raw(value.as_bool() ? "true" : "false", value.as_bool() ? 4 : 5);
                return;
            case value_type::integer:
                write_raw(std::to_string(value.as_integer()));
                return;
            case value_type::number:
            {
                const auto number = value.as_number();
                if (std::isnan(number) || std::isinf(number))
                {
                    write_raw("null", 4);
                    return;
                }
                std::ostringstream oss;
                oss << std::setprecision(15) << number;
                write_raw(oss.str());
                return;
            }
            case value_type::string:
                write_escaped(value.as_string());
                return;
            case value_type::array:
            {
                write_raw("[", 1);
                const auto values = value.values();
                for (size_t index = 0; index < values.size(); ++index)
                {
                    if (index != 0)
                    {
                        write_raw(",", 1);
                    }
                    if (indent > 0)
                    {
                        write_indent(level + 1, indent);
                    }
                    write_value(values[index], indent, level + 1);
                }
                if (indent > 0 && !values.empty())
                {
                    write_indent(level, indent);
                }
                write_raw("]", 1);
                return;
            }
            case value_type::object:
            {
                write_raw("{", 1);
                size_t index = 0;
                for (auto iter = value.begin(); iter != value.end(); ++iter, ++index)
                {
                    if (index != 0)
                    {
                        write_raw(",", 1);
                    }
                    if (indent > 0)
                    {
                        write_indent(level + 1, indent);
                    }
                    write_escaped(iter->first);
                    write_raw(":", 1);
                    if (indent > 0)
                    {
                        write_raw(" ", 1);
                    }
                    write_value(iter->second, indent, level + 1);
                }
                if (indent > 0 && value.size() > 0)
                {
                    write_indent(level, indent);
                }
                write_raw("}", 1);
                return;
            }
            }
        }

        void serializer::serialize(const myjson::json &value, int indent)
        {
            write_value(value, indent, 0);
        }

        //-------------------------------------------------------------------------
        // [SECTION] Details : Iterators
        //-------------------------------------------------------------------------

        //-------------------------------------------------------------------------
        // [SECTION] Details : Conversions
        //-------------------------------------------------------------------------

        //-----------------------------------------------------------------------------
        // [SECTION] Details : Functions
        //-----------------------------------------------------------------------------

        const char *string(mark type) { return ""; };

        const char *string(event type) { return ""; };

        const char *string(token type) { return ""; };

#ifndef MYJSON_NO_STL

        std::ostream &operator<<(std::ostream &ostream, const token_t &type)
        {
            switch (type)
            {
            default:
                ostream << "unknown";
            }
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const error_t &type)
        {
            switch (type)
            {
            default:
                ostream << "unknown";
            }
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const event_t &type)
        {
            switch (type)
            {
            default:
                ostream << "unknown";
            }
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const value_t &type)
        {
            switch (type)
            {
            default:
                ostream << "unknown";
            }
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const break_t &type)
        {
            switch (type)
            {
            case break_t::cr:
                ostream << "cr";
            case break_t::ln:
                ostream << "ln";
            case break_t::crln:
                ostream << "crln";
            default:
                ostream << "any";
            }
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const mark &type)
        {
            ostream << string(type);
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const event &type)
        {
            ostream << string(type);
            return ostream;
        };

        std::ostream &operator<<(std::ostream &ostream, const token &type)
        {
            ostream << string(type);
            return ostream;
        };

#endif // MYJSON_NO_STL

    }; // namespace detail

    MYJSON_VERSION_NAMESPACE_END
}; // namespace myjson

#pragma endregion // Detail

#pragma region Myjson

namespace myjson
{
    MYJSON_VERSION_NAMESPACE_BEGIN

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Classes
    //-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    // [Class] json
    //-----------------------------------------------------------------------------

    //========== Constructors ==========

    json::json() noexcept
        : m_value(nullptr)
    {
    }

    json::json(std::nullptr_t) noexcept
        : m_value(nullptr)
    {
    }

    json::json(bool value) noexcept
        : m_value(value)
    {
    }

    json::json(int value) noexcept
        : m_value(static_cast<integer_t>(value))
    {
    }

    json::json(integer_t value) noexcept
        : m_value(value)
    {
    }

    json::json(number_t value) noexcept
        : m_value(value)
    {
    }

    json::json(const string_t &value)
        : m_value(value)
    {
    }

    json::json(const char *value)
        : m_value(string_t(value != nullptr ? value : ""))
    {
    }

    json::json(const array_t &value)
        : m_value(value)
    {
    }

    json::json(const object_t &value)
        : m_value(value)
    {
    }

    json json::object()
    {
        json j;
        j.m_value = object_t();
        return j;
    }

    json json::array()
    {
        json j;
        j.m_value = array_t();
        return j;
    }

    //========== Destructor and Assignment ==========

    json::~json() noexcept = default;
    json::json(const json &other) = default;
    json::json(json &&other) noexcept = default;
    json &json::operator=(const json &other) = default;
    json &json::operator=(json &&other) noexcept = default;

    json &json::operator=(std::nullptr_t) noexcept
    {
        m_value = nullptr;
        return *this;
    }

    json &json::operator=(bool value) noexcept
    {
        m_value = value;
        return *this;
    }

    json &json::operator=(int value) noexcept
    {
        m_value = static_cast<integer_t>(value);
        return *this;
    }

    json &json::operator=(integer_t value) noexcept
    {
        m_value = value;
        return *this;
    }

    json &json::operator=(number_t value) noexcept
    {
        m_value = value;
        return *this;
    }

    json &json::operator=(const string_t &value)
    {
        m_value = value;
        return *this;
    }

    json &json::operator=(const char *value)
    {
        m_value = string_t(value != nullptr ? value : "");
        return *this;
    }

    json &json::operator=(const array_t &value)
    {
        m_value = value;
        return *this;
    }

    json &json::operator=(const object_t &value)
    {
        m_value = value;
        return *this;
    }

    //========== Type Information ==========

    value_type json::type() const noexcept
    {
        switch (m_value.index())
        {
        case 0:
            return value_type::null;
        case 1:
            return value_type::boolean;
        case 2:
            return value_type::integer;
        case 3:
            return value_type::number;
        case 4:
            return value_type::string;
        case 5:
            return value_type::array;
        case 6:
            return value_type::object;
        default:
            return value_type::null;
        }
    }

    bool json::is_null() const noexcept { return std::holds_alternative<null_t>(m_value); }
    bool json::is_object() const noexcept { return std::holds_alternative<object_t>(m_value); }
    bool json::is_array() const noexcept { return std::holds_alternative<array_t>(m_value); }
    bool json::is_string() const noexcept { return std::holds_alternative<string_t>(m_value); }
    bool json::is_number() const noexcept
    {
        return std::holds_alternative<number_t>(m_value) || std::holds_alternative<integer_t>(m_value);
    }
    bool json::is_integer() const noexcept { return std::holds_alternative<integer_t>(m_value); }
    bool json::is_boolean() const noexcept { return std::holds_alternative<boolean_t>(m_value); }
    bool json::is_primitive() const noexcept { return !is_array() && !is_object(); }
    bool json::is_structured() const noexcept { return is_array() || is_object(); }

    //========== Type Conversions ==========

    template <>
    bool json::get<bool>(const bool &default_value) const noexcept
    {
        if (is_boolean())
            return std::get<boolean_t>(m_value);
        if (is_integer())
            return std::get<integer_t>(m_value) != 0;
        if (is_number())
            return std::get<number_t>(m_value) != 0.0;
        return default_value;
    }

    template <>
    json::integer_t json::get<json::integer_t>(const integer_t &default_value) const noexcept
    {
        if (is_integer())
            return std::get<integer_t>(m_value);
        if (is_boolean())
            return std::get<boolean_t>(m_value) ? 1 : 0;
        if (is_number())
            return static_cast<integer_t>(std::get<number_t>(m_value));
        return default_value;
    }

    template <>
    int json::get<int>(const int &default_value) const noexcept
    {
        return static_cast<int>(get<integer_t>(static_cast<integer_t>(default_value)));
    }

    template <>
    json::number_t json::get<json::number_t>(const number_t &default_value) const noexcept
    {
        if (is_number())
            return std::get<number_t>(m_value);
        if (is_integer())
            return static_cast<number_t>(std::get<integer_t>(m_value));
        if (is_boolean())
            return std::get<boolean_t>(m_value) ? 1.0 : 0.0;
        return default_value;
    }

    template <>
    std::string json::get<std::string>(const std::string &default_value) const noexcept
    {
        if (is_string())
            return std::get<string_t>(m_value);
        if (is_null())
            return "null";
        if (is_boolean())
            return std::get<boolean_t>(m_value) ? "true" : "false";
        if (is_integer())
            return std::to_string(std::get<integer_t>(m_value));
        if (is_number())
        {
            auto num = std::get<number_t>(m_value);
            if (std::isnan(num))
                return "NaN";
            if (std::isinf(num))
                return num > 0 ? "Infinity" : "-Infinity";
            return std::to_string(num);
        }
        return default_value;
    }

    template <typename T>
    T json::get(const T &default_value) const noexcept
    {
        return default_value;
    }

    template <typename T>
    T json::get_safe() const
    {
        return get<T>(T{});
    }

    template <>
    int json::get_safe<int>() const
    {
        return get<int>(0);
    }

    bool json::as_bool() const noexcept { return get<bool>(false); }
    json::integer_t json::as_integer() const noexcept { return get<integer_t>(0); }
    json::number_t json::as_number() const noexcept { return get<number_t>(0.0); }
    json::string_t json::as_string() const noexcept { return get<std::string>(std::string()); }

    //========== Helper Methods ==========

    void json::ensure_object()
    {
        if (!is_object())
            m_value = object_t();
    }

    void json::ensure_array()
    {
        if (!is_array())
            m_value = array_t();
    }

    const json::object_t &json::get_object() const
    {
        if (!is_object())
            MYJSON_THROW(std::runtime_error("Cannot access as object"));
        return std::get<object_t>(m_value);
    }

    const json::array_t &json::get_array() const
    {
        if (!is_array())
            MYJSON_THROW(std::runtime_error("Cannot access as array"));
        return std::get<array_t>(m_value);
    }

    json::object_t &json::get_object()
    {
        if (!is_object())
            MYJSON_THROW(std::runtime_error("Cannot access as object"));
        return std::get<object_t>(m_value);
    }

    json::array_t &json::get_array()
    {
        if (!is_array())
            MYJSON_THROW(std::runtime_error("Cannot access as array"));
        return std::get<array_t>(m_value);
    }

    //========== Container Access (Objects) ==========

    json &json::at(const std::string &key) { return get_object().at(key); }
    const json &json::at(const std::string &key) const { return get_object().at(key); }

    json &json::operator[](const std::string &key)
    {
        ensure_object();
        return get_object()[key];
    }

    json json::operator[](const std::string &key) const
    {
        if (!is_object())
            return json();
        auto &obj = get_object();
        auto it = obj.find(key);
        return it != obj.end() ? it->second : json();
    }

    json &json::operator[](const char *key) { return operator[](std::string(key)); }
    json json::operator[](const char *key) const { return operator[](std::string(key)); }

    bool json::contains(const std::string &key) const noexcept
    {
        if (!is_object())
            return false;
        return get_object().find(key) != get_object().end();
    }

    size_t json::count(const std::string &key) const noexcept
    {
        if (!is_object())
            return 0;
        return get_object().count(key);
    }

    size_t json::erase(const std::string &key) noexcept
    {
        if (!is_object())
            return 0;
        return get_object().erase(key);
    }

    //========== Container Access (Arrays) ==========

    json &json::at(size_t index) { return get_array().at(index); }
    const json &json::at(size_t index) const { return get_array().at(index); }

    json &json::operator[](size_t index)
    {
        ensure_array();
        auto &arr = get_array();
        if (index >= arr.size())
            arr.resize(index + 1);
        return arr[index];
    }

    const json &json::operator[](size_t index) const { return get_array().at(index); }

    json &json::front() { return get_array().front(); }
    const json &json::front() const { return get_array().front(); }
    json &json::back() { return get_array().back(); }
    const json &json::back() const { return get_array().back(); }

    void json::push_back(const json &value)
    {
        ensure_array();
        get_array().push_back(value);
    }

    void json::push_back(json &&value)
    {
        ensure_array();
        get_array().push_back(std::move(value));
    }

    void json::push_back(bool value)
    {
        ensure_array();
        get_array().push_back(json(value));
    }

    void json::push_front(const json &value)
    {
        ensure_array();
        get_array().insert(get_array().begin(), value);
    }

    json::array_iterator json::insert(const array_const_iterator &pos, const json &value)
    {
        ensure_array();
        return get_array().insert(pos, value);
    }

    json::array_iterator json::insert(const array_const_iterator &pos, json &&value)
    {
        ensure_array();
        return get_array().insert(pos, std::move(value));
    }

    json::array_iterator json::erase(array_const_iterator pos) { return get_array().erase(pos); }
    json::array_iterator json::erase(array_const_iterator first, array_const_iterator last)
    {
        return get_array().erase(first, last);
    }

    //========== Size and Capacity ==========

    size_t json::size() const noexcept
    {
        if (is_object())
            return get_object().size();
        if (is_array())
            return get_array().size();
        return 0;
    }

    bool json::empty() const noexcept { return size() == 0; }

    void json::clear() noexcept
    {
        if (is_object())
            get_object().clear();
        else if (is_array())
            get_array().clear();
    }

    //========== Iteration ==========

    json::iterator json::begin() { return get_object().begin(); }
    json::const_iterator json::begin() const { return get_object().begin(); }
    json::const_iterator json::cbegin() const { return get_object().cbegin(); }
    json::iterator json::end() { return get_object().end(); }
    json::const_iterator json::end() const { return get_object().end(); }
    json::const_iterator json::cend() const { return get_object().cend(); }
    json::reverse_iterator json::rbegin() { return get_object().rbegin(); }
    json::const_reverse_iterator json::rbegin() const { return get_object().rbegin(); }
    json::reverse_iterator json::rend() { return get_object().rend(); }
    json::const_reverse_iterator json::rend() const { return get_object().rend(); }
    json::array_iterator json::array_begin() { return get_array().begin(); }
    json::array_const_iterator json::array_begin() const { return get_array().begin(); }
    json::array_iterator json::array_end() { return get_array().end(); }
    json::array_const_iterator json::array_end() const { return get_array().end(); }

    //========== Comparison ==========

    bool json::operator==(const json &other) const noexcept { return m_value == other.m_value; }
    bool json::operator!=(const json &other) const noexcept { return !(*this == other); }
    bool json::operator<(const json &other) const noexcept
    {
        if (type() != other.type())
            return static_cast<uint8_t>(type()) < static_cast<uint8_t>(other.type());

        switch (type())
        {
        case value_type::null:
            return false;
        case value_type::boolean:
            return as_bool() < other.as_bool();
        case value_type::integer:
            return as_integer() < other.as_integer();
        case value_type::number:
            return as_number() < other.as_number();
        case value_type::string:
            return as_string() < other.as_string();
        case value_type::array:
            return get_array() < other.get_array();
        case value_type::object:
            return get_object() < other.get_object();
        }

        return false;
    }
    bool json::operator<=(const json &other) const noexcept { return (*this < other) || (*this == other); }
    bool json::operator>(const json &other) const noexcept { return other < *this; }
    bool json::operator>=(const json &other) const noexcept { return !(*this < other); }

    //========== Serialization ==========

    std::string json::dump(int indent) const
    {
        std::ostringstream stream;
        detail::stream_oadapter adapter(stream);
        detail::serializer output(&adapter);
        output.serialize(*this, indent);
        return stream.str();
    }

    std::string json::dump_pretty() const { return dump(2); }
    std::string json::dump_compact() const { return dump(-1); }

    //========== Parsing ==========

    json json::parse(const std::string &str)
    {
        detail::memory_iadapter adapter(const_cast<char *>(str.data()), str.size());
        return parse(adapter);
    }

    json json::parse(const char *str)
    {
        if (str == nullptr)
            MYJSON_THROW(parse_error("Null pointer passed to parse"));

        detail::memory_iadapter adapter(const_cast<char *>(str), strlen(str));
        return parse(adapter);
    }

    json json::parse(FILE *file)
    {
        if (file == nullptr)
            MYJSON_THROW(parse_error("Null file pointer passed to parse"));

        detail::file_iadapter adapter(file);
        return parse(adapter);
    }

#ifndef MYJSON_NO_STL
    json json::parse(std::istream &stream)
    {
        detail::stream_iadapter adapter(stream);
        return parse(adapter);
    }
#endif // MYJSON_NO_STL

    json json::parse(detail::iadapter &adapter)
    {
        detail::lexer lex(&adapter);
        detail::parser parser(&lex);
        return parser.parse();
    }

    std::optional<json> json::try_parse(const std::string &str) noexcept
    {
        MYJSON_TRY { return parse(str); }
        MYJSON_CATCH(const std::exception &) { return std::nullopt; }
    }

    //========== JSON Pointer (RFC 6901) ==========

    json &json::at_pointer(const std::string &pointer)
    {
        if (pointer.empty() || pointer[0] != '/')
            MYJSON_THROW(std::invalid_argument("JSON Pointer must be empty or start with /"));

        return json_pointer(pointer).ref(*this);
    }

    const json &json::at_pointer(const std::string &pointer) const
    {
        return const_cast<json *>(this)->at_pointer(pointer);
    }

    std::optional<json *> json::find_pointer(const std::string &pointer) noexcept
    {
        MYJSON_TRY { return std::optional<json *>(&at_pointer(pointer)); }
        MYJSON_CATCH(const std::exception &) { return std::nullopt; }
    }

    std::optional<const json *> json::find_pointer(const std::string &pointer) const noexcept
    {
        MYJSON_TRY { return std::optional<const json *>(&at_pointer(pointer)); }
        MYJSON_CATCH(const std::exception &) { return std::nullopt; }
    }

    std::string json::pointer_to(const json &value) const { return ""; }

    //========== JSON Patch (RFC 6902) ==========

    json json::apply_patch(const json &patch) const
    {
        return json_patch(patch).apply(*this);
    }

    json json::generate_patch(const json &source, const json &target)
    {
        return diff(source, target);
    }

    //========== JSON Merge Patch (RFC 7386) ==========

    json json::apply_merge_patch(const json &patch) const
    {
        return json_merge_patch(patch).apply(*this);
    }

    //========== Utility ==========

    json json::clone() const { return json(*this); }

    void json::merge(const json &other)
    {
        if (!other.is_object())
            return;
        ensure_object();
        auto &self_obj = get_object();
        const auto &other_obj = other.get_object();
        for (const auto &[key, value] : other_obj)
        {
            if (self_obj.find(key) == self_obj.end())
                self_obj[key] = value;
        }
    }

    std::vector<std::string> json::keys() const
    {
        std::vector<std::string> result;
        if (is_object())
        {
            for (const auto &[key, _] : get_object())
                result.push_back(key);
        }
        return result;
    }

    std::vector<json> json::values() const
    {
        std::vector<json> result;
        if (is_array())
            result = get_array();
        else if (is_object())
        {
            for (const auto &[_, value] : get_object())
                result.push_back(value);
        }
        return result;
    }

    template <typename Visitor>
    auto json::apply_visitor(Visitor &&vis)
    {
        return std::visit(std::forward<Visitor>(vis), m_value);
    }

    //-----------------------------------------------------------------------------
    // [Class] json_patch
    //-----------------------------------------------------------------------------

    //========== JSON Patch Implementation (RFC 6902) ==========

    json_patch::json_patch(const json &patch_json)
        : m_operations(patch_json)
    {
        if (!m_operations.is_array())
            MYJSON_THROW(std::invalid_argument("JSON Patch must be an array"));
    }

    const json &json_patch::operations() const { return m_operations; }
    size_t json_patch::size() const { return m_operations.size(); }
    bool json_patch::empty() const { return m_operations.empty(); }

    json json_patch::apply(const json &document) const
    {
        json result = document.clone();
        apply_inplace(result);
        return result;
    }

    void json_patch::apply_inplace(json &document) const
    {
        MYJSON_TRY
        {
            for (size_t i = 0; i < m_operations.size(); ++i)
                apply_operation(m_operations[i], document);
        }
        MYJSON_CATCH(const std::exception &e)
        {
            MYJSON_THROW(std::runtime_error(std::string("Patch application failed: ") + e.what()));
        }
    }

    json_patch::operation_t json_patch::get_operation_type(const json &op)
    {
        std::string op_str = op["op"].as_string();
        if (op_str == "add")
            return json_patch::operation_t::add;
        if (op_str == "remove")
            return json_patch::operation_t::remove;
        if (op_str == "replace")
            return json_patch::operation_t::replace;
        if (op_str == "move")
            return json_patch::operation_t::move;
        if (op_str == "copy")
            return json_patch::operation_t::copy;
        if (op_str == "test")
            return json_patch::operation_t::test;
        MYJSON_THROW(std::invalid_argument("Unknown patch operation: " + op_str));
    }

    void json_patch::apply_operation(const json &op, json &document) const
    {
        if (!op.is_object() || !op.contains("op"))
            MYJSON_THROW(std::invalid_argument("Invalid patch operation"));

        auto op_type = get_operation_type(op);

        switch (op_type)
        {
        case operation_t::add:
        case operation_t::replace:
            if (!op.contains("value"))
                MYJSON_THROW(std::invalid_argument("Missing value in operation"));
            document.at_pointer(op["path"].as_string()) = op["value"];
            break;

        case operation_t::remove:
        {
            std::string path = op["path"].as_string();
            json_pointer ptr(path);
            if (!ptr.is_root())
            {
                auto parent = ptr.parent();
                std::string key = ptr.back();
                auto &p = parent.ref(document);
                if (p.is_object())
                    p.erase(key);
                else if (p.is_array())
                {
                    MYJSON_TRY
                    {
                        p.erase(p.array_begin() + std::stoul(key));
                    }
                    MYJSON_CATCH(...)
                    {
                        MYJSON_THROW(std::runtime_error("Invalid array index"));
                    }
                }
            }
            break;
        }

        case operation_t::move:
        case operation_t::copy:
        {
            if (!op.contains("from"))
                MYJSON_THROW(std::invalid_argument("Missing from in operation"));
            json value = document.at_pointer(op["from"].as_string());
            document.at_pointer(op["path"].as_string()) = value;
            if (op_type == operation_t::move)
            {
                std::string from = op["from"].as_string();
                json_pointer ptr(from);
                if (!ptr.is_root())
                {
                    auto parent = ptr.parent();
                    std::string key = ptr.back();
                    auto &p = parent.ref(document);
                    if (p.is_object())
                        p.erase(key);
                    else if (p.is_array())
                    {
                        MYJSON_TRY
                        {
                            p.erase(p.array_begin() + std::stoul(key));
                        }
                        MYJSON_CATCH(...)
                        {
                        }
                    }
                }
            }
            break;
        }

        case operation_t::test:
            if (!op.contains("value"))
                MYJSON_THROW(std::invalid_argument("Missing value in test"));
            if (!(document.at_pointer(op["path"].as_string()) == op["value"]))
                MYJSON_THROW(std::runtime_error("Test operation failed"));
            break;
        }
    }

    json json_patch::add_operation(const std::string &path, const json &value)
    {
        json op = json::object();
        op["op"] = "add";
        op["path"] = path;
        op["value"] = value;
        return op;
    }

    json json_patch::remove_operation(const std::string &path)
    {
        json op = json::object();
        op["op"] = "remove";
        op["path"] = path;
        return op;
    }

    json json_patch::replace_operation(const std::string &path, const json &value)
    {
        json op = json::object();
        op["op"] = "replace";
        op["path"] = path;
        op["value"] = value;
        return op;
    }

    json json_patch::move_operation(const std::string &from_path, const std::string &to_path)
    {
        json op = json::object();
        op["op"] = "move";
        op["from"] = from_path;
        op["path"] = to_path;
        return op;
    }

    json json_patch::copy_operation(const std::string &from_path, const std::string &to_path)
    {
        json op = json::object();
        op["op"] = "copy";
        op["from"] = from_path;
        op["path"] = to_path;
        return op;
    }

    json json_patch::test_operation(const std::string &path, const json &value)
    {
        json op = json::object();
        op["op"] = "test";
        op["path"] = path;
        op["value"] = value;
        return op;
    }

    //-----------------------------------------------------------------------------
    // [Class] json_pointer
    //-----------------------------------------------------------------------------

    //========== JSON Pointer Implementation (RFC 6901) ==========

    json_pointer::json_pointer(const std::string &pointer_str)
        : m_original(pointer_str)
    {
        if (!pointer_str.empty() && pointer_str != "/")
            parse(pointer_str);
    }

    void json_pointer::parse(const std::string &pointer_str)
    {
        if (pointer_str.empty() || pointer_str == "/")
            return;
        if (pointer_str[0] != '/')
            MYJSON_THROW(std::invalid_argument("JSON Pointer must start with '/'"));

        std::istringstream iss(pointer_str.substr(1));
        std::string token;
        while (std::getline(iss, token, '/'))
            m_tokens.push_back(unescape(token));
    }

    std::string json_pointer::unescape(const std::string &token)
    {
        std::string result = token;
        size_t pos = 0;
        while ((pos = result.find("~1", pos)) != std::string::npos)
        {
            result.replace(pos, 2, "/");
            ++pos;
        }
        pos = 0;
        while ((pos = result.find("~0", pos)) != std::string::npos)
        {
            result.replace(pos, 2, "~");
            ++pos;
        }
        return result;
    }

    std::string json_pointer::escape(const std::string &token)
    {
        std::string result = token;
        size_t pos = 0;
        while ((pos = result.find('~', pos)) != std::string::npos)
        {
            result.replace(pos, 1, "~0");
            pos += 2;
        }
        pos = 0;
        while ((pos = result.find('/', pos)) != std::string::npos)
        {
            result.replace(pos, 1, "~1");
            pos += 2;
        }
        return result;
    }

    std::string json_pointer::to_string() const { return m_original; }
    const std::vector<std::string> &json_pointer::tokens() const { return m_tokens; }
    size_t json_pointer::depth() const { return m_tokens.size(); }
    bool json_pointer::is_root() const { return m_tokens.empty(); }

    std::string json_pointer::back() const
    {
        return m_tokens.empty() ? "" : m_tokens.back();
    }

    json_pointer json_pointer::parent() const
    {
        if (m_tokens.empty())
            return json_pointer("");
        json_pointer p("");
        p.m_tokens.assign(m_tokens.begin(), m_tokens.end() - 1);
        std::string parent_str = "";
        for (size_t i = 0; i < p.m_tokens.size(); ++i)
        {
            parent_str += "/" + escape(p.m_tokens[i]);
        }
        p.m_original = parent_str.empty() ? "/" : parent_str;
        return p;
    }

    json_pointer json_pointer::push(const std::string &token) const
    {
        json_pointer p = *this;
        p.m_tokens.push_back(token);
        p.m_original += "/" + escape(token);
        return p;
    }

    json &json_pointer::ref(json &document)
    {
        json *current = &document;
        for (const auto &token : m_tokens)
        {
            if (current->is_array())
            {
                MYJSON_TRY
                {
                    size_t index = std::stoul(token);
                    current = &current->at(index);
                }
                MYJSON_CATCH(...)
                {
                    MYJSON_THROW(std::out_of_range("Invalid array index"));
                }
            }
            else if (current->is_object())
            {
                current = &current->at(token);
            }
            else
            {
                MYJSON_THROW(std::invalid_argument("Cannot traverse non-container"));
            }
        }
        return *current;
    }

    const json &json_pointer::ref(const json &document) const
    {
        return const_cast<json_pointer *>(this)->ref(const_cast<json &>(document));
    }

    std::optional<json *> json_pointer::try_ref(json &document) noexcept
    {
        MYJSON_TRY { return std::optional<json *>(&ref(document)); }
        MYJSON_CATCH(const std::exception &) { return std::nullopt; }
    }

    std::optional<const json *> json_pointer::try_ref(const json &document) const noexcept
    {
        MYJSON_TRY { return std::optional<const json *>(&ref(document)); }
        MYJSON_CATCH(const std::exception &) { return std::nullopt; }
    }

    //-----------------------------------------------------------------------------
    // [Class] json_merge_patch
    //-----------------------------------------------------------------------------
    // ================ JSON Merge Patch Implementation (RFC 7386) ================
    //-----------------------------------------------------------------------------

    json_merge_patch::json_merge_patch(const json &patch_json)
        : m_patch(patch_json) {}

    json json_merge_patch::apply(const json &document) const
    {
        return apply_recursive(document, m_patch);
    }

    void json_merge_patch::apply_inplace(json &document) const
    {
        document = apply_recursive(document, m_patch);
    }

    json json_merge_patch::apply_recursive(const json &target, const json &patch)
    {
        if (patch.is_null())
        {
            return json();
        }

        if (!patch.is_object() || !target.is_object())
        {
            return patch;
        }

        json result = target.clone();
        for (const auto &key : patch.keys())
        {
            json value = patch[key];
            if (value.is_null())
            {
                result.erase(key);
            }
            else
            {
                result[key] = apply_recursive(
                    result.contains(key) ? result[key] : json::object(),
                    value);
            }
        }
        return result;
    }

    json json_merge_patch::generate(const json &source, const json &target)
    {
        if (source == target)
        {
            return json::object();
        }

        if (!source.is_object() || !target.is_object())
        {
            return target;
        }

        json patch = json::object();
        for (const auto &key : target.keys())
        {
            json value = target[key];
            if (!source.contains(key) || source[key] != value)
            {
                patch[key] = value;
            }
        }

        for (const auto &key : source.keys())
        {
            if (!target.contains(key))
            {
                patch[key] = nullptr;
            }
        }
        return patch;
    }

    //-----------------------------------------------------------------------------
    // [Class] version
    //-----------------------------------------------------------------------------
    // Semver versioning
    //-----------------------------------------------------------------------------
    // - version()
    // - operator<()
    // - operator>()
    // - operator==()
    // - operator!=()
    // - operator<=()
    // - operator>=()
    // - operator<<()
    //-----------------------------------------------------------------------------

    version::version(int major, int minor, int patch)
        : major(major), minor(minor), patch(patch)
    {
    }

    bool operator<(const version &lhs, const version &rhs) noexcept
    {
        return lhs.major < rhs.major || (lhs.major == rhs.major && lhs.minor < rhs.minor) ||
               (lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch < rhs.patch);
    };

    bool operator>(const version &lhs, const version &rhs) noexcept { return rhs < lhs; };

    bool operator==(const version &lhs, const version &rhs) noexcept
    {
        return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch;
    };

    bool operator!=(const version &lhs, const version &rhs) noexcept { return !(lhs == rhs); };

    bool operator<=(const version &lhs, const version &rhs) noexcept { return !(rhs < lhs); };

    bool operator>=(const version &lhs, const version &rhs) noexcept { return !(lhs < rhs); };

#ifndef MYJSON_NO_STL

    std::ostream &operator<<(std::ostream &ostream, const version &version)
    {
        ostream << version.major << '.' << version.minor << '.' << version.patch;
        return ostream;
    };

#endif // MYJSON_NO_STL

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Functions
    //-----------------------------------------------------------------------------
    // - operator<<()
    // - operator>>()
    //-----------------------------------------------------------------------------

    //========== Diff Function ==========

    json diff(const json &source, const json &target)
    {
        json patch = json::array();

        if (source == target)
            return patch;

        if (!source.is_object() || !target.is_object())
        {
            patch.push_back(json_patch::replace_operation("", target));
            return patch;
        }

        for (const auto &key : target.keys())
        {
            json value = target[key];
            std::string path = "/" + key;
            if (!source.contains(key))
                patch.push_back(json_patch::add_operation(path, value));
            else if (source[key] != value)
                patch.push_back(json_patch::replace_operation(path, value));
        }

        for (const auto &key : source.keys())
        {
            if (!target.contains(key))
                patch.push_back(json_patch::remove_operation("/" + key));
        }

        return patch;
    }

    const char *string(encoding type)
    {
        switch (type)
        {
        case encoding::utf8:
            return "utf8";
        case encoding::utf16:
            return "utf16";
        case encoding::utf16le:
            return "utf16le";
        case encoding::utf16be:
            return "utf16be";
        case encoding::utf32:
            return "utf32";
        case encoding::utf32le:
            return "utf32le";
        case encoding::utf32be:
            return "utf32be";
        default:
            return "unspecified";
        }
    };

    const char *string(node_t type)
    {
        switch (type)
        {
        default:
            return "unknown";
        }
    };

#ifndef MYJSON_NO_STL

    std::ostream &operator<<(std::ostream &ostream, const encoding &type)
    {
        ostream << string(type);
        return ostream;
    };

    std::ostream &operator<<(std::ostream &ostream, const node_t &type)
    {
        ostream << string(type);
        return ostream;
    };

    std::ostream &operator<<(std::ostream &ostream, const json &node)
    {
        detail::stream_oadapter adapter(ostream);
        detail::serializer output(&adapter);
        output.serialize(node, -1);
        return ostream;
    };

    std::istream &operator>>(std::istream &stream, json &node)
    {
        node = json::parse(stream);
        return stream;
    };

#endif // MYJSON_NO_STL

#ifndef MYJSON_NO_EXCEPTIONS

    //-----------------------------------------------------------------------------
    // [SECTION] Myjson : Exceptions
    //-----------------------------------------------------------------------------
    // - exception()
    // - what()
    // - parse_error()
    // - generate()
    // - encoding_error()
    // - generate()
    //-----------------------------------------------------------------------------

    exception::exception(const char *message) noexcept
    {
        if (message != nullptr)
        {
            m_Message.append(message);
        }
    };

    const char *exception::what() const noexcept { return m_Message.c_str(); };

    parse_error::parse_error(const char *message) noexcept
        : exception(generate(message, {})) {};

    parse_error::parse_error(const char *message, detail::mark mark) noexcept
        : exception(generate(message, mark)) {};

    const char *parse_error::generate(const char *message, detail::mark mark) noexcept
    {
        // Use a thread_local buffer so the returned pointer remains valid
        // until the next call on the same thread. Callers should copy the
        // string if they need to keep it longer.
        thread_local std::string buffer;
        buffer.clear();

        if (message != nullptr)
        {
            buffer.append(message);
        }

        // Append positional information if available
        char tmp[128];
        int n = snprintf(tmp, sizeof(tmp), " (line: %zu, column: %zu, index: %zu)", mark.line, mark.column, mark.index);
        if (n > 0)
        {
            buffer.append(tmp, static_cast<size_t>(n));
        }

        // Ensure null-termination and return pointer
        return buffer.c_str();
    };

    encoding_error::encoding_error(const char *message) noexcept
        : exception(generate(encoding::unspecified, message, nullptr, 0)) {};

    encoding_error::encoding_error(encoding encoding, const char *message, void *data, size_t size) noexcept
        : exception(generate(encoding, message, data, size)) {};

    const char *encoding_error::generate(encoding enc, const char *message, void *data, size_t size) noexcept
    {
        thread_local std::string buffer;
        buffer.clear();

        if (message != nullptr)
        {
            buffer.append(message);
        }

        // Append encoding name
        const char *enc_name = "unspecified";
        switch (enc)
        {
        case encoding::utf8:
            enc_name = "utf-8";
            break;
        case encoding::utf16:
        case encoding::utf16le:
            enc_name = "utf-16-le";
            break;
        case encoding::utf16be:
            enc_name = "utf-16-be";
            break;
        case encoding::utf32:
        case encoding::utf32le:
            enc_name = "utf-32-le";
            break;
        case encoding::utf32be:
            enc_name = "utf-32-be";
            break;
        default:
            break;
        }

        char tmp[128];
        int n = snprintf(tmp, sizeof(tmp), " [encoding: %s]", enc_name);
        if (n > 0)
        {
            buffer.append(tmp, static_cast<size_t>(n));
        }

        // If data is provided, append a short hex preview (up to 8 bytes)
        if (data != nullptr && size > 0)
        {
            const unsigned char *b = reinterpret_cast<const unsigned char *>(data);
            size_t preview = (size < 8) ? size : 8; // limit
            buffer.append(" [data: 0x");
            for (size_t i = 0; i < preview; ++i)
            {
                int written = snprintf(tmp, sizeof(tmp), "%02x", b[i]);
                if (written > 0)
                {
                    buffer.append(tmp, static_cast<size_t>(written));
                }
            }
            if (size > preview)
            {
                buffer.append("...");
            }
            buffer.append("]");
        }

        return buffer.c_str();
    };

#endif // MYJSON_NO_EXCEPTIONS

    MYJSON_VERSION_NAMESPACE_END

}; // namespace myjson

#pragma endregion // Myjson

#pragma region Literal

namespace myjson
{

    MYJSON_VERSION_NAMESPACE_BEGIN

    namespace literals
    {

        //-----------------------------------------------------------------------------
        // [SECTION] Literals : Json
        //-----------------------------------------------------------------------------

        MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char *string, size_t size)
        {
            return json::parse(std::string(string, size));
        };

#if MYJSON_HAS_CHAR8_T

        MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char8_t *string, size_t size)
        {
            return json::parse(std::string(reinterpret_cast<const char *>(string), size));
        };

#endif // MYJSON_HAS_CHAR8_T

        MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char16_t *string, size_t size)
        {
            auto utf8_str = detail::utf16::to_utf8(
                std::vector<unsigned char>(reinterpret_cast<const unsigned char *>(string),
                                           reinterpret_cast<const unsigned char *>(string) + size * 2),
                detail::myjson_endian_t::native);
            return json::parse(utf8_str);
        };

        MYJSON_INLINE json MYJSON_QUOTE_OPERATOR(const char32_t *string, size_t size)
        {
            auto utf8_str = detail::utf32::to_utf8(
                std::vector<unsigned char>(reinterpret_cast<const unsigned char *>(string),
                                           reinterpret_cast<const unsigned char *>(string) + size * 4),
                detail::myjson_endian_t::native);
            return json::parse(utf8_str);
        };

        MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char *string, size_t size)
        {
            return myjson::json_pointer(std::string(string, size));
        };

#if MYJSON_HAS_CHAR8_T

        MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char8_t *string, size_t size)
        {
            return myjson::json_pointer(std::string(reinterpret_cast<const char *>(string), size));
        };

#endif // MYJSON_HAS_CHAR8_T

        MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char16_t *string, size_t size)
        {
            auto utf8_str = detail::utf16::to_utf8(
                std::vector<unsigned char>(reinterpret_cast<const unsigned char *>(string),
                                           reinterpret_cast<const unsigned char *>(string) + size * 2),
                detail::myjson_endian_t::native);
            return myjson::json_pointer(utf8_str);
        };

        MYJSON_INLINE json_pointer MYJSON_POINTER_QUOTE_OPERATOR(const char32_t *string, size_t size)
        {
            auto utf8_str = detail::utf32::to_utf8(
                std::vector<unsigned char>(reinterpret_cast<const unsigned char *>(string),
                                           reinterpret_cast<const unsigned char *>(string) + size * 4),
                detail::myjson_endian_t::native);
            return myjson::json_pointer(utf8_str);
        };

    }; // namespace literals

    MYJSON_VERSION_NAMESPACE_END

}; // namespace myjson

#pragma endregion // Literal

#endif // MYJSON_IMPLEMENTATION

/**
 * CHANGELOG: Version history
 */

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * data the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included data
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
 */