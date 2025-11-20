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

#include <stdint.h>

#pragma region Internal

//-------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

/**
 * @def MYJSON_MAX_FILE_SIZE
 * @brief Maximum JSON file size in bytes.
 * @note Default is 1073741824 [`2^30`] (1GB).
 */
#define MYJSON_MAX_FILE_SIZE 1073741824

/**
 * @def MYJSON_INPUT_RAW_BUFFER_SIZE
 * @brief The size of the input raw buffer.
 * @note Default is 16384 [`2^14`].
 */
#define MYJSON_INPUT_RAW_BUFFER_SIZE 16384

/**
 * @def MYJSON_OUPUT_BUFFER_SIZE
 * @brief The size of the output buffer.
 * @note Default is 16384 [`2^14`].
 */
#define MYJSON_OUPUT_BUFFER_SIZE 16384

/**
 * @def MYJSON_OUTPUT_RAW_BUFFER_SIZE
 * @brief The size of the input buffer.
 * @note It should be possible to decode the whole raw buffer.
 * @note Default is 3 times `MYJSON_INPUT_RAW_BUFFER_SIZE` .
 */
#define MYJSON_INPUT_BUFFER_SIZE (MYJSON_INPUT_RAW_BUFFER_SIZE * 3)

/**
 * @def MYJSON_OUTPUT_RAW_BUFFER_SIZE
 * @brief The size of the output raw buffer.
 * @note It should be possible to encode the whole output buffer.
 * @note Default is 2 times `MYJSON_OUPUT_BUFFER_SIZE` .
 */
#define MYJSON_OUTPUT_RAW_BUFFER_SIZE (MYJSON_OUPUT_BUFFER_SIZE * 2 + 2)

/**
 * @def MYJSON_MAX_STRING_LENGTH
 * @brief Maximum length for JSON string values.
 * @note Default is 4096 [`2^12`].
 */
#define MYJSON_MAX_STRING_LENGTH 4096

/**
 * @def MYJSON_MAX_NUMBER_LENGTH
 * @brief Maximum length for JSON number values.
 * @note Default is 9.
 */
#define MYJSON_MAX_NUMBER_LENGTH 9

/**
 * @def MYJSON_MAX_ARRAY_LENGTH
 * @brief Maximum length of JSON arrays.
 * @note Default is 131072 [`2^17`].
 */
#define MYJSON_MAX_ARRAY_LENGTH 131072

#define MYJSON_MALLOC(type) (type *)_myjson_malloc(sizeof(type))

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

typedef struct FileInputStream_t {
    size_t unread; /**< The number of read characters in the buffer. */
    size_t size;
    FILE *file;
    int eof; /** EOF flag */
} *FileInputStream_t;

typedef struct FileOutputStream_t {
    size_t written; /**< The number of written characters in the buffer. */
    size_t size;
    FILE *file;
    int eof; /** EOF flag */
} *FileOutputStream_t;

typedef struct MemoryInputStream_t {
    size_t unread; /**< The number of unread characters in the buffer. */
    char *buffer;  /* pointer to buffer start */
    size_t size;
    int eof; /** EOF flag */
} *MemoryInputStream_t;

typedef struct MemoryOutputStream_t {
    size_t written; /**< The number of written characters in the buffer. */
    size_t size;    /** The buffer size. */
    char *buffer;   /* pointer to buffer start */
    int eof;        /** EOF flag */
} *MemoryOutputStream_t;

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

//-----------------------------------------------------------------------------
// [SECTION] Memory Management
//-----------------------------------------------------------------------------

/*
 * Allocate a dynamic memory block.
 */
void *_myjson_malloc(size_t size);

/*
 * Reallocate a dynamic memory block.
 */
void *_myjson_realloc(void *ptr, size_t size);

/*
 * Free a dynamic memory block.
 */
void _myjson_free(void *ptr);

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

//-----------------------------------------------------------------------------
// [SECTION] Parser
//-----------------------------------------------------------------------------

static JsonEncoding DetectEncoding(const unsigned char *data, size_t size, size_t *offset);
static size_t Utf8FromUtf16(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian);
static size_t Utf8FromUtf32(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian);
static size_t Utf8Normalize(const void *data, size_t data_len, unsigned char *out, size_t out_len);
static void Utf8Decode(const void *data);
static void Utf8Encode(const void *data);

void FileInputStreamInit(FileInputStream_t stream, FILE *file);
size_t FileInputStreamRead(FileInputStream_t stream, void *data, size_t size_in_byte);
size_t FileInputStreamSeek(FileInputStream_t stream, size_t position);
size_t FileInputStreamTell(FileInputStream_t stream);
size_t FileInputStreamSize(FileInputStream_t stream);
void FileInputStreamFree(FileInputStream_t stream);

void MemoryInputStreamInit(MemoryInputStream_t stream, void *data, size_t size_in_byte);
size_t MemoryInputStreamRead(MemoryInputStream_t stream, void *data, size_t size_in_byte);
size_t MemoryInputStreamSeek(MemoryInputStream_t stream, size_t position);
size_t MemoryInputStreamTell(MemoryInputStream_t stream);
size_t MemoryInputStreamSize(MemoryInputStream_t stream);
void MemoryInputStreamFree(MemoryInputStream_t stream);

void MemoryOutputStreamInit(MemoryOutputStream_t stream, void *buffer, size_t size_in_byte);
size_t MemoryOutputStreamWrite(MemoryOutputStream_t stream, const void *data, size_t size_in_byte);
size_t MemoryOutputStreamTell(MemoryOutputStream_t stream);
size_t MemoryOutputStreamSize(MemoryOutputStream_t stream);
void MemoryOutputStreamFree(MemoryOutputStream_t stream);

