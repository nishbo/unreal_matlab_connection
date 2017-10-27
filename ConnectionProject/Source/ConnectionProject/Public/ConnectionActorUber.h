// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaSocketApi.h"
#include "ConnectionActorUber.generated.h"



UCLASS()
class CONNECTIONPROJECT_API AConnectionActorUberStorage : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AConnectionActorUberStorage();
    ~AConnectionActorUberStorage();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called when object is destroyed
    virtual void Destroyed() override;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ServerInData")
        float timeOfLastInUpdate;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ServerInData")
        float deltaOfLastInUpdate;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ServerInData")
        TArray<float> variableInArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerOutData")
        TArray<float> variableOutArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        float infoPrintDisplayPeriod;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool printMessages;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool doBeforeWriting;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool doAfterReading;
};


UCLASS()
class CONNECTIONPROJECT_API AConnectionActorUber : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConnectionActorUber();
	~AConnectionActorUber();

    static SaSocketApi* sasocketapi;

    static double preciseTimeOfLastInUpdate;
    static double preciseDeltaOfLastInUpdate;

    static bool serverRunning;

    // Thread to run the worker FRunnable on
    static FRunnableThread* Thread;

    // start dedicated server for connection with matlab
    UFUNCTION(BlueprintCallable, meta=(
              HidePin="WorldContextObject",
              DefaultToSelf="WorldContextObject",
              Keywords="matlab server start",
              UnsafeDuringActorConstruction=true
             ), Category="MatlabServer")
    static void startServer(AConnectionActorUberStorage* var);

    // stop dedicated server for connection with matlab
    UFUNCTION(BlueprintCallable, meta=(
              HidePin="WorldContextObject",
              DefaultToSelf="WorldContextObject",
              Keywords="matlab server shutdown",
              UnsafeDuringActorConstruction=true
             ), Category="MatlabServer")
    static void shutDownServer(AConnectionActorUberStorage* var);

    // read data from matlab
    UFUNCTION(BlueprintCallable, meta=(
              HidePin="WorldContextObject",
              DefaultToSelf="WorldContextObject",
              Keywords="matlab server update in",
              UnsafeDuringActorConstruction=true
             ), Category="MatlabServer")
    static void updateInDataBeforeReading(AConnectionActorUberStorage* var);

    // send data to matlab
    UFUNCTION(BlueprintCallable, meta=(
              HidePin="WorldContextObject",
              DefaultToSelf="WorldContextObject",
              Keywords="matlab server update out",
              UnsafeDuringActorConstruction=true
             ), Category="MatlabServer")
    static void updateOutDataAfterWriting(AConnectionActorUberStorage* var);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called when object is destroyed
    virtual void Destroyed() override;

};
