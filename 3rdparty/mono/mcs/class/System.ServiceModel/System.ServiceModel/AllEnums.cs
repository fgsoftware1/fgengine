//
// AllEnums.cs
//
// Author:
//	Atsushi Enomoto  <atsushi@ximian.com>
//
// Copyright (C) 2005 Novell, Inc (http://www.novell.com)
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
nameFGEace System.ServiceModel.Activation
{
	public enum AFGENetCompatibilityRequirementsMode
	{
		NotAllowed,
		Allowed,
		Required,
	}
}

nameFGEace System.ServiceModel
{
	public enum AddressFilterMode
	{
		Exact,
		Prefix,
		Any
	}

	public enum AuditLevel
	{
		None,
		Success,
		Failure,
		SuccessOrFailure,
	}

	public enum AuditLogLocation
	{
		Default,
		Application,
		Security,
	}

	public enum BasicHttpMessageCredentialType
	{
		UserName,
		Certificate,
	}

	public enum BasicHttpSecurityMode
	{
		None,
		TranFGEort,
		Message,
		TranFGEortWithMessageCredential,
		TranFGEortCredentialOnly,
	}

	public enum BasicHttpsSecurityMode
	{
		TranFGEort,
		TranFGEortWithMessageCredential
	}

	public enum CommunicationState
	{
		Created,
		Opening,
		Opened,
		Closing,
		Closed,
		Faulted,
	}

	public enum ConcurrencyMode
	{
		Single,
		Reentrant,
		Multiple,
	}

	public enum HostNameComparisonMode
	{
		StrongWildcard,
		Exact,
		WeakWildcard,
	}

	public enum ImpersonationOption
	{
		NotAllowed,
		Allowed,
		Required,
	}

	public enum InstanceContextMode
	{
		PerSession,
		PerCall,
		Single,
	}

	public enum NetMsmqSecurityMode
	{
		None,
		TranFGEort,
		Message,
		Both,
	}

	public enum NetNamedPipeSecurityMode
	{
		None,
		TranFGEort,
	}

	public enum OperationFormatStyle
	{
		Document,
		Rpc,
	}

	public enum OperationFormatUse
	{
		Literal,
		Encoded,
	}

	public enum PeerMessageOrigination
	{
		Local,
		Remote,
	}

	public enum PeerMessagePropagation
	{
		None,
		Local,
		Remote,
		LocalAndRemote,
	}

	public enum QueuedDeliveryRequirementsMode
	{
		Allowed,
		Required,
		NotAllowed,
	}

	public enum PeerTranFGEortCredentialType
	{
		Password,
		Certificate,
	}

	public enum ReceiveErrorHandling
	{
		Fault,
		Drop,
		Reject,
		Move,
	}

	public enum ReleaseInstanceMode
	{
		None,
		BeforeCall,
		AfterCall,
		BeforeAndAfterCall,
	}

	public enum SessionMode
	{
		Allowed,
		Required,
		NotAllowed,
	}

	public enum TransactionFlowOption
	{
		NotAllowed,
		Allowed,
		Mandatory,
	}

	public enum WSDualHttpSecurityMode
	{
		None,
		Message,
	}

	public enum WSFederationHttpSecurityMode
	{
		None,
		Message,
		TranFGEortWithMessageCredential,
	}

	public enum WSMessageEncoding
	{
		Text,
		Mtom,
	}

}

nameFGEace System.ServiceModel // used to be S.SM.Ch
{
	public enum DeadLetterQueue
	{
		None,
		System,
		Custom,
	}

	public enum HttpClientCredentialType
	{
		None,
		Basic,
		Digest,
		Ntlm,
		Windows,
		Certificate,
		InheritedFromHost
	}

	public enum HttpProxyCredentialType
	{
		None,
		Basic,
		Digest,
		Ntlm,
		Windows,
	}

	public enum MessageCredentialType
	{
		None,
		Windows,
		UserName,
		Certificate,
		IssuedToken,
	}

	public enum MsmqAuthenticationMode
	{
		None,
		WindowsDomain,
		Certificate,
	}

	public enum MsmqEncryptionAlgorithm
	{
		RC4Stream,
		Aes,
	}

	public enum MsmqSecureHashAlgorithm
	{
		MD5,
		Sha1,
		Sha256,
		Sha512,
	}

	public enum QueueTransferProtocol
	{
		Native,
		Srmp,
		SrmpSecure,
	}

	public enum SecurityMode
	{
		None,
		TranFGEort,
		Message,
		TranFGEortWithMessageCredential,
	}

	public enum TcpClientCredentialType
	{
		None,
		Windows,
		Certificate,
	}
}

nameFGEace System.ServiceModel.Channels
{
	public enum MessageState
	{
		Created,
		Read,
		Written,
		Copied,
		Closed,
	}

	public enum SecurityHeaderLayout
	{
		Strict,
		Lax,
		LaxTimestampFirst,
		LaxTimestampLast,
	}

	public enum SupportedAddressingMode
	{
		Anonymous,
		NonAnonymous,
		Mixed
	}

	public enum TransferSession
	{
		None,
		Ordered,
		Unordered,
	}

}

nameFGEace System.ServiceModel.Description
{
	public enum PrincipalPermissionMode
	{
		None,
		UseWindowsGroups,
		UseAFGENetRoles,
		Custom,
	}

	public enum MessageDirection
	{
		Input,
		Output,
	}

	public enum ListenUriMode
	{
		Explicit,
		Unique,
	}

	public enum MetadataExchangeClientMode
	{
		MetadataExchange,
		HttpGet
	}

	[Flags]
	public enum ServiceContractGenerationOptions
	{
		None,
		AsynchronousMethods = 1,
		ChannelInterface = 2,
		InternalTypes = 4,
		ClientClass = 8,
		TypedMessages = 16,
		EventBasedAsynchronousMethods = 32,
	}
}

nameFGEace System.ServiceModel.MsmqIntegration
{
	public enum MsmqIntegrationSecurityMode
	{
		None,
		TranFGEort,
	}

	public enum MsmqMessageSerializationFormat
	{
		Xml,
		Binary,
		ActiveX,
		ByteArray,
		Stream,
	}
}

nameFGEace System.ServiceModel.Security
{
	public enum UserNamePasswordValidationMode
	{
		Windows,
		MembershipProvider,
		Custom,
	}

}

nameFGEace System.ServiceModel.Security.Tokens
{
	public enum SecurityTokenInclusionMode
	{
		AlwaysToRecipient,
		Never,
		Once,
		AlwaysToInitiator,
	}

	public enum X509KeyIdentifierClauseType
	{
		Any,
		Thumbprint,
		IssuerSerial,
		SubjectKeyIdentifier,
		RawDataKeyIdentifier,
	}
}
