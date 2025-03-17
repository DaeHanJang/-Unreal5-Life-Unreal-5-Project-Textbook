#include "AccessTest.h"
#include "CodingTestActor.h"

//기본 값 설정(Sets default values)
AAccessTest::AAccessTest() {
	//매 프레임마다 Tick()을 호출하도록 이 액터를 설정함. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있음
	//(Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.)
	PrimaryActorTick.bCanEverTick = true;
}

//게임이 시작될 때 또는 스폰될 때 호출됨(Called when the game starts or when spawned)
void AAccessTest::BeginPlay() {
	Super::BeginPlay();

	ACodingTestActor* testActor = NewObject<ACodingTestActor>(this);
	testActor->number1 = -100;
	number = 200;
	numPointer = &number;
	*numPointer = -30;

	UE_LOG(LogTemp, Warning, TEXT("변수의 값: %d"), number);
	UE_LOG(LogTemp, Warning, TEXT("포인터의 값: %d"), *numPointer);

	if (testPointer != nullptr) testPointer->number2 = -10;

	//변수 생성
	int32 value1 = 5;
	int32 value2 = 10;
	int32 sum = 0;

	//AddPrint 함수를 실행한다.
	AddPrint(value1, value2, &sum);

	//sum 변수의 값을 로그로 출력한다.
	UE_LOG(LogTemp, Warning, TEXT("%d"), sum);
}

//매 프레임마다 호출됨(Called every frame)
void AAccessTest::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AAccessTest::AddPrint(int32 num1, int32 num2, int32* result) {
	//두 매개변수에서 받은 값을 더한 결과를 세 번째 매개변수에 넣는다.
	*result = num1 + num2;
}
