#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"

napi_value solve(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2;
  napi_value argv[2];

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (argc < 1) {
    napi_throw_error(env, "E80001", "Too few arguments");
    return NULL;
  }

  size_t len;
  char facelets[55];
  char pattern[55];
  char* facelets_ptr = facelets;

  status = napi_get_value_string_utf8(env, argv[0], facelets, 55, &len);
  if (status != napi_ok) {
    napi_throw_error(env, "E80002", "Invalid arguments");
    return NULL;
  }

  if (argc > 1) {
    char patternized[64];

    status = napi_get_value_string_utf8(env, argv[1], pattern, 55, &len);
    if (status != napi_ok) {
      napi_throw_error(env, "E80003", "Invalid arguments");
      return NULL;
    }

    patternize(facelets, pattern, patternized);
    facelets_ptr = patternized;
  }

  char *sol = solution(facelets_ptr, 24, 1000, 0, "cache");

  if (sol == NULL) {
    napi_throw_error(env, "E80004", "Unsolvable cube");
    return NULL;
  }

  napi_value data;
  status = napi_create_string_utf8(env, sol, NAPI_AUTO_LENGTH, &data);
  assert(status == napi_ok);
  return data;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("solve", solve);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
