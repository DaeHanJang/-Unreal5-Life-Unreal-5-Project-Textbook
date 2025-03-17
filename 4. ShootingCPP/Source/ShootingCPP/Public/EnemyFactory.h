#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyFactory : public AActor {
	GENERATED_BODY()
	
public:
	//�� ������ �Ӽ��� ���� �⺻ ���� ����(Sets default values for this actor's properties)
	AEnemyFactory();

protected:
	//������ ���۵� �� �Ǵ� ������ �� ȣ���(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:
	//�� �����Ӹ��� ȣ���(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float delayTime = 2.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemy;

private:
	float currentTime = 0.f;
};
