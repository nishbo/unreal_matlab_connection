// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectionActor.h"


// Sets default values
AConnectionActor::AConnectionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	deltaUpdateTime = -1.f;
	timeOfLastUpdate = -1.f;
	NInArray = 10;
	variableInArray.Init(-1.f, NInArray);

	newDataPresent = false;

	NArray = 69;
	variableArray.Init(-1.f, NArray);

	portNumber = 10000;
	portNumberOut = 10010;
	connectRefreshPeriod = 0.01f;
	acceptDataRefreshPeriod = 0.01f;
	sendDataCheckPeriod = 0.01f;
	infoPrintDisplayPeriod = 5.f;
	printMessages = false;
}

AConnectionActor::~AConnectionActor()
{
	if (ConnectionSocket)
	{
		ConnectionSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
	}
	if (ListenerSocket)
	{
		ListenerSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenerSocket);
	}
	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}

void AConnectionActor::Destroyed()
{
	//GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "DESTROYYYYED is called");
	if (SenderSocket)
	{
		FString serialized = TEXT("EOC");
		TCHAR *serializedChar = serialized.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;
		SenderSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
		SenderSocket = NULL;
	}
}

// Called when the game starts or when spawned
void AConnectionActor::BeginPlay()
{
	Super::BeginPlay();

	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);
	FString* YourChosenSocketName = new FString("MySocketListener");

	//Create Socket
	FIPv4Endpoint Endpoint(ip, portNumber);
	ListenerSocket = FTcpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(10);

	//Set Buffer Size
	int32 NewSize = 0;
	int32 ReceiveBufferSize = 2 * 1024 * 1024;
	ListenerSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);
	if (printMessages)
	{
		FString OpenSocketMessage = FString::Printf(TEXT("Socket listening at 127.0.0.1:%d."), portNumber);
		GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, OpenSocketMessage);
	}

	ListenerDelegate = FTimerDelegate::CreateUObject(this, &AConnectionActor::TCPConnectionListener);
	GetWorldTimerManager().SetTimer(ListenerTimerHandle, ListenerDelegate, connectRefreshPeriod, true);

	// Sender socket
	SenderSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(portNumberOut);
	bool connected = SenderSocket->Connect(*addr);
	if (!connected) {
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "Sending connection NOT established");
		}
	}
	else {
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "Sending connection established");
		}
		newDataPresent = true;

		SenderDelegate = FTimerDelegate::CreateUObject(this, &AConnectionActor::TCPSocketSender);
		GetWorldTimerManager().SetTimer(senderTimerHandle, SenderDelegate, sendDataCheckPeriod, true);
	}

	//GetWorldTimerManager().SetTimer(this, &AConnectionActor::TCPConnectionListener, 0.1f, true);
}

// Called every frame
void AConnectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this->TCPConnectionListener();
}

void AConnectionActor::DestroyConnectionSocket()
{
	GetWorldTimerManager().ClearTimer(connectionTimerHandle);
	ConnectionSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
	ConnectionSocket = NULL;
}

void AConnectionActor::TCPSocketSender()
{
	if (newDataPresent)
	{
		newDataPresent = false;

		//FString serialized = FString::Printf(TEXT("[%f %f %f %f %f %f %f %f %f %f %f %f]"), \
				//	variable1, variable2, variable3, variable4, variable5, variable6, variable7, variable8, variable9, variable10, variable11, variable12);
//FString serialized = TEXT("loadPlayer|1");

		FString serialized2;
		serialized2 += "[";
		for (auto v : variableArray)
		{
			serialized2 += FString::Printf(TEXT("%f "), v);
		}
		serialized2.TrimTrailing();
		serialized2 += "]";

		TCHAR *serializedChar = serialized2.GetCharArray().GetData();
		int32 size = FCString::Strlen(serializedChar);
		int32 sent = 0;

		bool successful = SenderSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);

		if (successful && printMessages)
		{
			serialized2 = FString(TEXT("Sent some data: ")) + serialized2;
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, serialized2);
		}
		else if (printMessages)
		{
			serialized2 = FString(TEXT("Failed to send some data: ")) + serialized2;
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, serialized2);
		}
	}
}

