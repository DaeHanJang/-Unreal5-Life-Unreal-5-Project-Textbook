#include "KillZone.h"
#include "Components/BoxComponent.h"

//기본 값 설정(Sets default values)
AKillZone::AKillZone() {
	//매 프레임마다 Tick()을 호출하도록 이 액터를 설정함. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있음
	//(Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.)
	PrimaryActorTick.bCanEverTick = true;

	//박스 컴포넌트를 생성하고 루트 컴포넌트로 설정한다.
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);

	//박스 컴포넌트의 모빌리티를 고정 상태로 설정한다.
	boxComp->SetMobility(EComponentMobility::Static);

	//박스의 크기를 50, 2000, 50으로 설정한다.
	boxComp->SetBoxExtent(FVector(50, 2000, 50));

	//박스 컴포넌트의 콜리전 프리셋을 KillZone으로 설정한다.
	boxComp->SetCollisionProfileName(TEXT("KillZone"));
}

//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
void AKillZone::BeginPlay() {
	Super::BeginPlay();
}

//매 프레임마다 호출됨(Called every frame)
void AKillZone::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

