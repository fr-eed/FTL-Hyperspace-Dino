#include "Global.h"
#include "ShipBounce.h"

HOOK_METHOD(CompleteShip, OnRenderShip, (bool unk1, bool unk2) -> void)
{
    LOG_HOOK("HOOK_METHOD -> CompleteShip::OnRenderShip -> Begin (ShipBounceHooks.cpp)\n")

    ShipBounce::OnRenderShipPre(iShipId);
    super(unk1, unk2);
    ShipBounce::OnRenderShipPost();
}

HOOK_METHOD(CommandGui, RenderPlayerShip, (Point &shipCenter, float jumpScale) -> void)
{
    LOG_HOOK("HOOK_METHOD -> CommandGui::RenderPlayerShip -> Begin (ShipBounceHooks.cpp)\n")

    ShipBounce::OnRenderPlayerShipPre(shipCenter.x, shipCenter.y);
    super(shipCenter, jumpScale);
    ShipBounce::OnRenderPlayerShipPost();
}
