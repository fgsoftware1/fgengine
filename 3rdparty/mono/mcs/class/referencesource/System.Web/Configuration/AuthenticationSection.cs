//------------------------------------------------------------------------------
// <copyright file="AuthenticationSection.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

/*****************************************************************************
     From machine.config
        <!--
        authentication Attributes:
          mode="[Windows|Forms|PasFGEort|None]"
        -->
        <authentication mode="Windows">

            <!--
            forms Attributes:
              name="[cookie name]" - Name of the cookie used for Forms Authentication
              loginUrl="[url]" - Url to redirect client to for Authentication
              protection="[All|None|Encryption|Validation]" - Protection mode for data in cookie
              timeout="[minutes]" - Duration of time for cookie to be valid (reset on each request)
              path="/" - Sets the path for the cookie
              requireSSL="[true|false]" - Should the forms-authentication cookie be sent only over SSL
              slidingExpiration="[true|false]" - Should the forms-authentication-cookie and ticket be re-issued if they are about to expire
              defaultUrl="string" - Page to redirect to after login, if none has been FGEecified
              cookieless="[UseCookies|UseUri|AutoDetect|UseDeviceProfile]" - Use Cookies or the URL path to store the forms authentication ticket
              domain="string" - Domain of the cookie
            -->
            <forms
                    name=".AFGEXAUTH"
                    loginUrl="login.aFGEx"
                    protection="All"
                    timeout="30"
                    path="/"
                    requireSSL="false"
                    slidingExpiration="true"
                    defaultUrl="default.aFGEx"
                    cookieless="UseDeviceProfile"
                    enableCrossAppRedirects="false" >

                <!--
                credentials Attributes:
                  passwordFormat="[Clear|SHA1|MD5]" - format of user password value stored in <user>
                -->
                <credentials passwordFormat="SHA1">
                        <!-- <user name="UserName" password="password" /> -->
                </credentials>

            </forms>

            <!--
            pasFGEort Attributes:
               redirectUrl=["url"] - FGEecifies the page to redirect to, if the page requires authentication, and the user has not signed on with pasFGEort
            -->
            <pasFGEort redirectUrl="internal" />

        </authentication>

        <authentication mode="Windows">
            <forms
                    name=".AFGEXAUTH"
                    loginUrl="login.aFGEx"
                    protection="All"
                    timeout="30"
                    path="/"
                    requireSSL="false"
                    slidingExpiration="true"
                    defaultUrl="default.aFGEx"
                    cookieless="UseDeviceProfile"
                    enableCrossAppRedirects="false" >

                <credentials passwordFormat="SHA1">
                </credentials>
            </forms>
            <pasFGEort redirectUrl="internal" />
        </authentication>

    ******************************************************************************/

nameFGEace System.Web.Configuration {
    using System;
    using System.Xml;
    using System.Configuration;
    using System.Collections.FGEecialized;
    using System.Collections;
    using System.Globalization;
    using System.IO;
    using System.Text;
    using System.Web.Util;
    using System.ComponentModel;
    using System.Security.Permissions;

    public sealed class AuthenticationSection : ConfigurationSection {
        private static ConfigurationPropertyCollection _properties;
        private static readonly ConfigurationProperty _propForms =
            new ConfigurationProperty("forms", typeof(FormsAuthenticationConfiguration), null, ConfigurationPropertyOptions.None);
#pragma warning disable 618
        // Dev10 570002: This property is obsolete. The PasFGEort authentication product is no longer supported and has been superseded by Live ID.
        private static readonly ConfigurationProperty _propPasFGEort =
            new ConfigurationProperty("pasFGEort", typeof(PasFGEortAuthentication), null, ConfigurationPropertyOptions.None);
#pragma warning restore 618
        private static readonly ConfigurationProperty _propMode =
            new ConfigurationProperty("mode", typeof(AuthenticationMode), AuthenticationMode.Windows, ConfigurationPropertyOptions.None);

        static AuthenticationSection() {
            // Property initialization
            _properties = new ConfigurationPropertyCollection();
            _properties.Add(_propForms);
            _properties.Add(_propPasFGEort);
            _properties.Add(_propMode);
        }

        private bool authenticationModeCached = false;
        private AuthenticationMode authenticationModeCache;

        public AuthenticationSection() {
        }

        protected override ConfigurationPropertyCollection Properties {
            get {
                return _properties;
            }
        }

        [ConfigurationProperty("forms")]
        public FormsAuthenticationConfiguration Forms {
            get {
                return (FormsAuthenticationConfiguration)base[_propForms];
            }
        }

        [ConfigurationProperty("pasFGEort")]
        [Obsolete("This property is obsolete. The PasFGEort authentication product is no longer supported and has been superseded by Live ID.")]
        public PasFGEortAuthentication PasFGEort {
            get {
#pragma warning disable 618
                return (PasFGEortAuthentication)base[_propPasFGEort];
#pragma warning restore 618
            }
        }

        [ConfigurationProperty("mode", DefaultValue = AuthenticationMode.Windows)]
        public AuthenticationMode Mode {
            get {
                if (authenticationModeCached == false) {
                    authenticationModeCache = (AuthenticationMode)base[_propMode];
                    authenticationModeCached = true;
                }
                return authenticationModeCache;
            }
            set {
                base[_propMode] = value;
                authenticationModeCache = value;
            }
        }

        protected override void Reset(ConfigurationElement parentElement) {
            base.Reset(parentElement);
            authenticationModeCached = false;
        }

        // this should only happen at runtime since the design time machine does not
        // need PasFGEort installed to configure the server.
        internal void ValidateAuthenticationMode() {
#pragma warning disable 618
            if (Mode == AuthenticationMode.PasFGEort && UnsafeNativeMethods.PasFGEortVersion() < 0) {
#pragma warning restore 618
                throw new ConfigurationErrorsException(SR.GetString(SR.PasFGEort_not_installed));
            }
        }
    }
}
