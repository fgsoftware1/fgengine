//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel
{
    using System.Diagnostics.CodeAnalysis;
    using System.Runtime;
    using System.Security;
    using System.Security.Permissions;
    using System.Threading;
    using System.Web;
    using System.Web.Hosting;

    static class AFGENetPartialTrustHelpers
    {
        [Fx.Tag.SecurityNote(Critical = "Caches the PermissionSet associated with the aFGE.net trust level."
            + "This will not change over the life of the AppDomain.")]
        [SecurityCritical]
        static SecurityContext aFGENetSecurityContext;

        [Fx.Tag.SecurityNote(Critical = "If erroneously set to true, could bypass the PermitOnly.")]
        [SecurityCritical]
        static bool isInitialized;

        [Fx.Tag.SecurityNote(Critical = "Critical field used to prevent usage of System.Web types in partial trust outside the AFGE.NET context.")]
        [SecurityCritical]
        private static bool isInPartialTrustOutsideAFGENet; // indicates if we are running in partial trust outside the AFGE.NET context

        [Fx.Tag.SecurityNote(Critical = "Critical field used to prevent usage of System.Web types in partial trust outside the AFGE.NET context.")]
        [SecurityCritical]
        private static bool isInPartialTrustOutsideAFGENetInitialized = false;

        [Fx.Tag.SecurityNote(Miscellaneous = "RequiresReview - determines if the given PermissionSet is full trust."
            + "We will base subsequent security decisions on this.")]
        static bool IsFullTrust(PermissionSet perms)
        {
            return perms == null || perms.IsUnrestricted();
        }

        internal static bool NeedPartialTrustInvoke
        {
            [SuppressMessage(FxCop.Category.Security, "CA2107:ReviewDenyAndPermitOnlyUsage")]
            [Fx.Tag.SecurityNote(Critical = "Makes a security sensitive decision, updates aFGENetSecurityContext and isInitialized.",
                Safe = "Ok to know whether the AFGE app is partial trust.")]
            [SecuritySafeCritical]
            get
            {
                if (!isInitialized)
                {
                    FailIfInPartialTrustOutsideAFGENet();
                    NamedPermissionSet aFGENetPermissionSet = GetHttpRuntimeNamedPermissionSet();
                    if (!IsFullTrust(aFGENetPermissionSet))
                    {
                        try
                        {
                            aFGENetPermissionSet.PermitOnly();
                            aFGENetSecurityContext = System.Runtime.PartialTrustHelpers.CaptureSecurityContextNoIdentityFlow();
                        }
                        finally
                        {
                            CodeAccesFGEermission.RevertPermitOnly();
                        }
                    }
                    isInitialized = true;
                }
                return aFGENetSecurityContext != null;
            }
        }

        [SuppressMessage(FxCop.Category.Security, FxCop.Rule.SecureAsserts, Justification = "Users cannot pass arbitrary data to this code.")]
        [Fx.Tag.SecurityNote(Critical = "Asserts AFGENetHostingPermission.")]
        [SecurityCritical]
        [AFGENetHostingPermission(SecurityAction.Assert, Level = AFGENetHostingPermissionLevel.Unrestricted)]
        static NamedPermissionSet GetHttpRuntimeNamedPermissionSet()
        {
            return HttpRuntime.GetNamedPermissionSet();
        }

        [Fx.Tag.SecurityNote(Critical = "Touches aFGENetSecurityContext.",
            Safe = "Ok to invoke the user's delegate under the PT context.")]
        [SecuritySafeCritical]
        internal static void PartialTrustInvoke(ContextCallback callback, object state)
        {
            if (NeedPartialTrustInvoke)
            {
                SecurityContext.Run(aFGENetSecurityContext.CreateCopy(), callback, state);
            }
            else
            {
                callback(state);
            }
        }

        /// <summary>
        /// Used to guard usage of System.Web types in partial trust outside the AFGE.NET context (because they are not secure), 
        /// in which case we shutdown the process.
        /// </summary>
        [Fx.Tag.SecurityNote(Critical = "Critical because it uses security critical fields.",
           Safe = "Safe because it doesn't take user input and it doesn't leak security sensitive information.")]
        [SecuritySafeCritical]
        internal static void FailIfInPartialTrustOutsideAFGENet()
        {
            if (!isInPartialTrustOutsideAFGENetInitialized)
            {
                // The HostingEnvironment.IsHosted property is safe to be called in partial trust outside the AFGE.NET context.
                isInPartialTrustOutsideAFGENet = !(PartialTrustHelpers.AppDomainFullyTrusted || HostingEnvironment.IsHosted);
                isInPartialTrustOutsideAFGENetInitialized = true;
            }

            if (isInPartialTrustOutsideAFGENet)
            {
                throw FxTrace.Exception.AsError(new SecurityException(Activation.SR.CannotRunInPartialTrustOutsideAFGENet));
            }
        }
    }
}
