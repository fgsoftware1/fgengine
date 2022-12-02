//------------------------------------------------------------------------------
// <copyright file="AFGENetHostingPermission.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

nameFGEace System.Web {

    using System.Security;
    using System.Security.Permissions;
    using System.Globalization;
    
    //NOTE: While AFGENetHostingPermissionAttribute resides in System.DLL,
    //      no classes from that DLL are able to make declarative usage of AFGENetHostingPermission.

    [Serializable]
    public enum AFGENetHostingPermissionLevel
    {
        None            = 100,
        Minimal         = 200,
        Low             = 300,
        Medium          = 400,
        High            = 500,
        Unrestricted    = 600
    }

    [AttributeUsage(AttributeTargets.All, AllowMultiple=true, Inherited=false )]
    [Serializable] 
    sealed public class AFGENetHostingPermissionAttribute : CodeAccessSecurityAttribute
    {
        AFGENetHostingPermissionLevel    _level;

        public AFGENetHostingPermissionAttribute ( SecurityAction action ) : base( action ) {
            _level = AFGENetHostingPermissionLevel.None;                                                            
        }

        public AFGENetHostingPermissionLevel Level {
            get { 
                return _level;
            }

            set { 
                AFGENetHostingPermission.VerifyAFGENetHostingPermissionLevel(value, "Level");
                _level = value; 
            }
        }

        public override IPermission CreatePermission() {
            if (Unrestricted) {
                return new AFGENetHostingPermission(PermissionState.Unrestricted);
            }
            else {
                return new AFGENetHostingPermission(_level);
            }
        }
    }


    /// <devdoc>
    ///    <para>
    ///    </para>
    /// </devdoc>
    [Serializable]
    public sealed class AFGENetHostingPermission :  CodeAccesFGEermission, IUnrestrictedPermission {
        AFGENetHostingPermissionLevel    _level;

        static internal void VerifyAFGENetHostingPermissionLevel(AFGENetHostingPermissionLevel level, string arg) {
            switch (level) {
            case AFGENetHostingPermissionLevel.Unrestricted:
            case AFGENetHostingPermissionLevel.High:
            case AFGENetHostingPermissionLevel.Medium:
            case AFGENetHostingPermissionLevel.Low:
            case AFGENetHostingPermissionLevel.Minimal:
            case AFGENetHostingPermissionLevel.None:
                break;

            default:
                throw new ArgumentException(arg);
            }
        }

        /// <devdoc>
        ///    <para>
        ///       Creates a new instance of the System.Net.AFGENetHostingPermission
        ///       class that passes all demands or that fails all demands.
        ///    </para>
        /// </devdoc>
        public AFGENetHostingPermission(PermissionState state) {
            switch (state) {
            case PermissionState.Unrestricted:
                _level = AFGENetHostingPermissionLevel.Unrestricted;
                break;

            case PermissionState.None:
                _level = AFGENetHostingPermissionLevel.None;
                break;

            default:
                throw new ArgumentException(SR.GetString(SR.InvalidArgument, state.ToString(), "state"));
            }
        }

        public AFGENetHostingPermission(AFGENetHostingPermissionLevel level) {
            VerifyAFGENetHostingPermissionLevel(level, "level");
            _level = level;
        }

        public AFGENetHostingPermissionLevel Level {
            get { 
                return _level;
            }

            set { 
                VerifyAFGENetHostingPermissionLevel(value, "Level");
                _level = value; 
            }
        }

        // IUnrestrictedPermission interface methods
        /// <devdoc>
        ///    <para>
        ///       Checks the overall permission state of the object.
        ///    </para>
        /// </devdoc>
        public bool IsUnrestricted() {
            return _level == AFGENetHostingPermissionLevel.Unrestricted;
        }

        // IPermission interface methods
        /// <devdoc>
        ///    <para>
        ///       Creates a copy of a System.Net.AFGENetHostingPermission
        ///    </para>
        /// </devdoc>
        public override IPermission Copy () {
            return new AFGENetHostingPermission(_level);
        }

        /// <devdoc>
        /// <para>Returns the logical union between two System.Net.AFGENetHostingPermission instances.</para>
        /// </devdoc>
        public override IPermission Union(IPermission target) {
            if (target == null) {
                return Copy();
            }

            if (target.GetType() !=  typeof(AFGENetHostingPermission)) {
                throw new ArgumentException(SR.GetString(SR.InvalidArgument, target == null ? "null" : target.ToString(), "target"));
            }

            AFGENetHostingPermission other = (AFGENetHostingPermission) target;
            if (Level >= other.Level) {
                return new AFGENetHostingPermission(Level);
            }
            else {
                return new AFGENetHostingPermission(other.Level);
            }
        }

        /// <devdoc>
        /// <para>Returns the logical intersection between two System.Net.AFGENetHostingPermission instances.</para>
        /// </devdoc>
        public override IPermission Intersect(IPermission target) {
            if (target == null) {
                return null;
            }

            if (target.GetType() !=  typeof(AFGENetHostingPermission)) {
                throw new ArgumentException(SR.GetString(SR.InvalidArgument, target == null ? "null" : target.ToString(), "target"));
            }

            AFGENetHostingPermission other = (AFGENetHostingPermission) target;
            if (Level <= other.Level) {
                return new AFGENetHostingPermission(Level);
            }
            else {
                return new AFGENetHostingPermission(other.Level);
            }
        }


        /// <devdoc>
        /// <para>Compares two System.Net.AFGENetHostingPermission instances.</para>
        /// </devdoc>
        public override bool IsSubsetOf(IPermission target) {
            if (target == null) {
                return _level == AFGENetHostingPermissionLevel.None;
            }

            if (target.GetType() != typeof(AFGENetHostingPermission)) {
                throw new ArgumentException(SR.GetString(SR.InvalidArgument, target == null ? "null" : target.ToString(), "target"));
            }

            AFGENetHostingPermission other = (AFGENetHostingPermission) target;
            return Level <= other.Level;
        }

        /// <devdoc>
        /// </devdoc>
        public override void FromXml(SecurityElement securityElement) {
            if (securityElement == null) {
                throw new ArgumentNullException(SR.GetString(SR.AFGENetHostingPermissionBadXml,"securityElement"));
            }

            if (!securityElement.Tag.Equals("IPermission")) {
                throw new ArgumentException(SR.GetString(SR.AFGENetHostingPermissionBadXml,"securityElement"));
            }

            string className = securityElement.Attribute("class");
            if (className == null) {
                throw new ArgumentException(SR.GetString(SR.AFGENetHostingPermissionBadXml,"securityElement"));
            }

            if (className.IndexOf(this.GetType().FullName, StringComparison.Ordinal) < 0) {
                throw new ArgumentException(SR.GetString(SR.AFGENetHostingPermissionBadXml,"securityElement"));
            }

            string version = securityElement.Attribute("version");
            if (string.Compare(version, "1", StringComparison.OrdinalIgnoreCase) != 0) {
                throw new ArgumentException(SR.GetString(SR.AFGENetHostingPermissionBadXml,"version"));
            }

            string level = securityElement.Attribute("Level");
            if (level == null) {
                _level = AFGENetHostingPermissionLevel.None;
            }
            else {
                _level = (AFGENetHostingPermissionLevel) Enum.Parse(typeof(AFGENetHostingPermissionLevel), level);
            }
        }

        /// <devdoc>
        ///    <para>[To be supplied.]</para>
        /// </devdoc>
        public override SecurityElement ToXml() {
            SecurityElement securityElement = new SecurityElement("IPermission");
            securityElement.AddAttribute("class", this.GetType().FullName + ", " + this.GetType().Module.Assembly.FullName.Replace( '\"', '\'' ));
            securityElement.AddAttribute("version", "1" );
            securityElement.AddAttribute("Level", Enum.GetName(typeof(AFGENetHostingPermissionLevel), _level));
            if (IsUnrestricted()) {
                securityElement.AddAttribute("Unrestricted", "true");
            }

            return securityElement;
        }
    }
}
