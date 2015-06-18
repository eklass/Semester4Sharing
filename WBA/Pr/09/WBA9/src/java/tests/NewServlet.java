package tests;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import static java.lang.Math.random;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Random;

/**
 *
 * @author erichklassen
 */
@WebServlet(urlPatterns = {"/NewServlet"})
public class NewServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            Cookie[] cookies = request.getCookies();
            /* TODO output your page here. You may use following sample code. */
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet NewServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet NewServlet at " + request.getContextPath() + "</h1>");
            out.println("CookieSize= "+cookies);
            for (int i = 0; i < cookies.length; i++) {
                String name = cookies[i].getName();
                String value = cookies[i].getValue();
                out.print("<b>Cookie Nr: "+i+"</b><br>"+"Name: "+ name + " Value: "+value+"<br>");
            }
            out.println("</body>");
            out.println("</html>");
        }
    }

    public String randomZahl(){
    Random rand = new Random();
    int digits = 10;
    String choices = "1234567890" ; // Zahlen werden hinzugefügt
    String password = "";
    int j = 0;
    while ( j<digits ) {
        password = password + choices.charAt( rand.nextInt( choices.length() ) );
        j = j + 1;
        }
    return password;
    }
    
    public String randomBuchstabe(){
    Random rand = new Random();
    int digits = 10;

 
    String choices = "abcdefghijklmnopqrstuvwxyz" ; // Alphabet wird erzeugt
    choices = choices + choices.toUpperCase() ; // Alphabet auch in Großbuchstaben
 
    String password = "";
    int j = 0;
    while ( j<digits ) {
        password = password + choices.charAt( rand.nextInt( choices.length() ) );
        j = j + 1;
        }
    return password;
    }
    
private void eraseCookie(HttpServletRequest req, HttpServletResponse resp) {
    resp.setContentType("text/html");
    Cookie[] cookies = req.getCookies();
    if (cookies != null)
        for (int i = 0; i < cookies.length; i++) {
            //cookies[i].setValue("");
            //cookies[i].setPath("/");
            cookies[i].setMaxAge(0);
            resp.addCookie(cookies[i]);
        }
}
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        Cookie cookie1 = new Cookie( randomBuchstabe(), randomZahl());
        cookie1.setMaxAge(60);
        Cookie cookie2 = new Cookie( randomBuchstabe(), randomZahl() );
        cookie2.setMaxAge(120);
        Cookie cookie3 = new Cookie( randomBuchstabe(), randomZahl() );
        cookie2.setMaxAge(180);
        response.addCookie( cookie1 );
        response.addCookie( cookie2 );
        response.addCookie( cookie3 );
//        eraseCookie(request,response);
        processRequest(request, response);
        
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException { 
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