void FileOutputStreamInit(FileOutputStream_t stream, FILE *file);
size_t FileOutputStreamWrite(FileOutputStream_t stream, const void *data, size_t size_in_byte);
size_t FileOutputStreamTell(FileOutputStream_t stream);
size_t FileOutputStreamSize(FileOutputStream_t stream);
void FileOutputStreamFree(FileOutputStream_t stream);

/*
 * String read handler.
 */
static int _myjson_string_read_handler(void *data, unsigned char *buffer, size_t size, size_t *size_read);

/*
 * File read handler.
 */
static int _myjson_file_read_handler(void *data, unsigned char *buffer, size_t size, size_t *size_read);

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

//-----------------------------------------------------------------------------
// [SECTION] Emitter
//-----------------------------------------------------------------------------

/*
 * String write handler.
 */
static int _myjson_string_write_handler(void *data, unsigned char *buffer, size_t size);

/*
 * File write handler.
 */
static int _myjson_file_write_handler(void *data, unsigned char *buffer, size_t size);

#endif  // MYJSON_DISABLE_WRITER

#pragma endregion  // C Declarations

#pragma region C Def

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

void *_myjson_malloc(size_t size) { return malloc(size ? size : 1); };

void *_myjson_realloc(void *ptr, size_t size) { return ptr ? realloc(ptr, size ? size : 1) : malloc(size ? size : 1); };

void _myjson_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
};

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

//-----------------------------------------------------------------------------
// [SECTION] Parser
//-----------------------------------------------------------------------------

static JsonEncoding DetectEncoding(const unsigned char *data, size_t size, size_t *offset) {
    if (!data || size == 0) {
        if (offset) *offset = 0;
        return JSON_UTF8_ENCODING;
    }
    // UTF-8 BOM
    if (size >= 3 && data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF) {
        if (offset) *offset = 3;
        return JSON_UTF8_ENCODING;
    }
    // UTF-16 LE BOM
    if (size >= 2 && data[0] == 0xFF && data[1] == 0xFE) {
        if (size >= 4 && data[2] == 0x00 && data[3] == 0x00) {
            if (offset) *offset = 4;
            return JSON_UTF32LE_ENCODING;
        }
        if (offset) *offset = 2;
        return JSON_UTF16LE_ENCODING;
    }
    // UTF-16 BE BOM
    if (size >= 2 && data[0] == 0xFE && data[1] == 0xFF) {
        if (offset) *offset = 2;
        return JSON_UTF16BE_ENCODING;
    }
    // UTF-32 BE BOM
    if (size >= 4 && data[0] == 0x00 && data[1] == 0x00 && data[2] == 0xFE && data[3] == 0xFF) {
        if (offset) *offset = 4;
        return JSON_UTF32BE_ENCODING;
    }
    // UTF-32 LE BOM
    if (size >= 4 && data[0] == 0xFF && data[1] == 0xFE && data[2] == 0x00 && data[3] == 0x00) {
        if (offset) *offset = 4;
        return JSON_UTF32LE_ENCODING;
    }
    if (offset) *offset = 0;
    return JSON_UTF8_ENCODING;  // default
}

// Convert UTF-16LE/BE (basic) to UTF-8 into a provided buffer. Returns bytes written or 0 on error.
static size_t Utf8FromUtf16(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian) {
    size_t in_pos = 0;
    size_t out_pos = 0;
    while (in_pos + 1 < in_len) {
        uint16_t ch;
        if (big_endian)
            ch = (in[in_pos] << 8) | in[in_pos + 1];
        else
            ch = (in[in_pos + 1] << 8) | in[in_pos];
        in_pos += 2;
        if (ch >= 0xD800 && ch <= 0xDBFF) {
            // surrogate pair; need next 2 bytes
            if (in_pos + 1 >= in_len) return 0;
            uint16_t ch2;
            if (big_endian)
                ch2 = (in[in_pos] << 8) | in[in_pos + 1];
            else
                ch2 = (in[in_pos + 1] << 8) | in[in_pos];
            in_pos += 2;
            uint32_t codepoint = 0x10000 + (((ch - 0xD800) << 10) | (ch2 - 0xDC00));
            if (codepoint <= 0x1FFFFF) {
                if (out_pos + 4 > out_len) return 0;
                out[out_pos++] = (char)(0xF0 | ((codepoint >> 18) & 0x07));
                out[out_pos++] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
                out[out_pos++] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
                out[out_pos++] = (char)(0x80 | (codepoint & 0x3F));
                continue;
            }
            return 0;
        }
        if (ch < 0x80) {
            if (out_pos + 1 > out_len) return 0;
            out[out_pos++] = (char)ch;
        } else if (ch < 0x800) {
            if (out_pos + 2 > out_len) return 0;
            out[out_pos++] = (char)(0xC0 | (ch >> 6));
            out[out_pos++] = (char)(0x80 | (ch & 0x3F));
        } else {
            if (out_pos + 3 > out_len) return 0;
            out[out_pos++] = (char)(0xE0 | (ch >> 12));
            out[out_pos++] = (char)(0x80 | ((ch >> 6) & 0x3F));
            out[out_pos++] = (char)(0x80 | (ch & 0x3F));
        }
    }
    return out_pos;
}

