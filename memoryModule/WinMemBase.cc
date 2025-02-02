#include "MemBase.cc"
class WinMemBase : public MemBase 
{
    public:
        long long int getTotalMemory(){
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullTotalPhys;
        }
        long long int getFreeMemory(){
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullAvailPhys;
        }
        memoryInfo ramDetails() {

            memoryInfo memoryInformation;

            HRESULT hres;

            // Initialize COM
            hres = CoInitializeEx(0, COINIT_MULTITHREADED);
            if (FAILED(hres)) {
                //std::cout << "Failed to initialize COM library. Error code = 0x" << std::hex << hres << std::endl;
                return memoryInformation;
            }

            // Initialize security
            hres = CoInitializeSecurity(
                NULL,
                -1,                          // Default authentication
                NULL,                        // No authentication services
                NULL,                        // Reserved
                RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
                RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
                NULL,                        // No additional parameters
                EOAC_NONE,                   // No proxy
                NULL                         // Reserved
            );

            if (FAILED(hres)) {
                //std::cout << "Failed to initialize security. Error code = 0x" << std::hex << hres << std::endl;
                CoUninitialize();
                return memoryInformation;
            }

            IWbemLocator* pLoc = NULL;

            // Create WMI Locator
            hres = CoCreateInstance(
                CLSID_WbemLocator,
                0,
                CLSCTX_INPROC_SERVER,
                IID_IWbemLocator,
                (LPVOID*)&pLoc
            );

            if (FAILED(hres)) {
                //std::cout << "Failed to create IWbemLocator object. Error code = 0x" << std::hex << hres << std::endl;
                CoUninitialize();
                return memoryInformation;
            }

            IWbemServices* pSvc = NULL;

            // Connect to WMI namespace
            hres = pLoc->ConnectServer(
                _bstr_t(L"ROOT\\CIMV2"), // WMI Namespace
                NULL,                    // User
                NULL,                    // Password
                0,                       // Locale
                NULL,                    // Security Flags
                0,                       // Authority
                0,                       // Context
                &pSvc                    // IWbemServices Proxy
            );

            if (FAILED(hres)) {
                //std::cout << "Could not connect to WMI namespace. Error code = 0x" << std::hex << hres << std::endl;
                pLoc->Release();
                CoUninitialize();
                return memoryInformation;
            }

            // Set security level for the proxy
            hres = CoSetProxyBlanket(
                pSvc,                        // IWbemServices Proxy
                RPC_C_AUTHN_WINNT,
                RPC_C_AUTHZ_NONE,
                NULL,
                RPC_C_AUTHN_LEVEL_CALL,
                RPC_C_IMP_LEVEL_IMPERSONATE,
                NULL,
                EOAC_NONE
            );

            if (FAILED(hres)) {
                //std::cout << "Could not set proxy blanket. Error code = 0x" << std::hex << hres << std::endl;
                pSvc->Release();
                pLoc->Release();
                CoUninitialize();
                return memoryInformation;
            }

            IEnumWbemClassObject* pEnumerator = NULL;
            hres = pSvc->ExecQuery(
                bstr_t("WQL"),
                bstr_t("SELECT * FROM Win32_PhysicalMemory"),
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                NULL,
                &pEnumerator
            );

            if (FAILED(hres)) {
                //std::cout << "Query for memory information failed. Error code = 0x" << std::hex << hres << std::endl;
                pSvc->Release();
                pLoc->Release();
                CoUninitialize();
                return memoryInformation;
            }

            IWbemClassObject* pclsObj = NULL;
            ULONG uReturn = 0;

            // Enumerate through the results
            while (pEnumerator) {
                HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

                if (0 == uReturn) {
                    break;
                }

                VARIANT vtProp;

                // RAM Type
                pclsObj->Get(L"SMBIOSMemoryType", 0, &vtProp, 0, 0);

                switch (vtProp.uintVal) {
                case 20:
                    memoryInformation.memType = "DDR";
                    break;
                case 21:
                    memoryInformation.memType = "DDR2";
                    break;
                case 22:
                    memoryInformation.memType = "DDR2 FB-DIMM";
                    break;
                case 24:
                    memoryInformation.memType = "DDR3";
                    break;
                case 26:
                    memoryInformation.memType = "DDR4";
                    break;
                case 27:
                    memoryInformation.memType = "DDR5";
                    break;
                default:
                    memoryInformation.memType = "Type Unknown";
                    break;
                }
                VariantClear(&vtProp);

                // Clock Speed
                pclsObj->Get(L"ConfiguredClockSpeed", 0, &vtProp, 0, 0);
                memoryInformation.clockSpeed = vtProp.uintVal;
                VariantClear(&vtProp);

                // Voltage
                pclsObj->Get(L"ConfiguredVoltage", 0, &vtProp, 0, 0);
                memoryInformation.voltage = vtProp.uintVal;
                VariantClear(&vtProp);

                pclsObj->Release();
            }

            // Cleanup
            pSvc->Release();
            pLoc->Release();
            pEnumerator->Release();
            CoUninitialize();
            return memoryInformation;
        }
};