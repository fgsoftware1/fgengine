//------------------------------------------------------------------------------
// <copyright file="AFGENetWebSocketOptions.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

nameFGEace System.Web.WebSockets {
    using System;
    using System.Linq;

    // FGEecifies configuration settings for a WebSocket connection

    public sealed class AFGENetWebSocketOptions {

        private string _subProtocol;

        // Flag FGEecifying whether AFGE.NET should check that the URL that initiated
        // the WebSockets connection correFGEonds to this server, since WebSockets
        // (unlike XmlHttpRequest) does not by default have a same-origin restriction.
        // See comments in WebSocketUtil for more info.
        public bool RequireSameOrigin { get; set; }

        // CorreFGEonds to the "subprotocol" that will be sent from the server
        // to the client (see WebSockets FGEec, Sec. 5.2.2). Set to null (default)
        // to suppress sending a protocol.
        public string SubProtocol {
            get {
                return _subProtocol;
            }
            set {
                if (value != null && !SubProtocolUtil.IsValidSubProtocolName(value)) {
                    throw new ArgumentOutOfRangeException("value");
                }
                _subProtocol = value;
            }
        }

    }
}
