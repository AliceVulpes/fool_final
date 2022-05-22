// Дурак проект.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <string>
#include <ctime>
#include<conio.h>
using namespace std;



enum Suit { Heart = 3, Diamonds, Clubs, Spades };
enum Rank { Six = 6, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
//структура карты
struct Card {
    char Suit;
    int Rank;
};

//структура игрока
struct Player {
    string name;
    int score = 5000;
    Card* array;
};
//структура противника
struct Enemy {
    string name;
    int score = 5000;
    Card* array;
};

//заполнение колоды
void deck_init(Card*& deck) {
    for (int i = 0, k = 6; i < 9; i++, k++) {
        deck[i].Suit = Heart;
        deck[i].Rank = k;
    }
    for (int i = 9, k = 6; i < 18; i++, k++) {
        deck[i].Suit = Diamonds;
        deck[i].Rank = k;
    }
    for (int i = 18, k = 6; i < 27; i++, k++) {
        deck[i].Suit = Clubs;
        deck[i].Rank = k;
    }
    for (int i = 27, k = 6; i < 36; i++, k++) {
        deck[i].Suit = Spades;
        deck[i].Rank = k;
    }
}


//вывод колоды
void showDeck(Card*& deck) {
    int size = _msize(deck) / sizeof(deck[0]);
    for (int i = 0; i < size; i++) {

        

        if (deck[i].Rank == 11) cout << "[J]" << " of " << deck[i].Suit << endl;
        else if (deck[i].Rank == 12) cout << "[Q]" << " of " << deck[i].Suit << endl;
        else if (deck[i].Rank == 13) cout << "[K]" << " of " << deck[i].Suit << endl;
        else if (deck[i].Rank == 14) cout << "[A]" << " of " << deck[i].Suit << endl;
        else cout << "[" << deck[i].Rank << "]" << " of " << deck[i].Suit << endl;

        

    }
}


//вывод буквенного значения карты
void show_pic(Card*& hand1,int i) {
    
    if (hand1[i].Rank == 11) cout  << "[ J" << " of " << hand1[i].Suit <<" ] "<<endl;
    else if (hand1[i].Rank == 12) cout <<  "[ Q" << " of " << hand1[i].Suit<<" ] " << endl;
    else if (hand1[i].Rank == 13) cout <<  "[ K" << " of " << hand1[i].Suit <<" ] " << endl;
    else if (hand1[i].Rank == 14) cout <<  "[ A" << " of " << hand1[i].Suit <<" ] " << endl;
    else cout  <<"[ " << hand1[i].Rank << " of " << hand1[i].Suit<<" ] " << endl;
}


//перемешка колоды
void shuffleDeck(Card*& deck) {
    for (int i = 0; i < 36; i++) {
        swap(deck[i], deck[rand() % 36]);
    }
}


// первая раздача карт
void takeCard(Card*& deck, Card*& hand1, Card*& hand2) {

    for (int i = 0, k = 0; i < 6; i++) {
        hand1[i].Rank = deck[i].Rank;
        hand1[i].Suit = deck[i].Suit;
    }
    for (int i = 0, k = 0; i < 6; i++) {
        hand2[i].Rank = deck[i + 6].Rank;
        hand2[i].Suit = deck[i + 6].Suit;
    }

}

//удаление карт из колоды после первой раздачи
void delFromDeck(Card*& deck) {
    int size = _msize(deck) / sizeof(deck[0]);
    int size2 = size - 12;
    Card* buf = new Card[size2];

    for (int i = 0,k=12; i < size2,k<size; i++,k++) {
        buf[i] = deck[k];
        
    }

    delete[]deck;
    

    deck = buf;
}


//вывод рук
void showHand(Card*& hand1,Card*&hand2) {
    int size = _msize(hand1) / sizeof(hand1[0]);
   int size2 = _msize(hand2) / sizeof(hand2[0]);
    cout << endl;
    cout << "[----My hand----] " << endl;

    for (int i = 0; i < size; i++) {
        
        cout << i + 1<<": ";
        show_pic(hand1, i);
       
    }
    cout << endl;

    cout << "[----Enemy hand----] " << endl;
        for (int i = 0; i < size2; i++) {

            cout << i + 1 << ": ";
            show_pic(hand2, i);
        }
}


// удаление из руки и вкладывание в стол.
void delHandToTable(Card*& hand, Card*& table,int b) {
    int size = _msize(hand) / sizeof(hand[0]);
    int size2 = _msize(table) / sizeof(table[0]);

    Card* buf = new Card[size - 1];
    Card* buftable = new Card[size2 + 1];

    for (int j = 0; j < size2; j++) {
        buftable[j] = table[j];
    }
    for (int j = size2; j < size2 + 1; j++) {
        buftable[j] = hand[b];
    }

    
        for (int j = 0; j < b; j++) {
            if (b != 0) {
                buf[j] = hand[j];
            }
            
        }
        for (int j = b; j < size; j++) {
            
                buf[j] = hand[j+1];

            
        }
    

    delete[]table;
    table = buftable;

    delete[]hand;
    hand = buf;
}

//Вывод стола
void show_table(Card*& table) {
    int size = _msize(table) / sizeof(table[0]);
    if (size > 0) {
        for (int i = 0; i < size; i++) {

            cout << i + 1 << ":";
            show_pic(table, i);
        }
    }
    else cout << "[__][__][__][__][__][__]" << endl;
}

//если нечем отбиваться и забираешь карты
void TakeAll(Card*& hand, Card*& table) {
    int size = _msize(hand) / sizeof(hand[0]);
    int size2 = _msize(table) / sizeof(table[0]);
    
    Card* buf = new Card[size + size2];
    for (int i = 0; i < size; i++) {
        buf[i] = hand[i];
    }

    for (int i = size; i < (size+size2); i++) {
        buf[i] = table[i-size];
    }
    delete[]table;
    delete[]hand;
    hand = buf;
    size2 = 0;
    table = new Card[size2];
}

//козырь
void trump_suit(Card*& deck,char*trump) {
    int size = _msize(deck) / sizeof(deck[0]);
   
    *trump = deck[size-1].Suit;
    
}

void show_trump( char *trump) {
    cout << '\t'<<'\t'<<"["<< * trump <<"]" << endl;
}


//добор карт и удаление из колоды
void moreCards(Card*&deck,Card*&hand) {
   
    int size = _msize(hand) / sizeof(hand[0]);
    int decksize = _msize(deck) / sizeof(deck[0]);
        int a = size;//рука сейчас
            int b = 6-a;//6-рука. сколько надо взять
            int d = decksize;//колода

            if (a < 6&&d>0) {//если на руке меньше шести и колода не пустая
                if ( d >= 6) {//если колода больше или равно 6
                    int c = d - b;//размер новой колоды. 
                    Card* buf = new Card[6];
                    Card* buf2 = new Card[c];
                    for (int i = 0; i < a; i++) {
                        buf[i] = hand[i];
                    }
                    for (int i = a; i < 6; i++) {
                        buf[i] = deck[i - size];
                    }

                    for (int i = 0; i < (c); i++) {
                        buf2[i] = deck[b];
                        b++;
                    }
                    delete[]hand;
                    hand = buf;
                    delete[]deck;
                    deck = buf2;
                    
                }
                if (d < 6 && d != 0) {//если колода меньше 6 и там не ноль
                    if (d > b) {//если колода больше,чем надо взять
                        int c = d - b;//размер новой колоды. 
                        Card* buf = new Card[6];
                        Card* buf2 = new Card[c];
                        for (int i = 0; i < a; i++) {
                            buf[i] = hand[i];
                        }
                        for (int i = a; i < 6; i++) {
                            buf[i] = deck[i - a];
                        }

                        for (int i = 0; i < c; i++) {
                            buf2[i] = deck[b];
                            b++;
                        }
                        delete[]hand;
                        hand = buf;
                        delete[]deck;
                        deck = buf2;
                        
                    }
                    else  {//если взять надо больше,чем в колоде или столько же
                        Card* buf = new Card[a + b];
                        Card* buf2 = new Card[0];
                        for (int i = 0; i < a; i++) {
                            buf[i] = hand[i];
                        }
                        for (int i = a; i < (a+b); i++) {
                            buf[i] = deck[i - a];
                        }
                        
                        delete[]hand;
                        hand = buf;
                        delete[]deck;
                        deck = buf2;
                        
                    }

                }
                
            }
}