static size_t Utf8FromUtf32(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian) {
    size_t in_pos = 0;
    size_t out_pos = 0;
    while (in_pos + 3 < in_len) {
        uint32_t ch;
        if (big_endian)
            ch = (in[in_pos] << 24) | (in[in_pos + 1] << 16) | (in[in_pos + 2] << 8) | in[in_pos + 3];
        else
            ch = (in[in_pos + 3] << 24) | (in[in_pos + 2] << 16) | (in[in_pos + 1] << 8) | in[in_pos];
        in_pos += 4;
        if (ch <= 0x7F) {
            if (out_pos + 1 > out_len) return 0;
            out[out_pos++] = (char)ch;
        } else if (ch <= 0x7FF) {
            if (out_pos + 2 > out_len) return 0;
            out[out_pos++] = (char)(0xC0 | (ch >> 6));
            out[out_pos++] = (char)(0x80 | (ch & 0x3F));
        } else if (ch <= 0xFFFF) {
            if (out_pos + 3 > out_len) return 0;
            out[out_pos++] = (char)(0xE0 | (ch >> 12));
            out[out_pos++] = (char)(0x80 | ((ch >> 6) & 0x3F));
            out[out_pos++] = (char)(0x80 | (ch & 0x3F));
        } else {
            if (out_pos + 4 > out_len) return 0;
            out[out_pos++] = (char)(0xF0 | ((ch >> 18) & 0x07));
            out[out_pos++] = (char)(0x80 | ((ch >> 12) & 0x3F));
            out[out_pos++] = (char)(0x80 | ((ch >> 6) & 0x3F));
            out[out_pos++] = (char)(0x80 | (ch & 0x3F));
        }
    }
    return out_pos;
}

// Read memory buffer of unknown encoding and normalize to UTF-8 in-place or into out buffer.
// Returns number of bytes in UTF-8 output or 0 on error. If encoding is UTF-8 and offset>0, copies
// the remainder to out.
static size_t Utf8Normalize(const void *data, size_t data_len, unsigned char *out, size_t out_len) {
    const unsigned char *src = (const unsigned char *)data;
    size_t offset = 0;
    JsonEncoding enc = DetectEncoding(src, data_len, &offset);
    if (enc == JSON_UTF8_ENCODING) {
        size_t tocopy = data_len - offset;
        if (tocopy > out_len) return 0;
        memcpy(out, src + offset, tocopy);
        return tocopy;
    }
    if (enc == JSON_UTF16LE_ENCODING) return Utf8FromUtf16(src + offset, data_len - offset, out, out_len, 0);
    if (enc == JSON_UTF16BE_ENCODING) return Utf8FromUtf16(src + offset, data_len - offset, out, out_len, 1);
    if (enc == JSON_UTF32LE_ENCODING) return Utf8FromUtf32(src + offset, data_len - offset, out, out_len, 0);
    if (enc == JSON_UTF32BE_ENCODING) return Utf8FromUtf32(src + offset, data_len - offset, out, out_len, 1);
    return 0;
}

static void MemoryInputStreamInit(MemoryInputStream_t stream, void *data, size_t size_in_byte) {
    if (!stream) return;
    stream->buffer = (char *)data;
    stream->unread = size_in_byte;
    stream->eof = (size_in_byte == 0);
}

static size_t MemoryInputStreamRead(MemoryInputStream_t stream, void *data, size_t size_in_byte) {
    if (!stream || !data) return 0;
    size_t toread = size_in_byte < stream->unread ? size_in_byte : stream->unread;
    if (toread == 0) {
        stream->eof = 1;
        return 0;
    }
    memcpy(data, stream->buffer, toread);
    stream->buffer += toread;
    stream->unread -= toread;
    if (stream->unread == 0) stream->eof = 1;
    return toread;
}

static size_t MemoryInputStreamSeek(MemoryInputStream_t stream, size_t position) {
    if (!stream) return (size_t)-1;
    // Not tracking original buffer start, so can't seek backwards reliably in this simple impl.
    // For header convenience we treat seek to current offset only.
    (void)position;
    return (size_t)-1;
}

static size_t MemoryInputStreamTell(MemoryInputStream_t stream) {
    if (!stream) return (size_t)-1;
    return stream->size - stream->unread;
}

static size_t MemoryInputStreamSize(MemoryInputStream_t stream) {
    if (!stream) return 0;
    return stream->size;
}

static void MemoryInputStreamFree(MemoryInputStream_t stream) {
    if (!stream) return;
    stream->buffer = NULL;
    stream->unread = 0;
    stream->size = 0;
    stream->eof = 1;
}

static void FileInputStreamInit(FileInputStream_t stream, FILE *file) {
    if (!stream) return;
    stream->file = file;
    stream->unread = 0;
    stream->size = 0;
    stream->eof = 0;
    if (file) {
        long cur = ftell(file);
        if (cur >= 0) {
            fseek(file, 0, SEEK_END);
            long len = ftell(file);
            if (len >= 0) stream->size = (size_t)len;
            fseek(file, cur, SEEK_SET);
        }
    }
}

static size_t FileInputStreamRead(FileInputStream_t stream, void *data, size_t size_in_byte) {
    if (!stream || !stream->file || !data) return 0;
    size_t n = fread(data, 1, size_in_byte, stream->file);
    if (n < size_in_byte && feof(stream->file)) stream->eof = 1;
    return n;
}

static size_t FileInputStreamSeek(FileInputStream_t stream, size_t position) {
    if (!stream || !stream->file) return (size_t)-1;
    if (fseek(stream->file, (long)position, SEEK_SET) != 0) return (size_t)-1;
    long pos = ftell(stream->file);
    return pos < 0 ? (size_t)-1 : (size_t)pos;
}

