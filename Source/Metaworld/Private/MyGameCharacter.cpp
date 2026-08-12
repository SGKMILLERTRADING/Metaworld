#include "MyGameCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

AMyGameCharacter::AMyGameCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMyGameCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                    LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (DefaultMappingContext)
                {
                    Subsystem->AddMappingContext(DefaultMappingContext, 0);
                }
            }
        }
    }

    UpdateCameraView();
}

void AMyGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent =
            Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(
                MoveAction,
                ETriggerEvent::Triggered,
                this,
                &AMyGameCharacter::Move);
        }

        if (LookAction)
        {
            EnhancedInputComponent->BindAction(
                LookAction,
                ETriggerEvent::Triggered,
                this,
                &AMyGameCharacter::Look);
        }

        if (JumpAction)
        {
            EnhancedInputComponent->BindAction(
                JumpAction,
                ETriggerEvent::Started,
                this,
                &ACharacter::Jump);

            EnhancedInputComponent->BindAction(
                JumpAction,
                ETriggerEvent::Completed,
                this,
                &ACharacter::StopJumping);
        }

        if (ToggleCameraAction)
        {
            EnhancedInputComponent->BindAction(
                ToggleCameraAction,
                ETriggerEvent::Started,
                this,
                &AMyGameCharacter::ToggleCamera);
        }
    }
}

void AMyGameCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (!Controller)
    {
        return;
    }

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void AMyGameCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (!Controller)
    {
        return;
    }

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void AMyGameCharacter::ToggleCamera()
{
    CurrentCameraMode =
        CurrentCameraMode == ECameraViewMode::ThirdPerson
            ? ECameraViewMode::FirstPerson
            : ECameraViewMode::ThirdPerson;

    UpdateCameraView();
}

void AMyGameCharacter::UpdateCameraView()
{
    if (!CameraBoom)
    {
        return;
    }

    if (CurrentCameraMode == ECameraViewMode::FirstPerson)
    {
        CameraBoom->TargetArmLength = 0.0f;
        CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 60.0f);
        GetCharacterMovement()->bOrientRotationToMovement = false;
        bUseControllerRotationYaw = true;
    }
    else
    {
        CameraBoom->TargetArmLength = 400.0f;
        CameraBoom->SocketOffset = FVector::ZeroVector;
        GetCharacterMovement()->bOrientRotationToMovement = true;
        bUseControllerRotationYaw = false;
    }
}
