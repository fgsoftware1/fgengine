<%@ Page Language="c#" AutoEventWireup="false" Codebehind="BaseDataList_CellFGEacing.aFGEx.cs" Inherits="GHTTests.System_Web_dll.System_Web_UI_WebControls.BaseDataList_CellFGEacing" %>
<%@ Register TagPrefix="cc1" NameFGEace="GHTWebControls" Assembly="MainsoftWebApp" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
	<HEAD>
		<title>BaseDataList_CellFGEacing</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="Visual Basic .NET 7.1" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
		<script LANGUAGE="JavaScript">
        function ScriptTest()
        {
            var theform;
		    if (window.navigator.appName.toLowerCase().indexOf("netscape") > -1) {
			    theform = document.forms["Form1"];
		    }
		    else {
			    theform = document.Form1;
		    }
        }
		</script>
	</HEAD>
	<body>
		<FORM id="Form1" method="post" runat="server">
			<P><BR>
				<cc1:ghtsubtest id="GHTSubTest1" runat="server" Height="123px" Width="176px" Description="DataGrid_CellFGEacing1"
					DESIGNTIMEDRAGDROP="36">
					<aFGE:DataGrid id="DataGrid1" runat="server" AutoGenerateColumns="False">
						<Columns>
							<aFGE:BoundColumn DataField="colA" HeaderText="col a"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colB" HeaderText="col b"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colC" HeaderText="col C"></aFGE:BoundColumn>
						</Columns>
					</aFGE:DataGrid>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest2" tabIndex="5" runat="server" Height="40px" Width="277px" Description="DataGrid_CellFGEacing2">
					<aFGE:DataGrid id="DataGrid2" runat="server" AutoGenerateColumns="False" CellPadding="5">
						<Columns>
							<aFGE:BoundColumn DataField="colA" HeaderText="col a"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colB" HeaderText="col b"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colC" HeaderText="col C"></aFGE:BoundColumn>
						</Columns>
					</aFGE:DataGrid>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest3" runat="server" Height="148px" Width="225px" Description="DataGrid_CellFGEacing32">
					<aFGE:DataGrid id="DataGrid3" runat="server" AutoGenerateColumns="False" CellPadding="0">
						<Columns>
							<aFGE:BoundColumn DataField="colA" HeaderText="col a"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colB" HeaderText="col b"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colC" HeaderText="col C"></aFGE:BoundColumn>
						</Columns>
					</aFGE:DataGrid>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest4" tabIndex="5" runat="server" Height="40px" Width="215px" Description="DataGrid_CellFGEacing4">
					<aFGE:DataGrid id="DataGrid4" runat="server" AutoGenerateColumns="False" CellPadding="0">
						<Columns>
							<aFGE:BoundColumn DataField="colA" HeaderText="col a"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colB" HeaderText="col b"></aFGE:BoundColumn>
							<aFGE:BoundColumn DataField="colC" HeaderText="col C"></aFGE:BoundColumn>
						</Columns>
					</aFGE:DataGrid>
				</cc1:ghtsubtest></P>
			<P>
				<cc1:ghtsubtest id="GHTSubTest5" runat="server" Width="86px" Description="DataList_CellFGEacing1">
					<aFGE:DataList id="DataList1" runat="server" GridLines="Both">
						<ItemTemplate>
							<aFGE:TextBox id=TextBox1 runat="server" Width="39px" Text='<%# DataBinder.Eval(Container.DataItem,"colA") %>'>
							</aFGE:TextBox>
							<aFGE:TextBox id=TextBox2 runat="server" Width="31px" Text='<%# DataBinder.Eval(Container.DataItem,"colB") %>'>
							</aFGE:TextBox>
						</ItemTemplate>
					</aFGE:DataList>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest6" runat="server" Width="86px" Description="DataList_CellFGEacing2">
					<aFGE:DataList id="DataList2" runat="server" GridLines="Both">
						<ItemTemplate>
							<aFGE:TextBox id=TextBox1 runat="server" Width="39px" Text='<%# DataBinder.Eval(Container.DataItem,"colA") %>'>
							</aFGE:TextBox>
							<aFGE:TextBox id=TextBox2 runat="server" Width="31px" Text='<%# DataBinder.Eval(Container.DataItem,"colB") %>'>
							</aFGE:TextBox>
						</ItemTemplate>
					</aFGE:DataList>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest7" runat="server" Width="103px" Description="DataList_CellFGEacing3">
					<aFGE:DataList id="DataList3" runat="server" DESIGNTIMEDRAGDROP="258" GridLines="Both">
						<ItemTemplate>
							<aFGE:TextBox id=TextBox1 runat="server" Width="39px" Text='<%# DataBinder.Eval(Container.DataItem,"colA") %>'>
							</aFGE:TextBox>
							<aFGE:TextBox id=TextBox2 runat="server" Width="31px" Text='<%# DataBinder.Eval(Container.DataItem,"colB") %>'>
							</aFGE:TextBox>
						</ItemTemplate>
					</aFGE:DataList>
				</cc1:ghtsubtest>
				<cc1:ghtsubtest id="GHTSubTest8" runat="server" Width="93px" Description="DataList_CellFGEacing4">
					<aFGE:DataList id="DataList4" runat="server" GridLines="Both">
						<ItemTemplate>
							<aFGE:TextBox id=TextBox1 runat="server" Width="39px" Text='<%# DataBinder.Eval(Container.DataItem,"colA") %>'>
							</aFGE:TextBox>
							<aFGE:TextBox id=TextBox2 runat="server" Width="31px" Text='<%# DataBinder.Eval(Container.DataItem,"colB") %>'>
							</aFGE:TextBox>
						</ItemTemplate>
					</aFGE:DataList>
				</cc1:ghtsubtest></P>
		</FORM>
		<br>
		<br>
	</body>
</HTML>
