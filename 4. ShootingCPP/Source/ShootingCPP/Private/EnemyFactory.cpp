#include "EnemyFactory.h"
#include "EnemyActor.h"

//�⺻ �� ����(Sets default values)
AEnemyFactory::AEnemyFactory() {
	//�� �����Ӹ��� Tick()�� ȣ���ϵ��� �� ���͸� ������. �ʿ����� ���� ��� �� ����� �����Ͽ� ������ ����ų �� ����
	//(Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.)
	PrimaryActorTick.bCanEverTick = true;
}

//������ ���۵� �� �Ǵ� ������ �� ȣ���(Called when the game starts or when spawned)
void AEnemyFactory::BeginPlay() {
	Super::BeginPlay();	
}

//�� �����Ӹ��� ȣ���(Called every frame)
void AEnemyFactory::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//����, ����� �ð��� ������ �ð��� �ʰ��ߴٸ�...
	if (currentTime > delayTime) {
		//����� �ð��� 0�ʷ� �ʱ�ȭ�Ѵ�.
		currentTime = 0.f;

		//enemy ������ �Ҵ�� �������Ʈ�� �ڽ��� ��ġ�� �����Ѵ�.
		AEnemyActor* spawnActor = GetWorld()->SpawnActor<AEnemyActor>(enemy, GetActorLocation(), GetActorRotation());
	}
	//�׷��� ������...
	else {
		//���� �������� ��� �ð��� ������Ų��.
		//currentTime = currentTime + DeltaTime;
		currentTime += DeltaTime;
	}
}
