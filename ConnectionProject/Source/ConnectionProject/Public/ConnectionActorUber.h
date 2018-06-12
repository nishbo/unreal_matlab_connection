// Fill out your copyright notice in the Description page of Project Settings.
/*
    Written by Anton Sobinov
    Based on the code by Emo Todorov

    Copyright (C) 2017 Roboti LLC
    Copyright (C) 2018 Anton Sobinov

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

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
        int32 portNumber;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool printMessages;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool doAfterWriting;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ServerConfig")
        bool doBeforeReading;
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
