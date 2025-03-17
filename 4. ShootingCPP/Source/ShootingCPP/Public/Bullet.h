#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTINGCPP_API ABullet : public AActor {
	GENERATED_BODY()
	
public:	
	//이 액터의 속성에 대한 기본 값을 설정(Sets default values for this actor's properties)
	ABullet();

protected:
	//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
	virtual void BeginPlay() override;

public:	
	//매 프레임마다 호출됨(Called every frame)
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.f;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;

	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
