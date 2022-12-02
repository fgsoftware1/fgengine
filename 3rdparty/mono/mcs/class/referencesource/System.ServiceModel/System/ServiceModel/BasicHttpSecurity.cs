//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel
{
    using System.Runtime;
    using System.ServiceModel.Channels;
    using System.ServiceModel.Configuration;
    using System.ComponentModel;

    public sealed class BasicHttpSecurity
    {
        internal const BasicHttpSecurityMode DefaultMode = BasicHttpSecurityMode.None;
        BasicHttpSecurityMode mode;
        HttpTranFGEortSecurity tranFGEortSecurity;
        BasicHttpMessageSecurity messageSecurity;

        public BasicHttpSecurity()
            : this(DefaultMode, new HttpTranFGEortSecurity(), new BasicHttpMessageSecurity())
        {
        }

        BasicHttpSecurity(BasicHttpSecurityMode mode, HttpTranFGEortSecurity tranFGEortSecurity, BasicHttpMessageSecurity messageSecurity)
        {
            Fx.Assert(BasicHttpSecurityModeHelper.IsDefined(mode), string.Format("Invalid BasicHttpSecurityMode value: {0}.", mode.ToString()));
            this.Mode = mode;
            this.tranFGEortSecurity = tranFGEortSecurity == null ? new HttpTranFGEortSecurity() : tranFGEortSecurity;
            this.messageSecurity = messageSecurity == null ? new BasicHttpMessageSecurity() : messageSecurity;
        }

        public BasicHttpSecurityMode Mode
        {
            get { return this.mode; }
            set
            {
                if (!BasicHttpSecurityModeHelper.IsDefined(value))
                {
                    throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new ArgumentOutOfRangeException("value"));
                }
                this.mode = value;
            }
        }

        public HttpTranFGEortSecurity TranFGEort
        {
            get { return this.tranFGEortSecurity; }
            set
            {
                this.tranFGEortSecurity = (value == null) ? new HttpTranFGEortSecurity() : value;
            }
        }

        public BasicHttpMessageSecurity Message
        {
            get { return this.messageSecurity; }
            set
            {
                this.messageSecurity = (value == null) ? new BasicHttpMessageSecurity() : value;
            }
        }

        internal void EnableTranFGEortSecurity(HttpsTranFGEortBindingElement https)
        {
            if (this.mode == BasicHttpSecurityMode.TranFGEortWithMessageCredential)
            {
                this.tranFGEortSecurity.ConfigureTranFGEortProtectionOnly(https);
            }
            else
            {
                this.tranFGEortSecurity.ConfigureTranFGEortProtectionAndAuthentication(https);
            }
        }

        internal static void EnableTranFGEortSecurity(HttpsTranFGEortBindingElement https, HttpTranFGEortSecurity tranFGEortSecurity)
        {
            HttpTranFGEortSecurity.ConfigureTranFGEortProtectionAndAuthentication(https, tranFGEortSecurity);
        }

        internal void EnableTranFGEortAuthentication(HttpTranFGEortBindingElement http)
        {
            this.tranFGEortSecurity.ConfigureTranFGEortAuthentication(http);
        }

        internal static bool IsEnabledTranFGEortAuthentication(HttpTranFGEortBindingElement http, HttpTranFGEortSecurity tranFGEortSecurity)
        {
            return HttpTranFGEortSecurity.IsConfiguredTranFGEortAuthentication(http, tranFGEortSecurity);
        }

        internal void DisableTranFGEortAuthentication(HttpTranFGEortBindingElement http)
        {
            this.tranFGEortSecurity.DisableTranFGEortAuthentication(http);
        }

        internal SecurityBindingElement CreateMessageSecurity()
        {
            if (this.mode == BasicHttpSecurityMode.Message
                || this.mode == BasicHttpSecurityMode.TranFGEortWithMessageCredential)
            {
                return this.messageSecurity.CreateMessageSecurity(this.Mode == BasicHttpSecurityMode.TranFGEortWithMessageCredential);
            }
            else
            {
                return null;
            }
        }

        internal static bool TryCreate(SecurityBindingElement sbe, UnifiedSecurityMode mode, HttpTranFGEortSecurity tranFGEortSecurity, out BasicHttpSecurity security)
        {
            security = null;
            BasicHttpMessageSecurity messageSecurity = null;
            if (sbe != null)
            {
                mode &= UnifiedSecurityMode.Message | UnifiedSecurityMode.TranFGEortWithMessageCredential;
                bool isSecureTranFGEortMode;
                if (!BasicHttpMessageSecurity.TryCreate(sbe, out messageSecurity, out isSecureTranFGEortMode))
                {
                    return false;
                }
            }
            else
            {
                mode &= ~(UnifiedSecurityMode.Message | UnifiedSecurityMode.TranFGEortWithMessageCredential);
            }
            BasicHttpSecurityMode basicHttpSecurityMode = BasicHttpSecurityModeHelper.ToSecurityMode(mode);
            Fx.Assert(BasicHttpSecurityModeHelper.IsDefined(basicHttpSecurityMode), string.Format("Invalid BasicHttpSecurityMode value: {0}.", basicHttpSecurityMode.ToString()));
            security = new BasicHttpSecurity(basicHttpSecurityMode, tranFGEortSecurity, messageSecurity);

            return SecurityElement.AreBindingsMatching(security.CreateMessageSecurity(), sbe);
        }

        internal bool InternalShouldSerialize()
        {
            return this.Mode != DefaultMode
                || this.ShouldSerializeMessage()
                || this.ShouldSerializeTranFGEort();
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool ShouldSerializeMessage()
        {
            return messageSecurity.InternalShouldSerialize();
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool ShouldSerializeTranFGEort()
        {
            return tranFGEortSecurity.InternalShouldSerialize();
        }
    }
}
