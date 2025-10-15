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
MYJSON_API int json_document_object_get_value(JsonDocument *document, int object_node_id, const JsonChar_t *key,
                                              int key_length) {};

MYJSON_API int json_document_get_node_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count) {};
MYJSON_API const JsonChar_t *json_document_get_value_by_path(JsonDocument *document, const JsonChar_t **keys,
                                                             int key_count) {};
MYJSON_API int json_document_get_value_length_by_path(JsonDocument *document, const JsonChar_t **keys, int key_count) {
};

#pragma endregion  // Json

#if !defined(MYJSON_DISABLE_ENCODING) || !MYJSON_DISABLE_ENCODING

#pragma region Encoding

#pragma endregion  // Encoding

#endif  // MYJSON_DISABLE_ENCODING

#if !defined(MYJSON_DISABLE_READER) || !MYJSON_DISABLE_READER

#pragma region Reader

MYJSON_API int json_parser_initialize(JsonParser *parser) {};
MYJSON_API int json_parser_parse(JsonParser *parser, JsonEvent *event) {};
MYJSON_API int json_parser_load(JsonParser *parser, JsonDocument *document) {};
MYJSON_API int json_parser_delete(JsonParser *parser) {};

MYJSON_API int json_parser_set_input_file(JsonParser *parser, FILE *file) {
    MYJSON_ASSERT(file);                  /**<  Non-NULL file object expected. */
    MYJSON_ASSERT(parser);                /**< Non-NULL parser object expected. */
    MYJSON_ASSERT(!parser->read_handler); /**< You can set the source only once. */

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

MYJSON_API int json_emitter_set_output_string(JsonEmitter *emitter, const unsigned char *output, size_t size,
                                              size_t *size_written) {
    MYJSON_ASSERT(output);                  /**< Non-NULL output string expected. */
    MYJSON_ASSERT(emitter);                 /**< Non-NULL emitter object expected. */
    MYJSON_ASSERT(!emitter->write_handler); /**< You can set the output only once. */

    emitter->write_handler = _myjson_string_write_handler;
    emitter->write_handler_data = emitter;

    emitter->output.string.buffer = output;
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
