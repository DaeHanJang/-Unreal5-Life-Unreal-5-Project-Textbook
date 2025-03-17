#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TPSPROJECT_API ABullet : public AActor {
	GENERATED_BODY()
	
public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	//�߻�ü�� �̵��� ����� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* movementComp;
	//�浹 ������Ʈ
	UPROPERTY(VisibleAnywhere, Category=Collision)
	class USphereComponent* collisionComp;
	//�ܰ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category=BodyMesh)
	class UStaticMeshComponent* bodyMeshComp;

	//�Ѿ� ���� �Լ�
	void Die();

	//�Ѿ� �ӵ�
	UPROPERTY(EditAnywhere, Category=Settings)
	float speed = 5000;
	//������ Ư�� �Ӽ��� �����ϸ� ȣ��Ǵ� �̺�Ʈ �Լ�
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
