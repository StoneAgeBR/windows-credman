#include <nan.h>
#include <wincred.h>



using namespace v8;



NAN_METHOD(GetCredentials) {  
  if (info.Length() < 1) {
    Nan::ThrowSyntaxError("You should provide saved credentials name");
    return;
  }

  if (!info[0]->IsString()) {
    Nan::ThrowSyntaxError("First parameter is not a string");
    return;
  }

  v8::Isolate* isolate = info.GetIsolate();
  v8::String::Utf8Value str(isolate, info[0]);

  auto length = str.length();

  PCREDENTIAL cred;
  if(::CredRead(*str, CRED_TYPE_GENERIC, 0, &cred))
  {
    auto blobSize = cred->CredentialBlobSize;
  
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    Nan::Set(obj, Nan::New("username").ToLocalChecked(), Nan::New(cred->UserName).ToLocalChecked());
    Nan::Set(obj, Nan::New("password").ToLocalChecked(), Nan::New((uint16_t *)cred->CredentialBlob, blobSize/2).ToLocalChecked());

    info.GetReturnValue().Set(obj);

    ::CredFree(cred);
  }

}

NAN_MODULE_INIT(InitAll) {

  Nan::Set(target, Nan::New<String>("getCredentials").ToLocalChecked(),

    Nan::GetFunction(Nan::New<FunctionTemplate>(GetCredentials)).ToLocalChecked());
}


NODE_MODULE(addon, InitAll)