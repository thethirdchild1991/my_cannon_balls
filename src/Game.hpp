#ifndef GAME_HPP
#define GAME_HPP

enum GAME_STATE{
    VOID,
    IDLE,// menu show
    PLAYING,
    FINISHED    
};

class Game{

    private:
        Game() = default;
        ~Game() = default;
        Game( const Game & ) = delete;
        Game &operator=( const Game & ) = delete;
        class State;

    public:
        static Game &instance(){
            static Game instance;
            return instance;
        };

        void run(){};
        const State& state() const { return m_state->state(); }
        // void state( const GAME_STATE val ) { m_state = val; }

    private:
        // GAME_STATE m_state = GAME_STATE::IDLE;
        State* m_state;
        // class Idle;
        // class Playing;
        // class Finished;
        class State{
            public:
                virtual const GAME_STATE& state() const { return GAME_STATE::VOID; }
        };

        class Idle : public State{

        };

        class Playing : public State{

        };

        class Finished : public State{

        };        

};

// class Machine
// {
//   class State *current;
//   public:
//     Machine();
//     void setCurrent(State *s)
//     {
//         current = s;
//     }
//     void on();
//     void off();
// };
 
// class State
// {
//   public:
//     virtual void on(Machine *m)
//     {
//         cout << "   already ON\n";
//     }
//     virtual void off(Machine *m)
//     {
//         cout << "   already OFF\n";
//     }
// };
 
// void Machine::on()
// {
//   current->on(this);
// }
 
// void Machine::off()
// {
//   current->off(this);
// }
 
// class ON: public State
// {
//   public:
//     ON()
//     {
//         cout << "   ON-ctor ";
//     };
//     ~ON()
//     {
//         cout << "   dtor-ON\n";
//     };
//     void off(Machine *m);
// };
 
// class OFF: public State
// {
//   public:
//     OFF()
//     {
//         cout << "   OFF-ctor ";
//     };
//     ~OFF()
//     {
//         cout << "   dtor-OFF\n";
//     };
//     void on(Machine *m)
//     {
//         cout << "   going from OFF to ON";
//         m->setCurrent(new ON());
//         delete this;
//     }
// };
 
// void ON::off(Machine *m)
// {
//   cout << "   going from ON to OFF";
//   m->setCurrent(new OFF());
//   delete this;
// }
 
// Machine::Machine()
// {
//   current = new OFF();
//   cout << '\n';
// }
 
// int main()
// {
//   void(Machine:: *ptrs[])() = 
//   {
//     Machine::off, Machine::on
//   };
//   Machine fsm;
//   int num;
//   while (1)
//   {
//     cout << "Enter 0/1: ";
//     cin >> num;
//     (fsm. *ptrs[num])();
//   }
// }


#endif