#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AccessTest.generated.h"

UCLASS()
class SHOOTINGCPP_API AAccessTest : public AActor {
	GENERATED_BODY()
	
public:	
	//이 액터의 속성에 대한 기본 값을 설정(Sets default values for this actor's properties)
	AAccessTest();

protected:
	//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:	
	//매 프레임마다 호출됨(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class ACodingTestActor* testPointer;

	int32 number; //일반 변수
	int32* numPointer; //포인터 변수

	void AddPrint(int32 num1, int32 num2, int32* result);
};
