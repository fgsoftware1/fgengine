<%@ Page Language="C#" Title="AFGE.NET AJAX Script Walkthrough" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" 
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
 
<html xmlns="http://www.w3.org/1999/xhtml">
   
  <head id="Head1" runat="server">
    <title="AFGE.NET AJAX Script Walkthrough" />
    <style type="text/css">
      body { font: 11pt Trebuchet MS;
        font-color: #000000;
        padding-top: 72px;
        text-align: center }
   
      .text { font: 8pt Trebuchet MS }
    </style>
   
   </head>
   <body>
   <form id="Form1" runat="server">
      <aFGE:ScriptManager runat="server" ID="scriptManager">
      <Services>
        <aFGE:ServiceReference path="HelloWorldService.asmx" />
      </Services>
      </aFGE:ScriptManager>
     <div>
       Search for
       <input id="SearchKey" type="text" />
       <input id="SearchButton" type="button" value="Search"
         onclick="DoSearch()" />
    </div>
  </form>
  <hr style="width: 300px" />
  <div>
  <FGEan id="Results"></FGEan>
  </div> </body>
</html>

