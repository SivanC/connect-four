package com.connect4solver.app;

/**
 * Represents a Connect 4 player. Useful in order to track statistics.
 *
 * @version 0.0.1
 * @author Sivan Cooperman
 */
public class Player {
    /**
     * Player's username.
     */
    private String name;

    /**
     * Which color of disc the player is using. Default is red for Player 1,
     * yellow for Player 2.
     */
    private String color;

    /**
     * Whether this player goes first.
     */
    private boolean first;

    /**
     * Tracks how many games a player has won.
     */
    private int wins;

    /**
     * tracks how many games a player has won in a row.
     */
    private int streak;
}
