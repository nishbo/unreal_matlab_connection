// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AConnectionActorUberStorage;
#ifdef SOCKETSERVERCONNECTION_ConnectionActorUber_generated_h
#error "ConnectionActorUber.generated.h already included, missing '#pragma once' in ConnectionActorUber.h"
#endif
#define SOCKETSERVERCONNECTION_ConnectionActorUber_generated_h

#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_RPC_WRAPPERS
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_RPC_WRAPPERS_NO_PURE_DECLS
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAConnectionActorUberStorage(); \
	friend SOCKETSERVERCONNECTION_API class UClass* Z_Construct_UClass_AConnectionActorUberStorage(); \
public: \
	DECLARE_CLASS(AConnectionActorUberStorage, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SocketServerConnection"), NO_API) \
	DECLARE_SERIALIZER(AConnectionActorUberStorage) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_INCLASS \
private: \
	static void StaticRegisterNativesAConnectionActorUberStorage(); \
	friend SOCKETSERVERCONNECTION_API class UClass* Z_Construct_UClass_AConnectionActorUberStorage(); \
public: \
	DECLARE_CLASS(AConnectionActorUberStorage, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SocketServerConnection"), NO_API) \
	DECLARE_SERIALIZER(AConnectionActorUberStorage) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AConnectionActorUberStorage(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AConnectionActorUberStorage) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AConnectionActorUberStorage); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AConnectionActorUberStorage); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AConnectionActorUberStorage(AConnectionActorUberStorage&&); \
	NO_API AConnectionActorUberStorage(const AConnectionActorUberStorage&); \
public:


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AConnectionActorUberStorage(AConnectionActorUberStorage&&); \
	NO_API AConnectionActorUberStorage(const AConnectionActorUberStorage&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AConnectionActorUberStorage); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AConnectionActorUberStorage); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AConnectionActorUberStorage)


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_PRIVATE_PROPERTY_OFFSET
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_31_PROLOG
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_PRIVATE_PROPERTY_OFFSET \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_RPC_WRAPPERS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_INCLASS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_PRIVATE_PROPERTY_OFFSET \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_INCLASS_NO_PURE_DECLS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execupdateOutDataAfterWriting) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::updateOutDataAfterWriting(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execupdateInDataBeforeReading) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::updateInDataBeforeReading(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execshutDownServer) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::shutDownServer(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execstartServer) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::startServer(Z_Param_var); \
		P_NATIVE_END; \
	}


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execupdateOutDataAfterWriting) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::updateOutDataAfterWriting(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execupdateInDataBeforeReading) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::updateInDataBeforeReading(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execshutDownServer) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::shutDownServer(Z_Param_var); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execstartServer) \
	{ \
		P_GET_OBJECT(AConnectionActorUberStorage,Z_Param_var); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		AConnectionActorUber::startServer(Z_Param_var); \
		P_NATIVE_END; \
	}


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAConnectionActorUber(); \
	friend SOCKETSERVERCONNECTION_API class UClass* Z_Construct_UClass_AConnectionActorUber(); \
public: \
	DECLARE_CLASS(AConnectionActorUber, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SocketServerConnection"), NO_API) \
	DECLARE_SERIALIZER(AConnectionActorUber) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_INCLASS \
private: \
	static void StaticRegisterNativesAConnectionActorUber(); \
	friend SOCKETSERVERCONNECTION_API class UClass* Z_Construct_UClass_AConnectionActorUber(); \
public: \
	DECLARE_CLASS(AConnectionActorUber, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SocketServerConnection"), NO_API) \
	DECLARE_SERIALIZER(AConnectionActorUber) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AConnectionActorUber(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AConnectionActorUber) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AConnectionActorUber); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AConnectionActorUber); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AConnectionActorUber(AConnectionActorUber&&); \
	NO_API AConnectionActorUber(const AConnectionActorUber&); \
public:


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AConnectionActorUber(AConnectionActorUber&&); \
	NO_API AConnectionActorUber(const AConnectionActorUber&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AConnectionActorUber); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AConnectionActorUber); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AConnectionActorUber)


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_PRIVATE_PROPERTY_OFFSET
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_74_PROLOG
#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_PRIVATE_PROPERTY_OFFSET \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_RPC_WRAPPERS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_INCLASS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_PRIVATE_PROPERTY_OFFSET \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_RPC_WRAPPERS_NO_PURE_DECLS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_INCLASS_NO_PURE_DECLS \
	ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h_77_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ConnectionProject_Plugins_Developer_SocketConnection_Source_SocketServerConnection_Public_ConnectionActorUber_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
