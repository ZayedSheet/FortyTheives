/**
 * \file GameBoard.cpp
 * \author Zayed Sheet
 */
#include "../include/GameBoard.h"

BoardT::BoardT(SeqCardT deck){
    if(!two_decks(init_seq(10),init_seq(8),CardStackT(deck),CardStackT(SeqCardT()))){
        throw std::invalid_argument("boardT error");
    }
    std::vector<CardT>::const_iterator first = deck.begin();
    std::vector<CardT>::const_iterator last = deck.begin() + 40;
    std::vector<CardT> tab(first, last);
    T = tab_deck(tab);

    F = init_seq(8);

    std::vector<CardT>::const_iterator firstD = deck.begin() + 40;
    std::vector<CardT>::const_iterator lastD = deck.begin() + 104;
    std::vector<CardT> tabD(firstD, lastD);
    D = CardStackT(tabD);

    W = CardStackT(SeqCardT());
}

SeqCardStackT BoardT::tab_deck(SeqCardT subDeck){
    //Referenced from https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
    for(unsigned int i= 0; i<10; i++){
        std::vector<CardT>::const_iterator first = subDeck.begin() + 4*i;
        std::vector<CardT>::const_iterator last = subDeck.begin() + (4*(i+1));
        std::vector<CardT> currentTab(first, last);
        T.push_back(CardStackT(currentTab));
    }
    return T;
}

SeqCardStackT BoardT::init_seq(unsigned int n) {
    SeqCardStackT seqStack;
    for(unsigned int i = 0; i < n; i++){
        seqStack.push_back(CardStackT(SeqCardT()));
    }
    return seqStack;
}

bool BoardT::two_decks(SeqCardStackT t, SeqCardStackT f, CardStackT d, CardStackT w) {
    for (RankT rank = ACE; rank <= KING; rank++){
        for(unsigned int st = 0; st < 4; st++){
            auto suit = static_cast<SuitT>(st);
            auto func = [suit,rank](CardT c){return c.s == suit && c.r == rank;};
            if (cnt_cards(t,f,d,w,func) != 2) return false;
        }
    }
    return true;
}

unsigned int BoardT::cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f) {
    SeqCardT x = s.toSeq();
    unsigned int count = 0;
    for(unsigned int i = 0; i < s.size(); i++){
        if (f(x.at(i))){
            count++;
        }
    }
    return count;
}

unsigned int BoardT::cnt_cards_seq(SeqCardStackT S, std::function<bool(CardT)> f) {
    unsigned int count = 0;
    for(unsigned int i = 0; i < S.size(); i++){
        count += cnt_cards_stack(S.at(i), f);
    }
    return count;
}

unsigned int BoardT::cnt_cards(SeqCardStackT tab, SeqCardStackT found, CardStackT deck, CardStackT waste, std::function<bool(CardT)> f) {
    unsigned int count = 0;
    count += cnt_cards_seq(tab, f);
    count += cnt_cards_seq(found, f);
    count += cnt_cards_stack(deck, f);
    count += cnt_cards_stack(waste, f);
    return count;
}

bool BoardT::is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1) {
    if(c == Tableau){
        if(!is_valid_pos(Tableau, n0) && !is_valid_pos(Tableau, n1)){
            throw std::out_of_range("tab mv error");
        }
        return valid_tab_tab(n0, n1);
    }
    if(c == Foundation){
        if(!is_valid_pos(Tableau, n0) && !is_valid_pos(Foundation, n1)){
            throw std::out_of_range("tab mv error");
        }
        return valid_tab_foundation(n0,n1);
    }
    return false;
}

bool BoardT::tab_placeable(CardT c, CardT d) {
    return ((c.s == d.s) && (c.r == d.r - 1));
}

bool BoardT::foundation_placeable(CardT c, CardT d) {
    return ((c.s == d.s) && (c.r == d.r + 1));
}

bool BoardT::valid_tab_tab(unsigned int n0, unsigned int n1) {
    if(T.at(n0).size() > 0){
        if(T.at(n1).size() > 0){
            return tab_placeable(T.at(n0).top(), T.at(n1).top());
        }
        else{
            return true;
        }
    }
    else{
        return false;
    }
}

