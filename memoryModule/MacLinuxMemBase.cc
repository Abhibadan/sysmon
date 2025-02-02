#include "MemBase.cc"
class MacLinuxMemBase : public MemBase{
    public:
        long long int getTotalMemory(){
            try{
                return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);

            }catch(...){
                return 0;
            }
        }
        long long int getFreeMemory(){
            try{
                return sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
            }catch(...) {
                return 0;
            }
        }
        memoryInfo ramDetails(){
            memoryInfo info;
            return info;
        }
};