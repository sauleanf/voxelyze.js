#include <napi.h>
#include "Voxelyze.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Voxelyze::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll)
