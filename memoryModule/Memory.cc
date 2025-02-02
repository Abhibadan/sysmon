
#ifdef _WIN32 
#include "WinMemBase.cc"
#elif __linux__ || __APPLE__ || __MACH__
#include "MacLinuxMemBase.cc"
// #elif __unix__
// #elif __FreeBSD__
#endif

class Memory: public MemBase {
    private:
        MemBase* memBase;
    public:
        Memory(){
            #ifdef _WIN32
                memBase = new WinMemBase();
            #elif __APPLE__ || __MACH__ || __linux__ 
                memBase = new MacLinuxMemBase();
            // #elif __linux__
            //     memBase = new MacLinuxMemBase();
            // #else
            //     memBase = new MacLinuxMemBase();
            #endif
        }
        ~Memory(){
            delete memBase;
        }
        long long int getTotalMemory(){
            return memBase->getTotalMemory();
        }
        long long int getFreeMemory(){
            return memBase->getFreeMemory();
        }
        memoryInfo ramDetails(){
            return memBase->ramDetails();
        }
};
