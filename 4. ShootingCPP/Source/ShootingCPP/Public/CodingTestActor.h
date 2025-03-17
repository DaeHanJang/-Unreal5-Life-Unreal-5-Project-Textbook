#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor.generated.h"

UCLASS()
class SHOOTINGCPP_API ACodingTestActor : public AActor {
	GENERATED_BODY()
	
public:
	//이 액터의 속성에 대한 기본 값을 설정(Sets default values for this actor's properties)
	ACodingTestActor();

protected:
	//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:	
	//매 프레임마다 호출됨(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 number1 = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 number2 = 30;

	//FString name = "Jang Dae Han";
	UPROPERTY(EditInstanceOnly)
	FString name = TEXT("장대한");

	UPROPERTY(EditAnywhere)
	bool isReady = true;
	bool isFinished = false;

	//더하기 함수 선언
	UFUNCTION(BlueprintPure)
	int32 Add(int32 num1, int32 num2);
};
