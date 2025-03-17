#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactory : public AActor {
	GENERATED_BODY()
	
public:
	//이 액터의 속성에 대한 기본 값을 설정(Sets default values for this actor's properties)
	AEnemyFactory();

protected:
	//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:
	//매 프레임마다 호출됨(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float delayTime = 2.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemy;

private:
	float currentTime = 0.f;
};
