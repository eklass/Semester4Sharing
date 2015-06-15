package org.apache.jsp;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import java.util.Map;
import java.util.Enumeration;

public final class newjsp_jsp extends org.apache.jasper.runtime.HttpJspBase
    implements org.apache.jasper.runtime.JspSourceDependent {

 Enumeration enm, header;
        String hName, hValue;
        
 Enumeration enmPara;
        Map<String,String[]>headerPara;
        String hNamePara, hValuePara;
        
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
      out.write("    <h3>Request Headers</h3>\n");
      out.write("        <table>\n");
      out.write("        ");
      out.write("\n");
      out.write("        ");

        enm = request.getHeaderNames();
        while (enm.hasMoreElements()) {
            hName = (String) enm.nextElement();
            header = request.getHeaders(hName);
            if(header != null) {
                while(header.hasMoreElements()){
                    hValue= (String) header.nextElement();
               }
            }
            
      out.write("\n");
      out.write("            <tr><td><b>");
      out.print( hName );
      out.write("</b></td><td>");
      out.print( hValue );
      out.write("</td></tr>\n");
      out.write("            ");

        }
            
      out.write("\n");
      out.write("        </table>\n");
      out.write("    <h3>Request Headers</h3>\n");
      out.write("        <table>\n");
      out.write("        ");
      out.write("\n");
      out.write("        ");

        enmPara = request.getParameterNames();
        while (enmPara.hasMoreElements()) {
            hNamePara = (String) enmPara.nextElement();
            headerPara = request.getParameterMap();
            if(headerPara != null) {
                if(headerPara.containsKey(hNamePara)){
                    
                }
                
            }
            
      out.write("\n");
      out.write("            <tr><td><b>");
      out.print( hNamePara );
      out.write("</b></td><td>");
      out.print( hValuePara );
      out.write("</td></tr>\n");
      out.write("            ");

        }
            
      out.write("\n");
      out.write("        </table>    \n");
      out.write("\n");
      out.write("       \n");
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
