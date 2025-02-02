#include "CpuBase.cc"

class MacLinuxCpuBase : public CpuBase {
    private:
        // FILETIME idleTime, kernelTime, userTime;
        // FILETIME prevIdleTime, prevKernelTime, prevUserTime;
    
    public:
    
        MacLinuxCpuBase(){
            // GetSystemTimes(&prevIdleTime, &prevKernelTime, &prevUserTime);
            cout <<"MacLinuxCpuBase"<<endl;
        }
        float getCpuIdle(){
            // GetSystemTimes(&idleTime, &kernelTime, &userTime);

            // ULARGE_INTEGER idle, kernel, user;
            // idle.LowPart = idleTime.dwLowDateTime;
            // idle.HighPart = idleTime.dwHighDateTime;

            // kernel.LowPart = kernelTime.dwLowDateTime;
            // kernel.HighPart = kernelTime.dwHighDateTime;

            // user.LowPart = userTime.dwLowDateTime;
            // user.HighPart = userTime.dwHighDateTime;

            // ULARGE_INTEGER prevIdle, prevKernel, prevUser;
            // prevIdle.LowPart = prevIdleTime.dwLowDateTime;
            // prevIdle.HighPart = prevIdleTime.dwHighDateTime;

            // prevKernel.LowPart = prevKernelTime.dwLowDateTime;
            // prevKernel.HighPart = prevKernelTime.dwHighDateTime;

            // prevUser.LowPart = prevUserTime.dwLowDateTime;
            // prevUser.HighPart = prevUserTime.dwHighDateTime;

            // prevIdleTime = idleTime;
            // prevKernelTime = kernelTime;
            // prevUserTime = userTime;

            // ULONGLONG totalTime = (kernel.QuadPart - prevKernel.QuadPart) + (user.QuadPart - prevUser.QuadPart);
            // ULONGLONG idleTimeDiff = idle.QuadPart - prevIdle.QuadPart;
            // //return idleTimeDiff;
            // return (1.0 - ((float)idleTimeDiff / totalTime)) * 100.0;
            return 55.55;
        }
};