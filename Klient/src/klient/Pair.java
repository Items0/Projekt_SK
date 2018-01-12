/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package klient;

/**
 *
 * @author Patryk
 */
public class Pair {
    private String name;
    private String IP;
    Pair(String name, String IP){
        this.name = name;
        this.IP = IP;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @return the IP
     */
    public String getIP() {
        return IP;
    }
}