static size_t FileInputStreamTell(FileInputStream_t stream) {
    if (!stream || !stream->file) return (size_t)-1;
    long pos = ftell(stream->file);
    return pos < 0 ? (size_t)-1 : (size_t)pos;
}

static size_t FileInputStreamSize(FileInputStream_t stream) {
    if (!stream || !stream->file) return 0;
    long cur = ftell(stream->file);
    if (cur < 0) return 0;
    if (fseek(stream->file, 0, SEEK_END) != 0) return 0;
    long len = ftell(stream->file);
    fseek(stream->file, cur, SEEK_SET);
    return len < 0 ? 0 : (size_t)len;
}

static void FileInputStreamFree(FileInputStream_t stream) {
    if (!stream) return;
    // do not close FILE* here; just reset
    stream->file = NULL;
    stream->unread = 0;
    stream->size = 0;
    stream->eof = 0;
}

static void MemoryOutputStreamInit(MemoryOutputStream_t stream, void *buffer, size_t size_in_byte) {
    if (!stream) return;
    stream->written = 0;
    stream->size = size_in_byte;
    stream->eof = (size_in_byte == 0);
    // We don't store pointer in the typedef; user should manage buffer externally.
}

static size_t MemoryOutputStreamWrite(MemoryOutputStream_t stream, const void *data, size_t size_in_byte) {
    if (!stream || !data) return 0;
    size_t canwrite = stream->size - stream->written;
    size_t towrite = size_in_byte < canwrite ? size_in_byte : canwrite;
    // Because MemoryOutputStream_t currently has no buffer pointer, we cannot actually copy bytes
    // into the buffer. This API records the bytes written and returns the number of bytes that
    // would have been written.
    stream->written += towrite;
    if (stream->written >= stream->size) stream->eof = 1;
    return towrite;
}

static size_t MemoryOutputStreamTell(MemoryOutputStream_t stream) {
    if (!stream) return (size_t)-1;
    return stream->written;
}

static size_t MemoryOutputStreamSize(MemoryOutputStream_t stream) {
    if (!stream) return 0;
    return stream->size;
}

static void MemoryOutputStreamFree(MemoryOutputStream_t stream) {
    if (!stream) return;
    stream->written = 0;
    stream->size = 0;
    stream->eof = 1;
}

static void FileOutputStreamInit(FileOutputStream_t stream, FILE *file) {
    if (!stream) return;
    stream->file = file;
    stream->written = 0;
    stream->size = 0;
    stream->eof = 0;
}

static size_t FileOutputStreamWrite(FileOutputStream_t stream, const void *data, size_t size_in_byte) {
    if (!stream || !stream->file || !data) return 0;
    size_t n = fwrite(data, 1, size_in_byte, stream->file);
    stream->written += n;
    if (n < size_in_byte) stream->eof = 1;
    return n;
}

static size_t FileOutputStreamTell(FileOutputStream_t stream) {
    if (!stream || !stream->file) return (size_t)-1;
    long pos = ftell(stream->file);
    return pos < 0 ? (size_t)-1 : (size_t)pos;
}

static size_t FileOutputStreamSize(FileOutputStream_t stream) {
    if (!stream || !stream->file) return 0;
    long cur = ftell(stream->file);
    if (cur < 0) return 0;
    if (fseek(stream->file, 0, SEEK_END) != 0) return 0;
    long len = ftell(stream->file);
    fseek(stream->file, cur, SEEK_SET);
    return len < 0 ? 0 : (size_t)len;
}

static void FileOutputStreamFree(FileOutputStream_t stream) {
    if (!stream) return;
    stream->file = NULL;
    stream->written = 0;
    stream->size = 0;
    stream->eof = 1;
}

/*
 * String read handler.
 */
static int _myjson_string_read_handler(void *data, unsigned char *buffer, size_t size, size_t *size_read) {
    JsonParser *parser = (JsonParser *)data;

    if (parser->input.string.current == parser->input.string.end) {
        *size_read = 0;
        return MYJSON_SUCCESS;
    }

    if (size > (size_t)(parser->input.string.end - parser->input.string.current)) {
        size = parser->input.string.end - parser->input.string.current;
    }

    memcpy(buffer, parser->input.string.current, size);
    parser->input.string.current += size;
    *size_read = size;

    return MYJSON_SUCCESS;
};

/*
 * File read handler.
 */
static int _myjson_file_read_handler(void *data, unsigned char *buffer, size_t size, size_t *size_read) {
    JsonParser *parser = (JsonParser *)data;

    *size_read = fread(buffer, 1, size, parser->input.file);
    return !ferror(parser->input.file);
};

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

//-----------------------------------------------------------------------------
// [SECTION] Emitter
//-----------------------------------------------------------------------------

/*
 * String write handler.
 */
static int _myjson_string_write_handler(void *data, unsigned char *buffer, size_t size) {
    JsonEmitter *emitter = (JsonEmitter *)data;

    if (emitter->output.string.size - *emitter->output.string.size_written < size) {
        memcpy(emitter->output.string.buffer + *emitter->output.string.size_written, buffer,
               emitter->output.string.size - *emitter->output.string.size_written);
        *emitter->output.string.size_written = emitter->output.string.size;
        return MYJSON_FAILURE;
    }

    memcpy(emitter->output.string.buffer + *emitter->output.string.size_written, buffer, size);
    *emitter->output.string.size_written += size;
    return MYJSON_SUCCESS;
};

/*
 * File write handler.
 */
static int _myjson_file_write_handler(void *data, unsigned char *buffer, size_t size) {
    JsonEmitter *emitter = (JsonEmitter *)data;
    return (fwrite(buffer, 1, size, emitter->output.file) == size);
};

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

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

