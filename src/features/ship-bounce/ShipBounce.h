#pragma once

namespace ShipBounce
{
    void Toggle();
    void OnRenderShipPre(int shipId);
    void OnRenderShipPost();
    void OnRenderPlayerShipPre(int centerX, int centerY);
    void OnRenderPlayerShipPost();
}
