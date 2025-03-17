#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

//����� ���� ����
UENUM(BlueprintType)
enum class EEnemyState : uint8 {
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPSPROJECT_API UEnemyFSM : public UActorComponent {
	GENERATED_BODY()

public:
	UEnemyFSM();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	//���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EEnemyState mState = EEnemyState::Idle;

	//��� ����
	void IdleState();
	//�̵� ����
	void MoveState();
	//���� ����
	void AttackState();
	//�ǰ� ����
	void DamageState();
	//���� ����
	void DieState();

	//��� �ð�
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2.f;
	//��� �ð�
	float currentTime = 0.f;

	//Ÿ��
	UPROPERTY(VisibleAnywhere, Category=FSM)
	class ATPSPlayer* target;

	//���� ����
	UPROPERTY()
	class AEnemy* me;

	//���� ����
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.f;

	//���� ��� �ð�
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackDelayTime = 2.f;

	//�ǰ� �˸� �̺�Ʈ �Լ�
	void OnDamageProcess();

	//ü��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	int32 hp = 3;
	//�ǰ� ��� �ð�
	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 2.f;

	//�Ʒ��� ������� �ӵ�
	UPROPERTY(EditAnywhere, Category=FSM)
	float dieSpeed = 50.f;

	//��� ���� �ִϸ��̼� �������Ʈ
	UPROPERTY()
	class UEnemyAnim* anim;

	//Enemy�� �����ϰ� �ִ� AIController
	UPROPERTY()
	class AAIController* ai;

	//�� ã�� ����� ���� ��ġ
	FVector randomPos;
	//���� ��ġ ��������
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest);
};
