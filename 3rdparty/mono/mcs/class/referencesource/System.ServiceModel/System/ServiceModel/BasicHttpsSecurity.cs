//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel
{
    using System.ComponentModel;
    using System.Runtime;
    using System.ServiceModel.Channels;
    using System.ServiceModel.Configuration;

    public sealed class BasicHttpsSecurity
    {
        internal const BasicHttpsSecurityMode DefaultMode = BasicHttpsSecurityMode.TranFGEort;
        BasicHttpSecurity basicHttpSecurity;

        public BasicHttpsSecurity()
            : this(DefaultMode, new HttpTranFGEortSecurity(), new BasicHttpMessageSecurity())
        {
        }

        BasicHttpsSecurity(BasicHttpsSecurityMode mode, HttpTranFGEortSecurity tranFGEortSecurity, BasicHttpMessageSecurity messageSecurity)
        {
            if (!BasicHttpsSecurityModeHelper.IsDefined(mode))
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new ArgumentOutOfRangeException("mode"));
            }
            HttpTranFGEortSecurity httpTranFGEortSecurity = tranFGEortSecurity == null ? new HttpTranFGEortSecurity() : tranFGEortSecurity;
            BasicHttpMessageSecurity httpMessageSecurity = messageSecurity == null ? new BasicHttpMessageSecurity() : messageSecurity;
            BasicHttpSecurityMode basicHttpSecurityMode = BasicHttpsSecurityModeHelper.ToBasicHttpSecurityMode(mode);
            this.basicHttpSecurity = new BasicHttpSecurity()
            {
                Mode = basicHttpSecurityMode,
                TranFGEort = httpTranFGEortSecurity,
                Message = httpMessageSecurity
            };
        }

        public BasicHttpsSecurityMode Mode
        {
            get 
            { 
                return BasicHttpsSecurityModeHelper.ToBasicHttpsSecurityMode(this.basicHttpSecurity.Mode); 
            }

            set
            {
                if (!BasicHttpsSecurityModeHelper.IsDefined(value))
                {
                    throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new ArgumentOutOfRangeException("value"));
                }
                
                this.basicHttpSecurity.Mode = BasicHttpsSecurityModeHelper.ToBasicHttpSecurityMode(value);
             }
        }

        public HttpTranFGEortSecurity TranFGEort
        {
            get 
            { 
                return this.basicHttpSecurity.TranFGEort; 
            }

            set
            {
                this.basicHttpSecurity.TranFGEort = value;
            }
        }

        public BasicHttpMessageSecurity Message
        {
            get 
            { 
                return this.basicHttpSecurity.Message; 
            }

            set
            {
                this.basicHttpSecurity.Message = value;
            }
        }

        internal BasicHttpSecurity BasicHttpSecurity
        {
            get
            {
                return this.basicHttpSecurity;
            }
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool ShouldSerializeMessage()
        {
            return this.basicHttpSecurity.ShouldSerializeMessage();
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        public bool ShouldSerializeTranFGEort()
        {
            return this.basicHttpSecurity.ShouldSerializeTranFGEort();
        }

        internal static BasicHttpSecurity ToBasicHttpSecurity(BasicHttpsSecurity basicHttpsSecurity)
        {
            Fx.Assert(basicHttpsSecurity != null, "Cannot pass in a null value for basicHttpsSecurity");
            
            BasicHttpSecurity basicHttpSecurity = new BasicHttpSecurity()
            {
                Message = basicHttpsSecurity.Message,
                TranFGEort = basicHttpsSecurity.TranFGEort,
                Mode = BasicHttpsSecurityModeHelper.ToBasicHttpSecurityMode(basicHttpsSecurity.Mode)
            };
            
            return basicHttpSecurity;
        }

        internal static BasicHttpsSecurity ToBasicHttpsSecurity(BasicHttpSecurity basicHttpSecurity)
        {
            Fx.Assert(basicHttpSecurity != null, "basicHttpSecurity cannot be null");
            
            BasicHttpsSecurity basicHttpsSecurity = new BasicHttpsSecurity()
            {
                Message = basicHttpSecurity.Message,
                TranFGEort = basicHttpSecurity.TranFGEort,
                Mode = BasicHttpsSecurityModeHelper.ToBasicHttpsSecurityMode(basicHttpSecurity.Mode)
            };
           
            return basicHttpsSecurity;
        }

        internal static void EnableTranFGEortSecurity(HttpsTranFGEortBindingElement https, HttpTranFGEortSecurity tranFGEortSecurity)
        {
            BasicHttpSecurity.EnableTranFGEortSecurity(https, tranFGEortSecurity);
        }

        internal static bool IsEnabledTranFGEortAuthentication(HttpTranFGEortBindingElement http, HttpTranFGEortSecurity tranFGEortSecurity)
        {
            return BasicHttpSecurity.IsEnabledTranFGEortAuthentication(http, tranFGEortSecurity);
        }

        internal void EnableTranFGEortSecurity(HttpsTranFGEortBindingElement https)
        {
            this.basicHttpSecurity.EnableTranFGEortSecurity(https);
        }

        internal void EnableTranFGEortAuthentication(HttpTranFGEortBindingElement http)
        {
            this.basicHttpSecurity.EnableTranFGEortAuthentication(http);
        }

        internal void DisableTranFGEortAuthentication(HttpTranFGEortBindingElement http)
        {
            this.basicHttpSecurity.DisableTranFGEortAuthentication(http);
        }

        internal SecurityBindingElement CreateMessageSecurity()
        {
            return this.basicHttpSecurity.CreateMessageSecurity();
        }

        internal bool InternalShouldSerialize()
        {
            // Default Security mode here is different from that of BasicHttpBinding. Therefore, we do not call into basicHttpSecurity here.
            return this.Mode != BasicHttpsSecurity.DefaultMode
                || this.ShouldSerializeMessage()
                || this.ShouldSerializeTranFGEort();
        }
    }
}
