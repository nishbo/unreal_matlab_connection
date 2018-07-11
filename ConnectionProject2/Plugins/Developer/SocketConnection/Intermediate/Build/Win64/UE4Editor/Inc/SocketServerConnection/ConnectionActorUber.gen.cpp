// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/ConnectionActorUber.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeConnectionActorUber() {}
// Cross Module References
	SOCKETSERVERCONNECTION_API UClass* Z_Construct_UClass_AConnectionActorUberStorage_NoRegister();
	SOCKETSERVERCONNECTION_API UClass* Z_Construct_UClass_AConnectionActorUberStorage();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_SocketServerConnection();
	SOCKETSERVERCONNECTION_API UClass* Z_Construct_UClass_AConnectionActorUber_NoRegister();
	SOCKETSERVERCONNECTION_API UClass* Z_Construct_UClass_AConnectionActorUber();
	SOCKETSERVERCONNECTION_API UFunction* Z_Construct_UFunction_AConnectionActorUber_shutDownServer();
	SOCKETSERVERCONNECTION_API UFunction* Z_Construct_UFunction_AConnectionActorUber_startServer();
	SOCKETSERVERCONNECTION_API UFunction* Z_Construct_UFunction_AConnectionActorUber_updateInDataBeforeReading();
	SOCKETSERVERCONNECTION_API UFunction* Z_Construct_UFunction_AConnectionActorUber_updateOutDataAfterWriting();