/**
 * @brief A class which handles UTF-8 encodings.
 */
template <typename CharType = char>
struct Utf8 {
    using Char = CharType;

    template <typename OutputStream>
    static void encode(OutputStream &os, unsigned codepoint);

    template <typename InputStream>
    static bool decode(InputStream &is, unsigned *codepoint);

    template <typename InputStream, typename OutputStream>
    static bool validate(InputStream &is, OutputStream &os);

    static size_t normalize(const void *data, size_t data_len, unsigned char *out, size_t out_len) {};

    /**
     * @brief Checks if `uint8_t` is a valid 1-uint8_t UTF-8 character.
     *
     * @param[in] uint8_t The uint8_t value.
     *
     * @return true if `uint8_t` is a valid 1-uint8_t UTF-8 character, false otherwise.
     */
    bool validate(uint8_t byte) { return Utf8Validate1(byte); };

    /**
     * @brief Checks if the given bytes are a valid 2-uint8_t UTF-8 character.
     *
     * @param[in] byte0 The first uint8_t value.
     * @param[in] byte1 The second uint8_t value.
     *
     * @return true if the given bytes a valid 2-uint8_t UTF-8 character, false otherwise.
     */
    bool validate(uint8_t byte0, uint8_t byte1) { return Utf8Validate2(byte0, byte1); };

    /**
     * @brief Checks if the given bytes are a valid 3-uint8_t UTF-8 character.
     *
     * @param[in] byte0 The first uint8_t value.
     * @param[in] byte1 The second uint8_t value.
     * @param[in] byte2 The third uint8_t value.
     *
     * @return true if the given bytes a valid 3-uint8_t UTF-8 character, false otherwise.
     */
    bool validate(uint8_t byte0, uint8_t byte1, uint8_t byte2) { return Utf8Validate3(byte0, byte1, byte3); };

    /**
     * @brief Checks if the given bytes are a valid 4-uint8_t UTF-8 character.
     *
     * @param[in] byte0 The first uint8_t value.
     * @param[in] byte1 The second uint8_t value.
     * @param[in] byte2 The third uint8_t value.
     * @param[in] byte3 The fourth uint8_t value.
     *
     * @return true if the given bytes a valid 4-uint8_t UTF-8 character, false otherwise.
     */
    bool validate(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3) { return Utf8Validate4(byte0, byte1, byte2, byte3); };

    static size_t from_utf16(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian) {}
    static size_t from_utf32(const unsigned char *in, size_t in_len, unsigned char *out, size_t out_len, int big_endian) {}
};

/**
 * @brief Abstract class for input streams
 */
class InputStream {
   public:
    /**
     * @brief Virtual destructor
     */
    virtual ~InputStream() = default;

    /**
     * @brief Read data from the stream
     *
     * After reading, the stream's reading position must be
     * advanced by the amount of bytes read.
     *
     * @param data Buffer where to copy the read data
     * @param size Desired number of bytes to read
     *
     * @return The number of bytes actually read, or `std::nullopt` on error.
     */
    [[nodiscard]] virtual std::optional<std::size_t> read(void *data, std::size_t size) = 0;

    /**
     * @brief Change the current reading position
     *
     * @param position The position to seek to, from the beginning
     *
     * @return The position actually sought to, or `std::nullopt` on error.
     */
    [[nodiscard]] virtual std::optional<std::size_t> seek(std::size_t position) = 0;

    /**
     * @brief Get the current reading position in the stream
     *
     * @return return The current position, or `std::nullopt` on error.
     */
    [[nodiscard]] virtual std::optional<std::size_t> tell() = 0;

    /**
     * @brief Return the size of the stream
     *
     * @return The total number of bytes available in the stream, or `std::nullopt` on error
     */
    virtual std::optional<std::size_t> size() = 0;
};

class MemoryInputStream : public InputStream {
   public:
    /**
     * @brief Default constructor
     */
    MemoryInputStream() = default;

    MemoryInputStream(MemoryInputStream_t stream) : m_MemoryInputStream(stream) {};

    /**
     * @brief Construct the stream from its data
     *
     * @param data        Pointer to the data in memory
     * @param sizeInBytes Size of the data, in bytes
     */
    MemoryInputStream(const void *data, std::size_t sizeInBytes) {
        MemoryInputStreamInit(m_MemoryInputStream, const_cast<void *>(data), sizeInBytes);
    };

    /**
     * @brief Deleted copy constructor
     */
    MemoryInputStream(const MemoryInputStream &) = delete;

    /**
     * @brief Deleted move constructor
     */
    MemoryInputStream(MemoryInputStream &&) noexcept = default;

    /**
     * @brief Read data from the stream
     *
     * After reading, the stream's reading position must be
     * advanced by the amount of bytes read.
     *
     * @param data Buffer where to copy the read data
     * @param size Desired number of bytes to read
     *
     * @return The number of bytes actually read, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> read(void *data, std::size_t size) override {
        const auto count = MemoryInputStreamRead(m_MemoryInputStream, data, size);
        return std::optional<std::size_t>(count);
    };

    /**
     * @brief Change the current reading position
     *
     * @param position The position to seek to, from the beginning
     *
     * @return The position actually sought to, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> seek(std::size_t position) override {
        const auto offset = MemoryInputStreamSeek(m_MemoryInputStream, position);
        if (offset == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(offset);
    };

    /**
     * @brief Get the current reading position in the stream
     *
     * @return return The current position, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> tell() override {
        const auto position = MemoryInputStreamTell(m_MemoryInputStream);
        if (position == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(position);
    };

    /**
     * @brief Return the size of the stream
     *
     * @return The total number of bytes available in the stream, or `std::nullopt` on error
     */
    std::optional<std::size_t> size() override {
        const auto s = MemoryInputStreamSize(m_MemoryInputStream);
        return std::optional<std::size_t>(s);
    };

