
<%@ Page Language="C#" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
        <aFGE:ScriptManager runat="server" ID="ScriptManager01">
            <Scripts>
               <aFGE:ScriptReference Path="ArrayMemberSampleJS.js" />
            </Scripts>
        </aFGE:ScriptManager>
        
         <script type="text/javascript">
            var app = Sys.Application;
                app.add_load(applicationLoadHandler);

                function applicationLoadHandler(sender, args) {
                  var aDemo = new Demo.Samples();
                  aDemo.runSample(); 
                }
         </script>
    </form>
</body>
</html>
