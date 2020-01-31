#ifndef MATERIAL_HELPER
#define MATERIAL_HELPER


void setColor(const Napi::CallbackInfo& info) {
  CVX_Material* mat = reinterpret_cast<CVX_Material*>(info.Data());

  if (info.Length() >= 3) {
    float red = info[0].As<Napi::Number>().Int64Value();
    float blue = info[1].As<Napi::Number>().Int64Value();
    float green = info[2].As<Napi::Number>().Int64Value();
    if (info.Length() == 3) {
        mat->setColor(red, blue, green);
    } else {
        float alpha = info[3].As<Napi::Number>().Int64Value();
        mat->setColor(red, blue, green, alpha);
    }
  } else {
    Napi::TypeError::New(info.Env(), "Wrong number of arguments")
            .ThrowAsJavaScriptException();
  }
}

Napi::Value getColor(const Napi::CallbackInfo& info) {
  CVX_Material* mat = reinterpret_cast<CVX_Material*>(info.Data());

  Napi::Array colorArray = Napi::Array::New(info.Env(), 4);
  colorArray[(uint32_t) 0] = Napi::Number::New(info.Env(), mat->red());
  colorArray[(uint32_t) 1] = Napi::Number::New(info.Env(), mat->blue());
  colorArray[(uint32_t) 2] = Napi::Number::New(info.Env(), mat->green());
  colorArray[(uint32_t) 3] = Napi::Number::New(info.Env(), mat->alpha());

  return colorArray;
}

#endif
