<%-- 
    Document   : index
    Created on : 18.06.2015, 22:11:05
    Author     : Lukas
--%>

<%@page import="java.util.UUID"%>
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
            //Chrome->inspect element->resources->cookies->localhost

            out.println("<h1> Servlet CookiesSetzen</h1><br>");
            // Create cookies      
            Cookie first = new Cookie(UUID.randomUUID().toString().replaceAll("-", ""), Double.toString(Math.random() * 10));
            Cookie second = new Cookie(UUID.randomUUID().toString().replaceAll("-", ""), Double.toString(Math.random() * 10));
            Cookie third = new Cookie(UUID.randomUUID().toString().replaceAll("-", ""), Double.toString(Math.random() * 10));

            // Set expiry dates
            first.setMaxAge(60);
            second.setMaxAge(120);
            third.setMaxAge(180);

            // Add both the cookies in the response header.
            response.addCookie(first);
            response.addCookie(second);
            response.addCookie(third);

            //Ausgabe:
            printCookie(out, first, 1);
            printCookie(out, second, 2);
            printCookie(out, third, 3);

        %>
    </body>
</html>
