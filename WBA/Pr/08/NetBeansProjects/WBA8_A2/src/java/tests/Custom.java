/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author erichklassen
 */
package tests;

public class Custom {
            private String userID = new String(); private String password = new String();
            //parameterloser Konstruktor, Instanz von Customer
            public Custom(){}
            public Custom( String user, String password){
            this.userID = user;
            this.password = password; }
            // getter/setter - Methoden
            public String getUserID(){return userID;}
            public void setUserID( String user){
            this.userID = user; }
            public String getPassword() {return password;}
            public void setPasswordID( String password){
            this.password = password;
            }
}