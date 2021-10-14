struct BankAccount {
    int value = 0;

    BankAccount() {};
    explicit BankAccount(const int v): value(v) {};

    inline void deposit(int amount) { value = value + amount; };
    inline bool withdraw(int amount) {
        if (amount > value)
            return false;
        else {
            value = value - amount;
            return true;
        }
    }
};