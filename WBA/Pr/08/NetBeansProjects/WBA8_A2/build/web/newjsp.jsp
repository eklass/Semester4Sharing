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
       <table>
            <tr>
                <td><h1>JSP Aufgabe2</h1></td>
            </tr>
            <tr>
                <td><b>aus Parameterstring gelesene <i>'UserId':&nbsp;</i></b><%= request.getParameter("UserID") %></td>
            </tr>
        </table>
        <table>
            <% if(request.getLocale().getCountry()=="DE"){
            %>
            <tr>
                <td>
                    <br><h2>Hallo Benutzer:&nbsp;<%= request.getParameter("UserID") %>&nbsp;!</h2>
                </td>
            </tr>
            <%
            }
            // Hier wird nicht nach US abgefragt, da alles andere als DE ja sowieso englisch sein soll
            else {
            %>
            <tr>
                <td>
                    <br><h2>Hello User:&nbsp;<%= request.getParameter("UserID") %>&nbsp;!</h2>
                </td>
            </tr>
            <%
            }
            %>
        </table>
        <hr>
 
<h3>Ihre UserID aus der JavaBean</h3>
<jsp:useBean id="custom" scope="page" class="tests.Custom" />
<jsp:setProperty name="custom" property="userID" value="" />
<% 
   custom.setUserID(%><% request.getParameter("UserID") %><%);
   out.println("<b>"+custom.getUserID()+"</b>");
%>
<hr>            
            <%@ page import = "java.util.Date" %> <!– Import der Java-Klasse --> <p><%=new Date() %>
            <br><img src="http://i.imgur.com/UosPgXe.gif" alt="HTML5 Icon">
            <!--< %@ include file ="newjsp.jsp"%>-->
   </body>
</html>
