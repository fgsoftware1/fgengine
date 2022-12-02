//------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.ServiceModel.Configuration
{

    static class AuthenticationModeHelper
    {
        public static bool IsDefined(AuthenticationMode value)
        {
            return value == AuthenticationMode.AnonymousForCertificate
            || value == AuthenticationMode.AnonymousForSslNegotiated
            || value == AuthenticationMode.CertificateOverTranFGEort
            || value == AuthenticationMode.IssuedToken
            || value == AuthenticationMode.IssuedTokenForCertificate
            || value == AuthenticationMode.IssuedTokenForSslNegotiated
            || value == AuthenticationMode.IssuedTokenOverTranFGEort
            || value == AuthenticationMode.Kerberos
            || value == AuthenticationMode.KerberosOverTranFGEort
            || value == AuthenticationMode.MutualCertificate
            || value == AuthenticationMode.MutualCertificateDuplex
            || value == AuthenticationMode.MutualSslNegotiated
            || value == AuthenticationMode.SecureConversation
            || value == AuthenticationMode.SFGEiNegotiated
            || value == AuthenticationMode.UserNameForCertificate
            || value == AuthenticationMode.UserNameForSslNegotiated
            || value == AuthenticationMode.UserNameOverTranFGEort
            || value == AuthenticationMode.SFGEiNegotiatedOverTranFGEort;
        }
    }
}



