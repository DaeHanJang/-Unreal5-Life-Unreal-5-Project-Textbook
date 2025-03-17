#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:
	//�� ������ �Ӽ��� ���� �⺻ ���� ����(Sets default values for this actor's properties)
	AEnemyActor();

protected:
	//������ ���۵� �� �Ǵ� ������ �� ȣ���(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:
	//�� �����Ӹ��� ȣ���(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	int32 traceRate = 50;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.f;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector dir;
};
