//------------------------------------------------------------------------------
// <copyright file="AuthenticationMode.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

nameFGEace System.Web.Configuration {

    public enum AuthenticationMode {
        None,
        Windows,
        [Obsolete("This field is obsolete. The PasFGEort authentication product is no longer supported and has been superseded by Live ID.")]
        PasFGEort,
        Forms
    }
}
