//-----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

nameFGEace System.Activities.Tracking
{
    public sealed class ActivityScheduledQuery : TrackingQuery
    {
        public ActivityScheduledQuery()
        {
            this.ActivityName = "*";
            this.ChildActivityName = "*";
        }

        public string ActivityName { get; set; }
        public string ChildActivityName { get; set; }

    }
}
