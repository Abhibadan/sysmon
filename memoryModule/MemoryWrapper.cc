#include "Memory.cc"
using namespace std;
class MemoryWrapper : public Napi::ObjectWrap<MemoryWrapper>{
    public:
        static Napi::Object Init(Napi::Env env,Napi::Object exports){
            Napi::Function constructor = DefineClass(env, "Memory", {
                InstanceMethod("getTotalMemory", &MemoryWrapper::getTotalMemory),
                InstanceMethod("getFreeMemory", &MemoryWrapper::getFreeMemory),
                InstanceMethod("ramDetails", &MemoryWrapper::ramDetails)
            });
            exports.Set("Memory", constructor);
            return exports;
        }

        MemoryWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MemoryWrapper>(info){
            memory = new Memory();
        }
        ~MemoryWrapper(){
            delete memory;
        }
        Napi::Value getTotalMemory(const Napi::CallbackInfo& info){
            Napi::Env env = info.Env();
            return Napi::Number::New(env, memory->getTotalMemory());
        }
        Napi::Value getFreeMemory(const Napi::CallbackInfo& info){
            Napi::Env env = info.Env();
            return Napi::Number::New(env, memory->getFreeMemory());
        }
        Napi::Value ramDetails(const Napi::CallbackInfo& info){
            Napi::Env env = info.Env();
            memoryInfo memoryInformation=memory->ramDetails();
            Napi::Object obj = Napi::Object::New(env);
            obj.Set("memType", Napi::String::New(env, memoryInformation.memType));
            obj.Set("clockSpeed", Napi::Number::New(env, memoryInformation.clockSpeed));
            obj.Set("voltage", Napi::Number::New(env, memoryInformation.voltage));
            return obj;
        }
    private:
        Memory *memory;        
};

// Napi::Object InitAll(Napi::Env env, Napi::Object exports){
//     MemoryWrapper::Init(env, exports);
//     return exports;
// }

// NODE_API_MODULE(Sys_info, InitAll)