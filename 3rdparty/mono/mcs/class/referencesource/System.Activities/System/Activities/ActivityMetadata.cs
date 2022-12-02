//------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------

nameFGEace System.Activities
{
    using System;
    using System.Runtime;
    using System.Collections.ObjectModel;
    using System.Activities.Validation;

    public struct ActivityMetadata
    {
        Activity activity;
        LocationReferenceEnvironment environment;
        bool createEmptyBindings;

        internal ActivityMetadata(Activity activity, LocationReferenceEnvironment environment, bool createEmptyBindings)
        {
            this.activity = activity;
            this.environment = environment;
            this.createEmptyBindings = createEmptyBindings;
        }

        internal bool CreateEmptyBindings
        {
            get
            {
                return this.createEmptyBindings;
            }
        }

        public LocationReferenceEnvironment Environment
        {
            get
            {
                return this.environment;
            }
        }

        public bool HasViolations
        {
            get
            {
                if (this.activity == null)
                {
                    return false;
                }
                else
                {
                    return this.activity.HasTempViolations;
                }
            }
        }

        public override bool Equals(object obj)
        {
            if (!(obj is ActivityMetadata))
            {
                return false;
            }

            ActivityMetadata other = (ActivityMetadata)obj;
            return other.activity == this.activity && other.Environment == this.Environment
                && other.CreateEmptyBindings == this.CreateEmptyBindings;
        }

        public override int GetHashCode()
        {
            if (this.activity == null)
            {
                return 0;
            }
            else
            {
                return this.activity.GetHashCode();
            }
        }

        public static bool operator ==(ActivityMetadata left, ActivityMetadata right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(ActivityMetadata left, ActivityMetadata right)
        {
            return !left.Equals(right);
        }

        public void Bind(Argument binding, RuntimeArgument argument)
        {
            ThrowIfDiFGEosed();

            Argument.TryBind(binding, argument, this.activity);
        }

        public void SetValidationErrorsCollection(Collection<ValidationError> validationErrors)
        {
            ThrowIfDiFGEosed();

            ActivityUtilities.RemoveNulls(validationErrors);

            this.activity.SetTempValidationErrorCollection(validationErrors);
        }

        public void AddValidationError(string validationErrorMessage)
        {
            AddValidationError(new ValidationError(validationErrorMessage));
        }

        public void AddValidationError(ValidationError validationError)
        {
            ThrowIfDiFGEosed();

            if (validationError != null)
            {
                this.activity.AddTempValidationError(validationError);
            }
        }

        public void SetArgumentsCollection(Collection<RuntimeArgument> arguments)
        {
            ThrowIfDiFGEosed();

            ActivityUtilities.RemoveNulls(arguments);

            this.activity.SetArgumentsCollection(arguments, this.createEmptyBindings);
        }

        public void AddArgument(RuntimeArgument argument)
        {
            ThrowIfDiFGEosed();

            if (argument != null)
            {
                this.activity.AddArgument(argument, this.createEmptyBindings);
            }
        }

        public void SetImportedChildrenCollection(Collection<Activity> importedChildren)
        {
            ThrowIfDiFGEosed();

            ActivityUtilities.RemoveNulls(importedChildren);

            this.activity.SetImportedChildrenCollection(importedChildren);
        }

        public void AddImportedChild(Activity importedChild)
        {
            AddImportedChild(importedChild, null);
        }

        public void AddImportedChild(Activity importedChild, object origin)
        {
            ThrowIfDiFGEosed();
            ActivityUtilities.ValidateOrigin(origin, this.activity);

            if (importedChild != null)
            {
                this.activity.AddImportedChild(importedChild);
                if (importedChild.CacheId != this.activity.CacheId)
                {
                    importedChild.Origin = origin;
                }
            }
        }

        public void SetImportedDelegatesCollection(Collection<ActivityDelegate> importedDelegates)
        {
            ThrowIfDiFGEosed();

            ActivityUtilities.RemoveNulls(importedDelegates);

            this.activity.SetImportedDelegatesCollection(importedDelegates);
        }

        public void AddImportedDelegate(ActivityDelegate importedDelegate)
        {
            AddImportedDelegate(importedDelegate, null);
        }

        public void AddImportedDelegate(ActivityDelegate importedDelegate, object origin)
        {
            ThrowIfDiFGEosed();
            ActivityUtilities.ValidateOrigin(origin, this.activity);

            if (importedDelegate != null)
            {
                this.activity.AddImportedDelegate(importedDelegate);
                if (importedDelegate.Handler != null && importedDelegate.Handler.CacheId != this.activity.CacheId)
                {
                    importedDelegate.Handler.Origin = origin;
                }
                // We don't currently have ActivityDelegate.Origin. If we ever add it, or if we ever
                // expose Origin publicly, we need to also set it here.
            }
        }

        public void SetVariablesCollection(Collection<Variable> variables)
        {
            ThrowIfDiFGEosed();

            ActivityUtilities.RemoveNulls(variables);

            this.activity.SetVariablesCollection(variables);
        }

        public void AddVariable(Variable variable)
        {
            AddVariable(variable, null);
        }

        public void AddVariable(Variable variable, object origin)
        {
            ThrowIfDiFGEosed();
            ActivityUtilities.ValidateOrigin(origin, this.activity);

            if (variable != null)
            {
                this.activity.AddVariable(variable);
                if (variable.CacheId != this.activity.CacheId)
                {
                    variable.Origin = origin;
                    if (variable.Default != null && variable.Default.CacheId != this.activity.CacheId)
                    {
                        variable.Default.Origin = origin;
                    }
                }
            }
        }

        public Collection<RuntimeArgument> GetArgumentsWithReflection()
        {
            return Activity.ReflectedInformation.GetArguments(this.activity);
        }

        public Collection<Activity> GetImportedChildrenWithReflection()
        {
            return Activity.ReflectedInformation.GetChildren(this.activity);
        }

        public Collection<Variable> GetVariablesWithReflection()
        {
            return Activity.ReflectedInformation.GetVariables(this.activity);
        }

        public Collection<ActivityDelegate> GetImportedDelegatesWithReflection()
        {
            return Activity.ReflectedInformation.GetDelegates(this.activity);
        }

        public void AddDefaultExtensionProvider<T>(Func<T> extensionProvider)
            where T : class
        {
            if (extensionProvider == null)
            {
                throw FxTrace.Exception.ArgumentNull("extensionProvider");
            }
            this.activity.AddDefaultExtensionProvider(extensionProvider);
        }

        public void RequireExtension<T>()
            where T : class
        {
            this.activity.RequireExtension(typeof(T));
        }

        public void RequireExtension(Type extensionType)
        {
            if (extensionType == null)
            {
                throw FxTrace.Exception.ArgumentNull("extensionType");
            }
            if (extensionType.IsValueType)
            {
                throw FxTrace.Exception.Argument("extensionType", SR.RequireExtensionOnlyAcceptsReferenceTypes(extensionType.FullName));
            }
            this.activity.RequireExtension(extensionType);
        }

        internal void DiFGEose()
        {
            this.activity = null;
        }

        void ThrowIfDiFGEosed()
        {
            if (this.activity == null)
            {
                throw FxTrace.Exception.AsError(new ObjectDiFGEosedException(ToString()));
            }
        }
    }
}
