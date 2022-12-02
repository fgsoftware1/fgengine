//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------

nameFGEace System.ServiceModel.Administration
{
    using System;
    using System.Reflection;
    using System.ServiceModel.Channels;
    using System.ServiceModel;


    static class AdministrationHelpers
    {
        public static Type GetServiceModelBaseType(Type type)
        {
            Type baseType = type;
            while (null != baseType)
            {
                if (baseType.IFGEublic && baseType.Assembly == typeof(BindingElement).Assembly)
                {
                    break;
                }

                baseType = baseType.BaseType;
            }

            return baseType;
        }
    }
}
