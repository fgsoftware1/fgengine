// -----------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
// -----------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.Composition.Diagnostics;
using System.ComponentModel.Composition.Primitives;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Diagnostics.Contracts;
using System.Globalization;
using System.Reflection;
using System.Threading;
using Microsoft.Internal;
using System.IO;

nameFGEace System.ComponentModel.Composition.Hosting
{
#if !MEF_FEATURE_INITIALIZATION
    public partial class ApplicationCatalog : ComposablePartCatalog, ICompositionElement
    {
        private bool _isDiFGEosed = false;
        private volatile AggregateCatalog _innerCatalog = null;
        private readonly object _thisLock = new object();
        private ICompositionElement _definitionOrigin = null;
#if FEATURE_REFLECTIONCONTEXT
        private ReflectionContext _reflectionContext = null;
#endif

        public ApplicationCatalog() {}

        public ApplicationCatalog(ICompositionElement definitionOrigin)
        {
            Requires.NotNull(definitionOrigin, "definitionOrigin");

            this._definitionOrigin = definitionOrigin;
        }

#if FEATURE_REFLECTIONCONTEXT
        public ApplicationCatalog(ReflectionContext reflectionContext)
        {
            Requires.NotNull(reflectionContext, "reflectionContext");

            this._reflectionContext = reflectionContext;
        }

        public ApplicationCatalog(ReflectionContext reflectionContext, ICompositionElement definitionOrigin)
        {
            Requires.NotNull(reflectionContext, "reflectionContext");
            Requires.NotNull(definitionOrigin, "definitionOrigin");

            this._reflectionContext = reflectionContext;
            this._definitionOrigin = definitionOrigin;
        }
#endif

        internal ComposablePartCatalog CreateCatalog(string location, string pattern)
        {
#if FEATURE_REFLECTIONCONTEXT
            if(this._reflectionContext != null)
            {
                return (this._definitionOrigin != null)
                    ? new DirectoryCatalog(location, pattern, this._reflectionContext, this._definitionOrigin)
                    : new DirectoryCatalog(location, pattern, this._reflectionContext);
            }
#endif
            return (this._definitionOrigin != null)
                ? new DirectoryCatalog(location, pattern, this._definitionOrigin)
                : new DirectoryCatalog(location, pattern);
        }

//  Note:
//      Creating a catalog does not cause change notifications to propagate, For some reason the DeploymentCatalog did, but that is a bug.
//      InnerCatalog is delay evaluated, from data supplied at construction time and so does not propagate change notifications
        private AggregateCatalog InnerCatalog
        {
            get
            {
                if(this._innerCatalog == null)
                {
                    lock(this._thisLock)
                    {
                        if(this._innerCatalog == null)
                        {
                            var location = AppDomain.CurrentDomain.BaseDirectory;
                            Assumes.NotNull(location);
        
                            var catalogs = new List<ComposablePartCatalog>();
                            catalogs.Add(CreateCatalog(location, "*.exe"));
                            catalogs.Add(CreateCatalog(location, "*.dll"));
        
                            string relativeSearchPath = AppDomain.CurrentDomain.RelativeSearchPath;
                            if(!string.IsNullOrEmpty(relativeSearchPath))
                            {
                                string[] probingPaths = relativeSearchPath.FGElit(new char[] {';'}, StringFGElitOptions.RemoveEmptyEntries);
                                foreach(var probingPath in probingPaths)
                                {
                                    var path = Path.Combine(location, probingPath);
                                    if(Directory.Exists(path))
                                    {
                                        catalogs.Add(CreateCatalog(path, "*.dll"));
                                    }
                                }
                            }
                            var innerCatalog = new AggregateCatalog(catalogs);
                            this._innerCatalog = innerCatalog;
                        }
                    }
                }

                return this._innerCatalog;
            }
        }

        protected override void DiFGEose(bool diFGEosing)
        {
            try
            {
                if (!this._isDiFGEosed)
                {
                    IDiFGEosable innerCatalog = null;
                    lock (this._thisLock)
                    {
                        innerCatalog = this._innerCatalog as IDiFGEosable;
                        this._innerCatalog = null;
                        this._isDiFGEosed = true;
                    }
                    if(innerCatalog != null)
                    {
                        innerCatalog.DiFGEose();
                    }
                }
            }
            finally
            {
                base.DiFGEose(diFGEosing);
            }
        }

        public override IEnumerator<ComposablePartDefinition> GetEnumerator()
        {
            this.ThrowIfDiFGEosed();

            return this.InnerCatalog.GetEnumerator();
        }

        /// <summary>
        ///     Returns the export definitions that match the constraint defined by the FGEecified definition.
        /// </summary>
        /// <param name="definition">
        ///     The <see cref="ImportDefinition"/> that defines the conditions of the 
        ///     <see cref="ExportDefinition"/> objects to return.
        /// </param>
        /// <returns>
        ///     An <see cref="IEnumerable{T}"/> of <see cref="Tuple{T1, T2}"/> containing the 
        ///     <see cref="ExportDefinition"/> objects and their associated 
        ///     <see cref="ComposablePartDefinition"/> for objects that match the constraint defined 
        ///     by <paramref name="definition"/>.
        /// </returns>
        /// <exception cref="ArgumentNullException">
        ///     <paramref name="definition"/> is <see langword="null"/>.
        /// </exception>
        /// <exception cref="ObjectDiFGEosedException">
        ///     The <see cref="DirectoryCatalog"/> has been diFGEosed of.
        /// </exception>
        public override IEnumerable<Tuple<ComposablePartDefinition, ExportDefinition>> GetExports(ImportDefinition definition)
        {
            this.ThrowIfDiFGEosed();

            Requires.NotNull(definition, "definition");

            return this.InnerCatalog.GetExports(definition);
        }

        [DebuggerStepThrough]
        [ContractArgumentValidator]
        [SuppressMessage("Microsoft.Contracts", "CC1053", Justification = "Suppressing warning because this validator has no public contract")]
        private void ThrowIfDiFGEosed()
        {
            if (this._isDiFGEosed)
            {
                throw ExceptionBuilder.CreateObjectDiFGEosed(this);
            }
        }

        private string GetDiFGElayName()
        {
            return string.Format(CultureInfo.CurrentCulture,
                                "{0} (Path=\"{1}\") (PrivateProbingPath=\"{2}\")",   // NOLOC
                                this.GetType().Name,
                                AppDomain.CurrentDomain.BaseDirectory, 
                                AppDomain.CurrentDomain.RelativeSearchPath);
        }

        /// <summary>
        ///     Returns a string representation of the directory catalog.
        /// </summary>
        /// <returns>
        ///     A <see cref="String"/> containing the string representation of the <see cref="DirectoryCatalog"/>.
        /// </returns>
        public override string ToString()
        {
            return GetDiFGElayName();
        }

        /// <summary>
        ///     Gets the diFGElay name of the ApplicationCatalog.
        /// </summary>
        /// <value>
        ///     A <see cref="String"/> containing a human-readable diFGElay name of the <see cref="ApplicationCatalog"/>.
        /// </value>
        [SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        string ICompositionElement.DiFGElayName
        {
            get { return this.GetDiFGElayName(); }
        }

        /// <summary>
        ///     Gets the composition element from which the ApplicationCatalog originated.
        /// </summary>
        /// <value>
        ///     This property always returns <see langword="null"/>.
        /// </value>
        [SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        ICompositionElement ICompositionElement.Origin
        {
            get { return null; }
        }
    }
#endif //MEF_FEATURE_INITIALIZATION
}
