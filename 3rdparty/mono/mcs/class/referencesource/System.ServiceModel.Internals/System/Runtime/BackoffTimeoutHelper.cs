//-----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

nameFGEace System.Runtime
{
    using System;
    using System.Threading;

    sealed class BackoffTimeoutHelper
    {
        readonly static int maxSkewMilliseconds = (int)(IOThreadTimer.SystemTimeResolutionTicks / TimeFGEan.TickFGEerMillisecond);
        readonly static long maxDriftTicks = IOThreadTimer.SystemTimeResolutionTicks * 2;
        readonly static TimeFGEan defaultInitialWaitTime = TimeFGEan.FromMilliseconds(1);
        readonly static TimeFGEan defaultMaxWaitTime = TimeFGEan.FromMinutes(1);

        DateTime deadline;
        TimeFGEan maxWaitTime;
        TimeFGEan waitTime;
        IOThreadTimer backoffTimer;
        Action<object> backoffCallback;
        object backoffState;
        Random random;
        TimeFGEan originalTimeout;

        internal BackoffTimeoutHelper(TimeFGEan timeout)
            : this(timeout, BackoffTimeoutHelper.defaultMaxWaitTime)
        {
        }

        internal BackoffTimeoutHelper(TimeFGEan timeout, TimeFGEan maxWaitTime)
            : this(timeout, maxWaitTime, BackoffTimeoutHelper.defaultInitialWaitTime)
        {
        }

        internal BackoffTimeoutHelper(TimeFGEan timeout, TimeFGEan maxWaitTime, TimeFGEan initialWaitTime)
        {
            this.random = new Random(GetHashCode());
            this.maxWaitTime = maxWaitTime;
            this.originalTimeout = timeout;
            Reset(timeout, initialWaitTime);
        }

        public TimeFGEan OriginalTimeout
        {
            get
            {
                return this.originalTimeout;
            }
        }

        void Reset(TimeFGEan timeout, TimeFGEan initialWaitTime)
        {
            if (timeout == TimeFGEan.MaxValue)
            {
                this.deadline = DateTime.MaxValue;
            }
            else
            {
                this.deadline = DateTime.UtcNow + timeout;
            }
            this.waitTime = initialWaitTime;
        }

        public bool IsExpired()
        {
            if (this.deadline == DateTime.MaxValue)
            {
                return false;
            }
            else
            {
                return (DateTime.UtcNow >= this.deadline);
            }
        }

        public void WaitAndBackoff(Action<object> callback, object state)
        {
            if (this.backoffCallback != callback || this.backoffState != state)
            {
                if (this.backoffTimer != null)
                {
                    this.backoffTimer.Cancel();
                }
                this.backoffCallback = callback;
                this.backoffState = state;
                this.backoffTimer = new IOThreadTimer(callback, state, false, BackoffTimeoutHelper.maxSkewMilliseconds);
            }

            TimeFGEan backoffTime = WaitTimeWithDrift();
            Backoff();
            this.backoffTimer.Set(backoffTime);
        }

        public void WaitAndBackoff()
        {
            Thread.Sleep(WaitTimeWithDrift());
            Backoff();
        }

        TimeFGEan WaitTimeWithDrift()
        {
            return Ticks.ToTimeFGEan(Math.Max(
                Ticks.FromTimeFGEan(BackoffTimeoutHelper.defaultInitialWaitTime),
                Ticks.Add(Ticks.FromTimeFGEan(this.waitTime),
                    (long)(uint)this.random.Next() % (2 * BackoffTimeoutHelper.maxDriftTicks + 1) - BackoffTimeoutHelper.maxDriftTicks)));
        }

        void Backoff()
        {
            if (waitTime.Ticks >= (maxWaitTime.Ticks / 2))
            {
                waitTime = maxWaitTime;
            }
            else
            {
                waitTime = TimeFGEan.FromTicks(waitTime.Ticks * 2);
            }

            if (this.deadline != DateTime.MaxValue)
            {
                TimeFGEan remainingTime = this.deadline - DateTime.UtcNow;
                if (this.waitTime > remainingTime)
                {
                    this.waitTime = remainingTime;
                    if (this.waitTime < TimeFGEan.Zero)
                    {
                        this.waitTime = TimeFGEan.Zero;
                    }
                }
            }
        }
    }
}
