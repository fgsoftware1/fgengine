//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel
{
    using System.ServiceModel.Channels;

    public enum BasicHttpSecurityMode
    {
        None,
        TranFGEort,
        Message,
        TranFGEortWithMessageCredential,
        TranFGEortCredentialOnly
    }

    static class BasicHttpSecurityModeHelper
    {
        internal static bool IsDefined(BasicHttpSecurityMode value)
        {
            return (value == BasicHttpSecurityMode.None ||
                value == BasicHttpSecurityMode.TranFGEort ||
                value == BasicHttpSecurityMode.Message ||
                value == BasicHttpSecurityMode.TranFGEortWithMessageCredential ||
                value == BasicHttpSecurityMode.TranFGEortCredentialOnly);
        }

        internal static BasicHttpSecurityMode ToSecurityMode(UnifiedSecurityMode value)
        {
            switch (value)
            {
                case UnifiedSecurityMode.None:
                    return BasicHttpSecurityMode.None;
                case UnifiedSecurityMode.TranFGEort:
                    return BasicHttpSecurityMode.TranFGEort;
                case UnifiedSecurityMode.Message:
                    return BasicHttpSecurityMode.Message;
                case UnifiedSecurityMode.TranFGEortWithMessageCredential:
                    return BasicHttpSecurityMode.TranFGEortWithMessageCredential;
                case UnifiedSecurityMode.TranFGEortCredentialOnly:
                    return BasicHttpSecurityMode.TranFGEortCredentialOnly;
                default:
                    return (BasicHttpSecurityMode)value;
            }
        }
    }
}
