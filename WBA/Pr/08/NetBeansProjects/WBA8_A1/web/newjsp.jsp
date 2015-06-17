<%-- 
    Document   : newjsp
    Created on : 15.06.2015, 20:11:19
    Author     : erichklassen
    Useful Link: http://www.jsptutorial.org/content/standardActions
                 http://beginnersbook.com/2013/11/jsp-forward-action-tag/
--%>
<%@page import="java.util.Map"%>
<%@ page import="java.util.Enumeration" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
   <head><title>First Example</title></head>

   <body>
    <h3>Request Headers</h3>
        <table>
        <%! Enumeration enm, header;
        String hName, hValue;
        %>
        <%
        enm = request.getHeaderNames();
        while (enm.hasMoreElements()) {
            hName = (String) enm.nextElement();
            header = request.getHeaders(hName);
            if(header != null) {
                while(header.hasMoreElements()){
                    hValue= (String) header.nextElement();
               }
            }
            %>
            <tr><td><b><%= hName %></b></td><td><%= hValue %></td></tr>
            <%
        }
            %>
        </table>
        <h3>Alle Request Parameter</h3>
    
        <table>

        <%! Enumeration enmPara;
        Map<String,String[]>headerPara;
        String hNamePara, hValuePara;
        %>
        <%
        enmPara = request.getParameterNames();
        while (enmPara.hasMoreElements()) {
            hNamePara = (String) enmPara.nextElement();
            headerPara = request.getParameterMap();
            if(headerPara != null && headerPara.containsKey(hNamePara)) {
                hValuePara=headerPara.get(hNamePara)[0];
            }
            %>
            <tr><td><b><%= hNamePara %></b></td><td><%= hValuePara %></td></tr>
            <%
        }
            %>
            </table>
            <br>
        <table>
            <tr><td><b>Kompletter QueryString: </b></td><td><%= request.getQueryString() %></td></tr> 
        </table>
        <hr>
        <%@ page import = "java.util.Date" %> <!– Import der Java-Klasse --> <p><%=new Date() %>
            <br><img src="http://i.imgur.com/UosPgXe.gif" alt="HTML5 Icon">
   </body>
</html>
