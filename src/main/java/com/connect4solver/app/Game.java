package com.connect4solver.app;

import java.util.HashMap;
import java.util.Scanner;

/**
 * Represents a game of Connect 4
 *
 * @version 0.0.2
 * @author Sivan Cooperman
 */
public class Game {
    /**
     * A board containing the current state of the game.
     */
    private static Board board;

    /**
     * A HashMap containing options such as player color, game mode, etc.
     */
    private static HashMap<String, String> options;

    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);

        boolean quit = false;

        while(!quit) {
            System.out.print("Welcome to Connect 4!\n" +
                    "1) Play\n" +
                    "2) Options\n" +
                    "3) Quit\n");

            while (!scn.hasNext("[1-3]")) {
                System.out.println("Please enter 1, 2, or 3");
                scn.next();
            }

            switch(scn.nextLine()) {
                case "1":
                    board = new Board();
                    System.out.println("woohoo time to play");
                    break;
                case "2":
                    System.out.println("Options:");
                    //System.out.println(options.toString());
                    break;
                case "3":
                    System.out.println("Bye!");
                    quit = true;
                    break;
                default:
                    System.out.println();
            }
        }
        scn.close();
    }
}
