
#include "Commands/multi.h"
#include <regex>

FChatReturn AFRMCommand::RemoteMonitoringCommand(UObject* WorldContext, class UCommandSender* Sender, TArray<FString> Arguments) {

	FChatReturn ChatReturn;
	FLinearColor color = FLinearColor::Red;
	FString chat;

	FString command = Arguments[0].ToLower();

	AFicsitRemoteMonitoring* ModSubsystem = AFicsitRemoteMonitoring::Get(WorldContext->GetWorld());
	fgcheck(ModSubsystem);

	if (command == "debug") {

		FString OutputType = Arguments[1].ToLower();
		FString sEndpoint = Arguments[2];

		bool bSuccess = false;
		FString Json = ModSubsystem->HandleEndpoint(WorldContext, sEndpoint, bSuccess);

		if (!bSuccess) {

			ChatReturn.Chat = TEXT("Unable to find endpoint, please refer to the documentation at docs.ficsit.app or the mod creator.");
			ChatReturn.Color = FLinearColor::Red;
			ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

			return ChatReturn;

		}

		if (OutputType == "file") {

			FString JsonPath = FPaths::ProjectDir() + "Mods/FicsitRemoteMonitoring/Debug/" + sEndpoint + ".json";

			UNotificationLoader::FileSaveString(Json, JsonPath);

			ChatReturn.Chat = TEXT("Data saved to Mod location in the Debug folder.");
			ChatReturn.Color = FLinearColor::White;
			ChatReturn.Status = EExecutionStatus::COMPLETED;

			return ChatReturn;

		}
		else if (OutputType == "info") {

			ChatReturn.Chat = Json;
			ChatReturn.Color = FLinearColor::White;
			ChatReturn.Status = EExecutionStatus::COMPLETED;

			return ChatReturn;

		}

		else {

			ChatReturn.Chat = TEXT("Usage: /frm debug <file/info> <Endpoint>");
			ChatReturn.Color = FLinearColor::Red;
			ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

			return ChatReturn;

		}
	}
	else if (command == "http") {

		FString arg1 = Arguments[1].ToLower();

		if (arg1 == "start") {

			auto config = FConfig_HTTPStruct::GetActiveConfig(WorldContext);
			int32 Port = config.HTTP_Port;
			
			ModSubsystem->StartWebSocketServer();

			ChatReturn.Chat = FString(TEXT("HTTP Service Initiated on Port: " + FString::FromInt(Port)));
			ChatReturn.Color = FLinearColor::Green;
			ChatReturn.Status = EExecutionStatus::COMPLETED;
			UE_LOG(LogHttpServer, Log, TEXT("HTTP Service started. Port: %d"), Port);


			return ChatReturn;

		}
		else if (arg1 == "stop") {
			ModSubsystem->StopWebSocketServer();
			UE_LOG(LogHttpServer, Log, TEXT("Stopping HTTP Service."));

			ChatReturn.Chat = TEXT("Stopping HTTP Service.");
			ChatReturn.Color = FLinearColor::White;
			ChatReturn.Status = EExecutionStatus::COMPLETED;

			return ChatReturn;
		}

		ChatReturn.Chat = TEXT("Usage: /frm http <start/stop>");
		ChatReturn.Color = FLinearColor::Red;
		ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

		return ChatReturn;

	}

	if (command == "serial") {

		FString arg1 = Arguments[1].ToLower();

		if (arg1 == "start") {

			auto config = FConfig_SerialStruct::GetActiveConfig(WorldContext);
			FString Port = config.COM_Port;

			ModSubsystem->StartWebSocketServer();

			ChatReturn.Chat = FString(TEXT("Serial/RS232 Service Initiated on Port: " + Port));
			ChatReturn.Color = FLinearColor::Green;
			ChatReturn.Status = EExecutionStatus::COMPLETED;
			UE_LOGFMT(LogHttpServer, Log, "Serial/RS232 Service started. Port: {Port}");


			return ChatReturn;

		}
		else if (arg1 == "stop") {
			ModSubsystem->StopWebSocketServer();
			UE_LOG(LogHttpServer, Log, TEXT("Stopping Serial/RS232 Service."));

			ChatReturn.Chat = TEXT("Stopping Serial/RS232 Service.");
			ChatReturn.Color = FLinearColor::White;
			ChatReturn.Status = EExecutionStatus::COMPLETED;

			return ChatReturn;
		}

		ChatReturn.Chat = TEXT("Usage: /frm serial <start/stop>");
		ChatReturn.Color = FLinearColor::Red;
		ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

		return ChatReturn;

	}

	if (command == "icon") {

		if (!UKismetSystemLibrary::IsDedicatedServer(WorldContext)) {

			ModSubsystem->IconGenerator_BIE();

			ChatReturn.Chat = TEXT("Icon Generatation Completed");
			ChatReturn.Color = FLinearColor::Green;
			ChatReturn.Status = EExecutionStatus::COMPLETED;

		}
		else {

			ChatReturn.Chat = TEXT("Dedicated Servers do not have graphical assets to extract. Cancelling... Generate locally, then upload to server.");
			ChatReturn.Color = FLinearColor::Red;
			ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

		}

		return ChatReturn;

	}

	ChatReturn.Chat = TEXT("Unable to find command type, please refer to the documentation at docs.ficsit.app.");
	ChatReturn.Color =  FLinearColor::Red;
	ChatReturn.Status = EExecutionStatus::UNCOMPLETED;

	return ChatReturn;
};