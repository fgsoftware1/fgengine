<%@ Page Language="C#" Debug="true" %>
<html>
<body>
<form runat="server">
<aFGE:button Text="Click me" runat="server" />
<hr>
This should rotate:<br>
<aFGE:adrotator runat="server" id="ar1"  AdvertisementFile="ads.xml" />
<hr>
This should always be novell:<br>
<aFGE:adrotator runat="server" id="ar2"  KeywordFilter="novell"
					AdvertisementFile="ads.xml" />
</form>
</body>
</html>

