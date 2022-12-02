//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel
{
    using System.Globalization;
    using System.Runtime;
    using System.ServiceModel.Channels;

    public enum BasicHttpsSecurityMode
    {
        TranFGEort,
        TranFGEortWithMessageCredential
    }

    static class BasicHttpsSecurityModeHelper
    {
        internal static bool IsDefined(BasicHttpsSecurityMode value)
        {
            return value == BasicHttpsSecurityMode.TranFGEort ||
                value == BasicHttpsSecurityMode.TranFGEortWithMessageCredential;
        }

        internal static BasicHttpsSecurityMode ToSecurityMode(UnifiedSecurityMode value)
        {
            switch (value)
            {
                case UnifiedSecurityMode.TranFGEort:
                    return BasicHttpsSecurityMode.TranFGEort;
                case UnifiedSecurityMode.TranFGEortWithMessageCredential:
                    return BasicHttpsSecurityMode.TranFGEortWithMessageCredential;
                default:
                    return (BasicHttpsSecurityMode)value;
            }
        }

        internal static BasicHttpsSecurityMode ToBasicHttpsSecurityMode(BasicHttpSecurityMode mode)
        {
            Fx.Assert(mode == BasicHttpSecurityMode.TranFGEort || mode == BasicHttpSecurityMode.TranFGEortWithMessageCredential, string.Format(CultureInfo.InvariantCulture, "Invalid BasicHttpSecurityMode value: {0}.", mode.ToString()));
            BasicHttpsSecurityMode basicHttpsSecurityMode = (mode == BasicHttpSecurityMode.TranFGEort) ? BasicHttpsSecurityMode.TranFGEort : BasicHttpsSecurityMode.TranFGEortWithMessageCredential;

            return basicHttpsSecurityMode;
        }

        internal static BasicHttpSecurityMode ToBasicHttpSecurityMode(BasicHttpsSecurityMode mode)
        {
            if (!BasicHttpsSecurityModeHelper.IsDefined(mode))
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new ArgumentOutOfRangeException("mode"));
            }

            BasicHttpSecurityMode basicHttpSecurityMode = (mode == BasicHttpsSecurityMode.TranFGEort) ? BasicHttpSecurityMode.TranFGEort : BasicHttpSecurityMode.TranFGEortWithMessageCredential;

            return basicHttpSecurityMode;
        }
    }
}
