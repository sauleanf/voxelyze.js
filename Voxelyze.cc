#include "Voxelyze.h"
#include "VoxelHelper.h"
#include "materialHelper.h"
#include <iostream>

Napi::FunctionReference Voxelyze::constructor;

Napi::Object Voxelyze::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func =
    DefineClass(env,
      "Voxelyze", {
        InstanceMethod("materialCount", & Voxelyze::materialCount),
        InstanceMethod("addMaterial", & Voxelyze::addMaterial),
        InstanceMethod("setVoxel", & Voxelyze::setVoxel),
        InstanceMethod("getVoxelSize", & Voxelyze::getVoxelSize),
        InstanceMethod("setVoxelSize", & Voxelyze::setVoxelSize),
        InstanceMethod("voxelCount", & Voxelyze::voxelCount),
        InstanceMethod("doLinearSolve", & Voxelyze::doLinearSolve),
        InstanceMethod("doTimeStep", & Voxelyze::doTimeStep),
        InstanceMethod("linkCount", & Voxelyze::linkCount),
        InstanceMethod("isFloorEnabled", & Voxelyze::isFloorEnabled),
        InstanceMethod("enableFloor", & Voxelyze::enableFloor),
        InstanceMethod("getGravity", & Voxelyze::getGravity),
        InstanceMethod("setGravity", & Voxelyze::setGravity),
        InstanceMethod("getVoxel", & Voxelyze::getVoxel),
        InstanceMethod("saveJSON", & Voxelyze::saveJSON),
        InstanceMethod("enableCollisions", & Voxelyze::enableCollisions),
        InstanceMethod("isCollisionsEnabled", & Voxelyze::isCollisionsEnabled),
        InstanceMethod("setAmbientTemperature", & Voxelyze::setAmbientTemperature),
        InstanceMethod("ambientTemperature", & Voxelyze::ambientTemperature)
      });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Voxelyze", func);
  return exports;
}

Voxelyze::Voxelyze(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Voxelyze>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 0) {
    this->voxelyze = new CVoxelyze();
  } else if(info.Length() == 1) {
    if(info[0].IsNumber()) {
      this->voxelyze = new CVoxelyze(info[0].As<Napi::Number>().FloatValue());
    } else if (info[0].IsString()) {
      this->voxelyze = new CVoxelyze(info[0].As<Napi::String>().Utf8Value().c_str());
    } else {
      Napi::TypeError::New(env, "Use either a number of string as argument")
      .ThrowAsJavaScriptException();
    }
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
    .ThrowAsJavaScriptException();
  }
}

Napi::Value Voxelyze::materialCount(const Napi::CallbackInfo& info) {
  int materialCount = voxelyze->materialCount();

  return Napi::Number::New(info.Env(), materialCount);
}

Napi::Value Voxelyze::addMaterial(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if(info.Length() != 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
    .ThrowAsJavaScriptException();
    return env.Null();
  } else if (!info[0].IsNumber() || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Numbers are expected")
    .ThrowAsJavaScriptException();
    return env.Null();
  }

  float youngsModulus = info[0].As<Napi::Number>().FloatValue();
  float density = info[1].As<Napi::Number>().FloatValue();

  int index = voxelyze->materialCount();
  auto mat = voxelyze->addMaterial(youngsModulus, density);

  Napi::Object matObject = Napi::Object::New(env);
  matObject.Set("index", index);
  matObject.DefineProperties({
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "setColor",
      setColor,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat)),
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "getColor",
      getColor,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat)),
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "stress",
      stress,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat)),
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "modulus",
      modulus,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat)),
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "isModelLinear",
      isModelLinear,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat)),
    Napi::PropertyDescriptor::Function(
      env,
      matObject,
      "getYoungsModulus",
      getYoungsModulus,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(mat))
  });

  return matObject;
}

