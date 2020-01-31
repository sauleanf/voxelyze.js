#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <napi.h>
#include "Voxelyze/CVoxelyze.h"
#include <string>

class Voxelyze : public Napi::ObjectWrap<Voxelyze> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Voxelyze(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;

  Napi::Value materialCount(const Napi::CallbackInfo& info);
  Napi::Value addMaterial(const Napi::CallbackInfo& info);
  Napi::Value setVoxel(const Napi::CallbackInfo& info);
  Napi::Value voxelCount(const Napi::CallbackInfo& info);
  void doLinearSolve(const Napi::CallbackInfo& info);
  void doTimeStep(const Napi::CallbackInfo& info);
  void setVoxelSize(const Napi::CallbackInfo& info);
	Napi::Value getVoxelSize(const Napi::CallbackInfo& info);
  Napi::Value linkCount(const Napi::CallbackInfo& info);
  void enableFloor(const Napi::CallbackInfo& info);
  Napi::Value isFloorEnabled(const Napi::CallbackInfo& info);
  void setGravity(const Napi::CallbackInfo& info);
  Napi::Value getGravity(const Napi::CallbackInfo& info);
  void getVoxel(const Napi::CallbackInfo& info);
  void saveJSON(const Napi::CallbackInfo& info);

  CVoxelyze* voxelyze;
};

#endif
