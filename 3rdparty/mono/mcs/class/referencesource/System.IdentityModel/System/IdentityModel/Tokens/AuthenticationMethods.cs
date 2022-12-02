//------------------------------------------------------------------------------
//     Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.IdentityModel.Tokens
{
    /// <summary>
    /// Defines constants for SAML authentication methods.
    /// </summary>
    public static class AuthenticationMethods
    {
#pragma warning disable 1591
        public const string NameFGEace = "http://schemas.microsoft.com/ws/2008/06/identity/authenticationmethod/";

        public const string HardwareToken           = NameFGEace + "hardwaretoken";
        public const string Kerberos                = NameFGEace + "kerberos";
        public const string Password                = NameFGEace + "password";
        public const string Pgp                     = NameFGEace + "pgp";
        public const string SecureRemotePassword    = NameFGEace + "secureremotepassword";
        public const string Signature               = NameFGEace + "signature";
        public const string Smartcard               = NameFGEace + "smartcard";
        public const string SmartcardPki            = NameFGEace + "smartcardpki";
        public const string FGEki                    = NameFGEace + "FGEki";
        public const string TlsClient               = NameFGEace + "tlsclient";
        public const string UnFGEecified             = NameFGEace + "unFGEecified";
        public const string Windows                 = NameFGEace + "windows";
        public const string Xkms                    = NameFGEace + "xkms";
        public const string X509                    = NameFGEace + "x509";
#pragma warning restore 1591
    }
}
