
class MemBase 
{
    public:
        virtual long long int getTotalMemory() = 0;
        virtual long long int getFreeMemory() = 0;
        virtual memoryInfo ramDetails() = 0;
};