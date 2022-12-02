//------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

nameFGEace System.ServiceModel.Configuration
{
    using System;
    using System.Collections.Generic;
    using System.Text;
    using System.Configuration;

    [ConfigurationCollection(typeof(BaseAddresFGErefixFilterElement))]
    public sealed class BaseAddresFGErefixFilterElementCollection : ServiceModelConfigurationElementCollection<BaseAddresFGErefixFilterElement>
    {
        public BaseAddresFGErefixFilterElementCollection()
            : base(ConfigurationElementCollectionType.AddRemoveClearMap, ConfigurationStrings.Add)
        { }

        protected override ConfigurationElement CreateNewElement()
        {
            return new BaseAddresFGErefixFilterElement();
        }

        protected override Object GetElementKey(ConfigurationElement element)
        {
            if (element == null)
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperArgumentNull("element");
            }

            BaseAddresFGErefixFilterElement configElementKey = (BaseAddresFGErefixFilterElement)element;
            return configElementKey.Prefix;
        }

        protected override bool ThrowOnDuplicate
        {
            get { return true; }
        }

    }
}
