#include <gtest/gtest.h>
#include "BankAccount.cpp"
// #include "square.cpp"

// TEST(SquareRootTest, Positive) {
//     ASSERT_EQ(65, sqrt_d(4225.0));
//     ASSERT_EQ(61.75, sqrt_d(3813.0625));
//     ASSERT_EQ(4, sqrt_d(16.0));
//     ASSERT_EQ(0.5, sqrt_d(0.25));
//     ASSERT_EQ(0, sqrt_d(0));
// }


// TEST(SquareRootTest, Negative) {
//     ASSERT_EQ(-1.0, sqrt_d(-4225.0));
//     ASSERT_EQ(-1.0, sqrt_d(-0.51));
// }

struct BankAccountTest : testing::Test {
    BankAccount* account = nullptr;

    BankAccountTest() {
        account = new BankAccount;
    }

    ~BankAccountTest() {
        delete account;
    }
};

struct account_state {
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;

    friend std::ostream& operator<<(std::ostream& os, const account_state& obj) {
        return os <<
        "initial_balance: " << obj.initial_balance <<
        " withdraw_amount: " << obj.withdraw_amount << 
        " final_balance: " << obj.final_balance <<
        " success: " << obj.success;
    }
};

struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state> {
    WithdrawAccountTest() {
        account->value = GetParam().initial_balance;
    }
};

TEST_P(WithdrawAccountTest, FinalBalance) {
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->value);
    EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest,
    testing::Values(
    account_state{100, 50, 50, true},
    account_state{0, 10, 0, false},
    account_state{25, 25, 0, true},
    account_state{7, 8, 7, false}
));

TEST_F(BankAccountTest, Empty) {
    EXPECT_EQ(0, account->value);
}

TEST_F(BankAccountTest, CanDeposit) {
    account->deposit(5);
    EXPECT_EQ(5, account->value);
};


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}