    /**
     * @brief Deleted copy assignment operator
     */
    MemoryInputStream &operator=(const MemoryInputStream &) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    MemoryInputStream &operator=(MemoryInputStream &&) = delete;

    ~MemoryInputStream() { MemoryInputStreamFree(m_MemoryInputStream); };

   private:
    MemoryInputStream_t m_MemoryInputStream;
};

class FileInputStream : public InputStream {
   public:
    /**
     * @brief Default constructor
     */
    FileInputStream() = default;

    FileInputStream(std::FILE *f) : m_FileInputStream(nullptr) {
        // allocate a C struct on the heap
        m_FileInputStream = (FileInputStream_t)malloc(sizeof(struct FileInputStream_t));
        if (!m_FileInputStream) return;
        FileInputStreamInit(m_FileInputStream, f);
    };

    FileInputStream(FileInputStream_t stream) : m_FileInputStream(stream) {};

    /**
     * @brief Deleted copy constructor
     */
    FileInputStream(const FileInputStream &) = delete;

    /**
     * @brief Deleted move constructor
     */
    FileInputStream(FileInputStream &&) noexcept = default;

    /**
     * @brief Read data from the stream
     *
     * After reading, the stream's reading position must be
     * advanced by the amount of bytes read.
     *
     * @param data Buffer where to copy the read data
     * @param size Desired number of bytes to read
     *
     * @return The number of bytes actually read, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> read(void *data, std::size_t size) override {
        if (!m_FileInputStream) return std::nullopt;
        const auto n = FileInputStreamRead(m_FileInputStream, data, size);
        return std::optional<std::size_t>(n);
    };

    /**
     * @brief Change the current reading position
     *
     * @param position The position to seek to, from the beginning
     *
     * @return The position actually sought to, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> seek(std::size_t position) override {
        if (!m_FileInputStream) return std::nullopt;
        const auto pos = FileInputStreamSeek(m_FileInputStream, position);
        if (pos == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(pos);
    };

    /**
     * @brief Get the current reading position in the stream
     *
     * @return return The current position, or `std::nullopt` on error.
     */
    [[nodiscard]] std::optional<std::size_t> tell() override {
        if (!m_FileInputStream) return std::nullopt;
        const auto pos = FileInputStreamTell(m_FileInputStream);
        if (pos == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(pos);
    };

    /**
     * @brief Return the size of the stream
     *
     * @return The total number of bytes available in the stream, or `std::nullopt` on error
     */
    std::optional<std::size_t> size() override {
        if (!m_FileInputStream) return std::nullopt;
        const auto s = FileInputStreamSize(m_FileInputStream);
        return std::optional<std::size_t>(s);
    };

    /**
     * @brief Deleted copy assignment operator
     */
    FileInputStream &operator=(const FileInputStream &) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    FileInputStream &operator=(FileInputStream &&) = delete;

    ~FileInputStream() { FileInputStreamFree(m_FileInputStream); };

   private:
    FileInputStream_t m_FileInputStream;
};

/**
 * @brief Abstract class for output streams
 */
class OutputStream {
   public:
    /**
     * @brief Virtual destructor
     */
    virtual ~OutputStream() = default;

    /**
     * @brief Return the size of the stream
     *
     * @return The total number of bytes available in the stream, or `std::nullopt` on error
     */
    virtual std::optional<std::size_t> size() = 0;
};

class MemoryOutputStream : public OutputStream {
   public:
    /**
     * @brief Deleted copy constructor
     */
    MemoryOutputStream(const MemoryOutputStream &) = delete;

    /**
     * @brief Deleted move constructor
     */
    MemoryOutputStream(MemoryOutputStream &&) noexcept = default;

    /**
     * @brief Deleted copy assignment operator
     */
    MemoryOutputStream &operator=(const MemoryOutputStream &) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    MemoryOutputStream &operator=(MemoryOutputStream &&) = delete;

    std::optional<std::size_t> write(const void *data, std::size_t size) {
        if (!m_MemoryOutputStream) return std::nullopt;
        const auto n = MemoryOutputStreamWrite(m_MemoryOutputStream, data, size);
        return std::optional<std::size_t>(n);
    }

    std::optional<std::size_t> tell() {
        if (!m_MemoryOutputStream) return std::nullopt;
        const auto t = MemoryOutputStreamTell(m_MemoryOutputStream);
        if (t == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(t);
    }

    std::optional<std::size_t> size() {
        if (!m_MemoryOutputStream) return std::nullopt;
        const auto s = MemoryOutputStreamSize(m_MemoryOutputStream);
        return std::optional<std::size_t>(s);
    }

    ~MemoryOutputStream() { MemoryOutputStreamFree(m_MemoryOutputStream); };

   private:
    MemoryOutputStream_t m_MemoryOutputStream;
};

class FileOutputStream : public OutputStream {
   public:
    FileOutputStream(std::FILE *stream) : m_FileOutputStream(nullptr) {
        // allocate a C struct on the heap
        m_FileOutputStream = (FileOutputStream_t)malloc(sizeof(struct FileInputStream_t));
        if (!m_FileOutputStream) return;
        FileOutputStreamInit(m_FileOutputStream, stream);
    };

    FileOutputStream(FileOutputStream_t stream) : m_FileOutputStream(stream) {};

