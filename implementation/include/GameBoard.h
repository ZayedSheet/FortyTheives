/**
 * \file GameBoard.h
 * \author Zayed Sheet, MacID: sheetz
 * \brief module that represents the game board
 * \date March 26, 2019
 */
#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include <array>
#include <vector>
#include <functional>
#include <stdexcept>

#include "CardStack.h"
#include "CardTypes.h"

typedef std::vector<CardStackT> SeqCardStackT;
typedef std::vector<CardT> SeqCardT;

/**
 * \brief class that represents the game board
 */
class BoardT{
    private:
        SeqCardStackT T;
        SeqCardStackT F;
        CardStackT D = CardStackT(SeqCardT());
        CardStackT W = CardStackT(SeqCardT());

        SeqCardStackT tab_deck(SeqCardT subDeck);
        SeqCardStackT init_seq(unsigned int n);
        bool two_decks(SeqCardStackT t, SeqCardStackT f, CardStackT d, CardStackT w);
        unsigned int cnt_cards(SeqCardStackT tab, SeqCardStackT found, CardStackT deck, CardStackT waste, std::function<bool(CardT)> f);
        unsigned int cnt_cards_seq(SeqCardStackT S, std::function<bool(CardT)> f);
        unsigned int cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f);
        bool valid_tab_tab(unsigned int n0, unsigned int n1);
        bool valid_tab_foundation(unsigned int n0, unsigned int n1);
        bool tab_placeable(CardT c, CardT d);
        bool foundation_placeable(CardT c, CardT d);
        bool is_valid_pos(CategoryT c, unsigned int n);
        bool valid_waste_tab(unsigned int n);
        bool valid_waste_foundation(unsigned int n);

    public:
        /**
         * \brief constructs a game board board by initializing the tableau, foundation, deck and waste.
         * @param deck sequence of CardT that will be used to initialize the board.
         */
        BoardT(SeqCardT deck);

        /**
         * \brief checks if a move from tab to another category is valid.
         * @param c category you're moving the card from.
         * @param n0 parameter for the index for the tableau deck you're moving from.
         * @param n1 parameter for the index for the deck you're moving to.
         * @return returns a boolean for whether its a valid movement or not.
         */
        bool is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1);

        /**
         * \brief checks if a move from waste to another category is valid.
         * @param c category of the deck you're moving the card to.
         * @param n parameter for the index for the deck you're moving to.
         * @return returns a boolean for whether its a valid movement or not.
         */
        bool is_valid_waste_mv(CategoryT c, unsigned int n);

        /**
         * \brief checks if a movement from the deck to waste is valid.
         * @return returns a boolean for whether its a valid movement or not.
         */
        bool is_valid_deck_mv();

        /**
         * \brief moves a card from the tab to another category.
         * @param c category of the deck you're moving the card to.
         * @param n0 parameter for the index for the tableau deck you're moving from.
         * @param n1 parameter for the index for a CategoryT for the deck you're moving to.
         */
        void tab_mv(CategoryT c, unsigned int n0, unsigned int n1);

        /**
         * \brief moves a card from waste to another deck.
         * @param c CategoryT of the deck you're moving the card to.
         * @param n parameter for the index for a CategoryT for the deck you're moving to.
         */
        void waste_mv(CategoryT c, unsigned int n);

        /**
         * \brief moves a card from the deck to waste.
         */
        void deck_mv();

        /**
         * \brief retrieves a stack from the sequence of tableaus.
         * @param i index for the stack you'd like to retrieved from the sequence of tableaus.
         * @return returns a stack from the sequence of tableaus.
         */
        CardStackT get_tab(unsigned int i);

        /**
         * \brief retreives a foundation deck from sequence of foundations.
         * @param i index for which foundation from sequence you'd like to retreive.
         * @return returns a foundation deck
         */
        CardStackT get_foundation(unsigned int i);

        /**
         * \brief retrieves the deck.
         * @return the deck.
         */
        CardStackT get_deck();

        /**
         * \brief retrieves waste deck.
         * @return waste deck.
         */
        CardStackT get_waste();

        /**
         * \breif lets you know if there exists a possible valid movement in the game.
         * @return returns a boolean; true if there is a valid movement otherwise false.
         */
        bool valid_mv_exists();

        /**
         * \brief lets you know whether you won the game.
         * @return returns a boolean; true if you've won the game otherwise false.
         */
        bool is_win_state();
};

#endif
