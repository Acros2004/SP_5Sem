#include <Windows.h>
#include <iostream>
#include <string>
#include <iostream>

#define SERVICENAME L"NIKITA"

#ifdef _WIN64
#define SERVICEPATH L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/x64/Debug/OS15_HTService.exe"
#else
#define SERVICEPATH L"C:/Users/nikit/Desktop/univer/3cource1sem/SP/SP_lab7/SP_lab6/x64/Debug/OS15_HTService.exe"
#endif

char* createErrorMessage(const char* msg, int code)
{
	char* buf = new char[512];
	sprintf_s(buf, 512, "%s: error code = %d\n", msg, code);
	return buf;
}

int main(int argc, char* argv[])
{
	SC_HANDLE schService = NULL, schSCManager = NULL;
	SERVICE_STATUS status;
	try
	{
		schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

		if (!schSCManager)
		{
			throw createErrorMessage("OpenSCManager", GetLastError());
		}
		else
		{
			if (std::string(argv[1]) == "install") {
				schService = CreateService(
					schSCManager,
					SERVICENAME,
					SERVICENAME,
					SERVICE_ALL_ACCESS,
					SERVICE_WIN32_SHARE_PROCESS,
					SERVICE_AUTO_START,
					SERVICE_ERROR_NORMAL,
					SERVICEPATH,
					NULL,
					NULL,
					NULL,
					NULL,
					NULL
				);

				if (!schService)
				{
					throw createErrorMessage("CreateService", GetLastError());
				}

				std::cout << "Successfully create service" << std::endl;
			}
			else if (std::string(argv[1]) == "delete") {

				schService = OpenService(schSCManager, SERVICENAME, SERVICE_ALL_ACCESS);
				if (!schService)
				{
					throw createErrorMessage("OpenService", GetLastError());
				}

				if (!DeleteService(schService))
				{
					throw createErrorMessage("DeleteService", GetLastError());
				}
				std::cout << "Service deleted successfully." << std::endl;
			}
			else if (std::string(argv[1]) == "delete") {
				schService = OpenService(schSCManager, SERVICENAME, SERVICE_START);
				if (!schService)
				{
					printf("Failed to open service. Error code: %d\n", GetLastError());
					throw createErrorMessage("OpenService", GetLastError());
				}

				if (!StartServiceW(schService, 0, NULL))
					throw createErrorMessage("StartService", GetLastError());

				std::cout << "Service started successfully." << std::endl;
			}
			else if (std::string(argv[1]) == "stop") {

				schService = OpenService(schSCManager, SERVICENAME, SERVICE_STOP);
				if (!schService)
				{
					printf("Failed to open service. Error code: %d\n", GetLastError());
					throw createErrorMessage("OpenService", GetLastError());
				}

				if (!ControlService(schService, SERVICE_CONTROL_STOP, &status))
					throw createErrorMessage("ControlService", GetLastError());

				std::cout << "Service stopped successfully." << std::endl;
			}
			
		}
	}
	catch (char* txt)
	{
		std::cout << txt << std::endl;
	}


	if (schSCManager)
	{
		CloseServiceHandle(schSCManager);
	}

	if (schService)
	{
		CloseServiceHandle(schService);
	}
	system("pause");

	return 0;
}