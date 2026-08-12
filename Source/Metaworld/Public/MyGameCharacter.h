#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UENUM(BlueprintType)
enum class ECameraViewMode : uint8
{
    ThirdPerson,
    FirstPerson
};

UCLASS()
class METAWORLD_API AMyGameCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyGameCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> ToggleCameraAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    ECameraViewMode CurrentCameraMode = ECameraViewMode::ThirdPerson;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void ToggleCamera();
    void UpdateCameraView();
};