    /**
     * @brief Deleted copy constructor
     */
    FileOutputStream(const FileOutputStream &) = delete;

    /**
     * @brief Deleted move constructor
     */
    FileOutputStream(FileOutputStream &&) noexcept = default;

    /**
     * @brief Deleted copy assignment operator
     */
    FileOutputStream &operator=(const FileOutputStream &) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    FileOutputStream &operator=(FileOutputStream &&) = delete;

    ~FileOutputStream() = default;

    std::optional<std::size_t> write(const void *data, std::size_t size) {
        if (!m_FileOutputStream) return std::nullopt;
        const auto n = FileOutputStreamWrite(m_FileOutputStream, data, size);
        return std::optional<std::size_t>(n);
    }

    std::optional<std::size_t> tell() {
        if (!m_FileOutputStream) return std::nullopt;
        const auto t = FileOutputStreamTell(m_FileOutputStream);
        if (t == (size_t)-1) return std::nullopt;
        return std::optional<std::size_t>(t);
    }

    std::optional<std::size_t> size() {
        if (!m_FileOutputStream) return std::nullopt;
        const auto s = FileOutputStreamSize(m_FileOutputStream);
        return std::optional<std::size_t>(s);
    }

   private:
    FileOutputStream_t m_FileOutputStream;
};

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

#pragma endregion  // Writer

#endif  // MYJSON_DISABLE_WRITER

#pragma endregion  // Cpp Declarations

#pragma region Cpp Def

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

MemoryInputStream::MemoryInputStream(const void *data, std::size_t sizeInBytes) {
    MemoryInputStreamInit(m_MemoryInputStream, const_cast<void *>(data), sizeInBytes);
};

std::optional<std::size_t> MemoryInputStream::read(void *data, std::size_t size) {
    const auto count = MemoryInputStreamRead(m_MemoryInputStream, data, size);
    return count < 0 ? std::nullopt : std::optional<std::size_t>(count);
};

std::optional<std::size_t> MemoryInputStream::seek(std::size_t position) {
    const auto offset = MemoryInputStreamSeek(m_MemoryInputStream, position);
    return offset < 0 ? std::nullopt : std::optional<std::size_t>(offset);
};

std::optional<std::size_t> MemoryInputStream::tell() {
    const auto position = MemoryInputStreamTell(m_MemoryInputStream);
    return position < 0 ? std::nullopt : std::optional<std::size_t>(position);
};

std::optional<std::size_t> MemoryInputStream::size() {
    const auto size = MemoryInputStreamSize(m_MemoryInputStream);
    return size < 0 ? std::nullopt : std::optional<std::size_t>(size);
};

MemoryInputStream::~MemoryInputStream() { MemoryInputStreamFree(m_MemoryInputStream); };

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

#pragma region Event

MYJSON_API int json_event_initialize_stream_start(JsonEvent *event, JsonEncoding encoding) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_STREAM_START_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;
    event->data.stream_start.encoding = encoding;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_stream_end(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_STREAM_END_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_document_start(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_DOCUMENT_START_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};
MYJSON_API int json_event_initialize_document_end(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_DOCUMENT_END_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_scalar(JsonEvent *event, const JsonChar_t *value, int length) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_SCALAR_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_array_start(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_ARRAY_START_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_array_end(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_ARRAY_END_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_object_start(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_OBJECT_START_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_event_initialize_object_end(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object is expected. */

    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event->type = JSON_OBJECT_END_EVENT;
    event->start_pos = pos;
    event->end_pos = pos;

    return MYJSON_SUCCESS;
};

MYJSON_API void json_event_delete(JsonEvent *event) {
    MYJSON_ASSERT(event); /**< Non-NULL event object expected. */
    switch (event->type) {
        case JSON_SCALAR_EVENT:
            break;

        case JSON_ARRAY_START_EVENT:
            break;

        case JSON_OBJECT_START_EVENT:
            break;

        default:
            break;
    }

    memset(event, 0, sizeof(JsonEvent));
};

#pragma endregion  // Event

#pragma region Json

MYJSON_API int json_document_initialize(JsonDocument *document) {};
MYJSON_API void json_document_delete(JsonDocument *document) {};

MYJSON_API JsonNode *json_document_get_root_node(JsonDocument *document) {};
MYJSON_API JsonNode *json_document_get_node(JsonDocument *document, int index) {};

MYJSON_API int json_document_add_scalar(JsonDocument *document, const JsonChar_t *value, int length) {};
MYJSON_API int json_document_add_array(JsonDocument *document) {};
MYJSON_API int json_document_add_object(JsonDocument *document) {};

MYJSON_API int json_document_append_array_item(JsonDocument *document, int array, int item) {};
MYJSON_API int json_document_append_object_pair(JsonDocument *document, int object, int key, int value) {};

MYJSON_API const JsonChar_t *json_document_get_scalar_value(JsonDocument *document, int node_id) {};
MYJSON_API int json_document_get_scalar_length(JsonDocument *document, int node_id) {};
MYJSON_API int json_document_array_get_item(JsonDocument *document, int array_node_id, int index) {};
MYJSON_API int json_document_object_get_value(JsonDocument *document, int object_node_id, const JsonChar_t *key, int key_length) {};

MYJSON_API int json_document_get_node_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count) {};
MYJSON_API const JsonChar_t *json_document_get_value_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count) {};
MYJSON_API int json_document_get_value_length_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count) {};

#pragma endregion  // Json

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region JsonEncoding

#pragma endregion  // JsonEncoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

MYJSON_API int json_parser_initialize(JsonParser *parser) {};
MYJSON_API int json_parser_parse(JsonParser *parser, JsonEvent *event) {};
MYJSON_API int json_parser_load(JsonParser *parser, JsonDocument *document) {};
MYJSON_API int json_parser_delete(JsonParser *parser) {};

MYJSON_API int json_parser_set_input_file(JsonParser *parser, FILE *file) {
    MYJSON_ASSERT(file);   /**<  Non-NULL file object expected. */
    MYJSON_ASSERT(parser); /**< Non-NULL parser object expected. */
    // MYJSON_ASSERT(!parser->read_handler); /**< You can set the source only once. */

    parser->read_handler = _myjson_file_read_handler;
    parser->read_handler_data = parser;

    parser->input.file = file;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_parser_set_input_string(JsonParser *parser, const unsigned char *input, size_t size) {
    MYJSON_ASSERT(input);                 /**< Non-NULL input string expected. */
    MYJSON_ASSERT(parser);                /**< Non-NULL parser object expected. */
    MYJSON_ASSERT(!parser->read_handler); /**< You can set the source only once. */

    parser->read_handler = _myjson_string_read_handler;
    parser->read_handler_data = parser;

    parser->input.string.start = input;
    parser->input.string.current = input;
    parser->input.string.end = input + size;
};

MYJSON_API int json_parser_set_input(JsonParser *parser, JsonReadHandler *handler, void *data) {
    MYJSON_ASSERT(parser);                /**< Non-NULL parser object expected. */
    MYJSON_ASSERT(handler);               /**< Non-NULL read handler expected. */
    MYJSON_ASSERT(!parser->read_handler); /**< You can set the source only once. */

    parser->read_handler = handler;
    parser->read_handler_data = data;

    return MYJSON_SUCCESS;
};

#pragma endregion  // Reader

#endif  // MYJSON_DISABLE_READER

#if !defined(MYJSON_DISABLE_WRITER) || !MYJSON_DISABLE_WRITER

#pragma region Writer

MYJSON_API int json_emitter_initialize(JsonEmitter *emitter) {};
MYJSON_API int json_emitter_emit(JsonEmitter *emitter, JsonEvent *event) {};
MYJSON_API int json_emitter_delete(JsonEmitter *emitter) {};

MYJSON_API int json_emitter_set_output_file(JsonEmitter *emitter, FILE *file) {
    MYJSON_ASSERT(file);                    /**< Non-NULL file object expected. */
    MYJSON_ASSERT(emitter);                 /**< Non-NULL emitter object expected. */
    MYJSON_ASSERT(!emitter->write_handler); /**< You can set the output only once. */

    emitter->write_handler = _myjson_file_write_handler;
    emitter->write_handler_data = emitter;

    emitter->output.file = file;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_set_output_string(JsonEmitter *emitter, const unsigned char *output, size_t size, size_t *size_written) {
    MYJSON_ASSERT(output);                  /**< Non-NULL output string expected. */
    MYJSON_ASSERT(emitter);                 /**< Non-NULL emitter object expected. */
    MYJSON_ASSERT(!emitter->write_handler); /**< You can set the output only once. */

    emitter->write_handler = _myjson_string_write_handler;
    emitter->write_handler_data = emitter;

    emitter->output.string.buffer = (unsigned char *)output;
    emitter->output.string.size = size;
    emitter->output.string.size_written = size_written;
    *size_written = 0;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_set_output(JsonEmitter *emitter, JsonWriteHandler *handler, void *data) {
    MYJSON_ASSERT(handler);                 /**< Non-NULL handler object expected. */
    MYJSON_ASSERT(emitter);                 /**< Non-NULL emitter object expected. */
    MYJSON_ASSERT(!emitter->write_handler); /**< You can set the output only once. */

    emitter->write_handler = handler;
    emitter->write_handler_data = data;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_set_encoding(JsonEmitter *emitter, JsonEncoding encoding) {
    MYJSON_ASSERT(emitter);            /**< Non-NULL emitter object expected. */
    MYJSON_ASSERT(!emitter->encoding); /**< You can set encoding only once. */

    emitter->encoding = encoding;
    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_open(JsonEmitter *emitter) {
    MYJSON_ASSERT(emitter);          /**< Non-NULL emitter object is required. */
    MYJSON_ASSERT(!emitter->opened); /**< Emitter should not be opened yet. */

    JsonEvent event;
    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event.type = JSON_STREAM_START_EVENT;
    event.start_pos = pos;
    event.end_pos = pos;
    event.data.stream_start.encoding = JSON_ANY_ENCODING;

    if (!json_emitter_emit(emitter, &event)) {
        return MYJSON_FAILURE;
    }

    emitter->opened = 1;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_close(JsonEmitter *emitter) {
    MYJSON_ASSERT(emitter);         /**< Non-NULL emitter object is required. */
    MYJSON_ASSERT(emitter->opened); /**< Emitter should be opened. */

    if (emitter->closed) {
        return MYJSON_SUCCESS;
    }

    JsonEvent event;
    JsonPosition pos = {0, 0, 0};

    memset(&(event), 0, sizeof(JsonEvent));
    event.type = JSON_STREAM_END_EVENT;
    event.start_pos = pos;
    event.end_pos = pos;

    if (!json_emitter_emit(emitter, &event)) {
        return MYJSON_FAILURE;
    }

    emitter->closed = 1;

    return MYJSON_SUCCESS;
};

MYJSON_API int json_emitter_flush(JsonEmitter *emitter) {};

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

#pragma region JsonEncoding

#pragma endregion  // JsonEncoding

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

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
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
 */