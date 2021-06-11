﻿

namespace YY
{
	namespace Thunks
	{
#if (YY_Thunks_Support_Version < NTDDI_WINXP)

		//Minimum supported client	Windows Vista
		//Minimum supported server	Windows Server 2008
		//Windows XP有这个API啊……微软文档抽风了？
		EXTERN_C
		DWORD
		WINAPI
		WTSGetActiveConsoleSessionId(
			VOID
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pWTSGetActiveConsoleSessionId = try_get_WTSGetActiveConsoleSessionId())
			{
				return pWTSGetActiveConsoleSessionId();
			}


			//因为Windows 2000没有会话隔离，所有的进程始终在 0 会话中运行，因此直接返回 0 即可。
			return 0;
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, WTSGetActiveConsoleSessionId, 0);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WINXPSP2)

		//Minimum supported client	Windows Vista, Windows XP Professional x64 Edition, Windows XP with SP2[desktop apps only]
		//Minimum supported server	Windows Server 2003 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaProcessorNode(
			_In_  UCHAR Processor,
			_Out_ PUCHAR NodeNumber
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaProcessorNode = try_get_GetNumaProcessorNode())
			{
				return pGetNumaProcessorNode(Processor, NodeNumber);
			}

			//对于没有 Node 概念的系统，我们统一认为只有一个 Node。

			SYSTEM_INFO SystemInfo;
			GetSystemInfo(&SystemInfo);

			if (SystemInfo.dwNumberOfProcessors < Processor)
			{
				*NodeNumber = '\0';
				return TRUE;
			}
			else
			{
				*NodeNumber = 0xffu;

				SetLastError(ERROR_INVALID_PARAMETER);
				return FALSE;
			}
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaProcessorNode, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WIN7)

		//Minimum supported client	Windows 7 [desktop apps only]
		//Minimum supported server	Windows Server 2008 R2 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaNodeNumberFromHandle(
			_In_  HANDLE hFile,
			_Out_ PUSHORT NodeNumber
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaNodeNumberFromHandle = try_get_GetNumaNodeNumberFromHandle())
			{
				return pGetNumaNodeNumberFromHandle(hFile, NodeNumber);
			}

			//始终认为来自 Node 0
			*NodeNumber = 0;

			return TRUE;
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaNodeNumberFromHandle, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WIN7)

		//Minimum supported client	Windows 7 [desktop apps only]
		//Minimum supported server	Windows Server 2008 R2 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaProcessorNodeEx(
			_In_  PPROCESSOR_NUMBER Processor,
			_Out_ PUSHORT NodeNumber
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaProcessorNodeEx = try_get_GetNumaProcessorNodeEx())
			{
				return pGetNumaProcessorNodeEx(Processor, NodeNumber);
			}

			//老版本系统假定只有一组处理器
			if (Processor->Group == 0)
			{
				UCHAR NodeNumberTmp;
				auto bRet = GetNumaProcessorNode(Processor->Number, &NodeNumberTmp);

				if (bRet)
				{
					*NodeNumber = NodeNumberTmp;
				}
				else
				{
					*NodeNumber = 0xffffu;
				}

				return bRet;
			}

			*NodeNumber = 0xffffu;

			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaProcessorNodeEx, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WINXPSP2)

		//Minimum supported client	Windows Vista, Windows XP Professional x64 Edition, Windows XP with SP2 [desktop apps only]
		//Minimum supported server	Windows Server 2003 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaAvailableMemoryNode(
			_In_  UCHAR Node,
			_Out_ PULONGLONG AvailableBytes
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaAvailableMemoryNode = try_get_GetNumaAvailableMemoryNode())
			{
				return pGetNumaAvailableMemoryNode(Node, AvailableBytes);
			}

			if (Node == 0)
			{
				//统一的假定，Node数量为 1，所以该值必然为 0
				//我们把所有可用内存都认为是该节点0的可用内存。
				MEMORYSTATUSEX statex = { sizeof(statex) };

				if (!GlobalMemoryStatusEx(&statex))
				{
					return FALSE;
				}

				*AvailableBytes = statex.ullAvailPhys;
				return TRUE;
			}

			SetLastError(ERROR_INVALID_PARAMETER);
			return FALSE;
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaAvailableMemoryNode, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WIN7)

		//Minimum supported client	Windows 7 [desktop apps only]
		//Minimum supported server	Windows Server 2008 R2 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaAvailableMemoryNodeEx(
			_In_  USHORT Node,
			_Out_ PULONGLONG AvailableBytes
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaAvailableMemoryNodeEx = try_get_GetNumaAvailableMemoryNodeEx())
			{
				return pGetNumaAvailableMemoryNodeEx(Node, AvailableBytes);
			}


			//GetNumaAvailableMemoryNode 最大只接受 0xFF
			if (Node >= 0x100u)
			{
				SetLastError(ERROR_INVALID_PARAMETER);
				return FALSE;
			}

			return GetNumaAvailableMemoryNode(Node, AvailableBytes);
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaAvailableMemoryNodeEx, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WIN6)

		//Minimum supported client	Windows Vista [desktop apps only]
		//Minimum supported server	Windows Server 2008 [desktop apps only]
		EXTERN_C
		BOOL
		WINAPI
		GetNumaProximityNode(
			_In_  ULONG ProximityId,
			_Out_ PUCHAR NodeNumber
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pGetNumaProximityNode = try_get_GetNumaProximityNode())
			{
				return pGetNumaProximityNode(ProximityId, NodeNumber);
			}

			//我们不知道CPU的组成情况，但是我们可以假定最接近的分组就是 Node 0。
			//对于电脑来说，Node数量始终等于 1，因此问题不是特别的大。
			*NodeNumber = 0;
			return TRUE;
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, GetNumaProximityNode, 8);

#endif


#if (YY_Thunks_Support_Version < NTDDI_WIN6)

		//Minimum supported client	Windows Vista [desktop apps only]
		//Minimum supported server	Windows Server 2008 [desktop apps only]
		EXTERN_C
		LPVOID
		WINAPI
		MapViewOfFileExNuma(
			_In_     HANDLE hFileMappingObject,
			_In_     DWORD dwDesiredAccess,
			_In_     DWORD dwFileOffsetHigh,
			_In_     DWORD dwFileOffsetLow,
			_In_     SIZE_T dwNumberOfBytesToMap,
			_In_opt_ LPVOID lpBaseAddress,
			_In_     DWORD nndPreferred
			)
#ifdef YY_Thunks_Defined
			;
#else
		{
			if (const auto pMapViewOfFileExNuma = try_get_MapViewOfFileExNuma())
			{
				return pMapViewOfFileExNuma(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress, nndPreferred);
			}

			return MapViewOfFileEx(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress);
		}
#endif

		__YY_Thunks_Expand_Function(kernel32, MapViewOfFileExNuma, 28);

#endif
	}
}