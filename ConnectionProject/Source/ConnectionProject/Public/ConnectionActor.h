// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "CoreUObject.h"
#include <ctime>
#include <string>
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "SharedPointer.h"
#include "IPv4Address.h"
#include "ConnectionActor.generated.h"

UCLASS()
class CONNECTIONPROJECT_API AConnectionActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AConnectionActor();
	~AConnectionActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called when object is destroyed
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerData")
		float timeOfLastUpdate;
	double preciseTimeOfLastUpdate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerData")
		float deltaUpdateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerData")
		TArray<float> variableInArray;
	int NInArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerOutData")
		bool newDataPresent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerOutData")
		TArray<float> variableArray;
	int NArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		int32 portNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		int32 portNumberOut;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		float connectRefreshPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		float acceptDataRefreshPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		float sendDataCheckPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		float infoPrintDisplayPeriod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
		bool printMessages;

	FSocket* ListenerSocket;
	FTimerDelegate ListenerDelegate;
	FTimerHandle ListenerTimerHandle;
	FSocket* ConnectionSocket;
	FTimerDelegate ConnectionDelegate;
	FTimerHandle connectionTimerHandle;
	FSocket* SenderSocket;
	FTimerDelegate SenderDelegate;
	FTimerHandle senderTimerHandle;

	FIPv4Endpoint RemoteAddressForConnection;
	void TCPConnectionListener();
	void TCPSocketListener();
	void TCPSocketSender();
	void DestroyConnectionSocket();
	void UpdateSpeedsAndTime(const FString ReceivedUE4String);
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);
	
};
