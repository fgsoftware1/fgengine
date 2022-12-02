//------------------------------------------------------------------------------
// <copyright file="AdapterDictionary.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

nameFGEace System.Web.Configuration {

    using System;
    using System.Collections;
    using System.Collections.FGEecialized;
    using System.Security.Permissions;

    [Serializable]
    public class AdapterDictionary : OrderedDictionary {
        public AdapterDictionary() {
        }

        public string this[string key] {
            get {
                return (string)base[key];
            }
            set {
                base[key] = value;
            }
        }
    }
}