Napi::Value Voxelyze::setVoxel(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() != 4) {
    Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
  }
  int index = 0;
  if(info[0].IsNumber()) {
    index = info[0].As<Napi::Number>().Int32Value();
  } else if (info[0].IsObject() && info[0].ToObject().Has("index")) {
    index = info[0].ToObject().Get("index").As<Napi::Number>().Int32Value();
  } else {
    Napi::TypeError::New(env, "First argument has be either an Object with the field index set or an integer")
    .ThrowAsJavaScriptException();
    return env.Null();
  }
  float x = info[1].As<Napi::Number>().FloatValue();
  float y = info[2].As<Napi::Number>().FloatValue();
  float z = info[3].As<Napi::Number>().FloatValue();

  if(index > voxelyze->materialCount()) {
    Napi::TypeError::New(env, "There is no material at that index")
    .ThrowAsJavaScriptException();
        return env.Null();
  }

  auto mat = voxelyze->material(index);
  auto voxel = voxelyze->setVoxel(mat, x, y, z);

  Napi::Object voxelObject = Napi::Object::New(env);

  setVoxelObjectProperities(voxel, env, voxelObject);

  return voxelObject;
}

void Voxelyze::doLinearSolve(const Napi::CallbackInfo& info) {
  voxelyze->doLinearSolve();
}

void Voxelyze::doTimeStep(const Napi::CallbackInfo& info) {
  float dt = -1.0f;
  if(info.Length() == 1) {
    dt = info[0].As<Napi::Number>().FloatValue();
  } else if(info.Length() > 1) {
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
  } else if(info.Length() == 0) {
    voxelyze->enableFloor();
  } else {
    voxelyze->enableFloor(info[0].ToBoolean());
  }
}

Napi::Value Voxelyze::isFloorEnabled(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), voxelyze->isFloorEnabled());
}

void Voxelyze::setGravity(const Napi::CallbackInfo& info) {
  if(info.Length() != 1) {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  } else if(!info[0].IsNumber()) {
    Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
  } else {
    voxelyze->setGravity(info[0].As<Napi::Number>().FloatValue());
  }
}

Napi::Value Voxelyze::getGravity(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->gravity());
}

void Voxelyze::getVoxel(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(info.Env(), "Three numbers are expected").ThrowAsJavaScriptException();
  } else {
    float x = info[0].As<Napi::Number>().FloatValue();
    float y = info[1].As<Napi::Number>().FloatValue();
    float z = info[2].As<Napi::Number>().FloatValue();

    Napi::Object voxelCallbackObject = Napi::Object::New(env);

    CVX_Voxel* voxel = voxelyze->voxel(x, y, z);

    Napi::Function cb = info[3].As<Napi::Function>();

    setVoxelObjectProperities(voxel, env, voxelCallbackObject);

    cb.Call(env.Global(), { voxelCallbackObject });
  }
}

void Voxelyze::saveJSON(const Napi::CallbackInfo& info) {
  if(info[0] && info[0].IsString()) {
    voxelyze->saveJSON(info[0].As<Napi::String>().Utf8Value().c_str());
  } else {
    Napi::TypeError::New(info.Env(), "A string is expected")
    .ThrowAsJavaScriptException();
  }
}

void Voxelyze::setAmbientTemperature(const Napi::CallbackInfo& info) {
  if(info.Length() != 1 && info.Length() != 2) {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  } else if(info.Length() == 1) {
    if(!info[0].IsNumber()) {
      Napi::TypeError::New(info.Env(), "Number expected").ThrowAsJavaScriptException();
    } else {
      voxelyze->setAmbientTemperature(info[0].As<Napi::Number>().FloatValue());
    }
  } else {
    if(!info[0].IsNumber() && !info[1].IsBoolean()) {
      Napi::TypeError::New(info.Env(), "Number and Boolean expected").ThrowAsJavaScriptException();
    } else {
      voxelyze->setAmbientTemperature(info[0].As<Napi::Number>().FloatValue(), info[1].ToBoolean());
    }
  }
}

Napi::Value Voxelyze::ambientTemperature(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), voxelyze->ambientTemperature());
}

void Voxelyze::enableCollisions(const Napi::CallbackInfo& info) {
  if(info.Length() == 0) {
    voxelyze->enableCollisions();
  } else if (info.Length() == 1) {
    if(info[0].IsBoolean()) {
      voxelyze->enableCollisions(info[1].ToBoolean());
    } else {
      Napi::TypeError::New(info.Env(), "Boolean expected").ThrowAsJavaScriptException();
    }
  } else {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
  }
}

Napi::Value Voxelyze::isCollisionsEnabled(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), voxelyze->isCollisionsEnabled());
}
