// Snake Game, Copyright Adam Mambetov. All Rights Reserved.

#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

namespace
{
float HalfFOVTan(float FOVDegrees)
{
    return FMath::Tan(FMath::DegreesToRadians(FOVDegrees * 0.5f));
}
float VerticalFOV(float HorFOVDegrees, float ViewportAspectHW)
{
    // https://en.m.wikipedia.org/wiki/Field_of_view_in_video_games
    return FMath::RadiansToDegrees(2.f * FMath::Atan(FMath::Tan(FMath::DegreesToRadians(HorFOVDegrees) * 0.5f) * ViewportAspectHW));
}
}  // namespace

ASG_Pawn::ASG_Pawn()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    check(Camera);
    Camera->SetupAttachment(Origin);
}
void ASG_Pawn::UpdateLocation(const Snake::Dim& InDim, const int32 InCellSize, const FTransform& InGridOrigin)
{
    Dim = InDim;
    CellSize = InCellSize;
    GridOrigin = InGridOrigin;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto* Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.AddUObject(this, &ASG_Pawn::OnViewportResized);

#if WITH_EDITOR
    OnViewportResized(Viewport, 0);
#endif
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Val)
{
    if (!Viewport || Viewport->GetSizeXY().Y == 0 || Dim.height == 0) return;

    const float WorldWidth = Dim.width * CellSize;
    const float WorldHeight = Dim.height * CellSize;

    const float ViewportAspect = static_cast<float>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const float GridAspect = static_cast<float>(Dim.width) / Dim.height;

    float LocationZ;
    if (ViewportAspect <= GridAspect)
    {
        LocationZ = WorldWidth / HalfFOVTan(Camera->FieldOfView);
    }
    else
    {
        check(ViewportAspect);
        const float VFOV = VerticalFOV(Camera->FieldOfView, 1.f / ViewportAspect);
        LocationZ = WorldHeight / HalfFOVTan(VFOV);
    }

    const FVector NewPawnLocation = GridOrigin.GetLocation() + 0.5f * FVector(WorldHeight, WorldWidth, LocationZ);
    SetActorLocation(NewPawnLocation);
}