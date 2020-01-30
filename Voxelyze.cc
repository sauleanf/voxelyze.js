#include "voxelyze.h"
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
                    InstanceMethod("setVoxel", &Voxelyze::setVoxel),
                    InstanceMethod("getVoxelSize", &Voxelyze::getVoxelSize),
                    InstanceMethod("setVoxelSize", &Voxelyze::setVoxelSize),
                    InstanceMethod("voxelCount", &Voxelyze::voxelCount),
                    InstanceMethod("doLinearSolve", &Voxelyze::doLinearSolve),
                    InstanceMethod("doTimeStep", &Voxelyze::doTimeStep),
                    InstanceMethod("linkCount", &Voxelyze::linkCount),
                    InstanceMethod("isFloorEnabled", &Voxelyze::isFloorEnabled),
                    InstanceMethod("enableFloor", &Voxelyze::enableFloor),
                    InstanceMethod("getGravity", &Voxelyze::getGravity),
                    InstanceMethod("setGravity", &Voxelyze::setGravity),
                    InstanceMethod("getVoxel", &Voxelyze::getVoxel)
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Voxelyze", func);
  return exports;
}

Voxelyze::Voxelyze(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Voxelyze>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->voxelyze = new CVoxelyze(info[0].As<Napi::Number>().FloatValue());
}

Napi::Value Voxelyze::materialCount(const Napi::CallbackInfo& info) {
  int materialCount = voxelyze->materialCount();

  return Napi::Number::New(info.Env(), materialCount);
}

Napi::Value Voxelyze::addMaterial(const Napi::CallbackInfo& info) {
  //std::string density = info[0].ToString();
  float youngsModulus = info[0].As<Napi::Number>().FloatValue();
  float density = info[1].As<Napi::Number>().FloatValue();

  int index = voxelyze->materialCount();
  voxelyze->addMaterial(youngsModulus, density);

  return Napi::Number::New(info.Env(), index);
}

Napi::Value Voxelyze::setVoxel(const Napi::CallbackInfo& info) {
  int index = info[0].As<Napi::Number>().Int32Value();
  float x = info[1].As<Napi::Number>().FloatValue();
  float y = info[2].As<Napi::Number>().FloatValue();
  float z = info[3].As<Napi::Number>().FloatValue();

  auto mat = voxelyze->material(index);
  auto voxel = voxelyze->setVoxel(mat, x, y, z);

  return Napi::Number::New(info.Env(), index);
}

void Voxelyze::doLinearSolve(const Napi::CallbackInfo& info) {
  voxelyze->doLinearSolve();
}

void Voxelyze::doTimeStep(const Napi::CallbackInfo& info) {
  float dt;
  if(info.Length() == 0) {
    dt = -1.0f;
  } else if(info.Length() == 1) {
    dt = info[0].As<Napi::Number>().FloatValue();
  } else {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  }

  voxelyze->doTimeStep(dt);
}

void Voxelyze::setVoxelSize(const Napi::CallbackInfo& info) {
  voxelyze->setVoxelSize(info[0].As<Napi::Number>().DoubleValue());
}

Napi::Value Voxelyze::getVoxelSize(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->voxelSize());
}

Napi::Value Voxelyze::voxelCount(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->voxelCount());
}

Napi::Value Voxelyze::linkCount(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->linkCount());
}

void Voxelyze::enableFloor(const Napi::CallbackInfo& info) {
  if(info.Length() != 1) {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  } else if(!info[0].IsBoolean()) {
    Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
  }
  voxelyze->enableFloor(info[0].ToBoolean());
}

Napi::Value Voxelyze::isFloorEnabled(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), voxelyze->isFloorEnabled());
}

void Voxelyze::setGravity(const Napi::CallbackInfo& info) {
  if(info.Length() != 1) {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  } else if(!info[0].IsNumber()) {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  }
  voxelyze->setGravity(info[0].As<Napi::Number>().FloatValue());
}

Napi::Value Voxelyze::getGravity(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->gravity());
}

void setForce(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  float x = info[0].As<Napi::Number>().FloatValue();
  float y = info[1].As<Napi::Number>().FloatValue();
  float z = info[2].As<Napi::Number>().FloatValue();

  voxel->external()->setForce(x, y, z);
}

Napi::Value position(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  auto position = voxel->position();
  Napi::Array positionArray = Napi::Array::New(info.Env(), 3);
  positionArray[(uint32_t) 0] = Napi::Number::New(info.Env(), position.x);
  positionArray[(uint32_t) 1] = Napi::Number::New(info.Env(), position.y);
  positionArray[(uint32_t) 2] = Napi::Number::New(info.Env(), position.z);
  return positionArray;
}

void Voxelyze::getVoxel(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  float x = info[0].As<Napi::Number>().FloatValue();
  float y = info[1].As<Napi::Number>().FloatValue();
  float z = info[2].As<Napi::Number>().FloatValue();

  Napi::Object voxelCallbackObject = Napi::Object::New(env);

  CVX_Voxel* voxel = voxelyze->voxel(x, y, z);

  Napi::Function cb = info[3].As<Napi::Function>();

  voxelCallbackObject.DefineProperties({
    Napi::PropertyDescriptor::Function(env, voxelCallbackObject, "setForce", setForce, napi_property_attributes::napi_default, reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env, voxelCallbackObject, "position", position, napi_property_attributes::napi_default, reinterpret_cast<void*>(voxel))
  });

  cb.Call(env.Global(), { voxelCallbackObject });
}
