#ifndef SIMDJSON_STREAM_ARRAY_INL_H
#define SIMDJSON_STREAM_ARRAY_INL_H

#include "simdjson/stream/array.h"
#include "simdjson/stream/element.h"

namespace simdjson {
namespace stream {

//
// array
//
really_inline array::array(internal::json_iterator &_json) noexcept
  : json{_json} {
}
really_inline array::iterator array::begin() noexcept {
  return iterator(json);
}
really_inline array::iterator array::end() const noexcept {
  return iterator(json);
}

//
// array::iterator
//
really_inline array::iterator::iterator(internal::json_iterator &_json) noexcept
  : json{_json} {
}
really_inline simdjson_result<element> array::iterator::operator*() noexcept {
  // Check the comma
  error_code error;
  if (at_start) {
    at_start = false; // If we're at the start, there's no comma to check.
    error = SUCCESS;
  } else {
    error = *json.advance() == ',' ? SUCCESS : TAPE_ERROR;
  }

  return { element(json), error };
}
really_inline array::iterator &array::iterator::operator++() noexcept {
  return *this;
}
really_inline bool array::iterator::operator!=(const array::iterator &) noexcept {
  // Stop if we hit }
  if (*json.get() == ']') { json.advance(); return false; }
  return true;
}

} // namespace stream
} // namespace simdjson

#endif // SIMDJSON_STREAM_ARRAY_INL_H