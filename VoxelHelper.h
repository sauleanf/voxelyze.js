#ifndef VOXEL_HELPER
#define VOXEL_HELPER

void setForce(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  float x = info[0].As<Napi::Number>().FloatValue();
  float y = info[1].As<Napi::Number>().FloatValue();
  float z = info[2].As<Napi::Number>().FloatValue();

  voxel->external()->setForce(x, y, z);
}

Napi::Value getVertices(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());

  Napi::Array vertices = Napi::Array::New(info.Env(), 2);

  Napi::Array topVertices = Napi::Array::New(info.Env(), 4);
  Napi::Array bottomVertices = Napi::Array::New(info.Env(), 4);
  Vec3D<float> cornerPosition;

  for(int i = 0; i < 4; i++) {
    Napi::Array vertexCoordinates = Napi::Array::New(info.Env(), 3);

    cornerPosition = voxel->cornerPosition((CVX_Voxel::voxelCorner) i);

    vertexCoordinates[(uint32_t) 0] = Napi::Number::New(env, cornerPosition.x);
    vertexCoordinates[(uint32_t) 1] = Napi::Number::New(env, cornerPosition.y);
    vertexCoordinates[(uint32_t) 2] = Napi::Number::New(env, cornerPosition.z);

    topVertices[(uint32_t) i] = vertexCoordinates;

    cornerPosition = voxel->cornerPosition((CVX_Voxel::voxelCorner) (i + 4));

    vertexCoordinates = Napi::Array::New(info.Env(), 3);

    vertexCoordinates[(uint32_t) 0] = Napi::Number::New(env, cornerPosition.x);
    vertexCoordinates[(uint32_t) 1] = Napi::Number::New(env, cornerPosition.y);
    vertexCoordinates[(uint32_t) 2] = Napi::Number::New(env, cornerPosition.z);

    bottomVertices[(uint32_t) i] = vertexCoordinates;
  }

  vertices[(uint32_t) 0] = topVertices;
  vertices[(uint32_t) 1] = bottomVertices;

  return vertices;
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

Napi::Value displacementMagnitude(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->displacementMagnitude());
}

Napi::Value angularDisplacementMagnitude(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->angularDisplacementMagnitude());
}

Napi::Value velocity(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  auto velocity = voxel->velocity();

  Napi::Array velocityArray = Napi::Array::New(info.Env(), 3);
  velocityArray[(uint32_t) 0] = Napi::Number::New(info.Env(), velocity.x);
  velocityArray[(uint32_t) 1] = Napi::Number::New(info.Env(), velocity.y);
  velocityArray[(uint32_t) 2] = Napi::Number::New(info.Env(), velocity.z);

  return velocityArray;
}

Napi::Value velocityMagnitude(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->velocityMagnitude());
}

Napi::Value angularVelocity(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  auto angularVelocity = voxel->angularVelocity();

  Napi::Array angularVelocityArray = Napi::Array::New(info.Env(), 3);
  angularVelocityArray[(uint32_t) 0] = Napi::Number::New(info.Env(), angularVelocity.x);
  angularVelocityArray[(uint32_t) 1] = Napi::Number::New(info.Env(), angularVelocity.y);
  angularVelocityArray[(uint32_t) 2] = Napi::Number::New(info.Env(), angularVelocity.z);

  return angularVelocityArray;
}

Napi::Value angularVelocityMagnitude(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->angularVelocityMagnitude());
}

Napi::Value kineticEnergy(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->kineticEnergy());
}

Napi::Value volumetricStrain(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->volumetricStrain());
}

Napi::Value pressure(const Napi::CallbackInfo& info) {
  CVX_Voxel* voxel = reinterpret_cast<CVX_Voxel*>(info.Data());
  return Napi::Number::New(info.Env(), voxel->pressure());
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
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "getVertices",
      getVertices,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "displacementMagnitude",
      displacementMagnitude,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "angularDisplacementMagnitude",
      angularDisplacementMagnitude,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "velocity",
      velocity,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "velocityMagnitude",
      velocityMagnitude,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "angularVelocity",
      angularVelocity,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "angularVelocityMagnitude",
      angularVelocityMagnitude,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "kineticEnergy",
      kineticEnergy,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "volumetricStrain",
      volumetricStrain,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
    Napi::PropertyDescriptor::Function(env,
      voxelObject,
      "pressure",
      pressure,
      napi_property_attributes::napi_default,
      reinterpret_cast<void*>(voxel)),
  });
}

#endif
