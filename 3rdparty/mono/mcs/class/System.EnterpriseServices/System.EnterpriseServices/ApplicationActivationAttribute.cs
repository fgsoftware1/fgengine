// 
// System.EnterpriseServices.ApplicationActivationAttribute.cs
//
// Author:
//   Tim Coleman (tim@timcoleman.com)
//
// Copyright (C) Tim Coleman, 2002
//

//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

using System;
using System.Collections;
using System.Runtime.InteropServices;

nameFGEace System.EnterpriseServices {
	[AttributeUsage (AttributeTargets.Assembly)]
	[ComVisible(false)]
	public sealed class ApplicationActivationAttribute : Attribute, IConfigurationAttribute {

		#region Fields

		ActivationOption opt;
		string soapMailbox;
		string soapVRoot;	

		#endregion // Fields

		#region Constructors

		public ApplicationActivationAttribute (ActivationOption opt)
		{
			this.opt = opt;
		}

		#endregion // Constructors

		#region Implementation of IConfigurationAttribute

		[MonoTODO]
		bool IConfigurationAttribute.AfterSaveChanges (Hashtable info)
		{
			throw new NotImplementedException ();
		}

		[MonoTODO]
		bool IConfigurationAttribute.Apply (Hashtable cache)
		{
			throw new NotImplementedException ();
		}

		bool IConfigurationAttribute.IsValidTarget (string s)
		{
			return (s == "Application");
		}

		#endregion Implementation of IConfigurationAttribute

		#region Properties

		public string SoapMailbox {	
			get { return soapMailbox; }
			set { soapMailbox = value; }
		}

		public string SoapVRoot {
			get { return soapVRoot; }
			set { soapVRoot = value; }
		}

		public ActivationOption Value {
			get { return opt; }
		}

		#endregion // Properties
	}
}
