/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/UnitTest/TestTypes.h>
#include <AzTest/AzTest.h>
#include <AzToolsFramework/PaintBrush/PaintBrush.h>
#include <AZTestShared/Math/MathTestHelpers.h>

namespace UnitTest
{
    class MockPaintBrushNotificationBusHandler : public AzToolsFramework::PaintBrushNotificationBus::Handler
    {
    public:
        MockPaintBrushNotificationBusHandler(const AZ::EntityComponentIdPair& entityComponentIdPair)
        {
            AzToolsFramework::PaintBrushNotificationBus::Handler::BusConnect(entityComponentIdPair);
        }

        ~MockPaintBrushNotificationBusHandler() override
        {
            AzToolsFramework::PaintBrushNotificationBus::Handler::BusDisconnect();
        }

        MOCK_METHOD0(OnPaintModeBegin, void());
        MOCK_METHOD0(OnPaintModeEnd, void());
        MOCK_METHOD1(OnBrushStrokeBegin, void(const AZ::Color& color));
        MOCK_METHOD0(OnBrushStrokeEnd, void());
        MOCK_METHOD3(OnPaint, void(const AZ::Aabb& dirtyArea, ValueLookupFn& valueLookupFn, BlendFn& blendFn));
        MOCK_METHOD1(OnGetColor, AZ::Color(const AZ::Vector3& brushCenterPoint));
        MOCK_METHOD4(OnSmooth, void(
            const AZ::Aabb& dirtyArea,
            ValueLookupFn& valueLookupFn,
            AZStd::span<const AZ::Vector3> valuePointOffsets,
            SmoothFn& smoothFn));
    };
}