bool BoardT::valid_tab_foundation(unsigned int n0, unsigned int n1) {
    if(T.at(n0).size() > 0){
        if(F.at(n1).size() > 0){
            return foundation_placeable(T.at(n0).top(), F.at(n1).top());
        }
        else{
            return (T.at(n0).top().r == ACE);
        }
    }
    else{
        return false;
    }
}

bool BoardT::is_valid_waste_mv(CategoryT c, unsigned int n) {
    if (W.size() == 0){
        throw std::invalid_argument("waste error size");
    }
    if(c == Tableau){
        if(!is_valid_pos(Tableau,n)){
            throw std::out_of_range("waste error tab");
        }
        return valid_waste_tab(n);
    }
    if(c == Foundation){
        if(!is_valid_pos(Foundation,n)){
            throw std::out_of_range("waste error found");
        }
        return valid_waste_foundation(n);
    }
    return false;
}

bool BoardT::is_valid_pos(CategoryT c, unsigned int n) {
    if (c == Tableau){
        return (n >= 0 && n <= 9);
    }
    else if (c == Foundation){
        return (n >= 0 && n <= 7);
    }
    else return true;
}

bool BoardT::valid_waste_tab(unsigned int n) {
    if (T.at(n).size()>0){
        return tab_placeable(W.top(),T.at(n).top());
    }
    else return true;
}

bool BoardT::valid_waste_foundation(unsigned int n) {
    if (F.at(n).size() > 0){
        return foundation_placeable(W.top(),F.at(n).top());
    }
    else{
        return W.top().r == ACE;
    }
}

bool BoardT::is_valid_deck_mv() {
    return D.size() > 0;
}

void BoardT::tab_mv(CategoryT c, unsigned int n0, unsigned int n1) {
    if(!is_valid_tab_mv(c, n0, n1)){
        throw std::invalid_argument{"tab mv error"};
    }
    if(c == Tableau){
        T.at(n1) = T.at(n1).push(T.at(n0).top());
        T.at(n0) = T.at(n0).pop();
    }
    if(c == Foundation){
        F.at(n1) = F.at(n1).push(T.at(n0).top());
        T.at(n0) = T.at(n0).pop();
    }
}

void BoardT::waste_mv(CategoryT c, unsigned int n) {
    if(!is_valid_waste_mv(c, n)){
        throw std::invalid_argument{"waste mv error"};
    }
    if(c == Tableau){
        T.at(n) = T.at(n).push(W.top());
        W = W.pop();
    }
    if(c == Foundation){
       F.at(n) = F.at(n).push(W.top());
       W = W.pop();
    }
}

void BoardT::deck_mv() {
    if(!is_valid_deck_mv()){
        throw std::invalid_argument("deck mv error");
    }
    W = W.push(D.top());
    D = D.pop();
}

CardStackT BoardT::get_tab(unsigned int i) {
    if(!is_valid_pos(Tableau, i)){
        throw std::out_of_range("get tab error");
    }
    return T.at(i);
}

CardStackT BoardT::get_foundation(unsigned int i) {
    if(!is_valid_pos(Foundation,i)){
        throw std::out_of_range("get foundation error");
    }
    return F.at(i);
}

CardStackT BoardT::get_deck() {
    return D;
}

CardStackT BoardT::get_waste() {
    return W;
}

bool BoardT::valid_mv_exists() {
    if (is_valid_deck_mv()) return true;

    for(unsigned int i = 0; i < T.size(); i++){
        for(unsigned int j = 0; j < T.size(); j++){
            if(is_valid_tab_mv(Tableau,i,j)) return true;
        }
    }
    for(unsigned int i = 0; i < T.size(); i++){
        for(unsigned int j = 0; j < F.size(); j++){
            if(is_valid_tab_mv(Foundation,i,j)) return true;
        }
    }

    for(unsigned int i = 0; i < T.size(); i++){
        if((!W.size() == 0) && is_valid_waste_mv(Tableau,i)) return true;
    }
    for(unsigned int i = 0; i < F.size(); i++){
        if((!W.size() == 0) && is_valid_waste_mv(Foundation,i)) return true;
    }

    return false;
}

bool BoardT::is_win_state() {
    for(unsigned int i = 0; i<8; i++){
        if (!((F.at(i).size() > 0) && F.at(i).top().r == KING)) return false;
    }
    return true;
}




