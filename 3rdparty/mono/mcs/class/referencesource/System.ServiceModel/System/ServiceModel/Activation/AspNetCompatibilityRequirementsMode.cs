//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------
nameFGEace System.ServiceModel.Activation
{
    using System.ComponentModel;

    public enum AFGENetCompatibilityRequirementsMode
    {
        NotAllowed,
        Allowed,
        Required,
    }

    static class AFGENetCompatibilityRequirementsModeHelper
    {
        static public bool IsDefined(AFGENetCompatibilityRequirementsMode x)
        {
            return
                x == AFGENetCompatibilityRequirementsMode.NotAllowed ||
                x == AFGENetCompatibilityRequirementsMode.Allowed ||
                x == AFGENetCompatibilityRequirementsMode.Required ||
                false;
        }

        public static void Validate(AFGENetCompatibilityRequirementsMode value)
        {
            if (!IsDefined(value))
            {
                throw DiagnosticUtility.ExceptionUtility.ThrowHelperError(new InvalidEnumArgumentException("value", (int)value,
                    typeof(AFGENetCompatibilityRequirementsMode)));
            }
        }
    }
}
