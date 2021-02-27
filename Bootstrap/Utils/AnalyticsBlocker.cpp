#include "AnalyticsBlocker.h"
#include "Debug.h"
#include "Assertion.h"
#include "../Managers/Hook.h"
#include <algorithm>

bool AnalyticsBlocker::ShouldDAB = false;
const char* AnalyticsBlocker::HostNames[] = { new char[21] { 0x70, 0x69, 0x78, 0x65, 0x6c, 0x73, 0x74, 0x72, 0x69, 0x6b, 0x65, 0x33, 0x64, 0x61, 0x77, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[13] { 0x66, 0x61, 0x63, 0x65, 0x62, 0x6f, 0x6f, 0x6b, 0x2e, 0x6e, 0x65, 0x74, 0x00 }, new char[26] { 0x65, 0x63, 0x6f, 0x6d, 0x6d, 0x65, 0x72, 0x63, 0x65, 0x2e, 0x69, 0x61, 0x70, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[22] { 0x66, 0x61, 0x63, 0x65, 0x62, 0x6f, 0x6f, 0x6b, 0x2d, 0x68, 0x61, 0x72, 0x64, 0x77, 0x61, 0x72, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[9] { 0x70, 0x61, 0x73, 0x74, 0x65, 0x62, 0x69, 0x6e, 0x00 }, new char[8] { 0x68, 0x61, 0x74, 0x65, 0x62, 0x69, 0x6e, 0x00 }, new char[21] { 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2d, 0x61, 0x6e, 0x61, 0x6c, 0x79, 0x74, 0x69, 0x63, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[30] { 0x70, 0x65, 0x72, 0x66, 0x2d, 0x65, 0x76, 0x65, 0x6e, 0x74, 0x73, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[16] { 0x63, 0x72, 0x61, 0x73, 0x68, 0x6c, 0x79, 0x74, 0x69, 0x63, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[22] { 0x63, 0x64, 0x70, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[25] { 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[9] { 0x68, 0x61, 0x73, 0x74, 0x65, 0x62, 0x69, 0x6e, 0x00 }, new char[8] { 0x64, 0x72, 0x6f, 0x70, 0x62, 0x6f, 0x78, 0x00 }, new char[19] { 0x67, 0x72, 0x61, 0x70, 0x68, 0x2e, 0x66, 0x61, 0x63, 0x65, 0x62, 0x6f, 0x6f, 0x6b, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[14] { 0x6f, 0x63, 0x75, 0x6c, 0x75, 0x73, 0x63, 0x64, 0x6e, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[6] { 0x66, 0x62, 0x2e, 0x6d, 0x65, 0x00 }, new char[16] { 0x73, 0x6f, 0x66, 0x74, 0x6c, 0x69, 0x67, 0x68, 0x74, 0x2e, 0x61, 0x74, 0x2e, 0x75, 0x61, 0x00 }, new char[10] { 0x66, 0x62, 0x73, 0x62, 0x78, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[12] { 0x69, 0x63, 0x65, 0x62, 0x75, 0x72, 0x6e, 0x2e, 0x78, 0x79, 0x7a, 0x00 }, new char[14] { 0x61, 0x6d, 0x70, 0x6c, 0x69, 0x74, 0x75, 0x64, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[21] { 0x67, 0x6c, 0x75, 0x65, 0x68, 0x65, 0x6e, 0x64, 0x65, 0x72, 0x2d, 0x61, 0x6c, 0x75, 0x68, 0x75, 0x74, 0x2e, 0x64, 0x65, 0x00 }, new char[8] { 0x64, 0x69, 0x73, 0x63, 0x6f, 0x72, 0x64, 0x00 }, new char[42] { 0x64, 0x61, 0x74, 0x61, 0x2d, 0x6f, 0x70, 0x74, 0x6f, 0x75, 0x74, 0x2d, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x2e, 0x75, 0x63, 0x61, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[18] { 0x67, 0x61, 0x6d, 0x65, 0x61, 0x6e, 0x61, 0x6c, 0x79, 0x74, 0x69, 0x63, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[26] { 0x61, 0x70, 0x69, 0x2e, 0x75, 0x63, 0x61, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[10] { 0x66, 0x62, 0x63, 0x64, 0x6e, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[29] { 0x63, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x2e, 0x75, 0x63, 0x61, 0x2e, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x75, 0x6e, 0x69, 0x74, 0x79, 0x33, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[13] { 0x66, 0x61, 0x63, 0x65, 0x62, 0x6f, 0x6f, 0x6b, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[11] { 0x6f, 0x63, 0x75, 0x6c, 0x75, 0x73, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[7] { 0x66, 0x62, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[10] { 0x66, 0x62, 0x63, 0x64, 0x6e, 0x2e, 0x6e, 0x65, 0x74, 0x00 } }; 
std::list<const char*> AnalyticsBlocker::HostNames_DAB = { new char[11] { 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[22] { 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x75, 0x73, 0x65, 0x72, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[14] { 0x72, 0x75, 0x62, 0x79, 0x2d, 0x63, 0x6f, 0x72, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[13] { 0x62, 0x6f, 0x6e, 0x65, 0x74, 0x6f, 0x6d, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x00 }, new char[11] { 0x73, 0x61, 0x6d, 0x62, 0x6f, 0x79, 0x2e, 0x64, 0x65, 0x76, 0x00 }, new char[20] { 0x74, 0x68, 0x65, 0x74, 0x72, 0x75, 0x65, 0x79, 0x6f, 0x73, 0x68, 0x69, 0x66, 0x61, 0x6e, 0x2e, 0x63, 0x6f, 0x6d, 0x00 } };

bool AnalyticsBlocker::Initialize()
{
#ifdef _WIN64
	Debug::Msg("Initializing Analytics Blocker...");
	return (wsock32::Initialize()
		&& ws2_32::Initialize()
		);
#else
	return true;
#endif
}

void AnalyticsBlocker::Hook()
{
#ifdef _WIN64
	wsock32::Hooks::Initialize();
	ws2_32::Hooks::Initialize();
#endif
}

bool AnalyticsBlocker::CheckHostNames(const char* name)
{
	std::string namestr = name;
	std::transform(namestr.begin(), namestr.end(), namestr.begin(), [](unsigned char c) { return std::tolower(c); });
	if (namestr._Equal("localhost") || namestr._Equal("127.0.0.1"))
		return false;
	bool found = IsInBlockedHostNameList(namestr.c_str());
	if (Debug::Enabled || ShouldDAB)
	{
		if (found)
			Debug::DirectWrite(("HostName Blocked: " + namestr).c_str());
		else if (!IsInDABHostNameList(namestr.c_str()))
		{
			Debug::DirectWrite(("Unique HostName Found: " + namestr).c_str());
			HostNames_DAB.push_back(namestr.c_str());
		}
	}
	return found;
}

bool AnalyticsBlocker::IsInBlockedHostNameList(const char* url)
{
	bool found = false;
	for (int i = 0; i < (sizeof(HostNames) / sizeof(HostNames[0])); i++)
	{
		if (strstr(url, HostNames[i]) != NULL)
		{
			found = true;
			break;
		}
	}
	return found;
}

bool AnalyticsBlocker::IsInDABHostNameList(const char* url)
{
	bool found = false;
	for (std::list<const char*>::iterator iter = HostNames_DAB.begin(); iter != HostNames_DAB.end(); iter++)
	{
		const char* currentname = *iter;
		if (strstr(url, currentname) != NULL)
		{
			found = true;
			break;
		}
	}
	return found;
}

#pragma region wsock32
HMODULE AnalyticsBlocker::wsock32::Module = NULL;
AnalyticsBlocker::wsock32::Exports::gethostbyname_t AnalyticsBlocker::wsock32::Exports::Gethostbyname = NULL;

bool AnalyticsBlocker::wsock32::Initialize()
{
	Debug::Msg("Initializing wsock32...");
	Module = LoadLibraryA("wsock32.dll");
	if (Module != NULL)
	{
		if (!Exports::Initialize())
			return false;
	}
	else
	{
		// Display Warning
	}
	return true;
}

bool AnalyticsBlocker::wsock32::Exports::Initialize()
{
	Debug::Msg("Initializing wsock32 Exports...");

	Gethostbyname = (gethostbyname_t)Assertion::GetExport(Module, "gethostbyname");

	return Assertion::ShouldContinue;
}

void AnalyticsBlocker::wsock32::Hooks::Initialize()
{
	if (Module == NULL)
		return;
	Debug::Msg("Attaching Hooks to wsock32...");

	Debug::Msg("gethostbyname");
	Hook::Attach(&(LPVOID&)Exports::Gethostbyname, Gethostbyname);
}

void* AnalyticsBlocker::wsock32::Hooks::Gethostbyname(const char* name)
{
	try
	{
		if ((name == NULL) || CheckHostNames(name))
			name = "localhost";
		return Exports::Gethostbyname(name);
	}
	catch(...){}
	return NULL;
}
#pragma endregion

#ifdef _WIN64
#pragma region ws2_32
HMODULE AnalyticsBlocker::ws2_32::Module = NULL;
AnalyticsBlocker::ws2_32::Exports::getaddrinfo_t AnalyticsBlocker::ws2_32::Exports::Getaddrinfo = NULL;

bool AnalyticsBlocker::ws2_32::Initialize()
{
	Debug::Msg("Initializing ws2_32...");
	Module = LoadLibraryA("ws2_32");
	if (Module != NULL)
	{
		if (!Exports::Initialize())
			return false;
	}
	else
	{
		// Display Warning
	}
	return true;
}

bool AnalyticsBlocker::ws2_32::Exports::Initialize()
{
	Debug::Msg("Initializing ws2_32 Exports...");

	Getaddrinfo = (getaddrinfo_t)Assertion::GetExport(Module, "getaddrinfo");

	return Assertion::ShouldContinue;
}

void AnalyticsBlocker::ws2_32::Hooks::Initialize()
{
	if (Module == NULL)
		return;
	Debug::Msg("Attaching Hooks to ws2_32...");

	Debug::Msg("getaddrinfo");
	Hook::Attach(&(LPVOID&)Exports::Getaddrinfo, Getaddrinfo);
}

int AnalyticsBlocker::ws2_32::Hooks::Getaddrinfo(PCSTR pNodeName, PCSTR pServiceName, void* pHints, void* ppResult)
{
	try
	{
		if ((pNodeName == NULL) || CheckHostNames(pNodeName))
			pNodeName = "localhost";
		return Exports::Getaddrinfo(pNodeName, pServiceName, pHints, ppResult);
	}
	catch (...){}
	return WSATRY_AGAIN;
}
#pragma endregion
#endif