#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Configs/Config_FactoryStruct.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FicsitRemoteMonitoringModule.h"
#include "FGBuildableSubsystem.h"
#include "Buildables\FGBuildableManufacturer.h"
#include "FGPowerInfoComponent.h"
#include "Serialization/JsonWriter.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "FRM_Library.generated.h"

UCLASS()
class FICSITREMOTEMONITORING_API UFRM_Library : public UFGBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TSharedPtr<FJsonObject> getActorJSON(AActor* Actor);
	static TSharedPtr<FJsonObject> getActorFactoryCompXYZ(UFGFactoryConnectionComponent* BeltPipe);
	static TSharedPtr<FJsonObject> getActorPipeXYZ(UFGPipeConnectionComponent* BeltPipe);
	static TSharedPtr<FJsonObject> getActorFeaturesJSON(AActor* Actor, FString DisplayName, FString TypeName);
	static FString APItoJSON(TArray<TSharedPtr<FJsonValue>> JSONArray, UObject* WorldContext);
	static bool IsIntInRange(int32 Number, int32 LowerBound, int32 UpperBound);

	static double SafeDivide_Double(double Numerator, double Denominator)
	{
		return (Denominator == 0.0) ? 0.0 : (Numerator / Denominator);
	}

	static float SafeDivide_Float(float Numerator, float Denominator)
	{
		return (Denominator == 0.0f) ? 0.0f : (Numerator / Denominator);
	}

	static TSharedPtr<FJsonValue> ConvertStringToFJsonValue(const FString& JsonString);
};
