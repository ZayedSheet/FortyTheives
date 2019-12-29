/**
 * \file CardTypes.h
 * \author Zayed Sheet, MacID: sheetz
 * \brief Record to define a card and card type
 * \date March 26, 2019
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief Describes the Suit of a card.
 */
enum SuitT {Heart, Diamond, Club, Spade};

/**
 * \brief Describes the Category of a card.
 */
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief Describes a card (suit and rank).
 */
struct CardT{
    SuitT s;
    RankT r;
};


/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13


#endif
