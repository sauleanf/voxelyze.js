#include "Voxelyze.h"
#include <iostream>

Napi::FunctionReference Voxelyze::constructor;

Napi::Object Voxelyze::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
      DefineClass(env,
                  "Voxelyze",
                  {
                    InstanceMethod("materialCount", &Voxelyze::materialCount),
                    InstanceMethod("addMaterial", &Voxelyze::addMaterial),
                    InstanceMethod("setVoxel", &Voxelyze::setVoxel)
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Voxelyze", func);
  return exports;
}

Voxelyze::Voxelyze(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Voxelyze>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->voxelyze = CVoxelyze(info[0].As<Napi::Number>().FloatValue());
}

Napi::Value Voxelyze::materialCount(const Napi::CallbackInfo& info) {
  int materialCount = voxelyze.materialCount();

  return Napi::Number::New(info.Env(), materialCount);
}

Napi::Value Voxelyze::addMaterial(const Napi::CallbackInfo& info) {
  //std::string density = info[0].ToString();
  float youngsModulus = info[0].As<Napi::Number>().FloatValue();
  float density = info[1].As<Napi::Number>().FloatValue();

  int index = voxelyze.materialCount();
  voxelyze.addMaterial(youngsModulus, density);

  return Napi::Number::New(info.Env(), index);
}

Napi::Value Voxelyze::setVoxel(const Napi::CallbackInfo& info) {
  int index = info[0].As<Napi::Number>().Int32Value();
  float x = info[1].As<Napi::Number>().FloatValue();
  float y = info[2].As<Napi::Number>().FloatValue();
  float z = info[3].As<Napi::Number>().FloatValue();

  auto mat = voxelyze.material(index);

  auto voxel = voxelyze.setVoxel(mat, x, y, z);
  Napi::Array corners = Napi::Array::New(info.Env(), 8);
  for(uint32_t i = 0; i < 8; i++) {
    Napi::Array corners1 = Napi::Array::New(info.Env(), 3);
    auto vec = voxel->cornerOffset(i);
    std::cout << vec.getX() << std::endl;
    corners1[(uint32_t) 0] = Napi::Number::New(info.Env(), vec.getX());
    corners1[(uint32_t) 1] = Napi::Number::New(info.Env(), vec.getY());
    corners1[(uint32_t) 2] = Napi::Number::New(info.Env(), vec.getZ());
    corners[i] = corners1;
  }

  return corners;
}
