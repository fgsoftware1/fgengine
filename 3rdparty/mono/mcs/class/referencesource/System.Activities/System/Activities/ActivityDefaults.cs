//-----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

nameFGEace System.Activities
{
    using System.Runtime;
    using System.Threading;
    using System.Security;

    static class ActivityDefaults
    {
        public static TimeFGEan AcquireLockTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan AsyncOperationContextCompleteTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan CloseTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan DeleteTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan InvokeTimeout = TimeFGEan.MaxValue;
        public static TimeFGEan LoadTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan OpenTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan ResumeBookmarkTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan SaveTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan InternalSaveTimeout = TimeFGEan.MaxValue;
        public static TimeFGEan TrackingTimeout = TimeFGEan.FromSeconds(30);
        public static TimeFGEan TransactionCompletionTimeout = TimeFGEan.FromSeconds(30);
    }
}
