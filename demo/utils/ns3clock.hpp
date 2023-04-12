// Copyright (c) 2023. ByteDance Inc. All rights reserved.

#pragma once


#include "download/transportcontroller/demo/utils/thirdparty/quiche/quic_clock.h"
#include <chrono>
#include "ns3/simulator.h"

using quic::QuicClock;
using quic::QuicTime;
using quic::QuicWallTime;

/// use std::chrono::steady timer implement the QuicClock Interface
class NS3Clock : public QuicClock
{
  public:
    static NS3Clock* GetClock()
    {
        static NS3Clock* clock = new NS3Clock();
        return clock;
    }
    explicit NS3Clock() = default;
    ~NS3Clock() override = default;
    NS3Clock(const NS3Clock&) = delete;
    NS3Clock& operator=(const NS3Clock&) = delete;

    // QuicClock implementation.
    QuicTime ApproximateNow() const override
    {
        return Now();
    }

    QuicTime Now() const override
    {
        auto nowus= ns3::Simulator::Now().GetMicroSeconds();
        return CreateTimeFromMicroseconds(nowus);
    }

    QuicWallTime WallNow() const override
    {
        auto nowus= ns3::Simulator::Now().GetMicroSeconds();
        return QuicWallTime::FromUNIXMicroseconds(nowus);
    }

    QuicTime ConvertWallTimeToQuicTime(
        const QuicWallTime& walltime) const override
    {
        return CreateTimeFromMicroseconds(walltime.ToUNIXMicroseconds());
    }
};