// End Cross Module References
	void AConnectionActorUberStorage::StaticRegisterNativesAConnectionActorUberStorage()
	{
	}
	UClass* Z_Construct_UClass_AConnectionActorUberStorage_NoRegister()
	{
		return AConnectionActorUberStorage::StaticClass();
	}
	UClass* Z_Construct_UClass_AConnectionActorUberStorage()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AActor,
				(UObject* (*)())Z_Construct_UPackage__Script_SocketServerConnection,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "ConnectionActorUber.h" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_doBeforeReading_MetaData[] = {
				{ "Category", "ServerConfig" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			auto NewProp_doBeforeReading_SetBit = [](void* Obj){ ((AConnectionActorUberStorage*)Obj)->doBeforeReading = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_doBeforeReading = { UE4CodeGen_Private::EPropertyClass::Bool, "doBeforeReading", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(AConnectionActorUberStorage), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_doBeforeReading_SetBit)>::SetBit, METADATA_PARAMS(NewProp_doBeforeReading_MetaData, ARRAY_COUNT(NewProp_doBeforeReading_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_doAfterWriting_MetaData[] = {
				{ "Category", "ServerConfig" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			auto NewProp_doAfterWriting_SetBit = [](void* Obj){ ((AConnectionActorUberStorage*)Obj)->doAfterWriting = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_doAfterWriting = { UE4CodeGen_Private::EPropertyClass::Bool, "doAfterWriting", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(AConnectionActorUberStorage), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_doAfterWriting_SetBit)>::SetBit, METADATA_PARAMS(NewProp_doAfterWriting_MetaData, ARRAY_COUNT(NewProp_doAfterWriting_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_printMessages_MetaData[] = {
				{ "Category", "ServerConfig" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			auto NewProp_printMessages_SetBit = [](void* Obj){ ((AConnectionActorUberStorage*)Obj)->printMessages = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_printMessages = { UE4CodeGen_Private::EPropertyClass::Bool, "printMessages", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(AConnectionActorUberStorage), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_printMessages_SetBit)>::SetBit, METADATA_PARAMS(NewProp_printMessages_MetaData, ARRAY_COUNT(NewProp_printMessages_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_portNumber_MetaData[] = {
				{ "Category", "ServerConfig" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_portNumber = { UE4CodeGen_Private::EPropertyClass::Int, "portNumber", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, portNumber), METADATA_PARAMS(NewProp_portNumber_MetaData, ARRAY_COUNT(NewProp_portNumber_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_infoPrintDisplayPeriod_MetaData[] = {
				{ "Category", "ServerConfig" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_infoPrintDisplayPeriod = { UE4CodeGen_Private::EPropertyClass::Float, "infoPrintDisplayPeriod", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, infoPrintDisplayPeriod), METADATA_PARAMS(NewProp_infoPrintDisplayPeriod_MetaData, ARRAY_COUNT(NewProp_infoPrintDisplayPeriod_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_variableOutArray_MetaData[] = {
				{ "Category", "ServerOutData" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_variableOutArray = { UE4CodeGen_Private::EPropertyClass::Array, "variableOutArray", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, variableOutArray), METADATA_PARAMS(NewProp_variableOutArray_MetaData, ARRAY_COUNT(NewProp_variableOutArray_MetaData)) };
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_variableOutArray_Inner = { UE4CodeGen_Private::EPropertyClass::Float, "variableOutArray", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_variableInArray_MetaData[] = {
				{ "Category", "ServerInData" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_variableInArray = { UE4CodeGen_Private::EPropertyClass::Array, "variableInArray", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, variableInArray), METADATA_PARAMS(NewProp_variableInArray_MetaData, ARRAY_COUNT(NewProp_variableInArray_MetaData)) };
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_variableInArray_Inner = { UE4CodeGen_Private::EPropertyClass::Float, "variableInArray", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_deltaOfLastInUpdate_MetaData[] = {
				{ "Category", "ServerInData" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_deltaOfLastInUpdate = { UE4CodeGen_Private::EPropertyClass::Float, "deltaOfLastInUpdate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, deltaOfLastInUpdate), METADATA_PARAMS(NewProp_deltaOfLastInUpdate_MetaData, ARRAY_COUNT(NewProp_deltaOfLastInUpdate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_timeOfLastInUpdate_MetaData[] = {
				{ "Category", "ServerInData" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const UE4CodeGen_Private::FFloatPropertyParams NewProp_timeOfLastInUpdate = { UE4CodeGen_Private::EPropertyClass::Float, "timeOfLastInUpdate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, STRUCT_OFFSET(AConnectionActorUberStorage, timeOfLastInUpdate), METADATA_PARAMS(NewProp_timeOfLastInUpdate_MetaData, ARRAY_COUNT(NewProp_timeOfLastInUpdate_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_doBeforeReading,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_doAfterWriting,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_printMessages,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_portNumber,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_infoPrintDisplayPeriod,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_variableOutArray,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_variableOutArray_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_variableInArray,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_variableInArray_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_deltaOfLastInUpdate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_timeOfLastInUpdate,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AConnectionActorUberStorage>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AConnectionActorUberStorage::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				nullptr, 0,
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AConnectionActorUberStorage, 4166517976);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AConnectionActorUberStorage(Z_Construct_UClass_AConnectionActorUberStorage, &AConnectionActorUberStorage::StaticClass, TEXT("/Script/SocketServerConnection"), TEXT("AConnectionActorUberStorage"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AConnectionActorUberStorage);
	void AConnectionActorUber::StaticRegisterNativesAConnectionActorUber()
	{
		UClass* Class = AConnectionActorUber::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "shutDownServer", &AConnectionActorUber::execshutDownServer },
			{ "startServer", &AConnectionActorUber::execstartServer },
			{ "updateInDataBeforeReading", &AConnectionActorUber::execupdateInDataBeforeReading },
			{ "updateOutDataAfterWriting", &AConnectionActorUber::execupdateOutDataAfterWriting },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_AConnectionActorUber_shutDownServer()
	{
		struct ConnectionActorUber_eventshutDownServer_Parms
		{
			AConnectionActorUberStorage* var;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_var = { UE4CodeGen_Private::EPropertyClass::Object, "var", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(ConnectionActorUber_eventshutDownServer_Parms, var), Z_Construct_UClass_AConnectionActorUberStorage_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_var,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "MatlabServer" },
				{ "DefaultToSelf", "WorldContextObject" },
				{ "HidePin", "WorldContextObject" },
				{ "Keywords", "matlab server shutdown" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
				{ "ToolTip", "stop dedicated server for connection with matlab" },
				{ "UnsafeDuringActorConstruction", "TRUE" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AConnectionActorUber, "shutDownServer", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(ConnectionActorUber_eventshutDownServer_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AConnectionActorUber_startServer()
	{
		struct ConnectionActorUber_eventstartServer_Parms
		{
			AConnectionActorUberStorage* var;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_var = { UE4CodeGen_Private::EPropertyClass::Object, "var", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(ConnectionActorUber_eventstartServer_Parms, var), Z_Construct_UClass_AConnectionActorUberStorage_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_var,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "MatlabServer" },
				{ "DefaultToSelf", "WorldContextObject" },
				{ "HidePin", "WorldContextObject" },
				{ "Keywords", "matlab server start" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
				{ "ToolTip", "start dedicated server for connection with matlab" },
				{ "UnsafeDuringActorConstruction", "TRUE" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AConnectionActorUber, "startServer", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(ConnectionActorUber_eventstartServer_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AConnectionActorUber_updateInDataBeforeReading()
	{
		struct ConnectionActorUber_eventupdateInDataBeforeReading_Parms
		{
			AConnectionActorUberStorage* var;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_var = { UE4CodeGen_Private::EPropertyClass::Object, "var", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(ConnectionActorUber_eventupdateInDataBeforeReading_Parms, var), Z_Construct_UClass_AConnectionActorUberStorage_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_var,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "MatlabServer" },
				{ "DefaultToSelf", "WorldContextObject" },
				{ "HidePin", "WorldContextObject" },
				{ "Keywords", "matlab server update in" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
				{ "ToolTip", "read data from matlab" },
				{ "UnsafeDuringActorConstruction", "TRUE" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AConnectionActorUber, "updateInDataBeforeReading", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(ConnectionActorUber_eventupdateInDataBeforeReading_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AConnectionActorUber_updateOutDataAfterWriting()
	{
		struct ConnectionActorUber_eventupdateOutDataAfterWriting_Parms
		{
			AConnectionActorUberStorage* var;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_var = { UE4CodeGen_Private::EPropertyClass::Object, "var", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(ConnectionActorUber_eventupdateOutDataAfterWriting_Parms, var), Z_Construct_UClass_AConnectionActorUberStorage_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_var,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "MatlabServer" },
				{ "DefaultToSelf", "WorldContextObject" },
				{ "HidePin", "WorldContextObject" },
				{ "Keywords", "matlab server update out" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
				{ "ToolTip", "send data to matlab" },
				{ "UnsafeDuringActorConstruction", "TRUE" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AConnectionActorUber, "updateOutDataAfterWriting", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(ConnectionActorUber_eventupdateOutDataAfterWriting_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AConnectionActorUber_NoRegister()
	{
		return AConnectionActorUber::StaticClass();
	}
	UClass* Z_Construct_UClass_AConnectionActorUber()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AActor,
				(UObject* (*)())Z_Construct_UPackage__Script_SocketServerConnection,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_AConnectionActorUber_shutDownServer, "shutDownServer" }, // 351395932
				{ &Z_Construct_UFunction_AConnectionActorUber_startServer, "startServer" }, // 1930884947
				{ &Z_Construct_UFunction_AConnectionActorUber_updateInDataBeforeReading, "updateInDataBeforeReading" }, // 1603954694
				{ &Z_Construct_UFunction_AConnectionActorUber_updateOutDataAfterWriting, "updateOutDataAfterWriting" }, // 1422421854
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "ConnectionActorUber.h" },
				{ "ModuleRelativePath", "Public/ConnectionActorUber.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AConnectionActorUber>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AConnectionActorUber::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AConnectionActorUber, 2354291831);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AConnectionActorUber(Z_Construct_UClass_AConnectionActorUber, &AConnectionActorUber::StaticClass, TEXT("/Script/SocketServerConnection"), TEXT("AConnectionActorUber"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AConnectionActorUber);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
