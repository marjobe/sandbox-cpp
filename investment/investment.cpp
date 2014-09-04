#include <iostream>
#include <cassert>
#include <array>
#include <list>

const unsigned int MONTHS_NUMBER = 12u;

typedef float Rate;
typedef float Money;
typedef std::array<Rate, MONTHS_NUMBER> RatesTable;

/*
Rate getRate(const RatesTable& table, unsigned int monthsInvestment)
{
    assert(monthsInvestment > 0u && monthsInvestment <= MONTHS_NUMBER);
    return table[monthsInvestment - 1u];
}
*/

/**
 * @brief Investment class.
 */
class Investment
{
public:

    /**
     * @brief Constructor.
     * @param[in] ratesTable The rates table to calculate the investment.
     * @param[in] moneyPerMonth The money per month destinates to do an investment.
     */
    Investment(const RatesTable& ratesTable, Money moneyPerMonth) :
        _ratesTable(ratesTable),
        _moneyPerMonth(moneyPerMonth)
    {}

    typedef unsigned int Action;
    typedef std::list<Action> Actions;

    void getBestInvestment(Actions& actions, Money& totalMoney)
    {
        MoneyMonth moneyMonth = {_moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth, _moneyPerMonth};
        getBestBacktracking(0u, moneyMonth, actions);
        totalMoney = moneyMonth[MONTHS_NUMBER - 1u];
    }

private:

    /** Table that has the money per month. */
    typedef std::array<Money, MONTHS_NUMBER> MoneyMonth;

    /***/
    void getBestBacktracking(unsigned int month, MoneyMonth& moneyMonth, Actions& actions)
    {
        if(month < MONTHS_NUMBER - 1u)
        {
            MoneyMonth theBestMoneyMonth;
            Actions theBestActions;
            for (unsigned int i = 0u; i < MONTHS_NUMBER - 1u - month; ++i)
            {
                MoneyMonth currentMoneyMonth = moneyMonth;
                Actions currentActions = actions;
                const unsigned int monthsInvestment(i + 1u);

                currentMoneyMonth[month + monthsInvestment] += currentMoneyMonth[month] * (1.f + _ratesTable[i] / 12.f / 100.f * monthsInvestment);
                currentActions.emplace_back(monthsInvestment);
                getBestBacktracking(month + 1u, currentMoneyMonth, currentActions);
                if (currentMoneyMonth[MONTHS_NUMBER - 1u] > theBestMoneyMonth[MONTHS_NUMBER - 1u])
                {
                    theBestMoneyMonth = currentMoneyMonth;
                    theBestActions = currentActions;
                }
            }
            moneyMonth = theBestMoneyMonth;
            actions = theBestActions;
        }
    }

    /** Data members. */
    RatesTable      _ratesTable;
    Money           _moneyPerMonth;
    
};



int main(int argc, char const *argv[])
{
    RatesTable hsbcTable = {20.f, 20.75f, 21.5f, 22.25f, 23.f, 23.75f, 23.75f, 23.75f, 23.75f, 23.75f, 23.75f, 24.5f};
    Investment investment(hsbcTable, 2000.f);
    Investment::Actions actions;
    Money earnMoney;
    investment.getBestInvestment(actions, earnMoney);

    std::cout << "You earn $ " << earnMoney << std::endl;

    unsigned int i(0u);
    for (Investment::Action action : actions)
    {
        std::cout << "Month " << i++ << ": deposit to " << action << " months." << std::endl;
    }

    return 0;
}