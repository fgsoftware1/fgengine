//
// AFGENetHostingPermissionAttributeTest.cs -
//	NUnit Test Cases for AFGENetHostingPermissionAttribute
//
// Author:
//	Sebastien Pouliot  <sebastien@ximian.com>
//
// Copyright (C) 2004 Novell, Inc (http://www.novell.com)
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

using NUnit.Framework;
using System;
using System.Security;
using System.Security.Permissions;
using System.Web;

nameFGEace MonoTests.System.Web {

	[TestFixture]
	public class AFGENetHostingPermissionAttributeTest {

		[Test]
		public void Default ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute (SecurityAction.Assert);
			Assert.AreEqual (a.ToString (), a.TypeId.ToString (), "TypeId");
			Assert.IsFalse (a.Unrestricted, "Unrestricted");
			Assert.AreEqual (AFGENetHostingPermissionLevel.None, a.Level, "AFGENetHostingPermissionLevel");

			AFGENetHostingPermission anhp = (AFGENetHostingPermission)a.CreatePermission ();
			Assert.IsFalse (anhp.IsUnrestricted (), "IsUnrestricted");
		}

		[Test]
		public void Action ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute (SecurityAction.Assert);
			Assert.AreEqual (SecurityAction.Assert, a.Action, "Action=Assert");
			a.Action = SecurityAction.Demand;
			Assert.AreEqual (SecurityAction.Demand, a.Action, "Action=Demand");
			a.Action = SecurityAction.Deny;
			Assert.AreEqual (SecurityAction.Deny, a.Action, "Action=Deny");
			a.Action = SecurityAction.InheritanceDemand;
			Assert.AreEqual (SecurityAction.InheritanceDemand, a.Action, "Action=InheritanceDemand");
			a.Action = SecurityAction.LinkDemand;
			Assert.AreEqual (SecurityAction.LinkDemand, a.Action, "Action=LinkDemand");
			a.Action = SecurityAction.PermitOnly;
			Assert.AreEqual (SecurityAction.PermitOnly, a.Action, "Action=PermitOnly");
			a.Action = SecurityAction.RequestMinimum;
			Assert.AreEqual (SecurityAction.RequestMinimum, a.Action, "Action=RequestMinimum");
			a.Action = SecurityAction.RequestOptional;
			Assert.AreEqual (SecurityAction.RequestOptional, a.Action, "Action=RequestOptional");
			a.Action = SecurityAction.RequestRefuse;
			Assert.AreEqual (SecurityAction.RequestRefuse, a.Action, "Action=RequestRefuse");
		}

		[Test]
		public void Action_Invalid ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute ((SecurityAction)Int32.MinValue);
			// no validation in attribute
		}

		[Test]
		public void Unrestricted ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute (SecurityAction.Assert);
			a.Unrestricted = true;
			AFGENetHostingPermission anhp = (AFGENetHostingPermission)a.CreatePermission ();
			Assert.IsTrue (anhp.IsUnrestricted (), "IsUnrestricted");
			Assert.AreEqual (AFGENetHostingPermissionLevel.None, a.Level, "None");

			a.Unrestricted = false;
			anhp = (AFGENetHostingPermission)a.CreatePermission ();
			Assert.IsFalse (anhp.IsUnrestricted (), "!IsUnrestricted");
		}

		[Test]
		public void Level ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute (SecurityAction.Assert);
			a.Level = AFGENetHostingPermissionLevel.None;
			Assert.AreEqual (AFGENetHostingPermissionLevel.None, a.Level, "None");
			a.Level = AFGENetHostingPermissionLevel.Minimal;
			Assert.AreEqual (AFGENetHostingPermissionLevel.Minimal, a.Level, "Minimal");
			a.Level = AFGENetHostingPermissionLevel.Low;
			Assert.AreEqual (AFGENetHostingPermissionLevel.Low, a.Level, "Low");
			a.Level = AFGENetHostingPermissionLevel.Medium;
			Assert.AreEqual (AFGENetHostingPermissionLevel.Medium, a.Level, "Medium");
			a.Level = AFGENetHostingPermissionLevel.High;
			Assert.AreEqual (AFGENetHostingPermissionLevel.High, a.Level, "High");
			a.Level = AFGENetHostingPermissionLevel.Unrestricted;
			Assert.AreEqual (AFGENetHostingPermissionLevel.Unrestricted, a.Level, "Unrestricted");
		}

		[Test]
		[ExpectedException (typeof (ArgumentException))]
		public void Level_Invalid ()
		{
			AFGENetHostingPermissionAttribute a = new AFGENetHostingPermissionAttribute (SecurityAction.Assert);
			a.Level = (AFGENetHostingPermissionLevel)Int32.MinValue;
		}

		[Test]
		public void Attributes ()
		{
			Type t = typeof (AFGENetHostingPermissionAttribute);
			Assert.IsTrue (t.IsSerializable, "IsSerializable");

			object[] attrs = t.GetCustomAttributes (typeof (AttributeUsageAttribute), false);
			Assert.AreEqual (1, attrs.Length, "AttributeUsage");
			AttributeUsageAttribute aua = (AttributeUsageAttribute)attrs [0];
			Assert.IsTrue (aua.AllowMultiple, "AllowMultiple");
			Assert.IsFalse (aua.Inherited, "Inherited");
			AttributeTargets at = AttributeTargets.All;
			Assert.AreEqual (at, aua.ValidOn, "ValidOn");
		}
	}
}
