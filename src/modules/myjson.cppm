/**
 * @file myjson.cppm
 * @brief File containing the module declaration for myjson.
 */

module;

#include <myjson/myjson.hpp>

export module myjson;

/**
 * @namespace myjson
 * @brief The myjson namespace myjson::
 */
export namespace myjson {

/**
 * @namespace literals
 * @brief The myjson namespace myjson::literals::
 */
inline namespace literals {

using ::myjson::literals::operator""_json;

}  // namespace literals

using ::myjson::json;

}  // namespace myjson
