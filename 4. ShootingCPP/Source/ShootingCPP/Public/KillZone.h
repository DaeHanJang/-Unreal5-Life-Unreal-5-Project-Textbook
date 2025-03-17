#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class SHOOTINGCPP_API AKillZone : public AActor {
	GENERATED_BODY()
	
public:
	//�� ������ �Ӽ��� ���� �⺻ ���� ����(Sets default values for this actor's properties)
	AKillZone();

protected:
	//������ ���۵� �� �Ǵ� ������ �� ȣ���(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:
	//�� �����Ӹ��� ȣ���(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;
};
