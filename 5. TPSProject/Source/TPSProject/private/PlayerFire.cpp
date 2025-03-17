#include "PlayerFire.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include <Camera/CameraComponent.h>
#include "PlayerAnim.h"
#include "Particles/ParticleSystem.h"

UPlayerFire::UPlayerFire() {
	ConstructorHelpers::FClassFinder<ABullet> tempBullet(TEXT("Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (tempBullet.Succeeded()) bulletFactory = tempBullet.Class;

	ConstructorHelpers::FObjectFinder<UInputAction> tempFire(TEXT("InputAction'/Game/Input/IA_Fire.IA_Fire'"));
	if (tempFire.Succeeded()) ia_Fire = tempFire.Object;
	ConstructorHelpers::FObjectFinder<UInputAction> tempGrenadeGun(TEXT("InputAction'/Game/Input/IA_GrenadeGun.IA_GrenadeGun'"));
	if (tempGrenadeGun.Succeeded()) ia_GrenadeGun = tempGrenadeGun.Object;
	ConstructorHelpers::FObjectFinder<UInputAction> tempSniperGun(TEXT("InputAction'/Game/Input/IA_SniperGun.IA_SniperGun'"));
	if (tempSniperGun.Succeeded()) ia_SniperGun = tempSniperGun.Object;
	ConstructorHelpers::FObjectFinder<UInputAction> tempSniper(TEXT("InputAction'/Game/Input/IA_Sniper.IA_Sniper'"));
	if (tempSniper.Succeeded()) ia_Sniper = tempSniper.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempParticle(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_BulletEffect.P_BulletEffect'"));
	if (tempParticle.Succeeded()) bulletEffectFactory = tempParticle.Object;

	ConstructorHelpers::FClassFinder<UUserWidget> tempSniperUIe(TEXT("WidgetBlueprint'/Game/Blueprints/WBP_SniperUI.WBP_SniperUI_C'"));
	if (tempSniperUIe.Succeeded()) sniperUIFactory = tempSniperUIe.Class;
	ConstructorHelpers::FClassFinder<UUserWidget> tempCrosshairUI(TEXT("WidgetBlueprint'/Game/Blueprints/WBP_Crosshair.WBP_Crosshair_C'"));
	if (tempCrosshairUI.Succeeded()) crosshairUIFactory = tempCrosshairUI.Class;

	ConstructorHelpers::FClassFinder<UCameraShakeBase> tempCameraShake(TEXT("Blueprint'/Game/Blueprints/BP_CameraShake.BP_CameraShake_C'"));
	if (tempCameraShake.Succeeded()) cameraShake = tempCameraShake.Class;

	//�Ѿ� ���� ��������
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("SoundWave'/Game/SniperGun/Rifle.Rifle'"));
	if (tempSound.Succeeded()) bulletSound = tempSound.Object;
}

void UPlayerFire::BeginPlay() {
	Super::BeginPlay();

	tpsCamComp = me->tpsCamComp;
	gunMeshComp = me->gunMeshComp;
	sniperGunComp = me->sniperGunComp;

	//1. �������� UI ���� �ν��Ͻ� ����
	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
	//2. �Ϲ� ���� UI ũ�ν���� �ν��Ͻ� ����
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	//3. �Ϲ� ���� UI ���
	_crosshairUI->AddToViewport();

	//�⺻���� �������۰��� ����ϵ��� ����
	ChangeToSniperGun(FInputActionValue());
}

void UPlayerFire::SetupInputBinding(class UEnhancedInputComponent* PlayerInput) {
	//�Ѿ� �߻� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInput->BindAction(ia_Fire, ETriggerEvent::Started, this, &UPlayerFire::InputFire);
	//�� ��ü �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInput->BindAction(ia_GrenadeGun, ETriggerEvent::Started, this, &UPlayerFire::ChangeToGrenadeGun);
	PlayerInput->BindAction(ia_SniperGun, ETriggerEvent::Started, this, &UPlayerFire::ChangeToSniperGun);
	//�������� ���� ��� �̺�Ʈ ó�� �Լ� ���ε�
	PlayerInput->BindAction(ia_Sniper, ETriggerEvent::Started, this, &UPlayerFire::SniperAim);
	PlayerInput->BindAction(ia_Sniper, ETriggerEvent::Completed, this, &UPlayerFire::SniperAim);
}

void UPlayerFire::InputFire(const struct FInputActionValue& inputValue) {
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	//ī�޶� ����ũ ���
	auto controller = GetWorld()->GetFirstPlayerController();
	controller->PlayerCameraManager->StartCameraShake(cameraShake);

	//���� �ִϸ��̼� ���
	auto anim = Cast<UPlayerAnim>(me->GetMesh()->GetAnimInstance());
	anim->PlayAttackAnim();

	//��ź�� ��� ��
	if (bUsingGrenadeGun) {
		//�Ѿ� �߻� ó��
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	//�������۰� ��� ��
	else {
		//LineTrace�� ���� ��ġ
		FVector startPos = tpsCamComp->GetComponentLocation();
		//LineTrace�� ���� ��ġ
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;
		//LineTrace�� �浹 ������ ���� ����
		FHitResult hitInfo;
		//�浹 �ɼ� ���� ����
		FCollisionQueryParams params;
		//�ڱ� �ڽ�(�÷��̾�)�� �浹���� ����
		params.AddIgnoredActor(me);
		//Channel ���͸� �̿��� LineTrace �浹 ����(�浹 ����, ���� ��ġ, ���� ��ġ, ���� ä��, �浹 �ɼ�)
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
		//LineTrace�� �ε����� ��
		if (bHit) {
			//�Ѿ� ���� ȿ�� Ʈ������
			FTransform bulletTrans;
			//�ε��� ��ġ �Ҵ�
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			//�Ѿ� ���� ȿ�� �ν��Ͻ� ����
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

			auto hitComp = hitInfo.GetComponent();
			//1. ���� ������Ʈ�� ������ ����� �ִٸ�
			if (hitComp && hitComp->IsSimulatingPhysics()) {
				//2. ������ ������ �ʿ�
				FVector dir = (endPos - startPos).GetSafeNormal();
				//���� ���� ��(F = ma)
				FVector force = dir * hitComp->GetMass() * 500000;
				//3. �� �������� ���� ������ �ʹ�.
				hitComp->AddForceAtLocation(force, hitInfo.ImpactPoint);
			}

			//�ε��� ����� ������ �Ǵ��ϱ�
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy) {
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				enemyFSM->OnDamageProcess();
			}
		}
	}
}

//��ź������ ����
void UPlayerFire::ChangeToGrenadeGun(const FInputActionValue& inputValue) {
	//��ź�� ��� ������ üũ
	bUsingGrenadeGun = true;
	sniperGunComp->SetVisibility(false);
	gunMeshComp->SetVisibility(true);

	//��ź�� ������� ���� ����
	me->OnUsingGrenade(bUsingGrenadeGun);
}

//�������۰����� ����
void UPlayerFire::ChangeToSniperGun(const FInputActionValue& inputValue) {
	bUsingGrenadeGun = false;
	sniperGunComp->SetVisibility(true);
	gunMeshComp->SetVisibility(false);

	//��ź�� ������� ���� ����
	me->OnUsingGrenade(bUsingGrenadeGun);
}

//�������� ����
void UPlayerFire::SniperAim(const FInputActionValue& inputValue) {
	//�������۰� ��尡 �ƴ϶�� ó������ �ʴ´�.
	if (bUsingGrenadeGun) return;

	//Pressed �Է� ó��
	if (bSniperAim == false) {
		//1. �������� ���� ��� Ȱ��ȭ
		bSniperAim = true;
		//2. ������������ UI ���
		_sniperUI->AddToViewport();
		//3. ī�޶��� �þ߰� Field Of View ����
		tpsCamComp->SetFieldOfView(45.f);
		//4. �Ϲ� ���� UI ����
		_crosshairUI->RemoveFromParent();
	}
	//Released �Է� ó��
	else {
		//1. �������� ���� ��� ��Ȱ��ȭ
		bSniperAim = false;
		//2. �������� ���� UI ȭ�鿡�� ����
		_sniperUI->RemoveFromParent();
		//3. ī�޶� �þ߰� ������� ����
		tpsCamComp->SetFieldOfView(90.f);
		//4. �Ϲ� ���� UI ���
		_crosshairUI->AddToViewport();
	}
}
