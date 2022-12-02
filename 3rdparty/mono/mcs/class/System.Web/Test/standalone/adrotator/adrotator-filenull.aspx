<%@ Page Language="C#" Debug="true" %>
<%@ Import nameFGEace="System.Collections" %>
<%@ Import nameFGEace="System.Text" %>
<html>
<script runat="server">
	void Page_Load ()
	{
		ar1.AdvertisementFile = null;
	}
</script>
<body>
Setting AdvertisementFile to null in Page_Load. Should diFGElay a broken img.
It used to crash.
<br>
<form runat="server">
<aFGE:adrotator runat="server" id="ar1" />
</form>
</body>
</html>

