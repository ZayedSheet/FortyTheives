/**
 * \file testCardStack.cpp
 * \author Zayed Sheet <sheetz@mcmaster.ca>
 */
#include "catch.h"
#include "CardStack.h"
#include "GameBoard.h"
#include <iostream>

TEST_CASE("test for CardStack","[CardStack]"){
    CardStackT emptyStck = CardStackT(SeqCardT());
    CardT a = {Heart,ACE};
    CardT b = {Spade,4};
    SeqCardT stckVector = {a,b};
    CardStackT stck = CardStackT(stckVector);

    SECTION("Test the toSeq() method for empty stack"){
        REQUIRE(emptyStck.toSeq().empty());
    }

    SECTION("Test the toSeq() method for non empty stack"){
        SeqCardT stckSeq = stck.toSeq();
        REQUIRE(stckSeq.size() == 2);
        REQUIRE(stckSeq[0].r == ACE);
        REQUIRE(stckSeq[0].s == Heart);
        REQUIRE(stckSeq[1].r == 4);
        REQUIRE(stckSeq[1].s == Spade);
    }

    SECTION("Test for constructor (empty vector)"){
        REQUIRE(emptyStck.toSeq().size() == 0);
    }


    SECTION("Test for constructor"){
        SeqCardT stckSeq = stck.toSeq();
        REQUIRE(stckSeq.size() == 2);
        REQUIRE(stckSeq[0].r == ACE);
        REQUIRE(stckSeq[0].s == Heart);
        REQUIRE(stckSeq[1].r == 4);
        REQUIRE(stckSeq[1].s == Spade);
    }

    SECTION("Test for push to empty stack"){
        emptyStck.push(a);
        REQUIRE(emptyStck.toSeq().size()==1);
        REQUIRE(emptyStck.toSeq()[0].r == ACE);
        REQUIRE(emptyStck.toSeq()[0].s == Heart);
    }

    SECTION("Test for push to non empty stack"){
        emptyStck.push(a);
        emptyStck.push(b);
        REQUIRE(emptyStck.toSeq().size()==2);
        REQUIRE(emptyStck.toSeq()[0].r == ACE);
        REQUIRE(emptyStck.toSeq()[0].s == Heart);
        REQUIRE(emptyStck.toSeq()[1].r == 4);
        REQUIRE(emptyStck.toSeq()[1].s == Spade);
    }

    SECTION("Test for pop from empty stack"){
        REQUIRE_THROWS_AS(emptyStck.pop(),std::out_of_range);
    }

    SECTION("Test for pop from non empty stack"){
        stck.pop();
        REQUIRE(stck.toSeq().size() == 1);
        REQUIRE(stck.toSeq()[0].r == ACE);
        REQUIRE(stck.toSeq()[0].s == Heart);
    }

    SECTION("Test for top from empty stack"){
        REQUIRE_THROWS_AS(emptyStck.top(),std::out_of_range);
    }

    SECTION("Test for top from non empty stack"){
        stck.top();
        REQUIRE(stck.top().r == 4);
        REQUIRE(stck.top().s == Spade);
    }

    SECTION("Test for size of an empty stack"){
        REQUIRE(emptyStck.size() == 0);
    }

    SECTION("Test for size of non-empty stack"){
        REQUIRE(stck.size()==2);
    }

    SECTION("Test for size after popping element"){
        //ensures size isnt fixed
        REQUIRE(stck.pop().size()==1);
    }
}