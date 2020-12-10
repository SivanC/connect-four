package com.connect4solver.app;

import java.util.BitSet;

/**
 * Represents a 7x6 Connect 4 board, contains fields and variables that handle
 * the changing of the board's state.
 *
 * @version 0.0.1
 * @author Sivan Cooperman
 */
public class Board {
    /**
     * This bitset contains 0s in spaces that have not been played, and 1s
     * where either player has played a piece.
     *
     * From left to right, each bit represents a slot in the Connect 4 board
     * from bottom to top, left to right. There are 49 bits, 42 for the 7x6
     * board, and 7 for the "sentinel row" on the top (thus the 7th bit will
     * be the leftmost bit of the "sentinel row").
     */
    private BitSet mask;

    /**
     * Contains all of the current players moves. The XOR operation can be
     * applied to this bitset and the mask to receive the other player's
     * moves.
     */
    private BitSet currentPlayerPos;

    public Board() {
        this.setMask(new BitSet(49));
        this.setCurrentPlayerPos(new BitSet(49));
    }

    public Board(BitSet mask, BitSet currentPlayerPos) {
        this.setMask(mask);
        this.setCurrentPlayerPos(currentPlayerPos);
    }

    public BitSet getMask() {
        return mask;
    }

    public void setMask(BitSet mask) {
        this.mask = mask;
    }

    public BitSet getCurrentPlayerPos() {
        return currentPlayerPos;
    }

    public void setCurrentPlayerPos(BitSet currentPlayerPos) {
        this.currentPlayerPos = currentPlayerPos;
    }

    public boolean checkWin() {
        // Check horizontal
        return true;
    }
}
