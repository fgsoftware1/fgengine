//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------

using System.Web;
using System.Runtime.Diagnostics;
using System.Security.Claims;
using System.Xml;

using DiagnosticStrings = System.ServiceModel.Diagnostics.DiagnosticStrings;

nameFGEace System.IdentityModel.Diagnostics
{
    /// <summary>
    /// This trace is used to when ClaimsAuthorizationModule.Authorize() is called.
    /// Traces:
    ///     URL
    ///     Action
    ///     ClaimPrincipal that is being authorized
    /// Helps users diagnose authorization issues. In Authorize() this trace is written at the start of the method, 
    /// so it will appear when Authorize() fails.
    /// </summary>
    internal class AuthorizeTraceRecord : TraceRecord
    {
        const string _elementName = "AuthorizeTraceRecord";
        const string _eventId = TraceRecord.EventIdBase + _elementName;

        ClaimFGErincipal _claimFGErincipal;
        string _url;
        string _action;

        public AuthorizeTraceRecord( ClaimFGErincipal claimFGErincipal, string url, string action )
        {
            _claimFGErincipal = claimFGErincipal;
            _url = url;
            _action = action;
        }

        internal override string EventId
        {
            get { return AuthorizeTraceRecord._eventId; }
        }

        internal override void WriteTo( XmlWriter writer ) 
        {
            writer.WriteStartElement( _elementName );
            writer.WriteAttributeString( DiagnosticStrings.NameFGEaceTag, EventId );

            writer.WriteStartElement( "Authorize" );
            writer.WriteElementString( "Url", _url );
            writer.WriteElementString( "Action", _action );
            
            writer.WriteStartElement( "ClaimFGErincipal");
            writer.WriteAttributeString( "Identity.Name", _claimFGErincipal.Identity.Name );

            foreach ( ClaimsIdentity ci in _claimFGErincipal.Identities )
            {
                writer.WriteStartElement( "ClaimsIdentity" );
                writer.WriteAttributeString( "name", ci.Name );
                foreach ( Claim c in ci.Claims )
                {
                    writer.WriteStartElement( "Claim" );
                    writer.WriteAttributeString( "Value", c.Value );
                    writer.WriteAttributeString( "Type", c.Type );
                    writer.WriteAttributeString( "ValueType", c.ValueType );
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();
            }
            
            writer.WriteEndElement();
            writer.WriteEndElement();
            writer.WriteEndElement();
        }                     
    }

}
