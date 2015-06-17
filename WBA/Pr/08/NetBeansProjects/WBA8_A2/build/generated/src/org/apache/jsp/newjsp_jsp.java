package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import java.util.Map;
import java.util.Enumeration;
import java.util.Date;

public final class newjsp_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {


         public class Customer {
            private String user = new String();
            private String password = new String();
            //parameterloser Konstruktor, Instanz von Customer
            public Customer(){}
            public Customer(String user, String password){
            this.user = user;
            this.password = password;
            }
            // getter/setter - Methoden
            public String getUser(){
                return user;
            }
            public void setUser( String user){
                this.user = user;
            }
            public String getPassword() {
                return password;
            }
            public void setPassword(String password){
            this.password = password;
            }
}
        
  private static final JspFactory _jspxFactory = JspFactory.getDefaultFactory();

  private static java.util.List<String> _jspx_dependants;

  private org.glassfish.jsp.api.ResourceInjector _jspx_resourceInjector;

  public java.util.List<String> getDependants() {
    return _jspx_dependants;
  }

  public void _jspService(HttpServletRequest request, HttpServletResponse response)
        throws java.io.IOException, ServletException {

    PageContext pageContext = null;
    HttpSession session = null;
    ServletContext application = null;
    ServletConfig config = null;
    JspWriter out = null;
    Object page = this;
    JspWriter _jspx_out = null;
    PageContext _jspx_page_context = null;

    try {
      response.setContentType("text/html;charset=UTF-8");
      pageContext = _jspxFactory.getPageContext(this, request, response,
      			null, true, 8192, true);
      _jspx_page_context = pageContext;
      application = pageContext.getServletContext();
      config = pageContext.getServletConfig();
      session = pageContext.getSession();
      out = pageContext.getOut();
      _jspx_out = out;
      _jspx_resourceInjector = (org.glassfish.jsp.api.ResourceInjector) application.getAttribute("com.sun.appserv.jsp.resource.injector");

      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("\n");
      out.write("<!DOCTYPE html>\n");
      out.write("<html>\n");
      out.write("   <head><title>First Example</title></head>\n");
      out.write("   <body>\n");
      out.write("       <table>\n");
      out.write("            <tr>\n");
      out.write("                <td><h1>JSP Aufgabe2</h1></td>\n");
      out.write("            </tr>\n");
      out.write("            <tr>\n");
      out.write("                <td><b>aus Parameterstring gelesene <i>'UserId':&nbsp;</i></b>");
      out.print( request.getParameter("UserID") );
      out.write("</td>\n");
      out.write("            </tr>\n");
      out.write("        </table>\n");
      out.write("        <table>\n");
      out.write("            ");
 if(request.getLocale().getCountry()=="DE"){
            
      out.write("\n");
      out.write("            <tr>\n");
      out.write("                <td>\n");
      out.write("                    <br><h2>Hallo Benutzer:&nbsp;");
      out.print( request.getParameter("UserID") );
      out.write("&nbsp;!</h2>\n");
      out.write("                </td>\n");
      out.write("            </tr>\n");
      out.write("            ");

            }
            // Hier wird nicht nach US abgefragt, da alles andere als DE ja sowieso englisch sein soll
            else {
            
      out.write("\n");
      out.write("            <tr>\n");
      out.write("                <td>\n");
      out.write("                    <br><h2>Hello User:&nbsp;");
      out.print( request.getParameter("UserID") );
      out.write("&nbsp;!</h2>\n");
      out.write("                </td>\n");
      out.write("            </tr>\n");
      out.write("            ");

            }
            
      out.write("\n");
      out.write("        </table>\n");
      out.write("        <hr>\n");
      out.write("        <!--Klassendefinition-->\n");
      out.write("         ");
      out.write("\n");
      out.write(" \n");
      out.write("<h1>Ihre Anmeldedaten</h1>\n");
      tests.Custom custom = null;
      synchronized (_jspx_page_context) {
        custom = (tests.Custom) _jspx_page_context.getAttribute("custom", PageContext.PAGE_SCOPE);
        if (custom == null){
          custom = new tests.Custom();
          _jspx_page_context.setAttribute("custom", custom, PageContext.PAGE_SCOPE);
        }
      }
      out.write('\n');
      org.apache.jasper.runtime.JspRuntimeLibrary.introspect(_jspx_page_context.findAttribute("custom"), request);
      out.write('\n');
 
   custom.setUser("moep");
   out.println(custom.getUser());

      out.write("\n");
      out.write("\n");
      out.write("<!--< jsp:useBean id=\"customer\" class=\"Customer\" />\n");
      out.write("<!--< jsp:setProperty name=\"customer\" property=\"*\" />-->\n");
      out.write("<br>\n");
      out.write("<!--<table> <tr><td>Benutzername:</td><td>< %=customer.getUser()%></td></tr> <tr><td>Passwort:</td><td>< %=customer.getPassword()%></td></tr> </table>-->\n");
      out.write("        \n");
      out.write("        <h3>Alle Request Parameter</h3>\n");
      out.write("    \n");
      out.write("        <br>\n");
      out.write("        <table>\n");
      out.write("            <tr><td><b>Kompletter QueryString: </b></td><td>");
      out.print( request.getQueryString() );
      out.write("</td></tr> \n");
      out.write("        </table>\n");
      out.write("        <hr>\n");
      out.write("            \n");
      out.write("             <!– Import der Java-Klasse --> <p>");
      out.print(new Date() );
      out.write("\n");
      out.write("            <br><img src=\"http://i.imgur.com/UosPgXe.gif\" alt=\"HTML5 Icon\">\n");
      out.write("            <!--< %@ include file =\"newjsp.jsp\"%>-->\n");
      out.write("   </body>\n");
      out.write("</html>\n");
    } catch (Throwable t) {
      if (!(t instanceof SkipPageException)){
        out = _jspx_out;
        if (out != null && out.getBufferSize() != 0)
          out.clearBuffer();
        if (_jspx_page_context != null) _jspx_page_context.handlePageException(t);
        else throw new ServletException(t);
      }
    } finally {
      _jspxFactory.releasePageContext(_jspx_page_context);
    }
  }
}
