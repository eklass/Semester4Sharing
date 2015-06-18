<%-- 
    Document   : getCookies
    Created on : 18.06.2015, 22:36:20
    Author     : Lukas
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%!
    public void printCookie(JspWriter out, Cookie cook, int count) {
        try {
            out.println("<h2>Cookie Nr." + count + ":</h2><br>");
            out.println("Name: " + cook.getName() + "<br>");
            out.println("Value: " + cook.getValue() + "<br>");
            out.println("MaxAge: " + cook.getMaxAge() + "<br>");
        } catch (Exception e) {
            System.err.println("FATAL ERROR IN printCookie()!!!!");
        }

    }
%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
    </head>
    <body>
        <%
            Cookie cookie = null;
            Cookie[] cookies = null;
            // Get an array of Cookies associated with this domain
            cookies = request.getCookies();
            if (cookies != null) {
                out.println("<h2> Found Cookies Name and Value</h2>");
                for (int i = 0; i < cookies.length; i++) {
                    printCookie(out, cookies[i], i);
                }
            } else {
                out.println("<h2>No cookies founds</h2>");
            }
        %>
    </body>
</html>
