#include "KillZone.h"
#include "Components/BoxComponent.h"

//�⺻ �� ����(Sets default values)
AKillZone::AKillZone() {
	//�� �����Ӹ��� Tick()�� ȣ���ϵ��� �� ���͸� ������. �ʿ����� ���� ��� �� ����� �����Ͽ� ������ ����ų �� ����
	//(Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.)
	PrimaryActorTick.bCanEverTick = true;

	//�ڽ� ������Ʈ�� �����ϰ� ��Ʈ ������Ʈ�� �����Ѵ�.
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);

	//�ڽ� ������Ʈ�� �����Ƽ�� ���� ���·� �����Ѵ�.
	boxComp->SetMobility(EComponentMobility::Static);

	//�ڽ��� ũ�⸦ 50, 2000, 50���� �����Ѵ�.
	boxComp->SetBoxExtent(FVector(50, 2000, 50));

	//�ڽ� ������Ʈ�� �ݸ��� �������� KillZone���� �����Ѵ�.
	boxComp->SetCollisionProfileName(TEXT("KillZone"));
}

//������ ���۵� �� �Ǵ� ������ �� ȣ���(Called when the game starts or when spawned)
void AKillZone::BeginPlay() {
	Super::BeginPlay();
}

//�� �����Ӹ��� ȣ���(Called every frame)
void AKillZone::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