 //если мой ход первый
void my_turn(Card*&deck,Card*& hand1,Card*&hand2, Card*& table,int a,int b,int *close) {
    int size2 = _msize(table) / sizeof(table[0]);
     a=0;
    cout << "Select card:";
    cin >> a;
    cout << endl;
   
    if (a > 0) {
        b = a - 1;
        delHandToTable(hand1, table, b);
        
    }
    else {
        *close = 1;
        delete[]table;
        size2 = 0;
        table = new Card[size2];
        moreCards(deck, hand1);
        moreCards(deck, hand2);
    }
}


//если отбиваюсь
void my_answer(Card*& hand1, Card*& table,int*close) {

    int a = 0;
    int b = a - 1;
    cout << "Select card:";
    cin >> a;
    cout << endl;

    if (a > 0) {
        b = a - 1;
        delHandToTable(hand1, table, b);

    }

    else {
      TakeAll(hand1, table);
      *close = 1;
    }
}


//если ход противника
void enemy_turn(Card*& deck,Card*& hand1, Card*& hand2, Card*& table, char * trump,int*close) {
    int size = _msize(hand2) / sizeof(hand2[0]);
    int size2 = _msize(table) / sizeof(table[0]);
    if (size > 0) {
        int a = rand() % 1 + size;
        int b = 0;
        if (size2 == 0) {
            delHandToTable(hand2, table, a - 1);
        }
        else if (size2 <= 12) {

            for (int i = 0; i < size2; i++) {
                for (int j = 0; j < size; j++) {
                    if (hand2[j].Rank == table[i].Rank) {
                        delHandToTable(hand2, table, j);
                        b = 1;

                        break;
                    }

                }
                if (b == 1)break;
            }
            if (b == 0) {
                delete[]table;
                size2 = 0;
                table = new Card[size2];
                moreCards(deck, hand1);
                moreCards(deck, hand2);
                *close = 1;
            }
        }

    }
    else *close = 1;
    
}

//если противник отбивается
void enemy_answer(Card*&deck,Card*& hand2,  Card*& hand1 ,Card*& table,int r,char * trump) {
   

    int sizedeck = _msize(deck) / sizeof(deck[0]);
    int size = _msize(hand2) / sizeof(hand2[0]);
    int size2 = _msize(table) / sizeof(table[0]);
    
    int a = 0;

            //если на столе не козырь
            if (table[size2 - 1].Suit != *trump) {
              for (int j = 0; j <= size; j++) {
                  if (j != size) {
                     //если сьют равен сьюту стола
                      if (hand2[j].Suit == table[size2 - 1].Suit) {
                          //если ранк больше ранка руки
                          if (hand2[j].Rank > table[size2 - 1].Rank) {
                              delHandToTable(hand2, table, j);
                              break;
                          }
                      }
                  }
                  if(j==size) {
                       for (int i = 0; i <= size; i++) {
                           if (i != size) {
                               if (hand2[i].Suit == *trump) {

                                   delHandToTable(hand2, table, i);

                                   break;

                               }
                           }
                           if (i == size) {
                               TakeAll(hand2, table);
                               r = 0;
                               moreCards(deck, hand1);
                           }
                       }
                  }
                
              }
            }
            //если на столе козырь
             if (table[size2 - 1].Suit == *trump && a==0) {
                 
                for (int k = 0; k <= size; k++) {
                    //если на руке козырь
                    if (k != size) {
                        if (hand2[k].Suit == *trump) {
                            //если козырь старше
                            if (k != size) {
                                if (hand2[k].Rank > table[size2 - 1].Rank) {
                                    delHandToTable(hand2, table, k);
                                    a = 1;
                                    break;
                                }
                            }
                          
                        }
                    }
                    else {
                        TakeAll(hand2, table);
                        r = 0;
                        moreCards(deck, hand1);
                    }
                } 
             }
           
  }  
  

//проверка на выигрыш/проигрыш
void WinOrNot(Card*& deck,Card*&hand1,Card*&hand2,int*close) {
    int sizedeck = _msize(deck) / sizeof(deck[0]);
    int size = _msize(hand1) / sizeof(hand1[0]);
    int size2 = _msize(hand2) / sizeof(hand2[0]);
    if (sizedeck == 0 && size == 0) {
        cout << "[-----You Win!-----]" << endl;
        *close = 1;
    }
    if (sizedeck == 0 && size2 == 0 ) {
        cout << "[-----You Lose!-----]" << endl;
        *close = 1;
    }
}


int main() {
    srand(time(NULL));
    char trump =0;
    int a=0; //номер карты для ввода
    int b =0; //индекс карт
    int close=0;
    

    Card* deck = new Card[36];
    Card* my_hand = new Card[6];
    Card* enemy_hand = new Card[6];
    Card* table = new Card[0];
    
    deck_init(deck);
    shuffleDeck(deck);
    trump_suit(deck, &trump);
    takeCard(deck, my_hand, enemy_hand);
    delFromDeck(deck);
    
   //начало игры
    bool game=true;
        bool flag=true;

        while (game) {
            while (flag) {
                WinOrNot(deck, my_hand, enemy_hand, &close);
                if (close == 0) {
                    for (int i = 1; i <= 6; i++) {
                        /*showDeck(deck);*/
                        cout << '\t' << "[----Trump Card----]" << endl;
                        show_trump(&trump);
                        showHand(my_hand, enemy_hand);
                        cout << endl;
                        cout << "[----Table----]" << endl;
                        show_table(table);
                        cout << endl;
                        if (i <= 6) {
                            my_turn(deck, my_hand, enemy_hand, table, a, b, &close);

                            system("cls");
                        }
                        if (close == 0 && i <= 6) {

                            enemy_answer(deck, enemy_hand, my_hand, table, i, &trump);
                            cout << endl;
                            if (i > 0) {
                                cout << '\t' << "[----Trump Card----]" << endl;                               
                                show_trump(&trump);
                                showHand(my_hand, enemy_hand);
                                cout << endl;
                                cout << "[----Table----]" << endl;
                                show_table(table);
                                cout << endl;

                            }
                            else {
                                i = 1;
                                moreCards(deck, my_hand);
                                cout << endl;
                            }


                            system("cls");
                            
                        }
                        else {
                            moreCards(deck, my_hand);
                            moreCards(deck, enemy_hand);
                            flag = false;
                            close = 0;                         
                            break;
                        }
                    }
                }
                else {
                    game = false;
                    break;
                }
            }
            while (!flag) {
                WinOrNot(deck, my_hand, enemy_hand, &close);
                if(close==0){
                    for (int i = 1; i <= 6; i++) {


                        if (i < 6) {                         
                            enemy_turn(deck, my_hand, enemy_hand, table, &trump, &close);
                            if (close == 0) {
                                /*showDeck(deck);*/
                                cout << '\t' << "[----Trump Card----]" << endl;
                               
                                show_trump(&trump);
                                showHand(my_hand, enemy_hand);
                                cout << endl;
                                cout << "[----Table----]" << endl;                              
                                show_table(table);
                                cout << endl;                            
                                my_answer(my_hand, table, &close);
                                if (close == 0) {
                                    cout << endl;
                                    cout << '\t' << "[----Trump Card----]" << endl;                                 
                                    show_trump(&trump);
                                    showHand(my_hand, enemy_hand);
                                    cout << endl;
                                    cout << "[----Table----]" << endl;
                                    show_table(table);
                                    cout << endl;
                                    system("cls");
                                }
                                else {
                                    moreCards(deck, my_hand);
                                    moreCards(deck, enemy_hand);
                                    close = 0;
                                    system("cls");                                 
                                    break;
                                }
                            }
                            else {
                                moreCards(deck, my_hand);
                                moreCards(deck, enemy_hand);
                                flag = true;
                                close = 0;
                                break;
                            }
                        }
                    }
                }
                else {
                    game = false;
                    break;
                }
            }
        }

}
