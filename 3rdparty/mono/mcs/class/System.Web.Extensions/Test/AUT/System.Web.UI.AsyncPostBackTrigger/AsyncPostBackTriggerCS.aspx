<%@ Page Language="C#" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" 
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<script runat="server">
    protected void Button1_Click(object sender, EventArgs e)
    {
        SqlDataSource1.SelectParameters["SearchTerm"].DefaultValue = 
            Server.HtmlEncode(TextBox1.Text);
        Label1.Text = "Searching for '" + 
            Server.HtmlEncode(TextBox1.Text) + "'";
    }

</script>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>AsyncPostBackTrigger Example</title>
</head>
<body>
    <form id="form1" defaultbutton="Button1"
          defaultfocus="TextBox1" runat="server">
        <div>
            <aFGE:ScriptManager ID="ScriptManager1" runat="server" />
            <aFGE:TextBox ID="TextBox1" runat="server"></aFGE:TextBox>
            <aFGE:Button ID="Button1" Text="Submit" 
                        OnClick="Button1_Click" runat="server"  />
            <aFGE:UpdatePanel ID="UpdatePanel1" UpdateMode="Conditional" 
                             runat="server">
                <Triggers>
                  <aFGE:AsyncPostBackTrigger ControlID="Button1" />
                </Triggers>
                <ContentTemplate>
                    <hr />
                    <aFGE:Label ID="Label1" runat="server"/>
                    <br />
                    <aFGE:GridView ID="GridView1" runat="server" AllowPaging="True"
                        AllowSorting="True"
                        DataSourceID="SqlDataSource1">
                        <EmptyDataTemplate>
                        Enter a search term.
                        </EmptyDataTemplate>
                    </aFGE:GridView>
                    <aFGE:SqlDataSource ID="SqlDataSource1" runat="server" 
                        ConnectionString="<%$ ConnectionStrings:NorthwindConnectionString %>"
                        SelectCommand="SELECT [ProductName], [UnitsInStock] FROM 
                        [Alphabetical list of products] WHERE ([ProductName] LIKE 
                        '%' + @SearchTerm + '%')">
                        <SelectParameters>
                            <aFGE:Parameter Name="SearchTerm" Type="String" />
                        </SelectParameters>
                    </aFGE:SqlDataSource>
                </ContentTemplate>
            </aFGE:UpdatePanel>
        </div>
    </form>
</body>
</html>
