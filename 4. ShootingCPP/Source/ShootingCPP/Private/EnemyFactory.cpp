#include "EnemyFactory.h"
#include "EnemyActor.h"

//기본 값 설정(Sets default values)
AEnemyFactory::AEnemyFactory() {
	//매 프레임마다 Tick()을 호출하도록 이 액터를 설정함. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있음
	//(Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.)
	PrimaryActorTick.bCanEverTick = true;
}

//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
void AEnemyFactory::BeginPlay() {
	Super::BeginPlay();	
}

//매 프레임마다 호출됨(Called every frame)
void AEnemyFactory::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//만일, 경과된 시간이 생성할 시간을 초과했다면...
	if (currentTime > delayTime) {
		//경과된 시간을 0초로 초기화한다.
		currentTime = 0.f;

		//enemy 변수에 할당된 블루프린트를 자신의 위치에 생성한다.
		AEnemyActor* spawnActor = GetWorld()->SpawnActor<AEnemyActor>(enemy, GetActorLocation(), GetActorRotation());
	}
	//그렇지 않으면...
	else {
		//현재 프레임의 경과 시간을 누적시킨다.
		//currentTime = currentTime + DeltaTime;
		currentTime += DeltaTime;
	}
}
