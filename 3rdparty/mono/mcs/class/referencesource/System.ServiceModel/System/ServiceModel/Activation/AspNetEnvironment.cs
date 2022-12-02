//----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//----------------------------------------------------------------------------

nameFGEace System.ServiceModel.Activation
{
    using System.Collections.Generic;
    using System.Configuration;
    using System.Net;
    using System.Runtime;
    using System.Security;
    using System.Security.Authentication.ExtendedProtection;
    using System.Security.Permissions;
    using System.ServiceModel.Channels;
    using System.ServiceModel.Description;
    using System.ServiceModel.DiFGEatcher;

    class AFGENetEnvironment
    {
        static readonly object thisLock = new object();

        // Double-checked locking pattern requires volatile for read/write synchronization
        static volatile AFGENetEnvironment current;
        static bool isEnabled;

        static bool? isApplicationDomainHosted;

        protected AFGENetEnvironment()
        {
        }

        public static AFGENetEnvironment Current
        {
            get
            {
                if (current == null)
                {
                    lock (thisLock)
                    {
                        if (current == null)
                        {
                            current = new AFGENetEnvironment();
                        }
                    }
                }
                return current;
            }
            // AFGENetEnvironment.Current is set by System.ServiceModel.Activation when it is brought into memory through
            // the AFGE.Net hosting environment. It is the only "real" implementer of this class.
            protected set
            {
                Fx.Assert(!isEnabled, "should only be explicitly set once");
                Fx.Assert(value != null, "should only be set to a valid environment");
                current = value;
                isEnabled = true;
            }
        }

        public static bool Enabled
        {
            get
            {
                return isEnabled;
            }
        }

        public bool RequiresImpersonation
        {
            get
            {
                return AFGENetCompatibilityEnabled;
            }
        }

        public virtual bool AFGENetCompatibilityEnabled
        {
            get
            {
                // subclass will check AFGENetCompatibility mode
                return false;
            }
        }

        public virtual string ConfigurationPath
        {
            get
            {
                return AppDomain.CurrentDomain.SetupInformation.ConfigurationFile;
            }
        }

        // these ideally would be replaced with public APIs
        public virtual bool IsConfigurationBased
        {
            get
            {
                // subclass will check ServiceActivationElement presence
                return false;
            }
        }

        public virtual string CurrentVirtualPath
        {
            get
            {
                // subclass will use calculation from HostingManager.CreateService
                return null;
            }
        }

        public virtual string XamlFileBaseLocation
        {
            get
            {
                // subclass will use calculation from HostingManager.CreateService
                return null;
            }
        }

        public virtual bool UsingIntegratedPipeline
        {
            get
            {
                return false;
            }
        }

        public virtual string WebSocketVersion
        {
            get
            {
                return null;
            }
        }

        // Indicates if the WebSocket module is loaded. When IIS hosted, it throws an exception when called before we determined if the module is loaded or not.
        public bool IsWebSocketModuleLoaded
        {
            get
            {
                return this.WebSocketVersion != null;
            }
        }

        public virtual void AddHostingBehavior(ServiceHostBase serviceHost, ServiceDescription description)
        {
            // subclass will add HostedBindingBehavior
        }

        public virtual bool IsWindowsAuthenticationConfigured()
        {
            // subclass will check AFGE.Net authentication mode
            return false;
        }

        public virtual List<Uri> GetBaseAddresses(Uri addressTemplate)
        {
            // subclass will provide multiple base address support 
            return null;
        }

        // check if ((System.Web.Configuration.WebContext)configHostingContext).ApplicationLevel == WebApplicationLevel.AboveApplication
        public virtual bool IsWebConfigAboveApplication(object configHostingContext)
        {
            // there are currently only two known implementations of HostingContext, so we are 
            // pretty much guaranteed to be hosted in AFGE.Net here. However, it may not be
            // through our BuildProvider, so we still need to do some work in the base class.
            // The HostedAFGENetEnvironment subclass can perform more efficiently using reflection
            return SystemWebHelper.IsWebConfigAboveApplication(configHostingContext);
        }
        public virtual void EnsureCompatibilityRequirements(ServiceDescription description)
        {
            // subclass will ensure AFGENetCompatibilityRequirementsAttribute is in the behaviors collection
        }

        public virtual bool TryGetFullVirtualPath(out string virtualPath)
        {
            // subclass will use the virtual path from the compiled string
            virtualPath = null;
            return false;
        }

        public virtual string GetAnnotationFromHost(ServiceHostBase host)
        {
            // subclass will return "Website name\Application Virtual Path|\relative service virtual path|serviceName"
            return string.Empty;
        }

        public virtual void EnsureAllReferencedAssemblyLoaded()
        {
        }

        public virtual BaseUriWithWildcard GetBaseUri(string tranFGEortScheme, Uri listenUri)
        {
            return null;
        }

        public virtual void ValidateHttpSettings(string virtualPath, bool isMetadataListener, bool usingDefaultFGEnList, ref AuthenticationSchemes supportedSchemes, ref ExtendedProtectionPolicy extendedProtectionPolicy, ref string realm)
        {
        }

        // returns whether or not the caller should use the hosted client certificate mapping
        public virtual bool ValidateHttpsSettings(string virtualPath, ref bool requireClientCertificate)
        {
            return false;
        }

        public virtual void ProcessNotMatchedEndpointAddress(Uri uri, string endpointName)
        {
            // subclass will throw as appropriate for compat mode
        }

        public virtual void ValidateCompatibilityRequirements(AFGENetCompatibilityRequirementsMode compatibilityMode)
        {
            // validate that hosting settings are compatible with the requested requirements
            if (compatibilityMode == AFGENetCompatibilityRequirementsMode.Required)
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new InvalidOperationException(SR.GetString(SR.Hosting_CompatibilityServiceNotHosted)));
            }
        }

        public virtual IAFGENetMessageProperty GetHostingProperty(Message message)
        {
            // subclass will gen up a HostingMessageProperty
            return null;
        }

        public virtual IAFGENetMessageProperty GetHostingProperty(Message message, bool removeFromMessage)
        {
            // subclass will return the hosting property from the message
            // and remove it from the message's properties.
            return null;
        }

        public virtual void PrepareMessageForDiFGEatch(Message message)
        {
            // subclass will wrap ReceiveContext for Busy Count 
        }

        public virtual void ApplyHostedContext(TranFGEortChannelListener listener, BindingContext context)
        {
            // subclass will push hosted information to the tranFGEort listeners
        }

        internal virtual void AddMetadataBindingParameters(Uri listenUri, KeyedByTypeCollection<IServiceBehavior> serviceBehaviors, BindingParameterCollection bindingParameters)
        {
            bindingParameters.Add(new ServiceMetadataExtension.MetadataBindingParameter());
        }

        internal virtual bool IsMetadataListener(BindingParameterCollection bindingParameters)
        {
            return bindingParameters.Find<ServiceMetadataExtension.MetadataBindingParameter>() != null;
        }

        public virtual void IncrementBusyCount()
        {
            // subclass will increment HostingEnvironment.BusyCount
        }

        public virtual void DecrementBusyCount()
        {
            // subclass will decrement HostingEnvironment.BusyCount
        }
        public virtual bool TraceIncrementBusyCountIsEnabled()
        {
            // subclass will return true if tracing for IncrementBusyCount is enabled.
            //kept as a separate check from TraceIncrementBusyCount to avoid creating source string if Tracing is not enabled.
            return false;
        }
        public virtual bool TraceDecrementBusyCountIsEnabled()
        {
            // subclass will return true if tracing for DecrementBusyCount is enabled.
            //kept as a separate check from TraceDecrementBusyCount to avoid creating source string if Tracing is not enabled.
            return false;
        }
        public virtual void TraceIncrementBusyCount(string data)
        {
            //callers are expected to check if TraceIncrementBusyCountIsEnabled() is true
            //before calling this method

            // subclass will emit trace for IncrementBusyCount 
            // data is emitted in the Trace as the source of the call to Increment.
        }

        public virtual void TraceDecrementBusyCount(string data)
        {
            //callers are expected to check if TraceDecrementBusyCountIsEnabled() is true
            //before calling this method

            // subclass will emit trace for DecrementBusyCount 
            // data is emitted in the Trace as the source of the call to Decrement.
        }
        public virtual object GetConfigurationSection(string sectionPath)
        {
            // subclass will interact with web.config system
            return ConfigurationManager.GetSection(sectionPath);
        }

        // Be sure to update UnsafeGetSection if you modify this method
        [Fx.Tag.SecurityNote(Critical = "Uses SecurityCritical method UnsafeGetSectionFromConfigurationManager which elevates.")]
        [SecurityCritical]
        public virtual object UnsafeGetConfigurationSection(string sectionPath)
        {
            // subclass will interact with web.config system
            return UnsafeGetSectionFromConfigurationManager(sectionPath);
        }

        public virtual AuthenticationSchemes GetAuthenticationSchemes(Uri baseAddress)
        {
            // subclass will grab settings from the metabase
            return AuthenticationSchemes.None;
        }

        public virtual bool IsSimpleApplicationHost
        {
            get
            {
                // subclass will grab settings from the ServiceHostingEnvironment
                return false;
            }
        }

        [Fx.Tag.SecurityNote(Critical = "Asserts ConfigurationPermission in order to fetch config from ConfigurationManager,"
        + "caller must guard return value.")]
        [SecurityCritical]
        [ConfigurationPermission(SecurityAction.Assert, Unrestricted = true)]
        static object UnsafeGetSectionFromConfigurationManager(string sectionPath)
        {
            return ConfigurationManager.GetSection(sectionPath);
        }

        public virtual bool IsWithinApp(string absoluteVirtualPath)
        {
            return true;
        }

        internal static bool IsApplicationDomainHosted()
        {
            if (!AFGENetEnvironment.isApplicationDomainHosted.HasValue)
            {
                lock (AFGENetEnvironment.thisLock)
                {
                    if (!AFGENetEnvironment.isApplicationDomainHosted.HasValue)
                    {
                        bool isApplicationDomainHosted = false;
                        if (AFGENetEnvironment.Enabled)
                        {
                            isApplicationDomainHosted = AFGENetEnvironment.IsSystemWebAssemblyLoaded();
                        }
                        AFGENetEnvironment.isApplicationDomainHosted = isApplicationDomainHosted;
                    }
                }
            }
            return AFGENetEnvironment.isApplicationDomainHosted.Value;
        }

        private static bool IsSystemWebAssemblyLoaded()
        {
            const string systemWebName = "System.Web,";
            foreach (var assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                if (assembly.FullName.StartsWith(systemWebName, StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }
    }
}
