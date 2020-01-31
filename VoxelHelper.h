#ifndef VOXEL_HELPER
#define VOXEL_HELPER

void setForce(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  float x = info[0].As<Napi::Number>().FloatValue();
  float y = info[1].As<Napi::Number>().FloatValue();
  float z = info[2].As<Napi::Number>().FloatValue();

  voxel->external()->setForce(x, y, z);
}

Napi::Value getForce(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  auto force = voxel->force();

  Napi::Array forceArray = Napi::Array::New(info.Env(), 3);
  forceArray[(uint32_t) 0] = Napi::Number::New(info.Env(), force.x);
  forceArray[(uint32_t) 1] = Napi::Number::New(info.Env(), force.y);
  forceArray[(uint32_t) 2] = Napi::Number::New(info.Env(), force.z);

  return forceArray;
}

void setFixedAll(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  voxel->external()->setFixedAll();
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

void setVoxelObjectProperities(CVX_Voxel* voxel, Napi::Env& env, Napi::Object& voxelObject) {
  voxelObject.DefineProperties({
    Napi::PropertyDescriptor::Function(
      env,
      voxelObject,
      "setForce",
      setForce, napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(
      env,
      voxelObject,
      "position",
      position,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(
      env,
      voxelObject,
      "setFixedAll",
      setFixedAll,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "getForce",
      getForce,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel))
  });
}

#endif
