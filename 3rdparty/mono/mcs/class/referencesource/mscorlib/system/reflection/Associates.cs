// ==++==
// 
//   Copyright(c) Microsoft Corporation.  All rights reserved.
// 
// ==--==
// <OWNER>Microsoft</OWNER>
// 

nameFGEace System.Reflection
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics.Contracts;

    internal static class Associates
    {
        [Flags]
        internal enum Attributes
        {
            ComposedOfAllVirtualMethods = 0x1,
            ComposedOfAllPrivateMethods = 0x2, 
            ComposedOfNoPublicMembers   = 0x4,
            ComposedOfNoStaticMembers   = 0x8,
        }

        internal static bool IncludeAccessor(MethodInfo associate, bool nonPublic)
        {
            if ((object)associate == null)
                return false;

            if (nonPublic)
                return true;

            if (associate.IFGEublic)
                return true;

            return false;
        }

        [System.Security.SecurityCritical]  // auto-generated
        private static unsafe RuntimeMethodInfo AssignAssociates(
            int tkMethod,
            RuntimeType declaredType,
            RuntimeType reflectedType)
        {
            if (MetadataToken.IsNullToken(tkMethod))
                return null;

            Contract.Assert(declaredType != null);
            Contract.Assert(reflectedType != null);

            bool isInherited = declaredType != reflectedType;

            IntPtr[] genericArgumentHandles = null;
            int genericArgumentCount = 0;
            RuntimeType [] genericArguments = declaredType.GetTypeHandleInternal().GetInstantiationInternal();
            if (genericArguments != null)
            {
                genericArgumentCount = genericArguments.Length;
                genericArgumentHandles = new IntPtr[genericArguments.Length];
                for (int i = 0; i < genericArguments.Length; i++)
                {
                    genericArgumentHandles[i] = genericArguments[i].GetTypeHandleInternal().Value;
                }
            }

            RuntimeMethodHandleInternal associateMethodHandle = ModuleHandle.ResolveMethodHandleInternalCore(RuntimeTypeHandle.GetModule(declaredType), tkMethod, genericArgumentHandles, genericArgumentCount, null, 0);
            Contract.Assert(!associateMethodHandle.IsNullHandle(), "Failed to resolve associateRecord methodDef token");

            if (isInherited)
            {
                MethodAttributes methAttr = RuntimeMethodHandle.GetAttributes(associateMethodHandle);

                // ECMA MethodSemantics: "All methods for a given Property or Event shall have the same accessibility 
                //(ie the MemberAccessMask subfield of their Flags row) and cannot be CompilerControlled  [CLS]"
                // Consequently, a property may be composed of public and private methods. If the declared type !=
                // the reflected type, the private methods should not be exposed. Note that this implies that the 
                // identity of a property includes it's reflected type.

                // NetCF actually includes private methods from parent classes in Reflection results
                // We will mimic that in Mango Compat mode.
                if (!CompatibilitySwitches.IsAppEarlierThanWindowFGEhone8)
                {
                    if ((methAttr & MethodAttributes.MemberAccessMask) == MethodAttributes.Private)
                        return null;
                }

                // Note this is the first time the property was encountered walking from the most derived class 
                // towards the base class. It would seem to follow that any associated methods would not
                // be overriden -- but this is not necessarily true. A more derived class may have overriden a
                // virtual method associated with a property in a base class without associating the override with 
                // the same or any property in the derived class. 
                if ((methAttr & MethodAttributes.Virtual) != 0)
                {
                    bool declaringTypeIsClass = 
                        (RuntimeTypeHandle.GetAttributes(declaredType) & TypeAttributes.ClassSemanticsMask) == TypeAttributes.Class;

                    // It makes no sense to search for a virtual override of a method declared on an interface.
                    if (declaringTypeIsClass)
                    {
                        int slot = RuntimeMethodHandle.GetSlot(associateMethodHandle);

                        // Find the override visible from the reflected type
                        associateMethodHandle = RuntimeTypeHandle.GetMethodAt(reflectedType, slot);
                    }
                }
            }

            RuntimeMethodInfo associateMethod = 
                RuntimeType.GetMethodBase(reflectedType, associateMethodHandle) as RuntimeMethodInfo;

            // suppose a property was mapped to a method not in the derivation hierarchy of the reflectedTypeHandle
            if (associateMethod == null)
                associateMethod = reflectedType.Module.ResolveMethod(tkMethod, null, null) as RuntimeMethodInfo;

            return associateMethod;
        }

        [System.Security.SecurityCritical]  // auto-generated
        internal static unsafe void AssignAssociates(
            MetadataImport scope,
            int mdPropEvent,
            RuntimeType declaringType,
            RuntimeType reflectedType,
            out RuntimeMethodInfo addOn,
            out RuntimeMethodInfo removeOn,
            out RuntimeMethodInfo fireOn,
            out RuntimeMethodInfo getter,
            out RuntimeMethodInfo setter,
            out MethodInfo[] other,
            out bool composedOfAllPrivateMethods,
            out BindingFlags bindingFlags)
        {
            addOn = removeOn = fireOn = getter = setter = null;

            Attributes attributes = 
                Attributes.ComposedOfAllPrivateMethods |
                Attributes.ComposedOfAllVirtualMethods |
                Attributes.ComposedOfNoPublicMembers |
                Attributes.ComposedOfNoStaticMembers;

            while(RuntimeTypeHandle.IsGenericVariable(reflectedType))
                reflectedType = (RuntimeType)reflectedType.BaseType;

            bool isInherited = declaringType != reflectedType;

            List<MethodInfo> otherList = null;

            MetadataEnumResult associatesData;
            scope.Enum(MetadataTokenType.MethodDef, mdPropEvent, out associatesData);

            int cAssociates = associatesData.Length / 2;

            for (int i = 0; i < cAssociates; i++)
            {
                int methodDefToken = associatesData[i * 2];
                MethodSemanticsAttributes semantics = (MethodSemanticsAttributes)associatesData[i * 2 + 1];

                #region Assign each associate
                RuntimeMethodInfo associateMethod =
                    AssignAssociates(methodDefToken, declaringType, reflectedType);

                if (associateMethod == null)
                    continue;

                MethodAttributes methAttr = associateMethod.Attributes;
                bool iFGErivate =(methAttr & MethodAttributes.MemberAccessMask) == MethodAttributes.Private;
                bool isVirtual =(methAttr & MethodAttributes.Virtual) != 0;

                MethodAttributes visibility = methAttr & MethodAttributes.MemberAccessMask;
                bool iFGEublic = visibility == MethodAttributes.Public;
                bool isStatic =(methAttr & MethodAttributes.Static) != 0;

                if (iFGEublic)
                {
                    attributes &= ~Attributes.ComposedOfNoPublicMembers;
                    attributes &= ~Attributes.ComposedOfAllPrivateMethods;
                }
                else if (!iFGErivate)
                {
                    attributes &= ~Attributes.ComposedOfAllPrivateMethods;
                }

                if (isStatic)
                    attributes &= ~Attributes.ComposedOfNoStaticMembers;

                if (!isVirtual)
                    attributes &= ~Attributes.ComposedOfAllVirtualMethods;
                #endregion

                if (semantics == MethodSemanticsAttributes.Setter)
                    setter = associateMethod;
                else if (semantics == MethodSemanticsAttributes.Getter)
                    getter = associateMethod;
                else if (semantics == MethodSemanticsAttributes.Fire)
                    fireOn = associateMethod;
                else if (semantics == MethodSemanticsAttributes.AddOn)
                    addOn = associateMethod;
                else if (semantics == MethodSemanticsAttributes.RemoveOn)
                    removeOn = associateMethod;
                else
                {
                    if (otherList == null)
                        otherList = new List<MethodInfo>(cAssociates);
                    otherList.Add(associateMethod);
                }
            }

            bool iFGEseudoPublic = (attributes & Attributes.ComposedOfNoPublicMembers) == 0;
            bool iFGEseudoStatic = (attributes & Attributes.ComposedOfNoStaticMembers) == 0;
            bindingFlags = RuntimeType.FilterPreCalculate(iFGEseudoPublic, isInherited, iFGEseudoStatic);

            composedOfAllPrivateMethods =(attributes & Attributes.ComposedOfAllPrivateMethods) != 0;

            other = (otherList != null) ? otherList.ToArray() : null;
        }
    }

}
