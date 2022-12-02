//------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.ServiceModel.Configuration
{
    using System.ServiceModel;

    public partial class BasicHttpsBindingCollectionElement : StandardBindingCollectionElement<BasicHttpsBinding, BasicHttpsBindingElement>
    {
        internal static BasicHttpsBindingCollectionElement GetBindingCollectionElement()
        {
            return (BasicHttpsBindingCollectionElement)ConfigurationHelpers.GetBindingCollectionElement(ConfigurationStrings.BasicHttpsBindingCollectionElementName);
        }
    }
}
