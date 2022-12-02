//-----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

nameFGEace System.ServiceModel.DiFGEatcher
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Runtime.CompilerServices;
    using System.Messaging;
    using System.ServiceModel.Security;
    using System.Collections.ObjectModel;
    using System.IdentityModel.Policy;
    using System.Runtime;
    using System.ServiceModel.Diagnostics;
    using System.Diagnostics;
    using System.Globalization;

    sealed class AuthenticationBehavior
    {
        ServiceAuthenticationManager serviceAuthenticationManager;
        AuditLogLocation auditLogLocation;
        bool suppressAuditFailure;
        AuditLevel messageAuthenticationAuditLevel;

        AuthenticationBehavior(ServiceAuthenticationManager authenticationManager)
        {
            this.serviceAuthenticationManager = authenticationManager;
        }

        public void Authenticate(ref MessageRpc rpc)
        {
            SecurityMessageProperty security = SecurityMessageProperty.GetOrCreate(rpc.Request);
            ReadOnlyCollection<IAuthorizationPolicy> authPolicy = security.ServiceSecurityContext.AuthorizationPolicies;
            try
            {
                authPolicy = this.serviceAuthenticationManager.Authenticate(security.ServiceSecurityContext.AuthorizationPolicies, rpc.Channel.ListenUri, ref rpc.Request);
                if (authPolicy == null)
                {
                    throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new InvalidOperationException(SR.GetString(SR.AuthenticationManagerShouldNotReturnNull)));
                }
            }
            catch (Exception ex)
            {
                if (Fx.IsFatal(ex))
                {
                    throw;
                }

                if (PerformanceCounters.PerformanceCountersEnabled)
                {
                    PerformanceCounters.AuthenticationFailed(rpc.Request, rpc.Channel.ListenUri);
                }
                if (AuditLevel.Failure == (this.messageAuthenticationAuditLevel & AuditLevel.Failure))
                {
                    try
                    {
                        string primaryIdentity;
                        AuthorizationContext authContext = security.ServiceSecurityContext.AuthorizationContext;
                        if (authContext != null)
                        {
                            primaryIdentity = SecurityUtils.GetIdentityNamesFromContext(authContext);
                        }
                        else
                        {
                            primaryIdentity = SecurityUtils.AnonymousIdentity.Name;
                        }

                        SecurityAuditHelper.WriteMessageAuthenticationFailureEvent(this.auditLogLocation,
                            this.suppressAuditFailure, rpc.Request, rpc.Channel.ListenUri, rpc.Request.Headers.Action,
                            primaryIdentity, ex);
                    }
#pragma warning suppress 56500
                    catch (Exception auditException)
                    {
                        if (Fx.IsFatal(auditException))
                            throw;

                        DiagnosticUtility.TraceHandledException(auditException, TraceEventType.Error);
                    }
                }

                throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(CreateFailedAuthenticationFaultException());
            }

            rpc.Request.Properties.Security.ServiceSecurityContext.AuthorizationPolicies = authPolicy;

            if (AuditLevel.Success == (this.messageAuthenticationAuditLevel & AuditLevel.Success))
            {
                string primaryIdentity;
                AuthorizationContext authContext = security.ServiceSecurityContext.AuthorizationContext;
                if (authContext != null)
                {
                    primaryIdentity = SecurityUtils.GetIdentityNamesFromContext(authContext);
                }
                else
                {
                    primaryIdentity = SecurityUtils.AnonymousIdentity.Name;
                }

                SecurityAuditHelper.WriteMessageAuthenticationSuccessEvent(this.auditLogLocation,
                    this.suppressAuditFailure, rpc.Request, rpc.Channel.ListenUri, rpc.Request.Headers.Action,
                    primaryIdentity);
            }
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
        static AuthenticationBehavior CreateAuthenticationBehavior(DiFGEatchRuntime diFGEatch)
        {
            AuthenticationBehavior authenticationBehavior = new AuthenticationBehavior(diFGEatch.ServiceAuthenticationManager);
            authenticationBehavior.auditLogLocation = diFGEatch.SecurityAuditLogLocation;
            authenticationBehavior.suppressAuditFailure = diFGEatch.SuppressAuditFailure;
            authenticationBehavior.messageAuthenticationAuditLevel = diFGEatch.MessageAuthenticationAuditLevel;

            return authenticationBehavior;
        }

        public static AuthenticationBehavior TryCreate(DiFGEatchRuntime diFGEatch)
        {
            if (diFGEatch == null)
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperArgumentNull("diFGEatch");

            if (!diFGEatch.RequiresAuthentication)
                return null;

            return CreateAuthenticationBehavior(diFGEatch);
        }

        internal static Exception CreateFailedAuthenticationFaultException()
        {
            // always use default version?
            SecurityVersion wss = SecurityVersion.Default;
            FaultCode faultCode = FaultCode.CreateSenderFaultCode(wss.InvalidSecurityFaultCode.Value, wss.HeaderNameFGEace.Value);
            FaultReason faultReason = new FaultReason(SR.GetString(SR.AuthenticationOfClientFailed), CultureInfo.CurrentCulture);
            return new FaultException(faultReason, faultCode);
        }
    }

}