void AConnectionActor::TCPConnectionListener()
{
	if (!ListenerSocket) {
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "No listener socket");
		}
		return;
	}

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;
	//ListenerSocket->HasPendingConnection(Pending);
	//if (Pending)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pending");
	//} else {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Waiting...");
	//}

	// handle incoming connections
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "Pending connection");
		}
		//Already have a Connection? destroy previous
		if (ConnectionSocket)
		{
			DestroyConnectionSocket();
			if (printMessages)
			{
				GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "Closed previous connection");
			}
		}

		//New Connection receive!
		ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);
			if (printMessages)
			{
				GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, "Accepted connection");
			}

			ConnectionDelegate = FTimerDelegate::CreateUObject(this, &AConnectionActor::TCPSocketListener);
			GetWorldTimerManager().SetTimer(connectionTimerHandle, ConnectionDelegate, acceptDataRefreshPeriod, true);
		}
	}
}

//Rama's String From Binary Array
//This function requires 
//		#include <string>
FString AConnectionActor::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	return FString(cstr.c_str());
}

void AConnectionActor::UpdateSpeedsAndTime(const FString ReceivedUE4String)
{
	TArray<FString> Parsed;
	int NReceived = ReceivedUE4String.ParseIntoArray(Parsed, TEXT(" "), true);

	// Setup times of updates, etc
	if (timeOfLastUpdate != -1.f) {
		double currentTime = FPlatformTime::Seconds();
		deltaUpdateTime = currentTime - preciseTimeOfLastUpdate;

		preciseTimeOfLastUpdate = currentTime;
		timeOfLastUpdate = preciseTimeOfLastUpdate;
	}
	else {
		preciseTimeOfLastUpdate = FPlatformTime::Seconds();
		timeOfLastUpdate = preciseTimeOfLastUpdate;
	}

	if (printMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, \
			FString::Printf(TEXT("Data obtained! Time of update: %f, delta update time: %f"), \
				timeOfLastUpdate, deltaUpdateTime));
	}

	if (NReceived != NInArray)
	{
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red,
				TEXT("Failed to extract data, number of values is wrong. Aborting package."));
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, ReceivedUE4String);
		}
		return;
	}

	for (int i = 0; i < Parsed.Num(); i++)
	{
		if (Parsed[i].IsNumeric())
		{
			variableInArray[i] = FCString::Atof(*Parsed[i]);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, \
				FString::Printf(TEXT("Parsed string is not numerical! String %s, index %d."), \
					*Parsed[i], i));
		}
	}

}


void AConnectionActor::TCPSocketListener()
{
	if (ConnectionSocket == NULL) return;

	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		// ReceivedData.Init(FMath::Min(Size, 65507u));
		ReceivedData.Init(0, FMath::Min(Size, 65507u));
		//ReceivedData.Init(0, FMath::Min(Size, 407u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
		}
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	if (printMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						Rama's String From Binary Array
	const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	if (printMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, FString::Printf(TEXT("As String Data ~> %s"), *ReceivedUE4String));
	}
	if (ReceivedUE4String.Equals(TEXT("stop"), ESearchCase::IgnoreCase) || ReceivedUE4String.Equals(TEXT("done"), ESearchCase::IgnoreCase))
	{
		if (printMessages)
		{
			GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, TEXT("Closing connection"));
		}
		DestroyConnectionSocket();
		timeOfLastUpdate = -1.f;
		return;
	}

	if (ReceivedUE4String.Equals(TEXT("matlab handshake"), ESearchCase::IgnoreCase) && printMessages)
	{
		GEngine->AddOnScreenDebugMessage(-1, infoPrintDisplayPeriod, FColor::Red, TEXT("Handshake successfull"));
		return;
	}

	UpdateSpeedsAndTime(ReceivedUE4String);

}