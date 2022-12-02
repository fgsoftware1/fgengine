//------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.ServiceModel.Configuration
{
    using System.Configuration;
    using System.ServiceModel;

    public sealed partial class BasicHttpsSecurityElement : ServiceModelConfigurationElement
    {
        [ConfigurationProperty(ConfigurationStrings.Mode, DefaultValue = BasicHttpsSecurity.DefaultMode)]
        [ServiceModelEnumValidator(typeof(BasicHttpsSecurityModeHelper))]
        public BasicHttpsSecurityMode Mode
        {
            get { return (BasicHttpsSecurityMode)base[ConfigurationStrings.Mode]; }
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

        internal void ApplyConfiguration(BasicHttpsSecurity security)
        {
            if (security == null)
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperArgumentNull("security");
            }

            security.Mode = this.Mode;
            this.TranFGEort.ApplyConfiguration(security.TranFGEort);
            this.Message.ApplyConfiguration(security.Message);
        }

        internal void InitializeFrom(BasicHttpsSecurity security)
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
