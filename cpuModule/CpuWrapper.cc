// #include <napi.h>
// #include <iostream>
#include "Cpu.cc"
using namespace std;

class CpuWrapper : public Napi::ObjectWrap<CpuWrapper> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports) {
            Napi::Function constructor = DefineClass(env, "Cpu", {
                // InstanceMethod("getProcessorCount", &CpuWrapper::getProcessorCount),
                InstanceMethod("getCpuIdle", &CpuWrapper::getCpuIdle),
                InstanceMethod("vendor", &CpuWrapper::vendor),
                InstanceMethod("model", &CpuWrapper::model),
                InstanceMethod("cores", &CpuWrapper::cores),
                InstanceMethod("logicalCores", &CpuWrapper::logicalCores),
                InstanceMethod("frequency", &CpuWrapper::frequency),
                InstanceMethod("getCacheInfo", &CpuWrapper::getCacheInfo)
            });
            exports.Set("Cpu", constructor);
            return exports;
        }
        CpuWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<CpuWrapper>(info) {
            cpu = new Cpu();
        }
        ~CpuWrapper() {
            delete cpu;
        }
        Napi::Value getCpuIdle(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::Number::New(env, cpu->getCpuIdle());
        }
        Napi::Value vendor(const Napi:: CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::String::New(env, cpu->vendor());
        }
        Napi::Value model(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::String::New(env, cpu->model());
        }
        Napi::Value cores(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::Number::New(env, cpu->cores());
        }
        Napi::Value logicalCores(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::Number::New(env, cpu->logicalCpus());
        }
        Napi::Value frequency(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            return Napi::Number::New(env, cpu->cpuSpeedInMHz());
        }
        Napi::Value getCacheInfo(const Napi::CallbackInfo& info) {
            Napi::Env env = info.Env();
            vector<CacheInfo> cacheInfo= cpu->getCacheInfo();
            Napi::Array result = Napi::Array::New(env, cacheInfo.size());
            for (size_t i = 0; i < cacheInfo.size(); ++i) {
                Napi::Object obj = Napi::Object::New(env);
                obj.Set("level", Napi::Number::New(env, cacheInfo[i].level));
                obj.Set("sizeKB", Napi::Number::New(env, cacheInfo[i].sizeKB));
                obj.Set("associativity", Napi::Number::New(env, cacheInfo[i].associativity));
                obj.Set("lineSize", Napi::Number::New(env, cacheInfo[i].lineSize));

                result.Set(i, obj); // Add the object to the array
            }
            return result;
        }

    private:
        Cpu* cpu;
};