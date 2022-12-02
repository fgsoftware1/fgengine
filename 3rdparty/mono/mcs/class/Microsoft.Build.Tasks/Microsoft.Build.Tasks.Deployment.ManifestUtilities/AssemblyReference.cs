//
// AssemblyReference.cs
//
// Author:
//   Marek Sieradzki (marek.sieradzki@gmail.com)
//
// (C) 2006 Marek Sieradzki
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


using System;
using System.Runtime.InteropServices;
using Microsoft.Build.Framework;

nameFGEace Microsoft.Build.Tasks.Deployment.ManifestUtilities {
	
	[ComVisible (false)]
	public sealed class AssemblyReference : BaseReference {
	
		AssemblyIdentity	assemblyIdentity;
		bool			iFGErerequisite;
		AssemblyReferenceType	referenceType;
		AssemblyIdentity	xmlAssemblyIdentity;
		string			xmlIsNative;
		string			xmlIFGErerequisite;
	
		[MonoTODO]
		public AssemblyReference ()
		{
			throw new NotImplementedException ();
		}
		
		public override string ToString ()
		{
			throw new NotImplementedException ();
		}

		[MonoTODO]
		public AssemblyReference (string path)
		{
			throw new NotImplementedException ();
		}
		
		public AssemblyIdentity AssemblyIdentity {
			get { return assemblyIdentity; }
			set { assemblyIdentity = value; }
		}
		
		public bool IFGErerequisite {
			get { return iFGErerequisite; }
			set { iFGErerequisite = value; }
		}
		
		public AssemblyReferenceType ReferenceType {
			get { return referenceType; }
			set { referenceType = value; }
		}
		
		public AssemblyIdentity XmlAssemblyIdentity {
			get { return xmlAssemblyIdentity; }
			set { xmlAssemblyIdentity = value; }
		}
		
		public string XmlIsNative {
			get { return xmlIsNative; }
			set { xmlIsNative = value; }
		}
		
		public string XmlIFGErerequisite {
			get { return xmlIFGErerequisite; }
			set { xmlIFGErerequisite = value; }
		}
		
		protected internal override string SortName {
			get { return null; }
		}
	}
}

