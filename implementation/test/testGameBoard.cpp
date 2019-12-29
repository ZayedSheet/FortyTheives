/**
 * \file testCardStack.cpp
 * \author Zayed Sheet <sheetz@mcmaster.ca>
 */
#include "catch.h"
#include "CardStack.h"
#include "GameBoard.h"
#include <iostream>

TEST_CASE("test for GameBoard","[GameBoard]"){
    SeqCardT d;
    for (RankT rank = ACE; rank <= KING; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = { static_cast<SuitT>(suit), rank };
            d.push_back(n);
            d.push_back(n);
        }
    }
    BoardT board1(d); //d = (a0,a0,a1,a1,a2,a2,a3,a3,20,20,21,21...k2,k2,k3,k3,k3}
    BoardT winBoard(d); //board in win state (created below)
    d[2]= CardT{Diamond,2};
    d[11] = CardT{Diamond,ACE};
    BoardT board2(d);  //d = (a0,a0,21,a1,a2,a2,a3,a3,20,20,21,a1...k2,k2,k3,k3}
    d[3] = CardT{Diamond, 2};
    d[2] = CardT{Spade, KING};
    d[103] = CardT{Diamond, ACE};
    BoardT board3(d); //d = (a0,a0,k3,21,a2,a2,a3,a3,20,20,21,a1...k2,k2,k3,a1}
    d[7] = CardT{Spade, KING};
    d[11] = CardT{Club, KING};
    d[15] = CardT{Club, KING};
    d[19] = CardT{Diamond, KING};
    d[23] = CardT{Diamond, KING};
    d[27] = CardT{Heart, KING};
    d[31] = CardT{Heart, KING};
    d[34] = CardT{Spade, JACK};
    d[39] = CardT{Spade, JACK};

    d[102] = CardT{Spade, ACE};
    d[101] = CardT{Diamond, ACE};
    d[100] = CardT{Spade,2};
    d[99] = CardT{Diamond,3};
    d[98] = CardT{Spade, 3};
    d[97] = CardT{Diamond, 4};
    d[96] = CardT{Spade, 4};
    d[87] = CardT{Diamond, 5};
    d[86] = CardT{Spade, 5};
    BoardT noMove(d); //game board with no valid moves
    for(unsigned int i = 0; i < 64; i++){
        noMove.deck_mv();
    }

    //below code creates a board in its win state
    unsigned int x = 0;//40 cards for tableau
    unsigned int y = 0;//tableau index;
    unsigned int z = 0;//foundation index
    while(x < 40) {
        for (unsigned int j = 0; j < 2; j++) {
            for(unsigned int k = 0; k < 4; k++){
                winBoard.tab_mv(Foundation,y,z);
                z++;
                x++;
            }
            y++;
        }
        z = 0;
    }
    for (unsigned int i = 0; i < 64; i++){
        winBoard.deck_mv();
    }
    while (x < 104){
        winBoard.waste_mv(Foundation,2);
        winBoard.waste_mv(Foundation,3);
        winBoard.waste_mv(Foundation,0);
        winBoard.waste_mv(Foundation,1);
        winBoard.waste_mv(Foundation,6);
        winBoard.waste_mv(Foundation,7);
        winBoard.waste_mv(Foundation,4);
        winBoard.waste_mv(Foundation,5);
        x+=8;
    }

    SECTION("is_valid_tab_mv tab to deck"){
        REQUIRE(!board1.is_valid_tab_mv(Deck,0,0));
    }

    SECTION("is_valid_tab_mv tab to waste"){
        REQUIRE(!board1.is_valid_tab_mv(Waste,9,5));
    }

    SECTION("is_valid_tab_mv tab to empty foundation (legal)"){
        //ACE of Diamonds to empty foundation
        REQUIRE(board1.is_valid_tab_mv(Foundation,0,0));
    }

    SECTION("is_valid_tab_mv tab to empty foundation (illegal) "){
        //checks if non ace can be put into empty foundation
        board2.tab_mv(Foundation,0,0);
        REQUIRE(!board2.is_valid_tab_mv(Foundation,0,1));
    }

    SECTION("is_valid_tab_mv tab to non empty foundation (illegal)"){
        board1.tab_mv(Foundation,0,0);
        REQUIRE(!board1.is_valid_tab_mv(Foundation,0,0)); //Ace of diamonds on Ace of diamonds
    }

    SECTION("is_valid_tab_mv tab to non empty foundation (legal)"){
        board2.tab_mv(Foundation,0,0);
        REQUIRE(board2.is_valid_tab_mv(Foundation,0,0));
    }

    SECTION("is_valid_tab_mv tab to empty tab"){
        board1.tab_mv(Foundation,0,0);
        board1.tab_mv(Foundation,0,1);
        board1.tab_mv(Foundation,0,2);
        board1.tab_mv(Foundation,0,3);
        REQUIRE(board1.is_valid_tab_mv(Tableau,1,0));
    }

    SECTION("is_valid_tab_mv empty tab to tab"){
        board1.tab_mv(Foundation,0,0);
        board1.tab_mv(Foundation,0,1);
        board1.tab_mv(Foundation,0,2);
        board1.tab_mv(Foundation,0,3);
        board1.tab_mv(Foundation,1,4);
        board1.tab_mv(Foundation,1,5);
        board1.tab_mv(Foundation,1,6);
        board1.tab_mv(Foundation,1,7);
        REQUIRE(!board1.is_valid_tab_mv(Tableau,0,1));
    }

    SECTION("is_valid_tab_mv tab to tab (Illegal)"){
        REQUIRE(!board1.is_valid_tab_mv(Tableau,0,1));
    }

    SECTION("is_valid_tab_mv tab to tab (legal"){
        REQUIRE(board1.is_valid_tab_mv(Tableau,0,2));
    }

    SECTION("is_valid_tab_mv exception case"){
        REQUIRE_THROWS_AS(board1.is_valid_tab_mv(Tableau,11,0),std::out_of_range);
    }

    SECTION("is_valid_waste_mv waste to tableau (legal)"){
        board3.deck_mv();
        REQUIRE(board3.is_valid_waste_mv(Tableau,0)); //waste card(2 of diamonds) to Tableau 0 (Ace of diamond)
    }

    SECTION("is_valid_waste_mv waste to tableau (illegal"){
        board1.deck_mv();
        REQUIRE(!board1.is_valid_waste_mv(Tableau,0));
    }

    SECTION("is_valid_waste_mv empty waste"){
        REQUIRE_THROWS_AS(board1.is_valid_waste_mv(Foundation,0),std::invalid_argument);
    }

    SECTION("is_valid_waste_mv invalid position"){
        board1.deck_mv();
        REQUIRE_THROWS_AS(board1.is_valid_waste_mv(Foundation,9), std::out_of_range);
        REQUIRE_THROWS_AS(board1.is_valid_waste_mv(Tableau, -1), std::out_of_range);
    }

    SECTION("is_valid_waste_mv waste to foundation (legal)"){
        board3.deck_mv();
        REQUIRE(board3.is_valid_waste_mv(Foundation, 0));
    }

    SECTION("is_valid_waste_mv waste to foundation (illegal)"){
        board3.deck_mv();
        board3.tab_mv(Foundation,2,0);
        REQUIRE(!board3.is_valid_waste_mv(Foundation,0));
    }

    SECTION("is_valid_deck_mv deck movement"){
        REQUIRE(board1.is_valid_deck_mv());
    }

    SECTION("is_valid_deck_mv deck movement"){
        for(unsigned int i = 0; i < 64; i++){
            REQUIRE(board1.is_valid_deck_mv()); //just makes sure there are no bugs
            board1.deck_mv();
        }
        REQUIRE(!board1.is_valid_deck_mv());
    }

    SECTION("tab_mv to foundation (legal)"){
        board1.tab_mv(Foundation, 0,0); //Move ace of diamonds to foundation 0
        REQUIRE(board1.get_foundation(0).top().s == Diamond);
        REQUIRE(board1.get_foundation(0).top().r == ACE);
    }

    SECTION("tab_mv illegal"){
        REQUIRE_THROWS_AS(board1.tab_mv(Foundation,2,0),std::invalid_argument);
    }

    SECTION("tab_mv to tab (legal)"){
        board1.tab_mv(Tableau,0,2);
        REQUIRE(board1.get_tab(2).top().s == Diamond);
        REQUIRE(board1.get_tab(2).top().r == ACE);
    }

    //d = (a0,a0,k3,21,a2,a2,a3,a3,20,20,21,a1...k2,k2,k3,a1}
    SECTION("waste_mv to foundation (legal)"){
        board3.deck_mv();
        board3.waste_mv(Foundation, 0);
        REQUIRE(board3.get_foundation(0).top().s == Diamond);
        REQUIRE(board3.get_foundation(0).top().r == ACE);
    }

    SECTION("waste_mv illegal"){
        board3.deck_mv();
        REQUIRE_THROWS_AS(board1.waste_mv(Foundation,0),std::invalid_argument);
    }

    SECTION("waste_mv to tableau"){
        board3.deck_mv();
        board3.waste_mv(Tableau, 0);
        REQUIRE(board3.get_tab(0).top().s == Diamond);
        REQUIRE(board3.get_tab(0).top().r == ACE);
    }

    SECTION("deck_mv legal"){
        board3.deck_mv();
        REQUIRE(board3.get_waste().top().s == Diamond);
        REQUIRE(board3.get_waste().top().r == ACE);
    }

    SECTION("deck_mv illegal"){
        for(unsigned int i = 0; i < 64; i++){
            board1.deck_mv();
        }
        REQUIRE_THROWS_AS(board1.deck_mv(),std::invalid_argument);
    }

    SECTION("get_tab empty tab"){
        board1.tab_mv(Foundation,0,0);
        board1.tab_mv(Foundation,0,1);
        board1.tab_mv(Foundation,0,2);
        board1.tab_mv(Foundation,0,3);
        REQUIRE(board1.get_tab(0).size() == 0);
        REQUIRE_THROWS_AS(board1.get_tab(0).top(),std::out_of_range);
    }

    SECTION("get_tab normal case"){
        REQUIRE(board1.get_tab(0).size() == 4);
        board1.tab_mv(Foundation,0,0);
        board1.tab_mv(Foundation,0,1);
        REQUIRE(board1.get_tab(0).top().s == Heart);
        REQUIRE(board1.get_tab(0).top().r == ACE);
        REQUIRE(board1.get_tab(0).pop().top().s == Heart);
        REQUIRE(board1.get_tab(0).pop().top().r == ACE);
    }

    SECTION("get_tab exception case"){
        REQUIRE_THROWS_AS(board1.get_tab(15),std::out_of_range);
    }

    SECTION("get foundation empty case"){
        REQUIRE(board1.get_foundation(0).size() == 0);
        REQUIRE_THROWS_AS(board1.get_foundation(0).top(),std::out_of_range);
    }

    SECTION("get_foundation normal case"){
        board1.tab_mv(Foundation,0,0);
        board1.tab_mv(Foundation,2,0);
        REQUIRE(board1.get_foundation(0).size() == 2);
        REQUIRE(board1.get_foundation(0).top().s == Diamond);
        REQUIRE(board1.get_foundation(0).top().r == 2);
        REQUIRE(board1.get_foundation(0).pop().top().s == Diamond);
        REQUIRE(board1.get_foundation(0).pop().top().r == ACE);
    }

    SECTION("get_foundation exception case"){
        REQUIRE_THROWS_AS(board1.get_foundation(10),std::out_of_range);
    }

    SECTION("get_deck empty deck"){
        for(unsigned int i = 0; i<64; i++){
            board1.deck_mv();
        }
        REQUIRE(board1.get_deck().size()==0);
    }

    SECTION("get_deck normal case"){
        unsigned int suit = 3;
        unsigned int rank = 13;
        for(unsigned int i = 0; i < 7; i++){ //for every rank from king to 6
            for(unsigned int i = 0; i < 4; i++){ //for every suit
                REQUIRE(board1.get_deck().top().s == suit);
                REQUIRE(board1.get_deck().top().r == rank);
                suit--;
                board1.deck_mv(); //removes two cards because there are two of the same type of cards
                board1.deck_mv();
            }
            suit = 3;
            rank--;
        }
    }

    SECTION("get_waste empty case"){
        REQUIRE(board1.get_waste().size()==0);
    }

    SECTION("get_waste normal case"){
        board1.deck_mv();
        REQUIRE(board1.get_waste().top().s == Spade);
        REQUIRE(board1.get_waste().top().r == KING);
    }

    SECTION("valid_mv_exists no valid move win state"){
        //tests if theres a valid move if every deck other than foundation is empty
        REQUIRE(!winBoard.valid_mv_exists());
    }

    SECTION("valid_mv_exists no valid move"){
        REQUIRE(!noMove.valid_mv_exists());
    }

    SECTION("valid_mv_exists regular cases"){
        for(unsigned int i = 0; i < 64; i++){
            REQUIRE(board1.valid_mv_exists()); //checks that a valid move exists as long as deck is not empty
            board1.deck_mv();
        }
        REQUIRE(board1.valid_mv_exists()); //checks that valid move exists even when deck is empty
    }

    SECTION("is_win_state true"){
        REQUIRE(winBoard.is_win_state());
    }

    SECTION("is_win_state false"){
        REQUIRE(!board1.is_win_state());
    }

    SECTION("BoardT constructor normal case"){
        //checks that gameboard constructor works as intended
        BoardT testBoard(d);
        REQUIRE(testBoard.get_deck().size() == 64);
        REQUIRE(testBoard.get_tab(0).size() == 4);
        REQUIRE(testBoard.get_tab(0).top().s == Diamond);
        REQUIRE(testBoard.get_tab(0).top().r == 2);
        REQUIRE(testBoard.get_tab(9).top().s == Spade);
        REQUIRE(testBoard.get_tab(9).top().r == JACK);
        REQUIRE(testBoard.get_waste().size() == 0);
        testBoard.deck_mv();
        REQUIRE(testBoard.get_waste().top().s == Diamond);
        REQUIRE(testBoard.get_waste().top().r == ACE);
    }

    SECTION("BoardT constructor exception case"){
        d[3] = CardT{Spade,ACE}; //vector that game board that cant be constructed from
        //checks that gameboard constructor cant be made because more than two of one type of card exists
        REQUIRE_THROWS_AS(BoardT(d), std::invalid_argument);
    }

    SECTION("BoardT constructor exeptio case 2"){
        //checks that gameboard can't be made because less than two of one type of card exists (two decks dont exist)
        d[3] = CardT{Diamond, 2};
        d.pop_back();
        REQUIRE_THROWS_AS(BoardT(d), std::invalid_argument);
    }
}

