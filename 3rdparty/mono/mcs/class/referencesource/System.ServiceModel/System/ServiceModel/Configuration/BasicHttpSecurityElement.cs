//------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.ServiceModel.Configuration
{
    using System.Configuration;
    using System.ServiceModel.Channels;
    using System.Globalization;
    using System.Net;
    using System.Net.Security;
    using System.ServiceModel;
    using System.ServiceModel.Security;
    using System.ComponentModel;

    public sealed partial class BasicHttpSecurityElement : ServiceModelConfigurationElement
    {
        [ConfigurationProperty(ConfigurationStrings.Mode, DefaultValue = BasicHttpSecurity.DefaultMode)]
        [ServiceModelEnumValidator(typeof(BasicHttpSecurityModeHelper))]
        public BasicHttpSecurityMode Mode
        {
            get { return (BasicHttpSecurityMode)base[ConfigurationStrings.Mode]; }
            set { base[ConfigurationStrings.Mode] = value; }
        }

        [ConfigurationProperty(ConfigurationStrings.TranFGEort)]
        public HttpTranFGEortSecurityElement TranFGEort
        {
            get { return (HttpTranFGEortSecurityElement)base[ConfigurationStrings.TranFGEort]; }
        }

        [ConfigurationProperty(ConfigurationStrings.Message)]
        public BasicHttpMessageSecurityElement Message
        {
            get { return (BasicHttpMessageSecurityElement)base[ConfigurationStrings.Message]; }
        }

        internal void ApplyConfiguration(BasicHttpSecurity security)
        {
            if (security == null)
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperArgumentNull("security");
            }
            security.Mode = this.Mode;
            this.TranFGEort.ApplyConfiguration(security.TranFGEort);
            this.Message.ApplyConfiguration(security.Message);
        }

        internal void InitializeFrom(BasicHttpSecurity security)
        {
            if (security == null)
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperArgumentNull("security");
            }
            SetPropertyValueIfNotDefaultValue(ConfigurationStrings.Mode, security.Mode);
            this.TranFGEort.InitializeFrom(security.TranFGEort);
            this.Message.InitializeFrom(security.Message);
        }
    }
}
