#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerBaseComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPSPROJECT_API UPlayerBaseComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPlayerBaseComponent();

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	//사용자 입력 맵핑 처리 함수
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) {};

	//컴포넌트 소유 액터
	UPROPERTY()
	ATPSPlayer* me;

	UPROPERTY()
	UCharacterMovementComponent* moveComp;
};
